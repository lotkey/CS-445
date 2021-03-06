#include "Return.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    Return::Return()
        : Stmt::Stmt()
    {
        m_type = Type::Return;
    }

    Return::Return(unsigned linenum)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::Return;
    }

    Return::Return(unsigned linenum, Node *exp)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::Return;
        addChild(exp);
    }
}