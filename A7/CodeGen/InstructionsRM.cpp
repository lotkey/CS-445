#include "../strutil.hpp"
#include "Instruction.hpp"

#include <string>

Instruction Instruction::LDC(int r, const std::string &someconst,
                             const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "LDC", std::to_string(r), someconst, 0, comment,
                       true);
}

Instruction Instruction::LDA(int r, int d, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "LDA", std::to_string(r), std::to_string(d),
                       std::to_string(s), comment, true);
}

Instruction Instruction::LD(int r, int d, int s, const std::string &comment,
                            int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "LD", std::to_string(r), std::to_string(d),
                       std::to_string(s), comment, true);
}

Instruction Instruction::ST(int r, int d, int s, const std::string &comment,
                            int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "ST", std::to_string(r), std::to_string(d),
                       std::to_string(s), comment, true);
}

Instruction Instruction::JNZ(int r, int d, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "JNZ", std::to_string(r), std::to_string(d),
                       std::to_string(s), comment, true);
}

Instruction Instruction::JZR(int r, int d, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "JZR", std::to_string(r), std::to_string(d),
                       std::to_string(s), comment, true);
}

Instruction Instruction::JMP(int d, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "JMP", "7", std::to_string(d),
                       std::to_string(s), comment, true);
}