#include "Break.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    Break::Break()
        : Stmt::Stmt()
    {
        m_type = Type::Break;
    }

    Break::Break(unsigned linenum)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::Break;
    }
}