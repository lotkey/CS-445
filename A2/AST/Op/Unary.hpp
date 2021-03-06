#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Op
{
    /// Generic class for unary operator nodes
    /// "Generic" as in one-size-fits-all, not using generics or templates.
    class Unary : public Node
    {
    public:
        /// Unary operators
        enum class Type
        {
            Chsign,
            Sizeof,
            Random,
            Not
        };

        Unary();
        /// @param linenum
        Unary(unsigned linenum);
        /// exp is optional in this constructor, but must be provided eventually!
        /// Set later with addExp.
        /// @param linenum
        /// @param type Unary operator type
        /// @param exp Optional child expression
        Unary(unsigned linenum, Type type, Node *exp = nullptr);
        /// @param exp Child node
        void addExp(Node *exp);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}