#include "CodeGen.hpp"
#include "Instruction.hpp"

void CodeGen::generateCode(AST::Stmt::Stmt* stmt)
{
    switch (stmt->stmtType()) {
        case AST::StmtType::Compound: {
            generateCode(stmt->cast<AST::Stmt::Compound*>());
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
    m_instructions.push_back(Instruction::Comment(
        "TOFF set: " + std::to_string(stmt->memInfo().getSize())));
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
    m_instructions.push_back(Instruction::Comment("END COMPOUND"));
}