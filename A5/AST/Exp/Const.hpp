#pragma once

#include "../Node.hpp"
#include "Exp.hpp"

#include <variant>

namespace AST::Exp {
/// Node for constants
class Const : public Exp {
  public:
    Const();
    /// @param linenum Line number the node appears on
    Const(int linenum);
    /// @param linenum Line number the node appears on
    /// @param Type Type of the constant
    /// @param data String value of the data
    Const(int linenum, TypeInfo typeInfo, std::string data);
    
    virtual std::string toString(bool debugging = false) const override;
    std::string inputString() const;

  protected:
    std::variant<int, bool, char, std::string> m_value;
    std::string m_string;
};
} // namespace AST::Exp