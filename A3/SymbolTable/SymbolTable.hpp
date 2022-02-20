#pragma once

#include "../AST/AST.hpp"
#include "Scope.hpp"

#include <string>
#include <vector>

class SymbolTable {
  public:
    SymbolTable();
    int depth() const;
    void enter(const std::string &);
    void leave();
    void add(AST::Decl::Decl *);
    bool contains(const std::string &) const;
    bool containsImmediately(const std::string &) const;
    AST::Decl::Decl *getSymbol(const std::string &) const;
    AST::Decl::Decl *operator[](const std::string &) const;

  private:
    std::vector<Scope> m_scopes;
};