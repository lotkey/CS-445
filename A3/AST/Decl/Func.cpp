#include "Func.hpp"
#include "../Node.hpp"
#include "../Stmt/Compound.hpp"
#include "Decl.hpp"
#include "Parm.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Func::Func() : Decl::Decl() {}

Func::Func(unsigned linenum) : Decl::Decl(linenum) {}

Func::Func(unsigned linenum, const std::string &id, Node *parms,
           Node *compoundstmt)
    : Decl::Decl(linenum) {
    m_typeInfo = {{}, false, false};
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
    m_parms = (Parm *)parms;
    m_compoundStmt = (Stmt::Compound *)compoundstmt;
}

Func::Func(unsigned linenum, Type returnType, const std::string &id,
           Node *parms, Node *compoundstmt)
    : Decl::Decl(linenum) {
    m_typeInfo = {returnType, false, false};
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
    m_parms = (Parm *)parms;
    m_compoundStmt = (Stmt::Compound *)compoundstmt;
}

std::string Func::toString() const {
    std::string str = "Func: " + m_id + " returns type ";

    if (m_typeInfo.type.has_value()) {
        str += s_typeToString.at(m_typeInfo.type.value());
    } else {
        str += "void";
    }

    str += lineTag();
    return str;
}
} // namespace AST::Decl