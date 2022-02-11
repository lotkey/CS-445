#pragma once

#include "../Node.hpp"

#include <map>
#include <optional>
#include <string>

namespace AST::Decl
{
    enum class Type
    {
        Bool,
        Int,
        Char
    };

    static const std::map<Type, std::string> s_typeToString = {{Type::Bool, "bool"},
                                                               {Type::Char, "char"},
                                                               {Type::Int, "int"}};
    ;

    class Decl : public Node
    {
    public:
        Decl();
        Decl(unsigned);
        virtual void setType(Type);

    protected:
        std::optional<Type> m_type;
        std::string m_id;
    };
}

#include "Func.hpp"
#include "Parm.hpp"
#include "Var.hpp"