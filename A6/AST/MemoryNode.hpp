#pragma once

#include "../strutil.hpp"
#include "Node.hpp"
#include "Types.hpp"

#include <optional>

namespace AST {
class MemoryNode : public virtual Node {
  public:
    void setMemoryInfo(int loc, int size);
    void setMemoryInfo(ReferenceType refType, int loc, int size);
    void setReferenceType(ReferenceType refType);
    void setLocation(int location);
    void setSize(int size);
    std::optional<ReferenceType> getReferenceType() const;
    int getLocation() const;
    int getSize() const;
    std::string memoryTag() const;

  protected:
    virtual bool hasMemoryInfo() const override;

  private:
    std::optional<ReferenceType> m_refType;
    int m_loc;
    int m_size;
};

} // namespace AST