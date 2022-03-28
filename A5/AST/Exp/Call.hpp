#pragma once

#include "../Node.hpp"
#include "Exp.hpp"

#include <string>
#include <vector>

namespace AST::Exp {
/// Function call node
class Call : public Exp {
  public:
    Call();
    /// @param linenum Line number the node appears on
    Call(int linenum);
    /// @param linenum Line number the node appears on
    /// @param id String identifier of the function
    /// @param arglist Optional, argument list for function call
    Call(int linenum, const std::string &id, Node *arglist = nullptr);

    const std::string &id() const;
    Exp* arglist() const;
    int numArgs() const;
    std::vector<Exp*> argsVector() const;

    virtual std::string toString(bool debugging = false) const override;

  protected:
    std::string m_id;
};
} // namespace AST::Exp