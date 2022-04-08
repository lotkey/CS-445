#include "MemoryNode.hpp"

namespace AST {
void MemoryNode::setMemoryInfo(int loc, int size) {
    m_loc = loc;
    m_size = size;
}

void MemoryNode::setMemoryInfo(ReferenceType refType, int loc, int size) {
    m_refType = refType;
    m_loc = loc;
    m_size = size;
}

void MemoryNode::setReferenceType(ReferenceType refType) {
    m_refType = refType;
}

void MemoryNode::setLocation(int location) { m_loc = location; }

void MemoryNode::setSize(int size) { m_size = size; }

std::optional<ReferenceType> MemoryNode::getReferenceType() const {
    return m_refType;
}

int MemoryNode::getLocation() const { return m_loc; }

int MemoryNode::getSize() const { return m_size; }

std::string MemoryNode::memoryTag() const {
    return strutil::format("[mem: %s loc: %d size: %d]",
                           Types::toString(m_refType).c_str(), m_loc, m_size);
}

bool MemoryNode::hasMemoryInfo() const { return true; }
} // namespace AST