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

    virtual bool alreadyIncludesTypeTag() const override;
    bool is(DeclType) const override;

  protected:
    DeclType m_declType;
    std::string m_id;
};
} // namespace AST::Decl