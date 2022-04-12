#pragma once

#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
/// Variable declaration node
class Var : public Decl {
  public:
    Var();
    /// @param linenum Line number the node appears on
    Var(int linenum);
    /// @param linenum Line number the node appears on
    /// @param id String identifier
    Var(int linenum, const std::string &id);
    /// @param linenum Line number the node appears on
    /// @param id String identifier
    /// @param arraySize Size of the array
    Var(int linenum, const std::string &id, int arraySize);

    bool isInitialized() const;
    Exp::Exp *initValue();
    /// Set the variable and its siblings to static
    void setIsStatic(bool) override;
    void setGlobal(bool);

    virtual void setType(Type) override;
    virtual std::string toString() const override;
};
} // namespace AST::Decl