#include "Binary.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
Binary::Binary() : Op::Op() { m_opType = OpType::Binary; }

Binary::Binary(unsigned linenum) : Op::Op(linenum, OpType::Binary) {}

Binary::Binary(unsigned linenum, BinaryOpType opType, Node *exp1, Node *exp2)
    : Op::Op(linenum, OpType::Binary), m_binaryOpType(opType) {
    addChild(exp1);
    addChild(exp2);
}

void Binary::addChildren(Node *exp1, Node *exp2) {
    if (m_children.size() >= 1) {
        if (m_children[0] != nullptr && exp1 != nullptr) {
            throw std::runtime_error(
                "Binary operator already has a first child!");
        } else {
            m_children[0] = exp1;
        }
    } else {
        m_children.push_back(exp1);
    }

    if (m_children.size() >= 2) {
        if (m_children[1] != nullptr && exp2 != nullptr) {
            throw std::runtime_error(
                "Binary operator already has a second child!");
        } else {
            m_children[1] = exp2;
        }
    } else {
        m_children.push_back(exp2);
    }
}

std::string Binary::toString() const {
    return "Op: " + Types::toString(m_binaryOpType) + lineTag();
}
} // namespace AST::Exp::Op