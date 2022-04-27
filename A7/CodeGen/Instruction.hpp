#pragma once

#include "../strutil.hpp"

#include <string>

class Instruction {
  public:
    static Instruction Comment();
    static Instruction Comment(const std::string &comment);
#pragma region Register to Memory
    /// Loads constant d. Immediate.
    /// reg[r] = someconst
    /// @param r Register to load the constant into
    /// @param someconst Can be an integer or character enclosed in single
    /// quotes. If the first character is ^, then it means control ('^M' is
    /// control-M). Escaped characters: '\0', '\t', '\n', '\'', and '\\'.
    static Instruction LDC(int r, const std::string &someconst,
                           const std::string &comment = "", int emitLoc = -1);
    /// Loads direct address.
    /// reg[r] = d + reg[s]
    /// @param r Register to save address to
    /// @param d Some integer constant
    /// @param s Register to get address from (with offset)
    static Instruction LDA(int r, int d, int s, const std::string &comment = "",
                           int emitLoc = -1);
    /// Loads indirect.
    /// reg[r] = dMem[d + reg[s]]
    /// @param r Register to save data to
    /// @param d Some integer constant
    /// @param s Register to get data from (with offset)
    static Instruction LD(int r, int d, int s, const std::string &comment = "",
                          int emitLoc = -1);
    /// Store constant.
    /// dMem[d + reg[s]] = reg[r]
    /// @param r Register where constant is
    /// @param d Some integer constant
    /// @param s Register to use to get address of data memory
    static Instruction ST(int r, int d, int s, const std::string &comment = "",
                          int emitLoc = -1);
    /// Jump nonzero.
    /// if reg[r] != 0 reg[PC] = d + reg[s]
    /// @param r Contents of this register are tested
    /// @param d Some integer constant
    /// @param s Register to jump to (with offset)
    static Instruction JNZ(int r, int d, int s, const std::string &comment = "",
                           int emitLoc = -1);
    /// Jump zero.
    /// if reg[r] == 0 reg[PC] = d + reg[s]
    /// @param r Contents of this register are tested
    /// @param d Some integer constant
    /// @param s Register to jump to (with offset)
    static Instruction JZR(int r, int d, int s, const std::string &comment = "",
                           int emitLoc = -1);
    /// Jump.
    /// reg[PC] = d + reg[s]
    /// @param d Some integer constant
    /// @param s Register to jump to (with offset)
    static Instruction JMP(int d, int s, const std::string &comment = "",
                           int emitLoc = -1);
#pragma endregion
#pragma region Register Only
    /// Stops execution.
    static Instruction HALT(const std::string &comment = "", int emitLoc = -1);
    /// Does nothing but take space.
    static Instruction NOP(const std::string &comment = "", int emitLoc = -1);
    /// Reads integer from input.
    /// reg[r] = input integer value of register r from stdin
    /// @param r Register to read input into
    static Instruction IN(int r, const std::string &comment = "",
                          int emitLoc = -1);
    /// Reads boolean from input.
    /// reg[r] = input boolean value of register r from stdin
    /// @param r Register to read input into
    static Instruction INB(int r, const std::string &comment = "",
                           int emitLoc = -1);
    /// Reads boolean from input.
    /// reg[r] = input character value of register r from stdin
    /// @param r Register to read input into
    static Instruction INC(int r, const std::string &comment = "",
                           int emitLoc = -1);
    /// Ouputs integer from register.
    /// reg[r] -> stdout
    /// @param r Register to get integer to output
    static Instruction OUT(int r, const std::string &comment = "",
                           int emitLoc = -1);
    /// Ouputs boolean from register.
    /// reg[r] -> stdout
    /// @param r Register to get boolean to output
    static Instruction OUTB(int r, const std::string &comment = "",
                            int emitLoc = -1);
    /// Ouputs character from register.
    /// reg[r] -> stdout
    /// @param r Register to get character to output
    static Instruction OUTC(int r, const std::string &comment = "",
                            int emitLoc = -1);
    /// Outputs a newline to stdout.
    static Instruction OUTNL(const std::string &comment = "", int emitLoc = -1);
    /// Adds two registers and stores the result in another.
    /// reg[r] = reg[s] + reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction ADD(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Subtracts two registers and stores the result in another.
    /// reg[r] = reg[s] + reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction SUB(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Multiplies two registers and stores the result in another.
    /// reg[r] = reg[s] + reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction MUL(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Truncating integer divide.
    /// reg[r] = reg[s] / reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction DIV(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Nonnegative modulus of two registers.
    /// reg[r] = reg[s] % reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction MOD(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Bitwise and.
    /// reg[r] = reg[s] & reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction AND(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Bitwise or.
    /// reg[r] = reg[s] | reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction OR(int r, int s, int t, const std::string &comment = "",
                          int emitLoc = -1);
    /// Bitwise exclusive-or.
    /// reg[r] = reg[s] XOR reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction XOR(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Bitwise complement.
    /// reg[r] = !reg[s]
    /// @param r Result register
    /// @param s Operand
    static Instruction NOT(int r, int s, const std::string &comment = "",
                           int emitLoc = -1);
    /// Negative.
    /// reg[r] = -reg[s];
    /// @param r Result register
    /// @param s Operand
    static Instruction NEG(int r, int s, const std::string &comment = "",
                           int emitLoc = -1);
    /// Useful for min or max.
    /// reg[r] = min(reg[r], reg[s]), reg[s] = max(reg[r], reg[s])
    /// @param r Min register
    /// @param s Max register
    static Instruction SWP(int r, int s, const std::string &comment = "",
                           int emitLoc = -1);
    /// Get random number between 0 and |reg[s] - 1| inclusive.
    /// reg[r] = random(0, |reg[s] - 1|)
    /// @param r Result register
    /// @param s Exclusive ceiling
    static Instruction RND(int r, int s, const std::string &comment = "",
                           int emitLoc = -1);
