#include "../strutil.hpp"
#include "Instruction.hpp"

#include <string>

Instruction Instruction::HALT(const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "HALT", "0", "0", "0", comment, false);
}
Instruction Instruction::NOP(const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "NOP", "0", "0", "0", comment, false);
}
Instruction Instruction::IN(int r, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "IN", std::to_string(r), "0", "0", comment,
                       false);
}
Instruction Instruction::INB(int r, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "INB", std::to_string(r), "0", "0", comment,
                       false);
}
Instruction Instruction::INC(int r, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "INC", std::to_string(r), "0", "0", comment,
                       false);
}
Instruction Instruction::OUT(int r, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "OUT", std::to_string(r), "0", "0", comment,
                       false);
}
Instruction Instruction::OUTB(int r, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "OUTB", std::to_string(r), "0", "0", comment,
                       false);
}
Instruction Instruction::OUTC(int r, const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "OUTC", std::to_string(r), "0", "0", comment,
                       false);
}
Instruction Instruction::OUTNL(const std::string &comment, int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "OUTNL", "0", "0", "0", comment, false);
}

Instruction Instruction::ADD(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "ADD", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::SUB(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "SUB", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::MUL(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "MUL", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::DIV(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "DIV", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::MOD(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "MOD", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::AND(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "AND", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::OR(int r, int s, int t, const std::string &comment,
                            int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "OR", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::XOR(int r, int s, int t, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "XOR", std::to_string(r), std::to_string(s),
                       std::to_string(t), comment, false);
}

Instruction Instruction::NOT(int r, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "NOT", std::to_string(r), std::to_string(s),
                       "0", comment, false);
}

Instruction Instruction::NEG(int r, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "NEG", std::to_string(r), std::to_string(s),
                       "0", comment, false);
}

Instruction Instruction::SWP(int r, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "SWP", std::to_string(r), std::to_string(s),
                       "0", comment, false);
}

Instruction Instruction::RND(int r, int s, const std::string &comment,
                             int emitLoc) {
    if (emitLoc == -1) {
        emitLoc = s_emitLoc;
        s_emitLoc++;
    }
    return Instruction(emitLoc, "RND", std::to_string(r), std::to_string(s),
                       "0", comment, false);
}
