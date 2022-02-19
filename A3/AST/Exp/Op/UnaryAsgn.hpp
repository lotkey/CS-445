#pragma once

#include "../../Node.hpp"
#include "../Exp.hpp"
#include "../Id.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
/// Unary assignment operator
class UnaryAsgn : public Exp {
  public:
    /// Assignment type
    enum class Type { Inc, Dec };

    UnaryAsgn();
    /// @param linenum Line number the node appears on
    UnaryAsgn(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param opType Assignment type
    /// @param exp The node being assigned
    UnaryAsgn(unsigned linenum, Type opType, Node *exp);
    virtual std::string toString() const override;

  protected:
    static const std::map<Type, std::string> s_typeToString;

    Id *m_mutable;
    Type m_opType;
};
} // namespace AST::Exp::Op