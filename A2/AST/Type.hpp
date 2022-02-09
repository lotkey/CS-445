#pragma once

#include <string>
#include <variant>

namespace Type
{
    enum class Node : int
    {
        Declaration,
        Statement,
        Expression
    };

    enum class Declaration : int
    {
        Variable,
        Function,
        Parameter
    };

    enum class Statement : int
    {
        Select,
        Iterative,
        Expression,
        Compound,
        Return,
        Break
    };

    enum class Expression : int
    {
        Simple,
        Assign,
        Increment,
        Decrement,
        And,
        UnaryRelation,
        Sum
    };

    enum class Variable : int
    {
        Bool,
        Char,
        Int,
        String
    };

    struct VariableInfo
    {
        Variable type;
        bool isConst;
        bool isStatic;
        std::variant<bool, char, int, std::string> data;
    };
}