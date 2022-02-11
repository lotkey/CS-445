#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    class Break : public Stmt
    {
    public:
        Break();
        Break(unsigned);
    };
}