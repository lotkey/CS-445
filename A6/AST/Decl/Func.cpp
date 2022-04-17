#include "Func.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"
#include "../Stmt/Compound.hpp"
#include "Decl.hpp"
#include "Parm.hpp"
#include "Var.hpp"

#include <map>
#include <string>
#include <vector>

namespace AST::Decl {
Func::Func() : Decl::Decl() {
    m_declType = DeclType::Func;
    setTypeInfo({Type::Void, false, false});
    m_meminfo.setReferenceType(ReferenceType::Global);
    m_meminfo.setLocation(0);
}

Func::Func(int linenum) : Decl::Decl(linenum, DeclType::Func) {
    setTypeInfo({Type::Void, false, false});
    m_meminfo.setReferenceType(ReferenceType::Global);
    m_meminfo.setLocation(0);
}

Func::Func(int linenum, const std::string &id, Node *parms, Node *compoundstmt)
    : Decl::Decl(linenum, DeclType::Func) {
    setTypeInfo({Type::Void, false, false});
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
    m_meminfo.setReferenceType(ReferenceType::Global);
    m_meminfo.setLocation(0);
}

Func::Func(int linenum, Type returnType, const std::string &id, Node *parms,
           Node *compoundstmt)
    : Decl::Decl(linenum, DeclType::Func) {
    setTypeInfo({returnType, false, false});
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
    m_meminfo.setReferenceType(ReferenceType::Global);
    m_meminfo.setLocation(0);
}

std::string Func::toString() const {
    return strutil::format("Func: %s returns type %s", m_id.c_str(),
                           Types::toString(typeOptional()).c_str());
}

void Func::calculateMemory() {
    m_meminfo.setLocation(0);
    m_meminfo.setSize((numParms() + 2) * -1);
    MemoryInfo::enterScope();
    MemoryInfo::addReturnTicket();

    for (auto *parm = parms(); parm != nullptr;
         parm = parm->sibling()->cast<Parm *>()) {
        parm->calculateMemory();
    }

    auto *stmt = compoundStmt();
    if (stmt) {
        stmt->calculateMemory();
    }
    MemoryInfo::exitScope();
}

bool Func::hasParms() const { return parms() != nullptr; }

Parm *Func::parms() const { return getChild(0)->cast<Parm *>(); }

Stmt::Compound *Func::compoundStmt() const {
    return getChild(1)->cast<Stmt::Compound *>();
}

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