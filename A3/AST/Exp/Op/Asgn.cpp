#include "Asgn.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"
#include "../Id.hpp"
#include "Binary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
Asgn::Asgn() : Binary::Binary() { m_binaryOpType = BinaryOpType::Asgn; }

Asgn::Asgn(unsigned linenum) : Binary::Binary(linenum, BinaryOpType::Asgn) {}

Asgn::Asgn(unsigned linenum, AsgnType asgnType, Node *exp1, Node *exp2)
    : Binary::Binary(linenum, BinaryOpType::Asgn), m_asgnType(asgnType) {
    addChild(exp1);
    addChild(exp2);
    m_mutable = (Id *)exp1;
    m_exp = (Exp *)exp2;
    if (m_mutable != nullptr) {
        m_typeInfo = m_mutable->typeInfo();
    }
}

const AsgnType &Asgn::asgnType() const { return m_asgnType; }

std::string Asgn::toString(bool debugging) const {
    std::string str = "Assign: " + Types::toString(m_asgnType);

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}
} // namespace AST::Exp::Op