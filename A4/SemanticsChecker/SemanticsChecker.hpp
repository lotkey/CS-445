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
    /// Constructs a semantics checker
    /// @param debug Whether or not to print symbol table debugging info
    SemanticsChecker(bool debug);
    /// @returns The symbol table
    const SymbolTable &symbolTable() const;
    /// Analyzes an AST for semantic errors
    /// @param tree AST to analyze
    void analyze(AST::Node *tree);
    /// Print the errors and warnings from analyzing the last tee
    void print() const;
    /// @returns The number of errors in the last analyzed AST
    int numErrors() const;
    /// @returns The number of warnings in the last analyzed AST
    int numWarnings() const;

  private:
    SymbolTable m_symbolTable;
    /// Mapping for errors and warning messages
    /// Maps from line number to bucket of messages
    std::map<unsigned, std::vector<Message>> m_messages;
    /// Optional scope name
    /// Functions have named scopes, for loops have scopes named "for", compound
    /// statements have the name "compound"
    std::optional<std::string> m_scopeName;
    bool m_mainIsDefined;
    bool m_analyzed = false;
    bool m_debug = false;
    /// Parameters to add to a function's scope
    AST::Decl::Parm *m_parms = nullptr;

    /// Enter a scope
    void enterScope();
    /// Enter a scope (potentially unnamed)
    void enterScope(const std::optional<std::string> &);
    /// Analyze all elements on the top scope
    void checkTopScope();
    /// Pop off the top scope
    void leaveScope();
    /// Deduce the type of a node from the table
    /// Used for IDs and calls and such
    void deduceTypeFromTable(AST::Node *);
    /// Analyze variable definitions
    void analyzeDefinitions(AST::Exp::Op::Asgn *);
    /// Recursively analyze the whole tree
    void analyzeTree(AST::Node *);

    /// Analyze a single declaration node
    void analyzeNode(AST::Decl::Decl *);
    /// Analyze a single expression node
    void analyzeNode(AST::Exp::Exp *);
    /// Analyze a single operator node
    void analyzeNode(AST::Exp::Op::Op *);
    /// Analyze a single unary operator node
    void analyzeNode(AST::Exp::Op::Unary *);
    /// Analyze a single binary assignment operator node
    void analyzeNode(AST::Exp::Op::Asgn *);
    /// Analyze a single binary bool operator node
    void analyzeNode(AST::Exp::Op::Bool *);
    /// Analyze a single statement node
    void analyzeNode(AST::Stmt::Stmt *);
};