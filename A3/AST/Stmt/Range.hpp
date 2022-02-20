#pragma once

#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
/// Range node
class Range : public Stmt {
  public:
    Range();
    /// @param linenum Line number the node appears on
    Range(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param from Beginning of range
    /// @param to End of range
    /// @param by Optional, amount to increment by
    Range(unsigned linenum, Node *from, Node *to, Node *by = nullptr);
};
} // namespace AST::Exp