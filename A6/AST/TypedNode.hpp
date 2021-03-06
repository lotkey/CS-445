#pragma once

#include "Node.hpp"
#include "Types.hpp"

#include <optional>

namespace AST {
class TypedNode : public Node {
  public:
    TypedNode();
    TypedNode(int linenum);
    TypedNode(int linenum, NodeType nodeType);

    virtual bool isConst() const;
    virtual void setIsConst(bool);
    virtual bool isArray() const;
    virtual void setIsArray(bool);
    virtual bool isStatic() const;
    virtual void setIsStatic(bool);
    virtual bool hasType() const;
    virtual bool isTyped() const override;
    Type type() const;
    std::optional<Type> typeOptional() const;
    virtual void setType(Type);
    TypeInfo getTypeInfo() const;
    void setTypeInfo(TypeInfo);
    /// @returns The type tag to print for type debugging
    virtual std::string typeTag() const override;

  private:
    TypeInfo m_typeInfo;
};
} // namespace AST