#include "Compound.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    Compound::Compound()
        : Stmt::Stmt()
    {
        m_type = Type::Compound;
    }

    Compound::Compound(unsigned linenum)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::Compound;
    }

    Compound::Compound(unsigned linenum, Node *localdecls, Node *stmtlist)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::Compound;
        addChild(localdecls);
        addChild(stmtlist);
    }
}