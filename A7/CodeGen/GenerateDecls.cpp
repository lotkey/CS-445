#include "CodeGen.hpp"
#include "Instruction.hpp"

void CodeGen::generateCode(AST::Decl::Decl* decl)
{
    switch (decl->declType()) {
    case AST::DeclType::Func: {
        generateCode(decl->cast<AST::Decl::Func*>());
        break;
    }
    case AST::DeclType::Parm: {
        break;
    }
    case AST::DeclType::Var: {
        generateCode(decl->cast<AST::Decl::Var*>());
        break;
    }
    }
}

void CodeGen::generateCode(AST::Decl::Func* func)
{
    m_functionLocs.insert({func->id(), Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(Instruction::Comment("FUNCTION " + func->id()));
    m_instructions.push_back(Instruction::Comment(
        "TOFF set: " + std::to_string(func->memInfo().getSize())));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));

    if (func->compoundStmt()) {
        auto* compoundStmt = func->compoundStmt();
        generateCode(compoundStmt);
    }

    generateStandardFunctionClosing();
    m_instructions.push_back(
        Instruction::Comment("END FUNCTION " + func->id()));
}

void CodeGen::generateCode(AST::Decl::Var* var)
{
    if (!var->hasMemoryInfo()) {
        throw std::runtime_error("Variable has no memory info!");
    }

    if (var->isArray()) {
        m_instructions.push_back(
            Instruction::LDC(AC0,
                             std::to_string(var->memInfo().getSize() - 1),
                             "Load size of array " + var->id()));
        m_instructions.push_back(
            Instruction::ST(AC0,
                            var->memInfo().getLocation() + 1,
                            GP,
                            "Store size of " + var->id()));
    }

    if (var->isInitialized()) {
        generateCode(var->initValue()->cast<AST::Exp::Const*>());
        if (!var->initValue()->isArray()) {
            m_instructions.push_back(
                Instruction::ST(AC0,
                                var->memInfo().getLocation(),
                                GP,
                                "Store variable " + var->id()));
        }
    }
}