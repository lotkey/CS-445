#include "While.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
While::While() : Stmt::Stmt() { m_type = Type::While; }

While::While(unsigned linenum) : Stmt::Stmt(linenum) { m_type = Type::While; }

While::While(unsigned linenum, Node *exp, Node *stmt) : Stmt::Stmt(linenum) {
    m_type = Type::While;
    addChild(exp);
    addChild(stmt);
}
} // namespace AST::Stmt