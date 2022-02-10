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
        Assign,
        Break,
        Call,
        Compound,
        Expression,
        Iterative,
        Return,
        Select,
        While
    };

    enum class Expression : int
    {
        And,
        Constant,
        Decrement,
        Id,
        Increment,
        Operator,
        Or,
        Range,
        RelationalOperator,
        Simple,
        Sum,
        UnaryOperator
    };

    enum class ExpressionType : int
    {
        Void,
        Integer,
        Boolean,
        Char,
        CharInt,
        Equal,
        UndefinedType
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