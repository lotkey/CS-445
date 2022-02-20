#pragma once

#include "../AST/AST.hpp"
#include "Scope.hpp"
#include "Symbol.hpp"

#include <string>
#include <vector>

class SymbolTable {
  public:
    SymbolTable();
    int depth() const;
    void enter(const std::string &name = "unnamed scope");
    void leave();
    void declare(const std::string &id, AST::Decl::Decl *);
    bool contains(const std::string &) const;
    bool containsImmediately(const std::string &) const;
    std::map<std::string, Symbol> &getImmediateSymbols();
    Symbol &getSymbol(const std::string &);
    Symbol &operator[](const std::string &);

  private:
    std::vector<Scope> m_scopes;
};