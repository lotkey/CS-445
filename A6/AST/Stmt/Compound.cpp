#include "Compound.hpp"
#include "../Decl/Decl.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Compound::Compound() : Stmt::Stmt() {
    m_stmtType = StmtType::Compound;
    m_meminfo.setReferenceType({});
    m_meminfo.setLocation(0);
}

Compound::Compound(int linenum) : Stmt::Stmt(linenum, StmtType::Compound) {
    m_meminfo.setReferenceType({});
    m_meminfo.setLocation(0);
}

Compound::Compound(int linenum, Node *localdecls, Node *stmtlist)
    : Stmt::Stmt(linenum, StmtType::Compound) {
    addChild(localdecls);
    addChild(stmtlist);
    m_meminfo.setReferenceType({});
    m_meminfo.setLocation(0);
}

Decl::Decl *Compound::localdecls() const {
    return getChild(0)->cast<Decl::Decl *>();
}

Stmt *Compound::stmtlist() const { return getChild(1)->cast<Stmt *>(); }

void Compound::calculateMemory() {
    Node::calculateMemory();
    m_meminfo.setSize(MemoryInfo::frameOffset());
}
} // namespace AST::Stmt