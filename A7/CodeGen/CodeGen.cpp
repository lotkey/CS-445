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
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(
        Instruction::Comment("START IO library functions"));
    std::vector<Instruction> libraryInstructions = ioTmCode();
    m_instructions.insert(m_instructions.end(),
                          libraryInstructions.begin(),
                          libraryInstructions.end());
    m_instructions.push_back(Instruction::Comment("END IO library functions"));

    linearalize();

    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(
        Instruction::Comment("START User-declared functions"));
    for (auto* func : m_fundecls) {
        auto* decl = func->cast<AST::Decl::Func*>();
        generateCode(decl);
    }
    generateCode(m_main->cast<AST::Decl::Func*>());
    m_instructions.push_back(
        Instruction::Comment("END User-declared functions"));

    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(Instruction::Comment("INIT GLOBALS AND STATICS"));

    for (auto it = m_globaldecls.rbegin(); it != m_globaldecls.rend(); it++) {
        auto* var = *it;
        auto* decl = var->cast<AST::Decl::Var*>();
        generateCode(var);
    }
    m_instructions.push_back(Instruction::Comment("END GLOBALS AND STATICS"));
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

std::vector<Instruction> CodeGen::ioTmCode()
{
    Instruction::skip(1);
    std::vector<Instruction> instructions;
    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION input"));
    instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::IN(AC0, "Grab int input"));
    instructions.push_back(Instruction::LD(AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION input"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION inputb"));
    instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::INB(AC0, "Grab bool input"));
    instructions.push_back(Instruction::LD(AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION inputb"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION inputc"));
    instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::INC(AC0, "Grab char input"));
    instructions.push_back(Instruction::LD(AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION inputc"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION output"));
    instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::LD(AC0, -2, FP, "Load parameter"));
    instructions.push_back(Instruction::OUT(AC0, "Output integer"));
    instructions.push_back(Instruction::LD(AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION output"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION outputb"));
    instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::LD(AC0, -2, FP, "Load parameter"));
    instructions.push_back(Instruction::OUTB(AC0, "Output bool"));
    instructions.push_back(Instruction::LD(AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION outputb"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION outputc"));
    instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::LD(AC0, -2, FP, "Load parameter"));
    instructions.push_back(Instruction::OUTC(AC0, "Output char"));
    instructions.push_back(Instruction::LD(AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION outputc"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION outputnl"));
    instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::OUTNL("Output integer"));
    instructions.push_back(Instruction::LD(AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION output"));

    return instructions;
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