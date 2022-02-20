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
}

void Asgn::addChildren(Node *exp1, Node *exp2) {
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

    m_mutable = (Id *)exp1;
    m_exp = (Exp *)exp2;
}

std::string Asgn::toString() const {
    return "Assign: " + Types::toString(m_asgnType) + lineTag();
}
} // namespace AST::Exp::Op