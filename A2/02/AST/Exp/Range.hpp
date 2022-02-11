#pragma once

#include "../Node.hpp"

#include <string>

namespace AST::Exp
{
    class Range : public Node
    {
    public:
        Range();
        Range(unsigned);
        Range(unsigned, Node *, Node *, Node *by = nullptr);
        virtual std::string toString() const override;
    };
}