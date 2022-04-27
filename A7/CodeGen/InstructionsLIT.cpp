#include "../strutil.hpp"
#include "Instruction.hpp"

#include <string>

Instruction Instruction::LIT(const std::string &literal, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "LIT", literal, comment);
}