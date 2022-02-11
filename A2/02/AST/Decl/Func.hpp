#pragma once

#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl
{
    class Func : public Decl
    {
    public:
        Func();
        Func(unsigned);
        Func(unsigned, const std::string &, Node *, Node *);
        Func(unsigned, Type, const std::string &, Node *, Node *);
        virtual std::string toString() const override;
    };
}