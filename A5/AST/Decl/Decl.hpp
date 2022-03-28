#pragma once

#include "../Node.hpp"
#include "../TypedNode.hpp"

#include <map>
#include <optional>
#include <string>

/// Namespace for declaration nodes
namespace AST::Decl {

/// Base declaration node
class Decl : public TypedNode {
  public:
    Decl();
    /// @param linenum Line number the node appears on
    Decl(int linenum);
    Decl(int linenum, DeclType declType);

    const std::string &id() const;
    const DeclType &declType() const;

    virtual bool is(DeclType t) const override;
    /// Set the node and its sibling's types to the provided type
    /// @param type Type to set

  protected:
    DeclType m_declType;
    std::string m_id;

    virtual std::string typeTag() const override;
};
} // namespace AST::Decl