#pragma once

#include "../AST/AST.hpp"
#include "Symbol.hpp"

#include <string>
#include <vector>

class Scope {
  public:
    Scope();
    /// Creates a scope with the provided name
    /// @param id String identifier
    Scope(const std::string &id);
    /// @param id String identifier
    /// @returns True if contains a symbol with the provided identifier
    bool contains(const std::string &id) const;
    /// @param id String identifier
    /// @returns Reference to the symbol with the provided identifier
    Symbol &getSymbol(const std::string &id);
    /// @returns All the symbols in the scope mapped to by their identifiers
    std::map<std::string, Symbol> &getSymbols();
    /// @returns The string identifier of the scope
    std::string name() const;
    /// Removes the symbol with the provided identifier from the scope
    /// @param id String identifier
    void remove(const std::string &id);

  private:
    std::string m_id;
    std::map<std::string, Symbol> m_symbols;
};