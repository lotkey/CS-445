#pragma once

#include "../Node.hpp"

#include <variant>

namespace AST::Exp
{
    class Const : public Node
    {
    public:
        Const();
        Const(unsigned);
        Const(unsigned, int);
        Const(unsigned, bool);
        Const(unsigned, char);
        Const(unsigned, const std::string &);
        virtual std::string toString() const override;

    protected:
        enum class Type
        {
            Int,
            Bool,
            Char,
            String
        };

        std::variant<int, bool, char, std::string> m_data;
        Type m_type;
    };
}