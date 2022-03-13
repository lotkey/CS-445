#include "Var.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Var::Var() : Decl::Decl() { m_declType = DeclType::Var; }

Var::Var(unsigned linenum) : Decl::Decl(linenum, DeclType::Var) {}

Var::Var(unsigned linenum, const std::string &id, bool isArray)
    : Decl::Decl(linenum, DeclType::Var) {
    setIsArray(isArray);
    m_id = id;
}

void Var::setStatic() {
    if (m_sibling != nullptr) {
        ((Var *)m_sibling)->setStatic();
    }

    setIsStatic(true);
}

std::string Var::toString(bool debugging) const {
    std::string str = "Var: " + m_id;
    if (isArray()) {
        str += " is array";
    }
    str += " of";
    if (isStatic()) {
        str += " static";
    }
    str += " type " + Types::toString(typeOptional()) + lineTag();
    return str;
}

bool Var::isInitialized() const {
    return !m_children.empty() && m_children[0] != nullptr;
}

void Var::setType(Type t) {
    TypedNode::setType(t);
    if (sibling() != nullptr && sibling()->is(DeclType::Var)) {
        sibling()->cast<Var *>()->setType(t);
    }
}

Exp::Exp *Var::initValue() { return getChild(0)->cast<Exp::Exp *>(); }
} // namespace AST::Decl