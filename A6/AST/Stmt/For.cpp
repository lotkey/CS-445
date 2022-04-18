#include "For.hpp"
#include "../Exp/Id.hpp"
#include "../Node.hpp"
#include "Compound.hpp"
#include "Range.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
For::For() : Stmt::Stmt() {
    m_stmtType = StmtType::For;
    m_meminfo.setReferenceType({});
}

For::For(int linenum) : Stmt::Stmt(linenum, StmtType::For) {
    m_meminfo.setReferenceType({});
}

For::For(int linenum, Decl::Var *id, Node *range, Node *stmt)
    : Stmt::Stmt(linenum, StmtType::For) {
    id->setIsStatic(false);

    addChild(id);
    addChild(range);
    addChild(stmt);
    m_meminfo.setReferenceType({});
}

Decl::Var *For::id() const { return getChild(0)->cast<Decl::Var *>(); }

Range *For::range() const { return getChild(1)->cast<Range *>(); }

Stmt *For::stmt() const { return getChild(2)->cast<Stmt *>(); }

void For::calculateMemory() {
    MemoryInfo::enterScope();
    m_meminfo.setLocation(0);

    if (stmt() && stmt()->is(AST::StmtType::Compound)) {
        if (id()) {
            id()->calculateMemory();
        }
        if (range()) {
            range()->calculateMemory();
        }

        auto *compoundStmt = stmt()->cast<Compound *>();
        if (compoundStmt->localdecls()) {
            compoundStmt->localdecls()->calculateMemory();
        }
        if (compoundStmt->stmtlist()) {
            compoundStmt->stmtlist()->calculateMemory();
        }
        compoundStmt->memInfo().setSize(MemoryInfo::frameOffset());
    } else {
        Node::calculateMemory();
    }

    auto *iterator = id();
    if (!iterator || !iterator->memInfo().locationSet()) {
        return;
    }
    m_meminfo.setSize(iterator->memInfo().getLocation() - 1);

    MemoryInfo::exitScope();
}
} // namespace AST::Stmt