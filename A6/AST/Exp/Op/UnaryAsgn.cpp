#include "UnaryAsgn.hpp"
#include "../../../strutil.hpp"
#include "../../Node.hpp"
#include "../Id.hpp"
#include "Unary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
UnaryAsgn::UnaryAsgn() : Unary::Unary() { m_unaryOpType = UnaryOpType::Asgn; }

UnaryAsgn::UnaryAsgn(int linenum) : Unary::Unary(linenum, UnaryOpType::Asgn) {}

UnaryAsgn::UnaryAsgn(int linenum, UnaryAsgnType opType, Node *exp)
    : Unary::Unary(linenum, UnaryOpType::Asgn), m_unaryAsgnType(opType) {
    if (m_children.size() == 1 && getChild(0) == nullptr) {
        setChild(0, exp);
    } else {
        addChild(exp);
    }
}

UnaryAsgnType UnaryAsgn::unaryAsgnType() const { return m_unaryAsgnType; }

std::string UnaryAsgn::toString() const {
    return strutil::format("Assign: %s",
                           Types::toString(m_unaryAsgnType).c_str());
}

void UnaryAsgn::deduceType() {
    if (mutableExp() != nullptr) {
        setTypeInfo(mutableExp()->getTypeInfo());
    }
}

Exp *UnaryAsgn::mutableExp() const { return getChild(0)->cast<Exp *>(); }

bool UnaryAsgn::is(UnaryAsgnType t) const {
    return this && m_unaryAsgnType == t;
}
} // namespace AST::Exp::Op