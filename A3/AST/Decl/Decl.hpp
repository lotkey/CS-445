#pragma once

#include "../Node.hpp"

#include <map>
#include <optional>
#include <string>

/// Namespace for declaration nodes
namespace AST::Decl {

/// Base declaration node
class Decl : public Node {
  public:
    Decl();
    /// @param linenum Line number the node appears on
    Decl(unsigned linenum);
    Decl(unsigned linenum, DeclType declType);
    /// Set the node and its sibling's types to the provided type
    /// @param type Type to set
    virtual void setType(Type type);
    const std::string &id() const;
    const DeclType &declType() const;

  protected:
    DeclType m_declType;
    TypeInfo m_typeInfo;
    std::string m_id;
};
} // namespace AST::Decl