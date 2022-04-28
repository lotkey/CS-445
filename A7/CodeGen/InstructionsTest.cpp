#include "../strutil.hpp"
#include "Instruction.hpp"

#include <string>

Instruction Instruction::TLT(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "TLT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TLE(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "TLE", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TEQ(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "TEQ", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TNE(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "TNE", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TGE(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "TGE", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TGT(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "TGT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::SLT(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "SLT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::SGT(int r, int s, int t, const std::string &comment) {
    int emitLoc = s_emitLoc;
    s_emitLoc++;
    return Instruction(emitLoc, "SGT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}