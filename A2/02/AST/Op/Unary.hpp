#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Op
{
    class Unary : public Node
    {
    public:
        enum class Type
        {
            Inc,
            Dec,
            Chsign,
            Sizeof,
            Random,
            Not
        };

        Unary();
        Unary(unsigned);
        Unary(unsigned, Type, Node *exp = nullptr);
        void addExp(Node *);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}