#include "Var.hpp"
#include "../../strutil.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Var::Var() : Decl::Decl() {
    m_declType = DeclType::Var;
    m_meminfo.setReferenceType(ReferenceType::Local);
    m_meminfo.setSize(1);
}

Var::Var(int linenum) : Decl::Decl(linenum, DeclType::Var) {
    m_meminfo.setReferenceType(ReferenceType::Local);
    m_meminfo.setSize(1);
    setIsArray(false);
}

Var::Var(int linenum, const std::string &id)
    : Decl::Decl(linenum, DeclType::Var) {
    setIsArray(false);
    m_id = id;
    m_meminfo.setReferenceType(ReferenceType::Local);
    m_meminfo.setSize(1);
}

Var::Var(int linenum, const std::string &id, int arraySize)
    : Decl::Decl(linenum, DeclType::Var) {
    setIsArray(true);
    m_id = id;
    m_meminfo.setReferenceType(ReferenceType::Local);
    m_meminfo.setSize(arraySize + 1);
}

void Var::setIsStatic(bool b) {
    if (b) {
        m_meminfo.setReferenceType(ReferenceType::Static);
    }

    TypedNode::setIsStatic(b);
    if (sibling() && sibling()->is(AST::DeclType::Var)) {
        auto *var = sibling()->cast<AST::Decl::Var *>();
        var->setIsStatic(b);
    }
}

void Var::setGlobal(bool b) {
    m_meminfo.setReferenceType(ReferenceType::Global);
    m_meminfo.calculateLocation();
    if (sibling()) {
        sibling()->cast<Var *>()->setGlobal(b);
    }
}

std::string Var::toString() const {
    return strutil::format("Var: %s %s", m_id.c_str(), typeTag().c_str());
}

bool Var::isInitialized() const { return getChild(0); }

void Var::setType(Type t) {
    TypedNode::setType(t);
    if (sibling() != nullptr && sibling()->is(DeclType::Var)) {
        sibling()->cast<Var *>()->setType(t);
    }
}

Exp::Exp *Var::initValue() { return getChild(0)->cast<Exp::Exp *>(); }
} // namespace AST::Decl