#include "Const.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>
#include <variant>

namespace AST::Exp {
Const::Const() : Exp::Exp() { setIsConst(true); }

Const::Const(unsigned linenum) : Exp::Exp(linenum, ExpType::Const) {
    setIsConst(true);
}

Const::Const(unsigned linenum, TypeInfo typeInfo, std::string value)
    : Exp::Exp(linenum, ExpType::Const) {
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
            break;
        } else {
            m_value =
                strutil::make_char(strutil::remove_quotes(value), m_linenum);
            break;
        }
    };
    case Type::Int: {
        m_value = std::atoi(value.c_str());
        break;
    }
    };
}

std::string Const::toString(bool debugging) const {
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
            str += "is array \"" + std::get<std::string>(m_value) +
                   "\" of type char";
            break;
        } else {
            str += "'" + std::string(1, std::get<char>(m_value)) + "'";
            break;
        }
    }
    default: {
        str += std::get<std::string>(m_value);
        break;
    }
    };

    if (debugging && !(type() == Type::Char && isArray())) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}
} // namespace AST::Exp