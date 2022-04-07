#include "TypedNode.hpp"
#include "Node.hpp"
#include "Types.hpp"

namespace AST {
TypedNode::TypedNode() : Node::Node() {}

TypedNode::TypedNode(int linenum) : Node::Node(linenum) {}

TypedNode::TypedNode(int linenum, NodeType nodeType)
    : Node::Node(linenum, nodeType) {}

bool TypedNode::isConst() const { return m_typeInfo.isConst; }

void TypedNode::setIsConst(bool b) { m_typeInfo.isConst = b; }

bool TypedNode::isArray() const { return m_typeInfo.isArray; }

void TypedNode::setIsArray(bool b) { m_typeInfo.isArray = b; }

bool TypedNode::isStatic() const { return m_typeInfo.isStatic; }

void TypedNode::setIsStatic(bool b) { m_typeInfo.isStatic = b; }

bool TypedNode::hasType() const { return m_typeInfo.type.has_value(); }

Type TypedNode::type() const { return m_typeInfo.type.value(); }

bool TypedNode::isTyped() const { return true; }

std::optional<Type> TypedNode::typeOptional() const { return m_typeInfo.type; }

void TypedNode::setType(Type t) { m_typeInfo.type = t; }

TypeInfo TypedNode::getTypeInfo() const { return m_typeInfo; }

void TypedNode::setTypeInfo(TypeInfo ti) { m_typeInfo = ti; }

std::string TypedNode::typeTag() const {
    return Types::toString(getTypeInfo(), true, true);
}

} // namespace AST