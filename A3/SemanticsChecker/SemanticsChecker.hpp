#pragma once

#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "Message.hpp"

#include <map>
#include <optional>
#include <string>
#include <vector>

class SemanticsChecker {
  public:
    SemanticsChecker();
    const SymbolTable &symbolTable() const;
    void analyze(AST::Node *);

  private:
    SymbolTable m_symbolTable;
    /// Mapping for errors and warning messages
    /// Maps from line number to bucket of messages
    std::map<unsigned, std::vector<Message>> m_messages;
    unsigned m_numErrors = 0;
    unsigned m_numWarnings = 0;
    std::vector<AST::Decl::Parm *> m_parms;
    std::optional<std::string> m_scopeName;
    bool m_mainIsDefined;

    void enterScope();
    void leaveScope();

    void analyzeTree(AST::Node *);
    void analyzeNode(AST::Decl::Decl *);
    void analyzeNode(AST::Exp::Exp *);
    void analyzeNode(AST::Exp::Op::Op *);
    void analyzeNode(AST::Stmt::Stmt *);
};