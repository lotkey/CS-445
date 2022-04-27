#include "Decl.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"
#include "../TypedNode.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Decl::Decl() : TypedNode::TypedNode() { m_nodeType = NodeType::Decl; }

Decl::Decl(int linenum) : TypedNode::TypedNode(linenum, NodeType::Decl) {}

Decl::Decl(int linenum, DeclType declType)
    : TypedNode::TypedNode(linenum, NodeType::Decl) {
    m_declType = declType;
}

const DeclType &Decl::declType() const { return m_declType; }

const std::string &Decl::id() const { return m_id; }

bool Decl::is(DeclType t) const { return this && m_declType == t; }
} // namespace AST::Decl