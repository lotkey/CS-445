#pragma once

#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
/// Identifier node
class Id : public Exp {
  public:
    Id();
    /// @param linenum Line number the node appears on
    Id(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param id String identifier
    Id(unsigned linenum, const std::string &id);
    virtual std::string toString() const override;

  protected:
    std::string m_id;
};
} // namespace AST::Exp