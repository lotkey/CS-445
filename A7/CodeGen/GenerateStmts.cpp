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
    case AST::StmtType::While: {
        generateCode(stmt->cast<AST::Stmt::While*>());
        break;
    }
    case AST::StmtType::Break: {
        generateCode(stmt->cast<AST::Stmt::Break*>());
        break;
    }
    case AST::StmtType::Select: {
        generateCode(stmt->cast<AST::Stmt::Select*>());
        break;
    }
    default: {
        break;
    }
    }
}

void CodeGen::generateCode(AST::Stmt::Compound* stmt)
{
    enterComment("COMPOUND");

    toffPush(stmt->memInfo().getSize());
    if (stmt->localdecls()) {
        m_instructions.push_back(Instruction::Comment("LOCAL DECLARATIONS"));
        Instruction::indentComments();

        for (auto* decl = stmt->localdecls()->cast<AST::Node*>();
             decl != nullptr;
             decl = decl->sibling()) {
            generateCode(decl);
        }

        Instruction::unindentComments();
        m_instructions.push_back(
            Instruction::Comment("END LOCAL DECLARATIONS"));
    }
    if (stmt->stmtlist()) {
        m_instructions.push_back(Instruction::Comment("COMPOUND BODY"));
        Instruction::indentComments();

        for (auto* stmt_child = stmt->stmtlist()->cast<AST::Node*>();
             stmt_child != nullptr;
             stmt_child = stmt_child->sibling()) {
            generateCode(stmt_child);
        }

        Instruction::unindentComments();
        m_instructions.push_back(Instruction::Comment("END COMPOUND BODY"));
    }
    toffPop();

    exitComment("COMPOUND");
}

void CodeGen::generateCode(AST::Stmt::For* stmt)
{
    enterComment("FOR");

    auto* from = stmt->range()->from();
    auto* to = stmt->range()->to();

    // Pre-loop init
    generateCode(from, AC0);
    m_instructions.push_back(
        Instruction::ST(AC0, -2, FP, "Save starting value in index variable"));
    generateCode(to, AC0);
    m_instructions.push_back(Instruction::ST(AC0, -3, FP, "Save stop value"));

    if (stmt->range()->by()) {
        generateCode(stmt->range()->by(), AC0);
    } else {
        m_instructions.push_back(
            Instruction::LDC(AC0, "1", "Default increment by 1"));
    }
    m_instructions.push_back(Instruction::ST(AC0, -4, FP, "Save step value"));
    int loopStart = Instruction::whereAmI();
    m_instructions.push_back(Instruction::LD(AC1, -2, FP, "Loop index"));
    m_instructions.push_back(Instruction::LD(AC2, -3, FP, "Stop value"));
    m_instructions.push_back(Instruction::LD(AC0, -4, FP, "Step value"));
    m_instructions.push_back(Instruction::TLT(AC0, AC1, AC2, "Op <"));
    m_instructions.push_back(Instruction::JNZ(AC0, 1, PC, "Jump to loop body"));
    loopEndPush(Instruction::whereAmI());
    Instruction::skip(1);
    // End pre-loop init

    // Loop body
    toffPush(stmt->memInfo().getSize());
    generateCode(stmt->stmt());
    toffPop();

    // Bottom of loop
    m_instructions.push_back(
        Instruction::Comment("Bottom of loop increment and jump"));
    m_instructions.push_back(Instruction::LD(AC0, -2, FP, "Load index"));
    m_instructions.push_back(Instruction::LD(AC2, -4, FP, "Load step"));
    m_instructions.push_back(Instruction::ADD(AC0, AC0, AC2, "Increment"));
    m_instructions.push_back(
        Instruction::ST(AC0, -2, FP, "Store back to index"));
    int jumpLength = Instruction::whereAmI() - loopStart;
    jumpLength++;
    m_instructions.push_back(
        Instruction::JMP(-jumpLength, PC, "Go to beginning of loop"));
    int loopEnd = Instruction::whereAmI();

    jumpLength = loopEnd - loopEndBack();
    Instruction::skip(-jumpLength);
    m_instructions.push_back(
        Instruction::JMP(jumpLength - 1, PC, "Jump past loop [backpatch]"));
    Instruction::skip(jumpLength - 1);

    loopEndPop();
    exitComment("FOR");
}

void CodeGen::generateCode(AST::Stmt::Return* stmt)
{
    enterComment("RETURN");

    if (stmt->exp()) {
        generateCode(stmt->exp(), AC0);
        m_instructions.push_back(
            Instruction::LDA(RT, 0, AC0, "Copy result to return register"));
    }

    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust FP"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));

    exitComment("RETURN");
}

void CodeGen::generateCode(AST::Stmt::While* stmt)
{
    auto* condition = stmt->exp();
    auto* body = stmt->stmt();

    enterComment("WHILE");

    int loopstart = Instruction::whereAmI();
    generateCode(condition, AC0);
    m_instructions.push_back(
        Instruction::JNZ(AC0, 1, PC, "Jump to while part"));
    loopEndPush(Instruction::whereAmI());
    Instruction::skip(1);

    generateCode(body);

    int bodyend = Instruction::whereAmI();
    int jumplength = loopstart - bodyend;
    jumplength--;
    m_instructions.push_back(
        Instruction::JMP(jumplength, PC, "Go to beginning of loop"));

    int instructionAfterWhile = Instruction::whereAmI();
    jumplength = instructionAfterWhile - loopEndBack();
    Instruction::skip(-jumplength);
    m_instructions.push_back(
        Instruction::JMP(jumplength - 1, PC, "Jump past loop [backpatch]"));
    Instruction::skip(jumplength - 1);

    loopEndPop();
    exitComment("WHILE");
}

void CodeGen::generateCode(AST::Stmt::Break* stmt)
{
    int pos = Instruction::whereAmI();
    int loopend = loopEndBack();
    m_instructions.push_back(Instruction::Comment("BREAK"));
    m_instructions.push_back(
        Instruction::JMP((loopend - pos) - 1, PC, "Break"));
}

void CodeGen::generateCode(AST::Stmt::Select* stmt)
{
    enterComment("IF");

    generateCode(stmt->exp());
    int jumpLoc = Instruction::whereAmI();
    Instruction::skip(1);

    m_instructions.push_back(Instruction::Comment("THEN"));
    if (stmt->stmt1()) { generateCode(stmt->stmt1()->cast<AST::Node*>()); }
    m_instructions.push_back(Instruction::Comment("END THEN"));

    int thenLocation = Instruction::whereAmI();
    Instruction::skip(jumpLoc - thenLocation);

    int jmploc = (thenLocation - jumpLoc) - 1;
    if (stmt->stmt2()) { jmploc++; }

    m_instructions.push_back(Instruction::JZR(
        AC0, jmploc, PC, "Jump around the THEN if false [backpatch]"));
    Instruction::skip((thenLocation - jumpLoc) - 1);

    if (stmt->stmt2()) {
        int jmpLocation = Instruction::whereAmI();
        Instruction::skip(1);

        m_instructions.push_back(Instruction::Comment("ELSE"));
        generateCode(stmt->stmt2()->cast<AST::Node*>());
        m_instructions.push_back(Instruction::Comment("END ELSE"));

        int newLoc = Instruction::whereAmI();
        Instruction::newLoc(jmpLocation);
        m_instructions.push_back(
            Instruction::JMP((newLoc - jmpLocation) - 1,
                             PC,
                             "Jump around the ELSE [backpatch]"));
        Instruction::newLoc(newLoc);
    }

    exitComment("IF");
}