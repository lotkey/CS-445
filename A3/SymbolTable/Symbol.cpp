#include "Symbol.hpp"

#include <string>
#include <vector>

Symbol::Symbol() : m_decl(nullptr) {}

Symbol &Symbol::name(const std::string &name) {
    m_id = name;
    return *this;
}

Symbol &Symbol::declare(AST::Decl::Decl *decl) {
    if (m_decl != nullptr) {
        m_decl = decl;
    }
    return *this;
}

Symbol &Symbol::define(unsigned linenum) {
    if (!m_lineDefined.has_value()) {
        m_lineDefined = linenum;
    }
    return *this;
}

Symbol &Symbol::use(unsigned linenum) {
    m_linesUsed.push_back(linenum);
    return *this;
}

bool Symbol::isDeclared() const { return m_decl != nullptr; }

bool Symbol::isDefined() const { return m_lineDefined.has_value(); }

bool Symbol::isUsed() const { return !m_linesUsed.empty(); }

AST::Decl::Decl *Symbol::decl() const { return m_decl; }

const std::vector<unsigned> &Symbol::linesUsed() const { return m_linesUsed; }