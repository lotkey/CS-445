#include "Stmt.hpp"
#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Stmt
{
    Stmt::Stmt()
        : Node::Node()
    {
    }

    Stmt::Stmt(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    std::string Stmt::toString() const
    {
        return s_typeToString.at(m_type) + lineTag();
    }
}