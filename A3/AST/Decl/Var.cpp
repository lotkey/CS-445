#include "Var.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Var::Var() : Decl::Decl() { m_declType = DeclType::Var; }

Var::Var(unsigned linenum) : Decl::Decl(linenum, DeclType::Var) {}

Var::Var(unsigned linenum, const std::string &id, bool isArray)
    : Decl::Decl(linenum, DeclType::Var) {
    m_typeInfo.isArray = isArray;
    m_id = id;
}

void Var::setStatic() {
    if (m_sibling != nullptr) {
        ((Var *)m_sibling)->setStatic();
    }

    m_typeInfo.isStatic = true;
}

std::string Var::toString() const {
    std::string str = "Var: " + m_id;
    if (m_typeInfo.isArray) {
        str += " of array";
    }
    str += " of";
    if (m_typeInfo.isStatic) {
        str += " static";
    }
    str += " type " + Types::toString(m_typeInfo.type.value()) + lineTag();
    return str;
}
} // namespace AST::Decl