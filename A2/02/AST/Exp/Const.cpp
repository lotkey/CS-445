#include "Const.hpp"
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

    Const::Const(unsigned linenum, int data)
        : Node::Node(linenum),
          m_data(data),
          m_type(Type::Int)
    {
    }

    Const::Const(unsigned linenum, bool data)
        : Node::Node(linenum),
          m_data(data),
          m_type(Type::Bool)
    {
    }

    Const::Const(unsigned linenum, char data)
        : Node::Node(linenum),
          m_data(data),
          m_type(Type::Char)
    {
    }

    Const::Const(unsigned linenum, const std::string &data)
        : Node::Node(linenum),
          m_data(data),
          m_type(Type::String)
    {
    }

    std::string Const::toString() const
    {
        std::string str = "Const ";

        switch (m_type)
        {
        case Type::Int:
        {
            str += std::to_string(std::get<int>(m_data));
            break;
        }
        case Type::Bool:
        {
            if (std::get<bool>(m_data))
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
            str += "'" + std::string(1, std::get<char>(m_data)) + "'";
            break;
        }
        case Type::String:
        {
            str += "\"" + std::get<std::string>(m_data) + "\"";
            break;
        }
        default:
        {
            str += std::get<int>(m_data);
            break;
        }
        };

        str += lineTag();
        return str;
    }
}