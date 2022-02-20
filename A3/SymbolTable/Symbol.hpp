#pragma once

#include "../AST/AST.hpp"

#include <optional>
#include <string>
#include <vector>

class Symbol {
  public:
    Symbol();
    Symbol &name(const std::string &);
    Symbol &declare(AST::Decl::Decl *decl);
    Symbol &define(unsigned linenum);
    Symbol &use(unsigned linenum);
    bool isDeclared() const;
    bool isDefined() const;
    bool isUsed() const;
    AST::Decl::Decl *decl() const;
    const std::vector<unsigned> &linesUsed() const;

  private:
    std::string m_id;
    AST::Decl::Decl *m_decl;
    std::optional<unsigned> m_lineDefined;
    std::vector<unsigned> m_linesUsed;
};