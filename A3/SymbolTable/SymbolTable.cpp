#include "SymbolTable.hpp"
#include "../AST/AST.hpp"
#include "Scope.hpp"
#include "Symbol.hpp"

#include <algorithm>
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

void SymbolTable::declare(const std::string &id, AST::Decl::Decl *node) {
    m_scopes.back().getSymbol(id).declare(node);
}

bool SymbolTable::contains(const std::string &id) const {
    return std::any_of(m_scopes.begin(), m_scopes.end(),
                       [id](const Scope &scope) { return scope.contains(id); });
}

bool SymbolTable::containsImmediately(const std::string &id) const {
    return m_scopes.back().contains(id);
}

std::map<std::string, Symbol> &SymbolTable::getImmediateSymbols() {
    return m_scopes.back().getSymbols();
}

Symbol &SymbolTable::getSymbol(const std::string &id) {
    for (int i = m_scopes.size() - 1; i >= 0; i--) {
        if (m_scopes[i].contains(id)) {
            return m_scopes[i].getSymbol(id);
        }
    }

    // this creates a new symbol!
    // means it isn't declared yet
    return m_scopes.back().getSymbol(id);
}

Symbol &SymbolTable::operator[](const std::string &id) { return getSymbol(id); }