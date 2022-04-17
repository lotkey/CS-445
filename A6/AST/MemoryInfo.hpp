#pragma once

#include "../strutil.hpp"
#include "Types.hpp"

#include <optional>
#include <vector>

namespace AST {
class MemoryInfo {
  public:
    static void enterScope();
    static void exitScope();
    static void addReturnTicket();
    static int globalOffset();
    static int frameOffset();

    MemoryInfo();

    void setReferenceType(const std::optional<ReferenceType> &refType);
    void setLocation(int location);
    void calculateLocation();
    void setSize(int size);
    std::optional<ReferenceType> getReferenceType() const;
    int getLocation() const;
    int getSize() const;
    std::string tag() const;
    bool isSet() const;
    bool locationSet() const;
    bool sizeSet() const;
    bool reftypeSet() const;

  private:
    static int s_globalOffset;
    static std::vector<int> s_frameOffsets;

    std::optional<ReferenceType> m_refType;
    std::optional<int> m_loc;
    std::optional<int> m_size;
};

} // namespace AST