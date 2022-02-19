#include "Id.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
Id::Id() : Exp::Exp() {}

Id::Id(unsigned linenum) : Exp::Exp(linenum) {}

Id::Id(unsigned linenum, const std::string &id) : Exp::Exp(linenum), m_id(id) {}

std::string Id::toString() const { return "Id: " + m_id + lineTag(); }
} // namespace AST::Exp