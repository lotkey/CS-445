#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Stmt
{
    enum class Type
    {
        Break,
        Compound,
        For,
        Return,
        Select,
        While
    };

    static const std::map<Type, std::string> s_typeToString = {{Type::Break, "Break"},
                                                               {Type::Compound, "Compound"},
                                                               {Type::For, "For"},
                                                               {Type::Return, "Return"},
                                                               {Type::Select, "If"},
                                                               {Type::While, "While"}};
    ;

    class Stmt : public Node
    {
    public:
        Stmt();
        Stmt(unsigned);
        virtual std::string toString() const override;

    protected:
        Type m_type;
    };
}

#include "Break.hpp"
#include "Compound.hpp"
#include "For.hpp"
#include "Return.hpp"
#include "Select.hpp"
#include "While.hpp"