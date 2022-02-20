#include "Range.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Range::Range() : Stmt::Stmt() { m_stmtType = StmtType::Range; }

Range::Range(unsigned linenum) : Stmt::Stmt(linenum, StmtType::Range) {}

Range::Range(unsigned linenum, Node *from, Node *to, Node *by)
    : Stmt::Stmt(linenum, StmtType::Range) {
    addChild(from);
    addChild(to);
    addChild(by);
}
} // namespace AST::Stmt