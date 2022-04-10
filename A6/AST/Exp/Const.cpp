#include "Const.hpp"
#include "../../SemanticsChecker/Message.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <sstream>
#include <variant>

namespace AST::Exp {
Const::Const() : Exp::Exp() { setIsConst(true); }

Const::Const(int linenum) : Exp::Exp(linenum, ExpType::Const) {
    setIsConst(true);
}

Const::Const(int linenum, TypeInfo typeInfo, std::string value)
    : Exp::Exp(linenum, ExpType::Const), m_string(value) {
    setTypeInfo(typeInfo);
    setIsConst(true);
    switch (type()) {
    case Type::Bool: {
        m_value = (value == "true");
        break;
    }
    case Type::Char: {
        if (isArray()) {
            m_value = strutil::remove_quotes(value);
            m_value = strutil::make_str(std::get<std::string>(m_value));
            m_meminfo.setReferenceType(ReferenceType::Global);
            m_meminfo.setSize(std::get<std::string>(m_value).size() + 1);
            break;
        } else {
            int strlen = strutil::str_len(strutil::remove_quotes(value));
            if (strlen == 0) {
                Message::addSyntaxMessage(
                    m_linenum, Message::Type::Error,
                    "Empty character ''. Characters ignored.");
                m_value = strutil::make_char(strutil::remove_quotes(value));
            } else if (strlen > 1) {
                Message::addSyntaxMessage(
                    m_linenum, Message::Type::Warning,
                    "character is %d characters long and not a single "
                    "character: '%s'. The first char will be used.",
                    strutil::str_len(strutil::remove_quotes(value)),
                    value.c_str());
                m_value = ' ';
            } else {
                m_value = strutil::make_char(strutil::remove_quotes(value));
            }
            break;
        }
    };
    case Type::Int: {
        m_value = std::atoi(value.c_str());
        break;
    }
    };
}

std::string Const::inputString() const { return m_string; }

std::string Const::toString() const {
    std::string str = "Const ";

    switch (type()) {
    case Type::Int: {
        str += std::to_string(std::get<int>(m_value));
        break;
    }
    case Type::Bool: {
        if (std::get<bool>(m_value)) {
            str += "true";
        } else {
            str += "false";
        }
        break;
    }
    case Type::Char: {
        if (isArray()) {
            str += "\"" + std::get<std::string>(m_value) + "\"";
            break;
        } else {
            str += strutil::format("'%c'", std::get<char>(m_value));
            break;
        }
    }
    default: {
        str += std::get<std::string>(m_value);
        break;
    }
    };

    return str;
}
} // namespace AST::Exp