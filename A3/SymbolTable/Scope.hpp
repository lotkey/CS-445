#pragma once

#include "../AST/AST.hpp"

#include <string>
#include <vector>

class Scope {
  public:
    Scope();
    Scope(const std::string &);
    bool contains(const std::string &);
    void add(AST::Decl::Decl *);

  private:
    std::string m_id;
    std::map<std::string, AST::Decl::Decl *> m_symbols;
};