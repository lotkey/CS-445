#include "CodeGen.hpp"
#include "Instruction.hpp"

#include <string>

void CodeGen::generateCode(AST::Exp::Exp* exp)
{
    switch (exp->expType()) {
    case AST::ExpType::Const: {
        generateCode(exp->cast<AST::Exp::Const*>());
        break;
    }
    case AST::ExpType::Call: {
        generateCode(exp->cast<AST::Exp::Call*>());
    }
    default: {
        break;
    }
    }
}

void CodeGen::generateCode(AST::Exp::Const* constant)
{
    if (constant->isArray()) {
        m_instructions.push_back(Instruction::LIT(
            constant->getTmString(), "Load string into data memory"));
    } else {
        std::string comment = "Load constant";
        if (constant->getTmString() == "666") { comment += " ⸸"; }
        m_instructions.push_back(
            Instruction::LDC(AC0, constant->getTmString(), comment));
    }
}

void CodeGen::generateCode(AST::Exp::Call* call)
{
    // * CALL output
    //  40:     ST  1,-2(1)	Store fp in ghost frame for output
    // * TOFF dec: -3
    // * TOFF dec: -4
    // * Param 1
    //  41:    LDC  3,987(6)	Load integer constant
    //  42:     ST  3,-4(1)	Push parameter
    // * TOFF dec: -5
    // * Param end output
    //  43:    LDA  1,-2(1)	Ghost frame becomes new active frame
    //  44:    LDA  3,1(7)	Return address in ac
    //  45:    JMP  7,-40(7)	CALL output
    //  46:    LDA  3,0(2)	Save the result in ac
    // * Call end output
    auto* func = call->getFunc();

    m_instructions.push_back(Instruction::Comment("CALL " + call->id()));
    m_instructions.push_back(
        Instruction::ST(FP,
                        func->memInfo().getSize(),
                        FP,
                        "Store FP in ghost frame for output"));
    m_instructions.push_back(Instruction::Comment("CALL END " + call->id()));
}