#pragma endregion
#pragma region Test
    /// Less-than.
    /// reg[r] = reg[s] < reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TLT(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Less-than or equal.
    /// reg[r] = reg[s] <= reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TLE(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Equal.
    /// reg[r] = reg[s] == reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TEQ(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Not equal.
    /// reg[r] = reg[s] != reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TNE(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Greater-than or equal.
    /// reg[r] = reg[s] >= reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TGE(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Greater-than.
    /// reg[r] = reg[s] > reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TGT(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Signed test instruction, less-than. Useful for for loops.
    /// if (reg[r] >= 0) {
    ///   reg[r] = reg[s] < reg[t];
    /// } else {
    ///   reg[r] = -reg[s] < -reg[t];
    /// }
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction SLT(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    /// Signed test instruction, less-than. Useful for for loops.
    /// if (reg[r] >= 0) {
    ///   reg[r] = reg[s] > reg[t];
    /// } else {
    ///   reg[r] = -reg[s] > -reg[t];
    /// }
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction SGT(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
#pragma endregion
#pragma region Block Memory to Memory
    static Instruction MOV(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    static Instruction SET(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
    static Instruction CO(int r, int s, int t, const std::string &comment = "",
                          int emitLoc = -1);
    static Instruction COA(int r, int s, int t, const std::string &comment = "",
                           int emitLoc = -1);
#pragma endregion
#pragma region Literal Instructions
    static Instruction LIT(const std::string &literal,
                           const std::string &comment = "", int emitLoc = -1);
#pragma endregion

    Instruction();

    const std::string &toString() const;

  private:
    static int s_emitLoc;
    static int s_litLoc;

    Instruction(const std::string &comment);
    Instruction(int emitLoc, std::string opcode, const std::string &r0,
                const std::string &r1, const std::string &r2,
                const std::string &comment = "", bool paren = true);
    Instruction(int emitLoc, std::string opcode, std::string arg,
                const std::string &comment = "");
    void setString(const std::string &str);

    std::string m_str;
};