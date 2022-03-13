#include "Exp.hpp"

namespace AST::Exp {
Exp::Exp() : TypedNode::TypedNode() { m_nodeType = NodeType::Exp; }

Exp::Exp(unsigned linenum) : TypedNode::TypedNode(linenum, NodeType::Exp) {}

Exp::Exp(unsigned linenum, ExpType expType)
    : TypedNode::TypedNode(linenum, NodeType::Exp), m_expType(expType) {}

const ExpType &Exp::expType() const { return m_expType; }

std::string Exp::typeTag() const { return Types::toString(m_typeInfo); }

bool Exp::is(ExpType t) const { return this != nullptr && m_expType == t; }
} // namespace AST::Exp