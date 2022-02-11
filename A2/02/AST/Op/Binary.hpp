#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Op
{
    class Binary : public Node
    {
    public:
        enum class Type
        {
            Mul,
            Div,
            Mod,
            Add,
            Subtract,
            LT,
            LEQ,
            GT,
            GEQ,
            EQ,
            NEQ,
            And,
            Or,
            Index
        };

        Binary();
        Binary(unsigned);
        Binary(unsigned, Type, Node *exp1 = nullptr, Node *exp2 = nullptr);
        void addChildren(Node *, Node *);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}