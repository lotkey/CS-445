#pragma once

#include "AST/AST.hpp"

#include <memory>
#include <string>
#include <vector>

struct TokenData {
    /// Token class using the macros/enum (whatever it is, doesn't really
    /// matter) that is made for each of the tokens in the lex file.
    int tokenclass;
    /// Line number the token appeared on.
    unsigned linenum;
    /// Input string
    std::string tokenstr;
};