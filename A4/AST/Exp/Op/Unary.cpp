#include "Unary.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"
#include "Op.hpp"

#include <iostream>
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
        if (getChild(0) == nullptr) {
            setChild(0, exp);
        } else {
            throw std::runtime_error(
                "Unary operator cannot have more than one child.");
        }
    } else {
        addChild(exp);
    }
}

Exp *Unary::operand() const {
    if (m_children.empty()) {
        throw std::runtime_error("Unary operator has no operand.");
    }

    return getChild(0)->cast<Exp *>();
}

std::string Unary::toString(bool debugging) const {
    std::string str = "Op: " + Types::toString(m_unaryOpType);

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}

void Unary::deduceType() {

    if (operand() != nullptr && operand()->is(ExpType::Op)) {
        operand()->cast<Op *>()->deduceType();
    }

    switch (m_unaryOpType) {
    case UnaryOpType::Asgn: {
        // never reaches here, because deduceType is overloaded by UnaryAsgn
        break;
    }
    case UnaryOpType::Chsign: {
        setType(Type::Int);
        isConst() = operand() != nullptr && operand()->isConst();
        break;
    }
    case UnaryOpType::Not: {
        setType(Type::Bool);
        isConst() = operand() != nullptr && operand()->isConst();
        break;
    }
    case UnaryOpType::Random: {
        setType(Type::Int);
        break;
    }
    case UnaryOpType::Sizeof: {
        setType(Type::Int);
        break;
    }
    }
}

bool Unary::is(UnaryOpType t) const {
    return this != nullptr && m_unaryOpType == t;
}
} // namespace AST::Exp::Op