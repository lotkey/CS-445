#include "CodeGen.hpp"
#include "Instruction.hpp"

#include <fstream>
#include <map>
#include <string>
#include <vector>

const std::string CodeGen::s_ioTmCodePath = "./CodeGen/ioTmCode.tm";
std::map<std::string, int> CodeGen::s_labelCounts;

std::string CodeGen::make(const std::string& label)
{
    s_labelCounts.insert({label, 0});
    std::string numbered_label =
        label + std::to_string(s_labelCounts.at(label));
    s_labelCounts[label]++;
    return numbered_label;
}

CodeGen::CodeGen() : m_ast(nullptr) {}

CodeGen::CodeGen(AST::Node* ast) : m_ast(ast) {}

void CodeGen::generate(const std::string& filename)
{
    generateCode();
    std::ofstream outfile(filename);

    for (const auto& instruction : m_instructions) {
        outfile << instruction.toString();
        outfile << "\n";
    }
    outfile.close();
}

void CodeGen::generateCode()
{
    generateIoCode();
    m_instructions.push_back(Instruction::Comment(""));
    linearalize();

    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(
        Instruction::Comment("START User-declared functions"));

    for (int i = 0; i < m_fundecls.size(); i++) {
        auto* func = m_fundecls[i]->cast<AST::Decl::Func*>();
        generateCode(func);
        m_instructions.push_back(Instruction::Comment(""));
    }
    generateCode(m_main->cast<AST::Decl::Func*>());
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(
        Instruction::Comment("END User-declared functions"));
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(Instruction::Comment(""));
    generatePrologCode();
}

void CodeGen::generateCode(AST::Node* node)
{
    switch (node->nodeType()) {
    case AST::NodeType::Decl: {
        generateCode(node->cast<AST::Decl::Decl*>());
        break;
    }
    case AST::NodeType::Stmt: {
        generateCode(node->cast<AST::Stmt::Stmt*>());
        break;
    }
    case AST::NodeType::Exp: {
        generateCode(node->cast<AST::Exp::Exp*>());
        break;
    }
    }
}

void CodeGen::generatePrologCode()
{
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(Instruction::Comment("START INIT"));
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(
        Instruction::LDA(FP, 0, GP, "Set first frame at end of globals"));
    m_instructions.push_back(
        Instruction::ST(FP, 0, FP, "Store old FP (point to self)"));
    m_instructions.push_back(Instruction::Comment("START GLOBALS AND STATICS"));

    for (auto it = m_globaldecls.rbegin(); it != m_globaldecls.rend(); it++) {
        auto* var = *it;
        auto* decl = var->cast<AST::Decl::Var*>();
        generateCode(var);
    }
    m_instructions.push_back(Instruction::Comment("END GLOBALS AND STATICS"));

    m_instructions.push_back(
        Instruction::LDA(AC0, 1, PC, "Return address in AC"));
    int location = Instruction::whereAmI();
    location -= m_functionLocs.at("main");
    location--;
    m_instructions.push_back(Instruction::JMP(PC, location, "Jump to main"));
    m_instructions.push_back(Instruction::HALT("DONE!"));
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(Instruction::Comment("END INIT"));
    m_instructions.push_back(Instruction::Comment());
}

void CodeGen::generateStandardFunctionClosing()
{
    m_instructions.push_back(Instruction::Comment(
        "Add standard closing in case there is no return statement"));
    m_instructions.push_back(
        Instruction::LDC(RT, "0", "Set return value to 0"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, GP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
}

void CodeGen::linearalize()
{
    if (!m_ast) { return; }

    m_fundecls = m_ast->getAllWhere([](AST::Node* node) {
        if (node->is(AST::DeclType::Func)) {
            auto* fundecl = node->cast<AST::Decl::Func*>();
            return fundecl->lineNumber() >= 0 && fundecl->id() != "main";
        } else {
            return false;
        }
    });
    m_globaldecls = m_ast->getAllWhere([](AST::Node* node) {
        if (!node->hasMemoryInfo()) { return false; }
        if (!node->memInfo().reftypeSet()) { return false; }

        auto reftype = node->memInfo().getReferenceType();

        if (node->is(AST::DeclType::Var)) {
            auto* var = node->cast<AST::Decl::Var*>();
            if (var->lineNumber() < 0) {
                return false;
            } else {
                bool correctReftype = reftype == AST::ReferenceType::Global ||
                                      reftype == AST::ReferenceType::Static;

                return correctReftype &&
                       (var->isInitialized() || var->isArray());
            }
        } else {
            return false;
        }
    });
    m_main = m_ast->getFirstWhere([](AST::Node* node) {
        if (node->is(AST::DeclType::Func)) {
            auto* decl = node->cast<AST::Decl::Func*>();
            return decl->id() == "main";
        } else {
            return false;
        }
    });
}