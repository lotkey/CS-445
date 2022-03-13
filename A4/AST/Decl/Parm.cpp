#include "Parm.hpp"
#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Parm::Parm() : Decl::Decl() { m_declType = DeclType::Parm; }

Parm::Parm(unsigned linenum) : Decl::Decl(linenum, DeclType::Parm) {}

Parm::Parm(unsigned linenum, const std::string &id, bool isArray)
    : Decl::Decl(linenum, DeclType::Parm) {
    setIsArray(isArray);
    m_id = id;
}

std::string Parm::toString(bool debugging) const {
    std::string str = "Parm: " + m_id;
    if (isArray()) {
        str += " is array";
    }
    str += " of type " + Types::toString(typeOptional()) + lineTag();
    return str;
}
} // namespace AST::Decl