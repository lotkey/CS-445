#include "Bool.hpp"

namespace AST::Exp::Op::Bool {
Bool::Bool() : Binary::Binary() { m_binaryOpType = BinaryOpType::Bool; }

Bool::Bool(unsigned linenum) : Binary::Binary(linenum, BinaryOpType::Bool) {}

Bool::Bool(unsigned linenum, BoolOpType boolOpType)
    : Binary::Binary(linenum, BinaryOpType::Bool), m_boolOpType(boolOpType) {}

const BoolOpType &Bool::boolOpType() const { return m_boolOpType; }
} // namespace AST::Exp::Op::Bool