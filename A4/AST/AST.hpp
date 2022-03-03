#pragma once

#include "Decl/include.hpp"
#include "Exp/include.hpp"
#include "Node.hpp"
#include "Stmt/include.hpp"
#include "Types.hpp"

/// Abstract Syntax Tree
namespace AST {
[[nodiscard]] Node *ioLibraryTree();
}