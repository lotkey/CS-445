#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    class For : public Stmt
    {
    public:
        For();
        For(unsigned);
        For(unsigned, Node *id, Node *range, Node *stmt);
    };
}