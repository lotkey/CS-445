#include "Call.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>
#include <vector>

namespace AST::Exp {
Call::Call() : Exp::Exp() { m_expType = ExpType::Call; }

Call::Call(int linenum) : Exp::Exp(linenum, ExpType::Call) {}

Call::Call(int linenum, const std::string &id, Node *arglist)
    : Exp::Exp(linenum, ExpType::Call), m_id(id) {
    addChild(arglist);
}

const std::string &Call::id() const { return m_id; }

std::string Call::toString(bool debugging) const {
    if (debugging) {
        return strutil::format("Call: %s %s", m_id.c_str(), typeTag().c_str());
    } else {
        return strutil::format("Call: %s", m_id.c_str());
    }
}

Exp *Call::arglist() const { return getChild(0)->cast<Exp *>(); }

int Call::numArgs() const {
    int counter = 0;
    Exp *arg = arglist();
    while (arg != nullptr) {
        counter++;
        arg = arg->sibling()->cast<Exp *>();
    }

    return counter;
}

std::vector<Exp *> Call::argsVector() const {
    std::vector<Exp *> v;
    auto *arg = arglist();
    while (arg != nullptr) {
        v.push_back(arg);
        arg = arg->sibling()->cast<Exp *>();
    }

    return v;
}
} // namespace AST::Exp