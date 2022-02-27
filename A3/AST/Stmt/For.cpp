#include "For.hpp"
#include "../Exp/Id.hpp"
#include "../Node.hpp"
#include "Range.hpp"
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

Exp::Id *For::id() const { return (Exp::Id *)getChild(0); }

Range *For::range() const { return (Range *)getChild(1); }

Stmt *For::stmt() const { return (Stmt *)getChild(2); }

} // namespace AST::Stmt