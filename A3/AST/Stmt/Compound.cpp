#include "Compound.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Compound::Compound() : Stmt::Stmt() { m_stmtType = StmtType::Compound; }

Compound::Compound(unsigned linenum)
    : Stmt::Stmt(linenum, StmtType::Compound) {}

Compound::Compound(unsigned linenum, Node *localdecls, Node *stmtlist)
    : Stmt::Stmt(linenum, StmtType::Compound) {
    addChild(localdecls);
    addChild(stmtlist);
}
} // namespace AST::Stmt