#include "CodeGen.hpp"
#include "Instruction.hpp"

void CodeGen::generateIoCode()
{
    Instruction::skip(1);
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(
        Instruction::Comment("START IO library functions"));
    m_instructions.push_back(Instruction::Comment());
    generateInput();
    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    generateOutput();
    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    generateInputb();
    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    generateOutputb();
    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    generateInputc();
    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    generateOutputc();
    m_instructions.push_back(Instruction::Comment(""));
    m_instructions.push_back(Instruction::Comment());
    generateOutnl();
    m_instructions.push_back(Instruction::Comment());
    m_instructions.push_back(Instruction::Comment("END IO library functions"));
    m_instructions.push_back(Instruction::Comment());
}

void CodeGen::generateInput()
{
    m_functionLocs.insert({"input", Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment("FUNCTION input"));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    m_instructions.push_back(Instruction::IN(RT, "Grab int input"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    m_instructions.push_back(Instruction::Comment("END FUNCTION input"));
}

void CodeGen::generateOutput()
{
    m_functionLocs.insert({"output", Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment("FUNCTION output"));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    m_instructions.push_back(Instruction::LD(AC0, -2, FP, "Load parameter"));
    m_instructions.push_back(Instruction::OUT(AC0, "Output integer"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    m_instructions.push_back(Instruction::Comment("END FUNCTION output"));
}

void CodeGen::generateInputb()
{
    m_functionLocs.insert({"inputb", Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment("FUNCTION inputb"));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    m_instructions.push_back(Instruction::INB(RT, "Grab bool input"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    m_instructions.push_back(Instruction::Comment("END FUNCTION inputb"));
}

void CodeGen::generateOutputb()
{
    m_functionLocs.insert({"outputb", Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment("FUNCTION outputb"));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    m_instructions.push_back(Instruction::LD(AC0, -2, FP, "Load parameter"));
    m_instructions.push_back(Instruction::OUTB(AC0, "Output bool"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    m_instructions.push_back(Instruction::Comment("END FUNCTION outputb"));
}

void CodeGen::generateInputc()
{
    m_functionLocs.insert({"inputc", Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment("FUNCTION inputc"));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    m_instructions.push_back(Instruction::INC(RT, "Grab char input"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    m_instructions.push_back(Instruction::Comment("END FUNCTION inputc"));
}

void CodeGen::generateOutputc()
{
    m_functionLocs.insert({"outputc", Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment("FUNCTION outputc"));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    m_instructions.push_back(Instruction::LD(AC0, -2, FP, "Load parameter"));
    m_instructions.push_back(Instruction::OUTC(AC0, "Output char"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    m_instructions.push_back(Instruction::Comment("END FUNCTION outputc"));
}

void CodeGen::generateOutnl()
{
    m_functionLocs.insert({"outnl", Instruction::whereAmI()});
    m_instructions.push_back(Instruction::Comment("FUNCTION outputnl"));
    m_instructions.push_back(
        Instruction::ST(AC0, -1, FP, "Store return address"));
    m_instructions.push_back(Instruction::OUTNL("Output integer"));
    m_instructions.push_back(
        Instruction::LD(AC0, -1, FP, "Load return address"));
    m_instructions.push_back(Instruction::LD(FP, 0, FP, "Adjust fp"));
    m_instructions.push_back(Instruction::JMP(0, AC0, "Return"));
    m_instructions.push_back(Instruction::Comment("END FUNCTION output"));
}