#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Op
{
    class Asgn : public Node
    {
    public:
        enum class Type
        {
            Asgn,
            AddAsgn,
            SubAsgn,
            DivAsgn,
            MulAsgn
        };

        Asgn();
        Asgn(unsigned);
        Asgn(unsigned, Type, Node *exp1 = nullptr, Node *exp2 = nullptr);
        void addChildren(Node *, Node *);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}