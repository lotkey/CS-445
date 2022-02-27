#include "Range.hpp"
#include "../Exp/Exp.hpp"
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

Exp::Exp *Range::from() const { return (Exp::Exp *)getChild(0); }

Exp::Exp *Range::to() const { return (Exp::Exp *)getChild(1); }

Exp::Exp *Range::by() const { return (Exp::Exp *)getChild(2); }
} // namespace AST::Stmt