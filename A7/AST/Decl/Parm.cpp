#include "Parm.hpp"
#include "../../strutil.hpp"
#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Parm::Parm() : Decl::Decl() {
    m_declType = DeclType::Parm;
    m_meminfo.setReferenceType(ReferenceType::Parameter);
    m_meminfo.setSize(1);
}

Parm::Parm(int linenum) : Decl::Decl(linenum, DeclType::Parm) {
    m_meminfo.setReferenceType(ReferenceType::Parameter);
    m_meminfo.setSize(1);
}

Parm::Parm(int linenum, const std::string &id, bool isArray)
    : Decl::Decl(linenum, DeclType::Parm) {
    setIsArray(isArray);
    m_id = id;
    m_meminfo.setReferenceType(ReferenceType::Parameter);
    m_meminfo.setSize(1);
}

std::string Parm::toString() const {
    return strutil::format("Parm: %s %s", m_id.c_str(),
                           Types::toString(getTypeInfo(), false, true).c_str());
}

void Parm::calculateMemory() {
    m_meminfo.calculateLocation();
    Node::calculateMemory();
}

void Parm::setType(Type t) {
    TypedNode::setType(t);
    if (hasSibling() && sibling()->is(DeclType::Parm)) {
        sibling()->cast<Parm *>()->setType(t);
    }
}
} // namespace AST::Decl