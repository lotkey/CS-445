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
    m_exp1 = (Exp *)exp1;
    m_exp2 = (Exp *)exp2;
    deduceType();
}

void Binary::addChildren(Node *exp1, Node *exp2) {
    if (m_children.size() >= 1) {
        if (m_children[0] != nullptr && exp1 != nullptr) {
            throw std::runtime_error(
                "Binary operator already has a first child!");
        } else {
            m_children[0] = exp1;
            m_exp1 = (Exp *)exp1;
        }
    } else {
        m_children.push_back(exp1);
        m_exp1 = (Exp *)exp1;
    }

    if (m_children.size() >= 2) {
        if (m_children[1] != nullptr && exp2 != nullptr) {
            throw std::runtime_error(
                "Binary operator already has a second child!");
        } else {
            m_children[1] = exp2;
            m_exp2 = (Exp *)exp2;
        }
    } else {
        m_children.push_back(exp2);
        m_exp2 = (Exp *)exp2;
    }
    deduceType();
}

const BinaryOpType &Binary::binaryOpType() const { return m_binaryOpType; }

std::string Binary::toString(bool debugging) const {
    std::string str = "Op: " + Types::toString(m_binaryOpType);

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}

void Binary::deduceType() {
    if (m_binaryOpType == BinaryOpType::Add ||
        m_binaryOpType == BinaryOpType::Div ||
        m_binaryOpType == BinaryOpType::Mod ||
        m_binaryOpType == BinaryOpType::Mul ||
        m_binaryOpType == BinaryOpType::Subtract) {
        m_typeInfo.type = Type::Int;
    } else {
        switch (m_binaryOpType) {
        case BinaryOpType::Asgn: {
            if (m_exp1 != nullptr) {
                m_typeInfo.type = m_exp1->typeInfo().type;
            }
            break;
        }
        case BinaryOpType::Bool: {
            m_typeInfo.type = Type::Bool;
            break;
        }
        case BinaryOpType::Index: {
            if (m_exp1 != nullptr) {
                m_typeInfo.type = m_exp1->typeInfo().type;
            }
            break;
        }
        }
    }
}

Exp *Binary::exp1() { return m_exp1; }

Exp *Binary::exp2() { return m_exp2; }
} // namespace AST::Exp::Op