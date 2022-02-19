#include "Binary.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
const std::map<Binary::Type, std::string> Binary::s_typeToString = {
    {Type::Add, "+"},   {Type::And, "and"},   {Type::Div, "/"},
    {Type::EQ, "="},    {Type::GEQ, ">="},    {Type::GT, ">"},
    {Type::Index, "["}, {Type::LEQ, "<="},    {Type::LT, "<"},
    {Type::Mod, "%"},   {Type::Mul, "*"},     {Type::NEQ, "!="},
    {Type::Or, "or"},   {Type::Subtract, "-"}};

Binary::Binary() : Exp::Exp() {}

Binary::Binary(unsigned linenum) : Exp::Exp(linenum) {}

Binary::Binary(unsigned linenum, Type opType, Node *exp1, Node *exp2)
    : Exp::Exp(linenum), m_opType(opType) {
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
    return "Op: " + s_typeToString.at(m_opType) + lineTag();
}
} // namespace AST::Exp::Op