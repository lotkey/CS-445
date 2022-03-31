#include "Exp.hpp"

namespace AST::Exp {
Exp::Exp() : TypedNode::TypedNode() { m_nodeType = NodeType::Exp; }

Exp::Exp(int linenum) : TypedNode::TypedNode(linenum, NodeType::Exp) {}

Exp::Exp(int linenum, ExpType expType)
    : TypedNode::TypedNode(linenum, NodeType::Exp), m_expType(expType) {}

const ExpType &Exp::expType() const { return m_expType; }

std::string Exp::typeTag() const { return Types::toString(getTypeInfo()); }

bool Exp::is(ExpType t) const { return this && m_expType == t; }
} // namespace AST::Exp