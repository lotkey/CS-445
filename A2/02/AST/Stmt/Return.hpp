#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    class Return : public Stmt
    {
    public:
        Return();
        Return(unsigned);
        Return(unsigned, Node *);
    };
}