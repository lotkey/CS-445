#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt
{
    /// For loop node
    class For : public Stmt
    {
    public:
        For();
        /// @param linenum Line number the node appears on
        For(unsigned linenum);
        /// @param linenum Line number the node appears on
        /// @param id Iterator variable identifier
        /// @param range Iteration range
        /// @param stmt Loop body
        For(unsigned linenum, Node *id, Node *range, Node *stmt);
    };
}