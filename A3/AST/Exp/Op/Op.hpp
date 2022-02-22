#pragma once

#include "../Exp.hpp"

#include <map>

namespace AST::Exp::Op {

class Op : public Exp {
  public:
    Op();
    Op(unsigned linenum);
    Op(unsigned linenum, OpType opType);
    virtual void deduceType();
    const OpType &opType() const;

  protected:
    OpType m_opType;
};
} // namespace AST::Exp::Op