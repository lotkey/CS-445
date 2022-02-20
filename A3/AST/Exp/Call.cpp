#include "Call.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
Call::Call() : Exp::Exp() { m_expType = ExpType::Call; }

Call::Call(unsigned linenum) : Exp::Exp(linenum, ExpType::Call) {}

Call::Call(unsigned linenum, const std::string &id, Node *arglist)
    : Exp::Exp(linenum, ExpType::Call), m_id(id) {
    addChild(arglist);
    m_arglist = (Exp *)arglist;
}

const std::string &Call::id() const { return m_id; }

std::string Call::toString() const { return "Call: " + m_id + lineTag(); }
} // namespace AST::Exp