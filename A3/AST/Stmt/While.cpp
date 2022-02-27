#include "While.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
While::While() : Stmt::Stmt() { m_stmtType = StmtType::While; }

While::While(unsigned linenum) : Stmt::Stmt(linenum, StmtType::While) {}

While::While(unsigned linenum, Node *exp, Node *stmt)
    : Stmt::Stmt(linenum, StmtType::While) {
    addChild(exp);
    addChild(stmt);
}

Exp::Exp *While::exp() const { return (Exp::Exp *)getChild(0); }

Stmt *While::stmt() const { return (Stmt *)getChild(1); }
} // namespace AST::Stmt