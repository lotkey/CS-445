#include "Exp.hpp"

namespace AST::Exp {
Exp::Exp() : Node::Node() {}

Exp::Exp(unsigned linenum) : Node::Node(linenum) {}

Exp::Exp(unsigned linenum, TypeInfo typeInfo)
    : Node::Node(linenum), m_typeInfo(typeInfo) {}

void Exp::setType(TypeInfo typeInfo) { m_typeInfo = typeInfo; }

const TypeInfo &Exp::typeInfo() const { return m_typeInfo; }
} // namespace AST::Exp