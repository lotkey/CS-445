#pragma once

#include "../strutil.hpp"
#include "Types.hpp"

#include <optional>

namespace AST {
class MemoryInfo {
  public:
    MemoryInfo();

    void setReferenceType(const std::optional<ReferenceType> &refType);
    void setLocation(int location);
    void setSize(int size);
    std::optional<ReferenceType> getReferenceType() const;
    int getLocation() const;
    int getSize() const;
    std::string tag() const;
    bool isSet() const;

  private:
    std::optional<ReferenceType> m_refType;
    int m_loc = 0;
    int m_size = 0;
    bool m_set = false;
};

} // namespace AST