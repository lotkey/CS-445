#include "Const.hpp"
#include "../../SemanticsChecker/Message.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <sstream>
#include <variant>

namespace AST::Exp {
Const::Const() : Exp::Exp()
{
    setIsConst(true);
}

Const::Const(int linenum) : Exp::Exp(linenum, ExpType::Const)
{
    setIsConst(true);
}

Const::Const(int linenum, TypeInfo typeInfo, std::string value) :
      Exp::Exp(linenum, ExpType::Const), m_string(value)
{
    setTypeInfo(typeInfo);
    setIsConst(true);
    switch (type()) {
    case Type::Bool: {
        m_value.b = (value == "true");
        break;
    }
    case Type::Char: {
        if (isArray()) {
            m_value.s = strutil::remove_quotes(value);
            m_value.s = strutil::make_str(m_value.s);
            m_meminfo.setReferenceType(ReferenceType::Global);
            m_meminfo.setSize(m_value.s.size() + 1);
            m_meminfo.calculateLocation();
            m_meminfo.setLocation(m_meminfo.getLocation() - 1);
        } else {
            int strlen = strutil::str_len(strutil::remove_quotes(value));
            if (strlen == 0) {
                Message::addSyntaxMessage(
                    m_linenum,
                    Message::Type::Error,
                    "Empty character ''. Characters ignored.");
                m_value.c = strutil::make_char(strutil::remove_quotes(value));
            } else if (strlen > 1) {
                Message::addSyntaxMessage(
                    m_linenum,
                    Message::Type::Warning,
                    "character is %d characters long and not a single "
                    "character: '%s'. The first char will be used.",
                    strutil::str_len(strutil::remove_quotes(value)),
                    value.c_str());
                m_value.c = ' ';
            } else {
                m_value.c = strutil::make_char(strutil::remove_quotes(value));
            }
        }
        break;
    };
    case Type::Int: {
        m_value.i = std::atoi(value.c_str());
        break;
    }
    default: {
        throw std::runtime_error("No supplied type or samth");
        break;
    }
    };
}

std::string Const::inputString() const { return m_string; }

std::string Const::toString() const
{
    std::string str = "Const ";

    switch (type()) {
    case Type::Int: {
        str += std::to_string(m_value.i);
        break;
    }
    case Type::Bool: {
        str += (m_value.b) ? "true" : "false";
        break;
    }
    case Type::Char: {
        if (isArray()) {
            str += "\"" + m_value.s + "\"";
        } else {
            str += strutil::format("'%c'", m_value.c);
        }
        break;
    }
    default: {
        str += m_value.s;
        break;
    }
    };

    return str;
}

std::string Const::getTmString() const
{
    switch (type()) {
    case Type::Int: {
        return std::to_string(m_value.i);
    }
    case Type::Bool: {
        return (m_value.b) ? "1" : "0";
    }
    case Type::Char: {
        if (isArray()) {
            return "\"" + m_value.s + "\"";
        } else {
            return std::to_string((int)m_value.c);
        }
    }
    default: {
        return m_value.s;
    }
    };
}
} // namespace AST::Exp