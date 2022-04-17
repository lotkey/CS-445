#include "For.hpp"
#include "../Exp/Id.hpp"
#include "../Node.hpp"
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
    m_meminfo.setLocation(0);
    Node::calculateMemory();
    auto *iterator = id();
    if (!iterator || !iterator->memInfo().locationSet()) {
        return;
    }
    iterator->calculateMemory();
    m_meminfo.setSize(iterator->memInfo().getLocation() - 1);
}
} // namespace AST::Stmt