#include "Call.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
Call::Call() : Exp::Exp() {}

Call::Call(unsigned linenum) : Exp::Exp(linenum) {}

Call::Call(unsigned linenum, const std::string &id, Node *arglist)
    : Exp::Exp(linenum), m_id(id) {
    addChild(arglist);
    m_arglist = (Exp *)arglist;
}

std::string Call::toString() const { return "Call: " + m_id + lineTag(); }
} // namespace AST::Exp