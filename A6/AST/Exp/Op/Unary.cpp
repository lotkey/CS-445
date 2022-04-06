#include "Unary.hpp"
#include "../../../strutil.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"
#include "Op.hpp"

#include <iostream>
#include <map>
#include <string>

namespace AST::Exp::Op {

Unary::Unary() : Op::Op() { m_opType = OpType::Unary; }

Unary::Unary(int linenum) : Op::Op(linenum, OpType::Unary) {}

Unary::Unary(int linenum, UnaryOpType opType, Node *exp)
    : Op::Op(linenum, OpType::Unary), m_unaryOpType(opType) {
    addChild(exp);
}

const UnaryOpType &Unary::unaryOpType() const { return m_unaryOpType; }

void Unary::addExp(Node *exp) {
    if (this == nullptr) {
        return;
    }

    if (exp == nullptr) {
        return;
    }

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
    if (debugging) {
        return strutil::format("Op: %s %s",
                               Types::toString(m_unaryOpType).c_str(),
                               typeTag().c_str());
    } else {
        return strutil::format("Op: %s",
                               Types::toString(m_unaryOpType).c_str());
    }
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
        setIsConst(operand() != nullptr && operand()->isConst());
        break;
    }
    case UnaryOpType::Not: {
        setType(Type::Bool);
        setIsConst(operand() != nullptr && operand()->isConst());
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

bool Unary::is(UnaryOpType t) const { return this && m_unaryOpType == t; }
} // namespace AST::Exp::Op