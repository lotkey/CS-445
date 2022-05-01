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
    static std::string make(const std::string& label);

    CodeGen();
    CodeGen(AST::Node* ast);
    void generate(const std::string& filename);

  private:
    static const std::string s_ioTmCodePath;
    static std::map<std::string, int> s_labelCounts;

    std::vector<int> m_toffs;
    std::map<std::string, int> m_functionLocs;
    std::vector<AST::Node*> m_fundecls;
    std::vector<AST::Node*> m_globaldecls;
    AST::Node* m_main;
    std::vector<Instruction> m_instructions;
    AST::Node* m_ast;

    void generateCode();
    void generateCode(AST::Node*);

    void generateCode(AST::Decl::Decl*);
    void generateCode(AST::Decl::Func*);
    void generateCode(AST::Decl::Var*);

    void generateCode(AST::Stmt::Stmt*);
    void generateCode(AST::Stmt::Compound*);
    void generateCode(AST::Stmt::For*);
    void generateCode(AST::Stmt::Return*);

    void generateCode(AST::Exp::Exp*, int AC = AC0);
    void generateCode(AST::Exp::Const*, int AC = AC0);
    void generateCode(AST::Exp::Call*, int AC = AC0);
    void generateCode(AST::Exp::Id*, int AC = AC0);
    void generateCode(AST::Exp::Op::Op*, int AC = AC0);
    void generateCode(AST::Exp::Op::Binary*, int AC = AC0);
    void generateCode(AST::Exp::Op::Unary*, int AC = AC0);
    void generateCode(AST::Exp::Op::UnaryAsgn*, int AC = AC0);
    void generateCode(AST::Exp::Op::Asgn*, int AC = AC0);
    void generateCodeBinaryMathop(AST::Exp::Op::Binary*, int AC = AC0);
    void generateCodeModifyAsgn(AST::Exp::Op::Asgn*, int AC = AC0);
    void generateCodeIndexOp(AST::Exp::Op::Binary*, int AC = AC0);
    void generateCode(AST::Exp::Op::Bool*, int AC = AC0);

    void generatePrologCode();
    void generateIoCode();
    void generateInput();
    void generateOutput();
    void generateInputb();
    void generateOutputb();
    void generateInputc();
    void generateOutputc();
    void generateOutnl();
    void generateStandardFunctionClosing();
    void linearalize();

    void toffPush(int toff);
    int toffPop();
    int toffBack();
    void toffInc();
    void toffDec();
    void toffSet(int toff);
};