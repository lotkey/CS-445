#include "MemoryInfo.hpp"

#include <iostream>
#include <vector>

namespace AST {
int MemoryInfo::s_globalOffset = 0;
std::vector<int> MemoryInfo::s_frameOffsets = {};

void MemoryInfo::enterScope() { s_frameOffsets.push_back(0); }

void MemoryInfo::exitScope() { s_frameOffsets.pop_back(); }

void MemoryInfo::addReturnTicket() { s_frameOffsets.back() -= 2; }

int MemoryInfo::globalOffset() { return s_globalOffset; }

int MemoryInfo::frameOffset() { return s_frameOffsets.back(); }

MemoryInfo::MemoryInfo() {}

void MemoryInfo::setReferenceType(const std::optional<ReferenceType> &refType) {
    m_refType = refType;
}

void MemoryInfo::setLocation(int location) { m_loc = location; }

void MemoryInfo::setSize(int size) { m_size = size; }

void MemoryInfo::calculateLocation() {
    if (m_loc.has_value()) {
        return;
    }

    if (!m_refType.has_value()) {
        m_loc = 0;
        return;
    }
    if (!m_size.has_value()) {
        throw std::runtime_error(
            "Cannot calculate location when the size is unknown.");
    }

    if (m_refType == ReferenceType::Global ||
        m_refType == ReferenceType::Static) {
        m_loc = s_globalOffset;
        s_globalOffset -= m_size.value();
    } else {
        m_loc = s_frameOffsets.back();
        s_frameOffsets.back() -= m_size.value();
    }
}

std::optional<ReferenceType> MemoryInfo::getReferenceType() const {
    return m_refType;
}

int MemoryInfo::getLocation() const { return m_loc.value(); }

int MemoryInfo::getSize() const { return m_size.value(); }

std::string MemoryInfo::tag() const {
    int loc = 0;
    int size = 0;

    if (m_loc.has_value()) {
        loc = m_loc.value();
    }
    if (m_size.has_value()) {
        size = m_size.value();
    }

    return strutil::format("[mem: %s loc: %d size: %d]",
                           Types::toString(m_refType).c_str(), loc, size);
}

bool MemoryInfo::isSet() const {
    return m_loc.has_value() || m_size.has_value();
}

bool MemoryInfo::locationSet() const { return m_loc.has_value(); }

bool MemoryInfo::sizeSet() const { return m_size.has_value(); }

bool MemoryInfo::reftypeSet() const { return m_refType.has_value(); }
} // namespace AST