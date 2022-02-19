#include "UnaryAsgn.hpp"
#include "../../Node.hpp"
#include "../Id.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
const std::map<UnaryAsgn::Type, std::string> UnaryAsgn::s_typeToString = {
    {Type::Dec, "--"}, {Type::Inc, "++"}};

UnaryAsgn::UnaryAsgn() : Exp::Exp() {}

UnaryAsgn::UnaryAsgn(unsigned linenum) : Exp::Exp(linenum) {}

UnaryAsgn::UnaryAsgn(unsigned linenum, Type opType, Node *exp)
    : Exp::Exp(linenum), m_opType(opType) {
    addChild(exp);
    m_mutable = (Id *)exp;
}

std::string UnaryAsgn::toString() const {
    return "Assign: " + s_typeToString.at(m_opType) + lineTag();
}
} // namespace AST::Exp::Op