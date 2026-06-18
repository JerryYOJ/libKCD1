#pragma once

#include <cstdint>
// CryStringT<char> is provided via the PCH (CryString.h) -- never included per-header.

namespace wh::xgenaimodule {

class C_Variable;   // heap value object (polymorphic); C_SingleVariable for scalar tags

// ===========================================================================
// wh::xgenaimodule::S_DynamicInfoCell
// ===========================================================================
// One (information-id, tag) -> value cell: the element type of the global dynamic-info
// store's value vector (C_DynamicInformationStore::m_cells). Holds a per-crime dynamic
// value that the *DynamicInformationValue BT nodes read/write -- e.g. "expiration",
// "expired", "responderCount", "author" -- keyed globally by the crime's canonical
// information id (== S_InformationRecord::informationId).
//
// Layout VERIFIED in IDA: save serializer sub_1815DC76C (writes +0x00 id, the tag
// StringHash at +0x08, then virtual-serializes +0x10 via vtbl+0xF8), cell reader
// sub_1815D4490, key packer sub_18112994C. Elements are sorted ascending by
// (m_infoId, then strcmp(m_tag)).
//
// m_tag is a wh::framework::StringHash, which is BYTE-IDENTICAL to CryStringT<char>:
// a single pointer to a refcounted buffer whose header is {nRefCount @-0xC, nLength
// @-0x8, nAllocSize @-0x4} (verified from the StringHash ctor sub_18028CEA4). It is a
// VIEW over the game's string -- only ever take a POINTER to a live cell; never
// value-copy or destruct an S_DynamicInfoCell (that would touch the game's refcounts).
// ===========================================================================
struct S_DynamicInfoCell {
    uint32_t          m_infoId;   // +0x00  == S_InformationRecord::informationId (the store key)
    uint32_t          _pad04;     // +0x04
    CryStringT<char>  m_tag;      // +0x08  tag name (content-compared); == wh::framework::StringHash
    C_Variable*       m_value;    // +0x10  value object (C_SingleVariable for scalar tags)
};
static_assert(sizeof(S_DynamicInfoCell) == 0x18);

}  // namespace wh::xgenaimodule
