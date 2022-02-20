#include "Select.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Select::Select() : Stmt::Stmt() { m_stmtType = StmtType::Select; }

Select::Select(unsigned linenum) : Stmt::Stmt(linenum, StmtType::Select) {}

Select::Select(unsigned linenum, Node *exp, Node *stmt1, Node *stmt2)
    : Stmt::Stmt(linenum, StmtType::Select) {
    addChild(exp);
    addChild(stmt1);
    addChild(stmt2);
}
} // namespace AST::Stmt