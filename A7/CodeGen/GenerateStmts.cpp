#include "CodeGen.hpp"
#include "Instruction.hpp"

void CodeGen::generateCode(AST::Stmt::Stmt* stmt)
{
    switch (stmt->stmtType()) {
    case AST::StmtType::Compound: {
        generateCode(stmt->cast<AST::Stmt::Compound*>());
        break;
    }
    case AST::StmtType::For: {
        generateCode(stmt->cast<AST::Stmt::For*>());
        break;
    }
    case AST::StmtType::Return: {
        generateCode(stmt->cast<AST::Stmt::Return*>());
        break;
    }
    default: {
        break;
    }
    }
}

void CodeGen::generateCode(AST::Stmt::Compound* stmt)
{
    m_instructions.push_back(Instruction::Comment("COMPOUND"));
    toffPush(stmt->memInfo().getSize());
    if (stmt->localdecls()) {
        m_instructions.push_back(Instruction::Comment("LOCAL DECLARATIONS"));
        for (auto* decl = stmt->localdecls()->cast<AST::Node*>();
             decl != nullptr;
             decl = decl->sibling()) {
            generateCode(decl);
        }
        m_instructions.push_back(
            Instruction::Comment("END LOCAL DECLARATIONS"));
    }
    if (stmt->stmtlist()) {
        m_instructions.push_back(Instruction::Comment("COMPOUND BODY"));
        for (auto* stmt_child = stmt->stmtlist()->cast<AST::Node*>();
             stmt_child != nullptr;
             stmt_child = stmt_child->sibling()) {
            generateCode(stmt_child);
        }
        m_instructions.push_back(Instruction::Comment("END COMPOUND BODY"));
    }
    toffPop();
    m_instructions.push_back(Instruction::Comment("END COMPOUND"));
}

void CodeGen::generateCode(AST::Stmt::For* stmt)
{
    toffPush(stmt->memInfo().getSize());
    toffPop();
}

void CodeGen::generateCode(AST::Stmt::Return* stmt)
{
    //  40:    LDC  3,93(6)	Load integer constant
    //  41:    LDA  2,0(3)	Copy result to return register

    //  42:     LD  3,-1(1)	Load return address
    //  43:     LD  1,0(1)	Adjust fp
    //  44:    JMP  7,0(3)	Return

    if (stmt->exp()) {}

    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust FP"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
}