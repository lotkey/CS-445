#include "For.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
For::For() : Stmt::Stmt() { m_stmtType = StmtType::For; }

For::For(unsigned linenum) : Stmt::Stmt(linenum, StmtType::For) {}

For::For(unsigned linenum, Node *id, Node *range, Node *stmt)
    : Stmt::Stmt(linenum, StmtType::For) {
    addChild(id);
    addChild(range);
    addChild(stmt);
}
Node *For::id() { return m_children[0]; }

Node *For::range() { return m_children[1]; }

Node *For::stmt() { return m_children[2]; }

} // namespace AST::Stmt