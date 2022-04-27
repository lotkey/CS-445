#include "../strutil.hpp"
#include "Instruction.hpp"

#include <string>

Instruction Instruction::TLT(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "TLT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TLE(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "TLE", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TEQ(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "TEQ", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TNE(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "TNE", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TGE(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "TGE", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::TGT(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "TGT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::SLT(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "SLT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::SGT(int emitLoc, int r, int s, int t,
                             const std::string &comment) {
    return Instruction(emitLoc, "SGT", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}
