#include "Const.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"

#include <string>
#include <variant>

namespace AST::Exp
{
    Const::Const()
        : Node::Node()
    {
    }

    Const::Const(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    Const::Const(unsigned linenum, Type type, std::string value)
        : Node::Node(linenum),
          m_type(type)
    {
        switch (m_type)
        {
        case Type::String:
        {
            m_value = strutil::remove_quotes(value);
            break;
        }
        case Type::Bool:
        {
            m_value = (value == "true");
            break;
        }
        case Type::Char:
        {
            m_value = strutil::make_char(strutil::remove_quotes(value), m_linenum);
            break;
        };
        case Type::Int:
        {
            m_value = std::atoi(value.c_str());
            break;
        }
        };
    }

    std::string Const::toString() const
    {
        std::string str = "Const ";

        switch (m_type)
        {
        case Type::Int:
        {
            str += std::to_string(std::get<int>(m_value));
            break;
        }
        case Type::Bool:
        {
            if (std::get<bool>(m_value))
            {
                str += "true";
            }
            else
            {
                str += "false";
            }
            break;
        }
        case Type::Char:
        {
            str += "'" + std::string(1, std::get<char>(m_value)) + "'";
            break;
        }
        case Type::String:
        {
            str += "\"" + std::get<std::string>(m_value) + "\"";
            break;
        }
        default:
        {
            str += std::get<std::string>(m_value);
            break;
        }
        };

        str += lineTag();
        return str;
    }
}