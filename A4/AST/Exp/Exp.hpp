#pragma once

#include "../Node.hpp"
#include "../TypedNode.hpp"

/// Namespace for expression nodes
namespace AST::Exp {

class Exp : public TypedNode {
  public:
    Exp();
    Exp(unsigned);
    Exp(unsigned, ExpType);

    const ExpType &expType() const;
    virtual bool is(ExpType) const override;

  protected:
    ExpType m_expType;

    virtual std::string typeTag() const override;
};
} // namespace AST::Exp