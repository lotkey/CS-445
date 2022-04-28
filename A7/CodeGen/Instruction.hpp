#pragma once

#include "../strutil.hpp"

#include <string>

class Instruction {
  public:
    static Instruction Comment();
    static Instruction Comment(const std::string& comment);
#pragma region Register to Memory
    /// Loads constant d. Immediate.
    /// reg[r] = someconst
    /// @param r Register to load the constant into
    /// @param someconst Can be an integer or character enclosed in single
    /// quotes. If the first character is ^, then it means control ('^M' is
    /// control-M). Escaped characters: '\0', '\t', '\n', '\'', and '\\'.
    static Instruction LDC(int r,
                           const std::string& someconst,
                           const std::string& comment = "");
    /// Loads direct address.
    /// reg[r] = d + reg[s]
    /// @param r Register to save address to
    /// @param d Some integer constant
    /// @param s Register to get address from (with offset)
    static Instruction LDA(int r,
                           int d,
                           int s,
                           const std::string& comment = "");
    /// Loads indirect.
    /// reg[r] = dMem[d + reg[s]]
    /// @param r Register to save data to
    /// @param d Some integer constant
    /// @param s Register to get data from (with offset)
    static Instruction LD(int r, int d, int s, const std::string& comment = "");
    /// Store constant.
    /// dMem[d + reg[s]] = reg[r]
    /// @param r Register where constant is
    /// @param d Some integer constant
    /// @param s Register to use to get address of data memory
    static Instruction ST(int r, int d, int s, const std::string& comment = "");
    /// Jump nonzero.
    /// if reg[r] != 0 reg[PC] = d + reg[s]
    /// @param r Contents of this register are tested
    /// @param d Some integer constant
    /// @param s Register to jump to (with offset)
    static Instruction JNZ(int r,
                           int d,
                           int s,
                           const std::string& comment = "");
    /// Jump zero.
    /// if reg[r] == 0 reg[PC] = d + reg[s]
    /// @param r Contents of this register are tested
    /// @param d Some integer constant
    /// @param s Register to jump to (with offset)
    static Instruction JZR(int r,
                           int d,
                           int s,
                           const std::string& comment = "");
    /// Jump.
    /// reg[PC] = d + reg[s]
    /// @param d Some integer constant
    /// @param s Register to jump to (with offset)
    static Instruction JMP(int d, int s, const std::string& comment = "");
#pragma endregion
#pragma region Register Only
    /// Stops execution.
    static Instruction HALT(const std::string& comment = "");
    /// Does nothing but take space.
    static Instruction NOP(const std::string& comment = "");
    /// Reads integer from input.
    /// reg[r] = input integer value of register r from stdin
    /// @param r Register to read input into
    static Instruction IN(int r, const std::string& comment = "");
    /// Reads boolean from input.
    /// reg[r] = input boolean value of register r from stdin
    /// @param r Register to read input into
    static Instruction INB(int r, const std::string& comment = "");
    /// Reads boolean from input.
    /// reg[r] = input character value of register r from stdin
    /// @param r Register to read input into
    static Instruction INC(int r, const std::string& comment = "");
    /// Ouputs integer from register.
    /// reg[r] -> stdout
    /// @param r Register to get integer to output
    static Instruction OUT(int r, const std::string& comment = "");
    /// Ouputs boolean from register.
    /// reg[r] -> stdout
    /// @param r Register to get boolean to output
    static Instruction OUTB(int r, const std::string& comment = "");
    /// Ouputs character from register.
    /// reg[r] -> stdout
    /// @param r Register to get character to output
    static Instruction OUTC(int r, const std::string& comment = "");
    /// Outputs a newline to stdout.
    static Instruction OUTNL(const std::string& comment = "");
    /// Adds two registers and stores the result in another.
    /// reg[r] = reg[s] + reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction ADD(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Subtracts two registers and stores the result in another.
    /// reg[r] = reg[s] + reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction SUB(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Multiplies two registers and stores the result in another.
    /// reg[r] = reg[s] + reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction MUL(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Truncating integer divide.
    /// reg[r] = reg[s] / reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction DIV(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Nonnegative modulus of two registers.
    /// reg[r] = reg[s] % reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction MOD(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Bitwise and.
    /// reg[r] = reg[s] & reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction AND(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Bitwise or.
    /// reg[r] = reg[s] | reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction OR(int r, int s, int t, const std::string& comment = "");
    /// Bitwise exclusive-or.
    /// reg[r] = reg[s] XOR reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction XOR(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Bitwise complement.
    /// reg[r] = !reg[s]
    /// @param r Result register
    /// @param s Operand
    static Instruction NOT(int r, int s, const std::string& comment = "");
    /// Negative.
    /// reg[r] = -reg[s];
    /// @param r Result register
    /// @param s Operand
    static Instruction NEG(int r, int s, const std::string& comment = "");
    /// Useful for min or max.
    /// reg[r] = min(reg[r], reg[s]), reg[s] = max(reg[r], reg[s])
    /// @param r Min register
    /// @param s Max register
    static Instruction SWP(int r, int s, const std::string& comment = "");
    /// Get random number between 0 and |reg[s] - 1| inclusive.
    /// reg[r] = random(0, |reg[s] - 1|)
    /// @param r Result register
    /// @param s Exclusive ceiling
    static Instruction RND(int r, int s, const std::string& comment = "");
#pragma endregion
#pragma region Test
    /// Less-than.
    /// reg[r] = reg[s] < reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TLT(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Less-than or equal.
    /// reg[r] = reg[s] <= reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TLE(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Equal.
    /// reg[r] = reg[s] == reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TEQ(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Not equal.
    /// reg[r] = reg[s] != reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TNE(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Greater-than or equal.
    /// reg[r] = reg[s] >= reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TGE(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Greater-than.
    /// reg[r] = reg[s] > reg[t]
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction TGT(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Signed test instruction, less-than. Useful for for loops.
    /// if (reg[r] >= 0) {
    ///   reg[r] = reg[s] < reg[t];
    /// } else {
    ///   reg[r] = -reg[s] < -reg[t];
    /// }
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction SLT(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// Signed test instruction, less-than. Useful for for loops.
    /// if (reg[r] >= 0) {
    ///   reg[r] = reg[s] > reg[t];
    /// } else {
    ///   reg[r] = -reg[s] > -reg[t];
    /// }
    /// @param r Result register
    /// @param s Operand 1
    /// @param t Operand 2
    static Instruction SGT(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
#pragma endregion
#pragma region Block Memory to Memory
    /// These instructions use the registers as parameters for block moves of
    /// memory without the need for loops. It is as if a memory controller could
    /// move masses of memory by itself.
    /// dMem[reg[r] - (0..reg[t] - 1)] = dMem[reg[s] - (0..reg[t] - 1)]
    static Instruction MOV(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// These instructions use the registers as parameters for block moves of
    /// memory without the need for loops. It is as if a memory controller could
    /// move masses of memory by itself.
    /// Mkakes reg[t] copies of reg[s]. Useful for zeroing out memory.
    /// dMem[reg[r] - (0..reg[t] - 1)] = reg[s]
    static Instruction SET(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
    /// These instructions use the registers as parameters for block moves of
    /// memory without the need for loops. It is as if a memory controller could
    /// move masses of memory by itself.
    /// Sets a pair of registers based on comparing two blocks of memory.
    /// Overlapping source and target blocks of memory is undefined.
    ///
    // clang-format off
    /// reg[r] = dMem[reg[r] + k] (for the first k that yiels a diff or the last tested if no diff)
    /// reg[s] = dMem[reg[s] + k] (for the first k that yields a diff or the last tested if no diff)
    // clang-format on
    ///
    /// WARNING: memory is scanned from higher addresses to lower. reg[t] is the
    /// size of the arrays compared. Both reg[r] and reg[s] are set so they can
    /// be tested using any of the test instructions.
    static Instruction CO(int r, int s, int t, const std::string& comment = "");
    /// These instructions use the registers as parameters for block moves of
    /// memory without the need for loops. It is as if a memory controller could
    /// move masses of memory by itself.
    /// Sets a pair of registers based on comparing two blocks of memory.
    /// Overlapping source and target blocks of memory is undefined.
    ///
    // clang-format off
    /// reg[r] = reg[r] + k (for the first k that yields a diff at that address or the last tested if no diff)
    /// reg[s] = reg[s] + k (for the first k that yields a diff at that address or the last tested if no diff)
    // clang-format on
    ///
    /// WARNING: memory is scanned from higher addresses to lower. reg[t] is the
    /// size of the arrays.
    static Instruction COA(int r,
                           int s,
                           int t,
                           const std::string& comment = "");
#pragma endregion
#pragma region Literal Instructions
    static Instruction LIT(int literal, const std::string& comment = "");
    static Instruction LIT(char literal, const std::string& comment = "");
    static Instruction LIT(const std::string& literal,
                           const std::string& comment = "");
#pragma endregion

    static int whereAmI();
    static int skip(int howMany);
    static void newLoc(int loc);

    Instruction();

    const std::string& toString() const;

  private:
    static int s_emitLoc;
    static int s_litLoc;

    Instruction(const std::string& comment);
    Instruction(int emitLoc,
                std::string opcode,
                const std::string& r0,
                const std::string& r1,
                const std::string& r2,
                const std::string& comment = "",
                bool paren = true);
    Instruction(int emitLoc,
                std::string opcode,
                std::string arg,
                const std::string& comment = "");
    void setString(const std::string& str);

    std::string m_str;
};