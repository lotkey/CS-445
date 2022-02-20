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
} // namespace AST::Stmt