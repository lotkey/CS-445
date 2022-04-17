#pragma once

#include "Decl/include.hpp"
#include "Exp/include.hpp"
#include "MemoryInfo.hpp"
#include "Node.hpp"
#include "Stmt/include.hpp"
#include "TypedNode.hpp"
#include "Types.hpp"

/// Abstract Syntax Tree
namespace AST {
[[nodiscard]] Node *ioLibraryTree();
static constexpr int libraryLineNumber = -1;
} // namespace AST