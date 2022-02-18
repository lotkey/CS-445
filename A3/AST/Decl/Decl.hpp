#pragma once

#include "../Node.hpp"

#include <map>
#include <optional>
#include <string>

/// Namespace for declaration nodes
namespace AST::Decl
{
    static const std::map<Type, std::string> s_typeToString = {{Type::Bool, "bool"},
                                                               {Type::Char, "char"},
                                                               {Type::Int, "int"}};

    /// Base declaration node
    class Decl : public Node
    {
    public:
        Decl();
        /// @param linenum Line number the node appears on
        Decl(unsigned linenum);
        /// Set the node and its sibling's types to the provided type
        /// @param type Type to set
        virtual void setType(Type type);

    protected:
        TypeInfo m_typeInfo;
        std::string m_id;
    };
}