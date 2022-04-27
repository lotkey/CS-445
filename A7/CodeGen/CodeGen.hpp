#pragma once
#define GP 0
#define FP 1
#define RT 2
#define AC0 3
#define AC1 4
#define AC2 5
#define AC3 6
#define PC 7

#include "../AST/AST.hpp"
#include "Instruction.hpp"

#include <map>
#include <string>
#include <vector>

class CodeGen {
  public:
    static std::string make(const std::string &label);
    static std::vector<Instruction> ioTmCode();

    CodeGen();
    CodeGen(AST::Node *ast);
    void generate(const std::string &filename);

  private:
    static const std::string s_ioTmCodePath;
    static std::map<std::string, int> s_labelCounts;

    std::vector<Instruction> m_instructions;
    AST::Node *m_ast;

    void generateCode();
};