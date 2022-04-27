#include "../strutil.hpp"
#include "Instruction.hpp"

#include <string>

Instruction Instruction::MOV(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "MOV", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment);
}

Instruction Instruction::SET(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "SET", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment);
}

Instruction Instruction::CO(int r, int s, int t, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "CO", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment);
}

Instruction Instruction::COA(int r, int s, int t, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "COA", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment);
}
