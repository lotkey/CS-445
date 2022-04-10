#include "MemoryInfo.hpp"

namespace AST {
MemoryInfo::MemoryInfo() {}

void MemoryInfo::setReferenceType(const std::optional<ReferenceType> &refType) {
    m_set = true;
    m_refType = refType;
}

void MemoryInfo::setLocation(int location) {
    m_set = true;
    m_loc = location;
}

void MemoryInfo::setSize(int size) {
    m_set = true;
    m_size = size;
}

std::optional<ReferenceType> MemoryInfo::getReferenceType() const {
    return m_refType;
}

int MemoryInfo::getLocation() const { return m_loc; }

int MemoryInfo::getSize() const { return m_size; }

std::string MemoryInfo::tag() const {
    return strutil::format("[mem: %s loc: %d size: %d]",
                           Types::toString(m_refType).c_str(), m_loc, m_size);
}

bool MemoryInfo::isSet() const { return m_set; }
} // namespace AST