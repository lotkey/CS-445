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
    setMemoryInfo(ReferenceType::Local, 0, 0);
}

Var::Var(int linenum) : Decl::Decl(linenum, DeclType::Var) {
    setMemoryInfo(ReferenceType::Local, 0, 0);
    setIsArray(false);
}

Var::Var(int linenum, const std::string &id)
    : Decl::Decl(linenum, DeclType::Var) {
    setIsArray(true);
    m_id = id;
    setMemoryInfo(ReferenceType::Local, 0, 1);
}

Var::Var(int linenum, const std::string &id, int arraySize)
    : Decl::Decl(linenum, DeclType::Var) {
    setIsArray(true);
    m_id = id;
    setMemoryInfo(ReferenceType::Local, 0, arraySize + 1);
}

void Var::setStatic() {
    if (sibling() && sibling()->is(AST::DeclType::Var)) {
        auto *var = sibling()->cast<AST::Decl::Var *>();
        var->setStatic();
    }

    setIsStatic(true);
    setReferenceType(ReferenceType::Static);
}

std::string Var::toString() const {
    return strutil::format("Var: %s %s", m_id.c_str(), typeTag().c_str());
}

bool Var::isInitialized() const { return getChild(0); }

void Var::setType(Type t) {
    setType(t);
    if (sibling() != nullptr && sibling()->is(DeclType::Var)) {
        sibling()->cast<Var *>()->setType(t);
    }
}

Exp::Exp *Var::initValue() { return getChild(0)->cast<Exp::Exp *>(); }
} // namespace AST::Decl