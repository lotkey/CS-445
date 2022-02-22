#include "SymbolTable.hpp"
#include "../AST/AST.hpp"
#include "Scope.hpp"
#include "Symbol.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

SymbolTable::SymbolTable() { m_scopes.push_back(Scope()); }

SymbolTable::SymbolTable(bool debug) {
    m_scopes.push_back(Scope());
    m_debug = debug;
}

int SymbolTable::depth() const { return m_scopes.size(); }

void SymbolTable::enter(const std::string &id) {
    if (m_debug) {
        std::cout << "DEBUG(SymbolTable): enter scope \"" << id << "\"."
                  << std::endl;
    }

    m_scopes.push_back(Scope(id));
}

void SymbolTable::leave() {

    if (m_debug) {
        std::cout << "DEBUG(SymbolTable): leave scope \""
                  << m_scopes.back().name() << "\"." << std::endl;
    }

    if (m_scopes.size() == 1) {
        std::cout << "ERROR(SymbolTable): You cannot leave global scope.  "
                     "Number of scopes: "
                  << m_scopes.size() << "." << std::endl;
    } else {
        m_scopes.pop_back();
    }
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

bool SymbolTable::isGlobal(const std::string &id) const {
    for (int i = m_scopes.size(); i > 0; i--) {
        if (m_scopes[i].contains(id)) {
            return false;
        }
    }

    return m_scopes.front().contains(id);
}

Symbol &SymbolTable::getSymbol(const std::string &id) {

    if (m_debug) {
        std::cout << "DEBUG(SymbolTable): lookup the symbol \"" << id
                  << "\" and ";
    }

    for (int i = m_scopes.size() - 1; i >= 0; i--) {
        if (m_scopes[i].contains(id)) {
            if (m_debug) {
                std::cout << "found it in the scope named \""
                          << m_scopes[i].name() << "\"." << std::endl;
            }
            return m_scopes[i].getSymbol(id);
        }
    }

    if (m_debug) {
        std::cout << "did NOT find it!" << std::endl;
    }
    // this creates a new symbol!
    // means it isn't declared yet
    return m_scopes.back().getSymbol(id);
}

Symbol &SymbolTable::operator[](const std::string &id) { return getSymbol(id); }

void SymbolTable::remove(const std::string &id) {
    for (int i = m_scopes.size() - 1; i >= 0; i--) {
        if (m_scopes[i].contains(id)) {
            m_scopes[i].remove(id);
            return;
        }
    }
}

void SymbolTable::removeImmediately(const std::string &id) {
    if (m_scopes.back().contains(id)) {
        m_scopes.back().remove(id);
    }
}