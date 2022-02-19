#pragma once

#include "../Node.hpp"

/// Namespace for expression nodes
namespace AST::Exp {
class Exp : public Node {
  public:
    Exp();
    Exp(unsigned);
    Exp(unsigned, TypeInfo);
    virtual void setType(TypeInfo);
    virtual const TypeInfo &typeInfo() const;

  protected:
    TypeInfo m_typeInfo;
};
} // namespace AST::Exp