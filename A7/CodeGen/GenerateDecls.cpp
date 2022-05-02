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
    m_instructions.push_back(Instruction::Comment());
    enterComment("FUNCTION " + func->id());

    m_functionLocs.insert({func->id(), Instruction::whereAmI()});
    Instruction::indentComments();
    toffPush(func->memInfo().getSize());
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));

    if (func->compoundStmt()) {
        auto* compoundStmt = func->compoundStmt();
        generateCode(compoundStmt);
    }

    generateStandardFunctionClosing();
    toffPop();
    exitComment("FUNCTION " + func->id());
}

void CodeGen::generateCode(AST::Decl::Var* var)
{
    enterComment("VAR DECL " + var->id());

    int PTR = (var->memInfo().isInGlobalMemory()) ? GP : FP;
    if (var->isArray()) {
        m_instructions.push_back(
            Instruction::LDC(AC0,
                             std::to_string(var->memInfo().getSize() - 1),
                             "Load size of array " + var->id()));
        m_instructions.push_back(
            Instruction::ST(AC0,
                            var->memInfo().getLocation() + 1,
                            PTR,
                            "Store size of " + var->id()));
    }

    if (var->isInitialized()) {
        generateCode(var->initValue());
        if (!var->initValue()->isArray()) {
            m_instructions.push_back(
                Instruction::ST(AC0,
                                var->memInfo().getLocation(),
                                PTR,
                                "Store variable " + var->id()));
        }
    }

    exitComment("VAR DECL " + var->id());
}