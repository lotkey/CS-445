#pragma once

#include "../Node.hpp"

#include <string>

namespace AST::Exp
{
    class Call : public Node
    {
    public:
        Call();
        Call(unsigned);
        Call(unsigned, const std::string &id, Node *arglist = nullptr);
        virtual std::string toString() const override;

    protected:
        std::string m_id;
    };
}