#include "TypedNode.hpp"
#include "Node.hpp"
#include "Types.hpp"

namespace AST {
TypedNode::TypedNode() : Node::Node() {}

TypedNode::TypedNode(unsigned linenum) : Node::Node(linenum) {}

TypedNode::TypedNode(unsigned linenum, NodeType nodeType)
    : Node::Node(linenum, nodeType) {}

bool TypedNode::isConst() const { return m_typeInfo.isConst; }

bool &TypedNode::isConst() { return m_typeInfo.isConst; }

bool TypedNode::isArray() const { return m_typeInfo.isArray; }

bool &TypedNode::isArray() { return m_typeInfo.isArray; }

bool TypedNode::isStatic() const { return m_typeInfo.isStatic; }

bool &TypedNode::isStatic() { return m_typeInfo.isStatic; }

bool TypedNode::hasType() const { return m_typeInfo.type.has_value(); }

Type TypedNode::type() const { return m_typeInfo.type.value(); }

void TypedNode::setType(Type t) { m_typeInfo.type = t; }

TypeInfo TypedNode::getTypeInfo() const { return m_typeInfo; }

void TypedNode::setTypeInfo(TypeInfo ti) { m_typeInfo = ti; }
} // namespace AST