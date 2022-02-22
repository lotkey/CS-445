#include "Op.hpp"

namespace AST::Exp::Op {

Op::Op() : Exp::Exp() { m_expType = ExpType::Op; }

Op::Op(unsigned linenum) : Exp::Exp(linenum, ExpType::Op) {}

Op::Op(unsigned linenum, OpType opType)
    : Exp::Exp(linenum, ExpType::Op), m_opType(opType) {}

const OpType &Op::opType() const { return m_opType; }

void Op::deduceType() {}
} // namespace AST::Exp::Op