#include "Decl.hpp"
#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Decl::Decl() : Node::Node() { m_nodeType = NodeType::Decl; }

Decl::Decl(unsigned linenum) : Node::Node(linenum, NodeType::Decl) {}

Decl::Decl(unsigned linenum, DeclType declType)
    : Node::Node(linenum, NodeType::Decl) {
    m_declType = declType;
}

void Decl::setType(Type type) {
    m_typeInfo.type = type;
    if (m_sibling != nullptr) {
        ((Decl *)m_sibling)->setType(type);
    }
}

const std::string &Decl::id() const { return m_id; }
} // namespace AST::Decl