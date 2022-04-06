#pragma once

#include "../AST/AST.hpp"
#include "Scope.hpp"
#include "Symbol.hpp"

#include <string>
#include <vector>

class SymbolTable {
  public:
    SymbolTable();
    /// @param debug Whether or not to print symbol table debugging statements.
    SymbolTable(bool debug);
    /// @returns The current number of scopes in the symbol table
    int depth() const;
    /// Enters a new scope
    /// @param name Optional scope name
    void enter(const std::string &name = "unnamed scope");
    /// Pops off the top of the scope stack
    void leave();
    /// Adds a declaration to current scope
    /// @param id String identifier
    /// @param decl Declaration node
    void declare(const std::string &id, AST::Decl::Decl *decl);
    /// @param id String identifier
    /// @returns True if there is an entry for some symbol with the provided
    /// identifier.
    bool contains(const std::string &id) const;
    /// @param id String identifier
    /// @returns True if there is an entry for some symbol with the provided
    /// identifier in the current scope.
    bool containsImmediately(const std::string &id) const;
    /// @param id String identifier
    /// @returns True if there is a symbol with the provided identifier, it is
    /// in the global scope, and it is not shadowed by any other symbols in
    /// other scopes.
    bool isGlobal(const std::string &id) const;
    /// @param id String identifier
    /// Removes the entry for the symbol with the provided identifier in the
    /// closest scope.
    void remove(const std::string &id);
    /// @param id String identifier
    /// Removes the entry for the symbol with the provided identifier only if
    /// there is one in the current scope.
    void removeImmediately(const std::string &id);
    /// @returns Mapping from identifier to symbols of all of the symbols in the
    /// top scope.
    std::map<std::string, Symbol> &getImmediateSymbols();
    /// @param id String identifier
    /// Returns a reference to the symbol with the provided identifier.
    Symbol &getSymbol(const std::string &id);
    /// @param id String identifier
    /// Returns a reference to the symbol with the provided identifier.
    Symbol &operator[](const std::string &id);

  private:
    std::vector<Scope> m_scopes;
    bool m_debug = false;

    /// @returns The names of the scopes on the stack with the "::" C++-style
    /// namespace operator in between scope names.
    std::string scopeString() const;
};