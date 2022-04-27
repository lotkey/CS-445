#pragma once

#include "../AST/AST.hpp"

#include <optional>
#include <set>
#include <string>
#include <vector>

class Symbol {
  public:
    Symbol();
    /// Names the symbol with the provided identifier.
    /// @param id String identifier
    /// @returns Reference to the symbol
    Symbol &name(const std::string &id);
    /// Declares the symbol with the provided decl node.
    /// @param decl decl node
    /// @returns Reference to the symbol
    Symbol &declare(AST::Decl::Decl *decl);
    /// Notes that the symbol is defined on the provided line.
    /// @param linenum Line number the symbol is defined on
    /// @returns Reference to the symbol
    Symbol &define(int linenum);
    /// Notes that the symbol is used on the provided line.
    /// @param linenum Line number the symbol is used on
    /// @returns Reference to the symbol
    Symbol &use(int linenum);
    /// @returns True if the symbol has been declared
    bool isDeclared() const;
    /// @returns True if the symbol has been defined
    bool isDefined() const;
    /// @returns True if the symbol has been used
    bool isUsed() const;
    /// @returns True if the symbol is an iterator for a for loop
    bool isIterator() const;
    /// Notes that the symbol is an iterator or not
    /// @param b True if the symbol is to be marked an iterator
    void setIterator(bool b);
    /// @returns The declaration node that declares the symbol
    AST::Decl::Decl *decl() const;
    /// @returns A vector of lines where the symbol was used before it was
    /// defined
    std::vector<int> linesUsedBeforeDefined() const;
    /// @returns The line number where the symbol was defined, if at all.
    const std::optional<int> &lineDefined() const;

  private:
    std::string m_id;
    AST::Decl::Decl *m_decl = nullptr;
    std::vector<int> m_linesUsedBeforeDefined;
    std::vector<int> m_linesUsedAfterDefined;
    std::optional<int> m_lineDefined;
    bool m_isIterator = false;
};