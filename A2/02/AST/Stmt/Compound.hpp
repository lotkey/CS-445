#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    class Compound : public Stmt
    {
    public:
        Compound();
        Compound(unsigned);
        Compound(unsigned, Node *, Node *);
    };
}