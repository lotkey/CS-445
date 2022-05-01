#include "Id.hpp"
#include "../../strutil.hpp"
#include "../Decl/Var.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
Id::Id() : Exp::Exp() { m_expType = ExpType::Id; }

Id::Id(int linenum) : Exp::Exp(linenum, ExpType::Id) {}

Id::Id(int linenum, const std::string& id) :
      Exp::Exp(linenum, ExpType::Id), m_id(id)
{}

const std::string& Id::id() const { return m_id; }

std::string Id::toString() const
{
    return strutil::format("Id: %s", m_id.c_str());
}

void Id::setIdOf(Decl::Decl* decl)
{
    m_decl = decl;
    setTypeInfo(decl->getTypeInfo());
    m_meminfo = decl->memInfo();
}

Decl::Decl* Id::decl() { return m_decl->cast<Decl::Var*>(); }
} // namespace AST::Exp