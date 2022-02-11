#include "Var.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl
{
    Var::Var()
        : Decl::Decl()
    {
    }

    Var::Var(unsigned linenum)
        : Decl::Decl(linenum)
    {
    }

    Var::Var(unsigned linenum, const std::string &id, bool isArray)
        : Decl::Decl(linenum),
          m_isArray(isArray)
    {
        m_id = id;
    }

    void Var::setStatic()
    {
        m_isStatic = true;
    }

    std::string Var::toString() const
    {
        std::string str = "Var: " + m_id;
        if (m_isArray)
        {
            str += " of array";
        }
        str += " of type " + s_typeToString.at(m_type.value()) + lineTag();
        return str;
    }
}