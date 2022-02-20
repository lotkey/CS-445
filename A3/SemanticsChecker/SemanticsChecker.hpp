#pragma once

#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"

#include <map>
#include <string>
#include <vector>

class SemanticsChecker {
  public:
    SemanticsChecker();
    const std::vector<std::string> &errors() const;
    const std::vector<std::string> &warnings() const;
    const SymbolTable &symbolTable() const;
    void analyze(AST::Node *);

  private:
    struct VarInfo {
        bool isUsed;
        bool isInitialized;
        int lineDeclared;
        int lineInitialized;
        std::vector<int> linesUsed;

        VarInfo()
            : isUsed(false), isInitialized(false), lineDeclared(-1),
              lineInitialized(-1) {}
    };

    SymbolTable m_symbolTable;
    std::vector<std::string> m_errors;
    std::vector<std::string> m_warnings;
    std::map<std::string, VarInfo> m_varInfo;
    bool m_mainIsDefined;

    void analyzeTree(AST::Node *);
    void analyzeNode(AST::Decl::Decl *);
    void analyzeNode(AST::Exp::Exp *);
    void analyzeNode(AST::Exp::Op::Op *);
    void analyzeNode(AST::Stmt::Stmt *);
};