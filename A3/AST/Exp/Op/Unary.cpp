#include "Unary.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"
#include "Op.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {

Unary::Unary() : Op::Op() { m_opType = OpType::Unary; }

Unary::Unary(unsigned linenum) : Op::Op(linenum, OpType::Unary) {}

Unary::Unary(unsigned linenum, UnaryOpType opType, Node *exp)
    : Op::Op(linenum, OpType::Unary), m_unaryOpType(opType) {
    addChild(exp);
}

const UnaryOpType &Unary::unaryOpType() const { return m_unaryOpType; }

void Unary::addExp(Node *exp) {
    if (m_children.size() > 0) {
        if (m_children[0] == nullptr) {
            m_children[0] = exp;
        } else {
            throw std::runtime_error(
                "Unary operator cannot have more than one child.");
        }
    } else {
        addChild(exp);
    }
}

std::string Unary::toString() const {
    return "Op: " + Types::toString(m_unaryOpType) + lineTag();
}
} // namespace AST::Exp::Op