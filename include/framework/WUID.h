#pragma once

#include <cstdint>

// ===========================================================================
// wh::framework::WUID  -  World Unique ID (8-byte handle).
//
// RTTI: mangled as `UWUID@framework@wh@@` (a struct). Used pervasively as a
// stable handle for souls, items, inventories, entities, etc. — keys of
// std::unordered_set<WUID> (with std::hash<WUID>/equal_to<WUID>), C_Signal<WUID>,
// the soul/item registries, equipment slots, inventory owners.
//
// SIZE: 8 bytes (one uint64). Confirmed: the item-id std::unordered_set stores
// 8-byte elements; the item registry validates a single qword (`*(entry+8)==wuid`)
// and packs tag/generation/slot into one 64-bit value (see bit layout below).
// (Some owners store a 128-bit {WUID, extra} pair in their object, but the WUID
//  handle itself is the low 8 bytes.)
//
// BIT LAYOUT (VERIFIED from the registry lookup sub_180454638 + C_Soul ctor):
//   bits  0..16  (value & 0x1FFFF)        : slot index (max valid 0x1C137)
//   bits 17..55  (value >> 0x11)          : generation (uint16 read at +0x11)
//   bits 56..63  (HIBYTE)                 : TYPE TAG — 2 = item, 5 = soul, ...
//   A tag-2 (item) WUID with HIBYTE!=2 is rejected by the item-registry lookup.
// ===========================================================================

namespace wh { namespace framework {

struct WUID {
    uint64_t value;                                 // +0x00  packed {tag:8, generation:39, slot:17}

    constexpr uint32_t slot()       const { return (uint32_t)(value & 0x1FFFF); }
    constexpr uint16_t generation() const { return (uint16_t)(value >> 0x11); }
    constexpr uint8_t  tag()        const { return (uint8_t)(value >> 56); }

    constexpr bool operator==(const WUID& o) const { return value == o.value; }
    constexpr bool operator!=(const WUID& o) const { return value != o.value; }
};
static_assert(sizeof(WUID) == 0x08);

}}  // namespace wh::framework

// NOTE: the binary's std::unordered_set<WUID> uses std::hash<WUID>/equal_to<WUID>.
// The std::hash<WUID> specialization is provided by consumers that include <functional>
// (e.g. C_Inventory.h), to keep this handle header STL-free.
