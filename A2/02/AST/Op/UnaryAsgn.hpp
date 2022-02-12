#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Op
{
    class UnaryAsgn : public Node
    {
    public:
        enum class Type
        {
            Inc,
            Dec
        };

        UnaryAsgn();
        UnaryAsgn(unsigned);
        UnaryAsgn(unsigned, Type, Node *);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}