#include "Binary.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"

#include <iostream>
#include <map>
#include <string>

namespace AST::Exp::Op {
Binary::Binary() : Op::Op() { m_opType = OpType::Binary; }

Binary::Binary(int linenum) : Op::Op(linenum, OpType::Binary) {}

Binary::Binary(int linenum, BinaryOpType opType, Node *exp1, Node *exp2)
    : Op::Op(linenum, OpType::Binary), m_binaryOpType(opType) {
    addChild(exp1);
    addChild(exp2);
}

void Binary::addChildren(Node *exp1, Node *exp2) {
    if (m_children.size() >= 1) {
        if (getChild(0) != nullptr && exp1 != nullptr) {
            throw std::runtime_error(
                "Binary operator already has a first child!");
        } else if (getChild(0) == nullptr) {
            setChild(0, exp1);
        }
    } else {
        addChild(exp1);
    }

    if (m_children.size() >= 2) {
        if (getChild(1) != nullptr && exp2 != nullptr) {
            throw std::runtime_error(
                "Binary operator already has a second child!");
        } else if (getChild(1) == nullptr) {
            setChild(1, exp2);
        }
    } else {
        addChild(exp2);
    }
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
    if (exp1() != nullptr && exp1()->is(ExpType::Op)) {
        exp1()->cast<Op *>()->deduceType();
    }

    if (exp2() != nullptr && exp2()->is(ExpType::Op)) {
        exp2()->cast<Op *>()->deduceType();
    }

    if (m_binaryOpType == BinaryOpType::Add ||
        m_binaryOpType == BinaryOpType::Div ||
        m_binaryOpType == BinaryOpType::Mod ||
        m_binaryOpType == BinaryOpType::Mul ||
        m_binaryOpType == BinaryOpType::Subtract) {
        setType(Type::Int);

        setIsConst(exp1() != nullptr && exp2() != nullptr &&
                   exp1()->isConst() && exp2()->isConst());
    } else {
        switch (m_binaryOpType) {
        case BinaryOpType::Asgn: {
            if (exp1() != nullptr && exp1()->hasType()) {
                setType(exp1()->type());
            }
            break;
        }
        case BinaryOpType::Bool: {
            setType(Type::Bool);
            setIsConst(exp1() != nullptr && exp2() != nullptr &&
                       exp1()->isConst() && exp2()->isConst());
            break;
        }
        case BinaryOpType::Index: {
            if (exp1() != nullptr && exp1()->hasType()) {
                setType(exp1()->type());
            }
            break;
        }
        }
    }
}

Exp *Binary::exp1() const { return getChild(0)->cast<Exp *>(); }

Exp *Binary::exp2() const { return getChild(1)->cast<Exp *>(); }

bool Binary::is(BinaryOpType t) const {
    return this != nullptr && m_binaryOpType == t;
}
} // namespace AST::Exp::Op