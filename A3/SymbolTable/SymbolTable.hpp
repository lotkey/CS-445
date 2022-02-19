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

  private:
    std::vector<Scope> m_scopes;
};