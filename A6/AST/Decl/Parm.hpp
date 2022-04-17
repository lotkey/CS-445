#pragma once

#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
/// Parameter declaration node
class Parm : public Decl {
  public:
    Parm();
    /// @param linenum Line number the node appears on
    Parm(int linenum);
    /// @param linenum Line number the node appears on
    /// @param id Parameter name
    /// @param isArray Whether or not the parameter is an array
    Parm(int linenum, const std::string &id, bool isArray);

    virtual void calculateMemory() override;

    virtual void setType(Type) override;
    virtual std::string toString() const override;
};
} // namespace AST::Decl