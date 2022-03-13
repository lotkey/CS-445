#include "Func.hpp"
#include "../Node.hpp"
#include "../Stmt/Compound.hpp"
#include "Decl.hpp"
#include "Parm.hpp"

#include <map>
#include <string>
#include <vector>

namespace AST::Decl {
Func::Func() : Decl::Decl() {
    m_declType = DeclType::Func;
    setTypeInfo({Type::Void, false, false});
}

Func::Func(unsigned linenum) : Decl::Decl(linenum, DeclType::Func) {
    setTypeInfo({Type::Void, false, false});
}

Func::Func(unsigned linenum, const std::string &id, Node *parms,
           Node *compoundstmt)
    : Decl::Decl(linenum, DeclType::Func) {
    setTypeInfo({Type::Void, false, false});
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
}

Func::Func(unsigned linenum, Type returnType, const std::string &id,
           Node *parms, Node *compoundstmt)
    : Decl::Decl(linenum, DeclType::Func) {
    setTypeInfo({returnType, false, false});
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
}

std::string Func::toString(bool debugging) const {
    return "Func: " + m_id + " returns type " + Types::toString(type()) +
           lineTag();
}

bool Func::hasParms() const { return parms() != nullptr; }

Parm *Func::parms() const { return getChild(0)->cast<Parm *>(); }

int Func::numParms() const {
    auto *parm = parms();
    int counter = 0;
    while (parm != nullptr) {
        counter++;
        parm = parm->sibling()->cast<Parm *>();
    }

    return counter;
}

std::vector<Parm *> Func::parmsVector() const {
    std::vector<Parm *> v;
    auto *parm = parms();
    while (parm != nullptr) {
        v.push_back(parm);
        parm = parm->sibling()->cast<Parm *>();
    }

    return v;
}
} // namespace AST::Decl