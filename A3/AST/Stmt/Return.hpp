#pragma once

#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
/// Function return statement node
class Return : public Stmt {
  public:
    Return();
    /// @param linenum Line number the node appears on
    Return(unsigned linenum);
    /// @param linenum Line number the node appears on
    Return(unsigned linenum, Node *exp);
    Exp::Exp *exp() const;
};
} // namespace AST::Stmt