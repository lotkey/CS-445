#pragma once

#include "../../Node.hpp"
#include "../Exp.hpp"
#include "../Id.hpp"
#include "Binary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
/// Assignment node
class Asgn : public Binary {
  public:
    /// Assignment types

    Asgn();
    /// @param linenum Line number the node appears on
    Asgn(unsigned linenum);
    /// Children nodes are optional in the constructor, but they must be
    /// provided eventually! Use addChildren to add them later.
    /// @param linenum Line number the node appears on
    /// @param type Assignment type
    /// @param exp1 The assignee
    /// @param exp2 The expression assigned to exp1
    Asgn(unsigned linenum, AsgnType asgnType, Node *exp1 = nullptr,
         Node *exp2 = nullptr);
    /// @param exp1 The assignee
    /// @param exp2 The expression assigned to exp1
    void addChildren(Node *exp1, Node *exp2);
    virtual std::string toString() const override;

  protected:
    Id *m_mutable;
    Exp *m_exp;
    AsgnType m_asgnType;
};
} // namespace AST::Exp::Op