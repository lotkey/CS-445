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

Exp *Unary::operand() {
    if (m_children.empty()) {
        throw std::runtime_error("Unary operator has no operand.");
    }

    return (Exp *)m_children[0];
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
    switch (m_unaryOpType) {
    case UnaryOpType::Asgn: {
        // never reaches here, because deduceType is overloaded by UnaryAsgn
        break;
    }
    case UnaryOpType::Chsign: {
        m_typeInfo.type = Type::Int;
        break;
    }
    case UnaryOpType::Not: {
        m_typeInfo.type = Type::Bool;
        break;
    }
    case UnaryOpType::Random: {
        m_typeInfo.type = Type::Int;
        break;
    }
    case UnaryOpType::Sizeof: {
        m_typeInfo.type = Type::Int;
        break;
    }
    }
}
} // namespace AST::Exp::Op