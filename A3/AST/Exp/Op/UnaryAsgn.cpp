#include "UnaryAsgn.hpp"
#include "../../Node.hpp"
#include "../Id.hpp"
#include "Unary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
UnaryAsgn::UnaryAsgn() : Unary::Unary() { m_unaryOpType = UnaryOpType::Asgn; }

UnaryAsgn::UnaryAsgn(unsigned linenum)
    : Unary::Unary(linenum, UnaryOpType::Asgn) {}

UnaryAsgn::UnaryAsgn(unsigned linenum, UnaryAsgnType opType, Node *exp)
    : Unary::Unary(linenum, UnaryOpType::Asgn), m_unaryAsgnType(opType) {
    addChild(exp);
    m_mutable = (Id *)exp;
}

std::string UnaryAsgn::toString() const {
    return "Assign: " + Types::toString(m_unaryAsgnType) + lineTag();
}
} // namespace AST::Exp::Op