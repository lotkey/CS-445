#pragma once

#include "../AST/AST.hpp"

#include <optional>
#include <set>
#include <string>
#include <vector>

class Symbol {
  public:
    Symbol();
    Symbol &name(const std::string &);
    Symbol &declare(AST::Decl::Decl *decl);
    Symbol &define(int linenum);
    Symbol &use(int linenum);
    bool isDeclared() const;
    bool isDefined() const;
    bool isUsed() const;
    bool isIterator() const;
    void setIterator(bool);
    AST::Decl::Decl *decl() const;
    std::vector<int> linesUsedBeforeDefined() const;
    const std::optional<int> &lineDefined() const;

  private:
    std::string m_id;
    AST::Decl::Decl *m_decl = nullptr;
    std::vector<int> m_linesUsedBeforeDefined;
    std::vector<int> m_linesUsedAfterDefined;
    std::optional<int> m_lineDefined;
    bool m_isIterator = false;
};