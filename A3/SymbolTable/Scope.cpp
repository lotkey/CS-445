#include "Scope.hpp"

#include <map>
#include <string>

Scope::Scope() : m_id("global") {}

Scope::Scope(const std::string &id) : m_id(id) {}

bool Scope::contains(const std::string &id) {
    return m_symbols.find(id) != m_symbols.end();
}

void Scope::add(AST::Decl::Decl *node) {
    if (m_symbols.find(node->id()) != m_symbols.end()) {
        throw std::runtime_error("Variable already exists with name \"" +
                                 node->id() + "\"");
    }

    m_symbols[node->id()] = node;
}