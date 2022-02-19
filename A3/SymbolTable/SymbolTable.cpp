#include "SymbolTable.hpp"
#include "../AST/AST.hpp"
#include "Scope.hpp"

#include <string>
#include <vector>

SymbolTable::SymbolTable() { m_scopes.push_back(Scope()); }

int SymbolTable::depth() const { return m_scopes.size(); }

void SymbolTable::enter(const std::string &id) {
    m_scopes.push_back(Scope(id));
}

void SymbolTable::leave() {
    if (m_scopes.size() == 1) {
        throw std::runtime_error("Attempting to pop global scope");
    }

    m_scopes.pop_back();
}

void SymbolTable::add(AST::Decl::Decl *node) { m_scopes.back().add(node); }