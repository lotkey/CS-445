#include "Var.hpp"
#include "../../strutil.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Var::Var() : Decl::Decl() { m_declType = DeclType::Var; }

Var::Var(int linenum) : Decl::Decl(linenum, DeclType::Var) {}

Var::Var(int linenum, const std::string &id, bool isArray)
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

std::string Var::toString() const {
    return strutil::format("Var: %s %s", m_id.c_str(), typeTag().c_str());
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