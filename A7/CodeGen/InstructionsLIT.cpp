#include "../strutil.hpp"
#include "Instruction.hpp"

#include <string>

Instruction Instruction::LIT(int literal, const std::string& comment)
{
    int addr = s_litLoc;
    s_litLoc++;
    return Instruction(addr, "LIT", std::to_string(literal), comment);
}

Instruction Instruction::LIT(char literal, const std::string& comment)
{
    int addr = s_litLoc;
    s_litLoc++;
    return Instruction(addr, "LIT", std::to_string((int)literal), comment);
}

Instruction Instruction::LIT(const std::string& literal,
                             const std::string& comment)
{
    // Literal will have opening and closing double-quotes
    // Size will also include the -1 index, which has the size
    // So -2 for the quotes, + 1 for the size
    int size = literal.length() - 1;

    int addr = s_litLoc;
    s_litLoc += size;
    return Instruction(addr, "LIT", literal, comment);
}