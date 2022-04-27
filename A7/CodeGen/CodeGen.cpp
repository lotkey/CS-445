#include "CodeGen.hpp"
#include "Instruction.hpp"

#include <fstream>
#include <map>
#include <string>

const std::string CodeGen::s_ioTmCodePath = "./CodeGen/ioTmCode.tm";
std::map<std::string, int> CodeGen::s_labelCounts;

std::string CodeGen::make(const std::string &label) {
    s_labelCounts.insert({label, 0});
    std::string numbered_label =
        label + std::to_string(s_labelCounts.at(label));
    s_labelCounts[label]++;
    return numbered_label;
}

CodeGen::CodeGen() : m_ast(nullptr) {}

CodeGen::CodeGen(AST::Node *ast) : m_ast(ast) {}

void CodeGen::generate(const std::string &filename) {
    generateCode();
    std::ofstream outfile(filename);

    for (const auto &instruction : m_instructions) {
        outfile << instruction.toString();
        outfile << "\n";
    }
    outfile.close();
}

void CodeGen::generateCode() {
    std::vector<Instruction> libraryInstructions = ioTmCode();
    m_instructions.insert(m_instructions.end(), libraryInstructions.begin(),
                          libraryInstructions.end());
    // traverse and stuff
}

std::vector<Instruction> CodeGen::ioTmCode() {
    std::vector<Instruction> instructions;
    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION input"));
    instructions.push_back(
        Instruction::ST(1, AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::IN(2, AC0, "Grab int input"));
    instructions.push_back(
        Instruction::LD(3, AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(4, FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(5, PC, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION input"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION inputb"));
    instructions.push_back(
        Instruction::ST(6, AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::INB(7, AC0, "Grab bool input"));
    instructions.push_back(
        Instruction::LD(8, AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(9, FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(10, PC, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION inputb"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION inputc"));
    instructions.push_back(
        Instruction::ST(11, AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::INC(12, AC0, "Grab char input"));
    instructions.push_back(
        Instruction::LD(13, AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(14, FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(15, PC, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION inputc"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION output"));
    instructions.push_back(
        Instruction::ST(16, AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::LD(17, AC0, -2, FP, "Load parameter"));
    instructions.push_back(Instruction::OUT(18, AC0, "Output integer"));
    instructions.push_back(
        Instruction::LD(19, AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(20, FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(21, PC, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION output"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION outputb"));
    instructions.push_back(
        Instruction::ST(22, AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::LD(23, AC0, -2, FP, "Load parameter"));
    instructions.push_back(Instruction::OUTB(24, AC0, "Output bool"));
    instructions.push_back(
        Instruction::LD(25, AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(26, FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(27, PC, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION outputb"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION outputc"));
    instructions.push_back(
        Instruction::ST(28, AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::LD(29, AC0, -2, FP, "Load parameter"));
    instructions.push_back(Instruction::OUTC(30, AC0, "Output char"));
    instructions.push_back(
        Instruction::LD(31, AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(32, FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(33, PC, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION outputc"));
    instructions.push_back(Instruction::Comment(""));

    instructions.push_back(Instruction::Comment());
    instructions.push_back(Instruction::Comment("FUNCTION outputnl"));
    instructions.push_back(
        Instruction::ST(34, AC0, -1, FP, "Store return address"));
    instructions.push_back(Instruction::OUTNL(35, "Output integer"));
    instructions.push_back(
        Instruction::LD(36, AC0, -1, FP, "Load return address"));
    instructions.push_back(Instruction::LD(37, FP, 0, FP, "Adjust fp"));
    instructions.push_back(Instruction::JMP(38, PC, AC0, "Return"));
    instructions.push_back(Instruction::Comment("END FUNCTION output"));

    return instructions;
}