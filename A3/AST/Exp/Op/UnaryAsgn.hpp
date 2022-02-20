#pragma once

#include "../../Node.hpp"
#include "../Exp.hpp"
#include "../Id.hpp"
#include "Unary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
/// Unary assignment operator
class UnaryAsgn : public Unary {
  public:
    /// Assignment type

    UnaryAsgn();
    /// @param linenum Line number the node appears on
    UnaryAsgn(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param opType Assignment type
    /// @param exp The node being assigned
    UnaryAsgn(unsigned linenum, UnaryAsgnType opType, Node *exp);
    virtual std::string toString() const override;

  protected:
    Id *m_mutable;
    UnaryAsgnType m_unaryAsgnType;
};
} // namespace AST::Exp::Op