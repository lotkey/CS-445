#include "Stmt.hpp"
#include "../Node.hpp"
#include "../Types.hpp"

#include <map>
#include <string>

namespace AST::Stmt {

Stmt::Stmt() : Node::Node() { m_nodeType = AST::NodeType::Stmt; }

Stmt::Stmt(int linenum) : Node::Node(linenum, AST::NodeType::Stmt) {}

Stmt::Stmt(int linenum, StmtType stmtType)
    : Node::Node(linenum, AST::NodeType::Stmt) {
    m_stmtType = stmtType;
}

const StmtType &Stmt::stmtType() const { return m_stmtType; }

std::string Stmt::toString() const {
    return Types::toString(m_stmtType);
}

bool Stmt::is(StmtType t) const { return this && m_stmtType == t; }
} // namespace AST::Stmt