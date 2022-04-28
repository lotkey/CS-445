#include "Instruction.hpp"
#include "../strutil.hpp"

int Instruction::s_emitLoc = 0;
int Instruction::s_litLoc = 1;

Instruction Instruction::Comment() { return Instruction(); }

Instruction Instruction::Comment(const std::string &comment) {
    return Instruction(comment);
}

Instruction::Instruction() : m_str("* ** ** ** ** ** ** ** ** ** ** ** **") {}

Instruction::Instruction(const std::string &comment) : m_str("* " + comment) {}

Instruction::Instruction(int emitLoc, std::string opcode, const std::string &r0,
                         const std::string &r1, const std::string &r2,
                         const std::string &comment, bool paren) {
    std::string emit = std::to_string(emitLoc) + ":";
    while (emit.length() + opcode.length() < 10) {
        emit += " ";
    }

    std::string args;
    if (paren) {
        args = strutil::format("%s,%s(%s)", r0.c_str(), r1.c_str(), r2.c_str());
    } else {
        args = strutil::format("%s,%s,%s", r0.c_str(), r1.c_str(), r2.c_str());
    }
    while (args.length() < 10) {
        args += " ";
    }

    m_str = strutil::format("%s%s  %s %s", emit.c_str(), opcode.c_str(),
                            args.c_str(), comment.c_str());
}

Instruction::Instruction(int emitLoc, std::string opcode, std::string arg,
                         const std::string &comment) {
    std::string emit = std::to_string(emitLoc) + ":";
    while (emit.length() + opcode.length() < 10) {
        emit += " ";
    }

    while (arg.length() < 10) {
        arg += " ";
    }
    m_str = strutil::format("%s%s  %s %s", emit.c_str(), opcode.c_str(),
                            arg.c_str(), comment.c_str());
}

int Instruction::whereAmI() { return s_emitLoc; }

int Instruction::skip(int howMany) {
    int i = s_emitLoc;
    s_emitLoc += howMany;
    return i;
}

void Instruction::newLoc(int loc) { s_emitLoc = loc; }

void Instruction::setString(const std::string &str) { m_str = str; }

const std::string &Instruction::toString() const { return m_str; }