#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    class Select : public Stmt
    {
    public:
        Select();
        Select(unsigned);
        Select(unsigned, Node *, Node *stmt1, Node *stmt2 = nullptr);
    };
}