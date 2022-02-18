#include "Unary.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op
{
    const std::map<Unary::Type, std::string>
        Unary::s_typeToString = {{Type::Chsign, "chsign"},
                                 {Type::Not, "not"},
                                 {Type::Random, "?"},
                                 {Type::Sizeof, "sizeof"}};

    Unary::Unary()
        : Exp::Exp()
    {
    }

    Unary::Unary(unsigned linenum)
        : Exp::Exp(linenum)
    {
    }

    Unary::Unary(unsigned linenum, Type opType, Node *exp)
        : Exp::Exp(linenum),
          m_opType(opType)
    {
        addChild(exp);
    }

    void Unary::addExp(Node *exp)
    {
        if (m_children.size() > 0)
        {
            if (m_children[0] == nullptr)
            {
                m_children[0] = exp;
            }
            else
            {
                throw std::runtime_error("Unary operator cannot have more than one child.");
            }
        }
        else
        {
            addChild(exp);
        }
    }

    std::string Unary::toString() const
    {
        return "Op: " + s_typeToString.at(m_opType) + lineTag();
    }
}