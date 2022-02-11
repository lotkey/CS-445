#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    class While : public Stmt
    {
    public:
        While();
        While(unsigned);
        While(unsigned, Node *exp, Node *stmt);
    };
}