#pragma once

#include "../Decl/Decl.hpp"
#include "../Decl/Var.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
/// Identifier node
class Id : public Exp {
  public:
    Id();
    /// @param linenum Line number the node appears on
    Id(int linenum);
    /// @param linenum Line number the node appears on
    /// @param id String identifier
    Id(int linenum, const std::string& id);

    const std::string& id() const;
    void setIdOf(Decl::Decl*);
    Decl::Decl* decl();

    virtual std::string toString() const override;

  protected:
    std::string m_id;
    Decl::Decl* m_decl = nullptr;
};
} // namespace AST::Exp