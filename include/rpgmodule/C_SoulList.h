#pragma once

#include <cstdint>
#include "../framework/C_Signal.h"
#include "../databasemodule/I_DatabaseListener.h"
#include "../framework/I_WUIDMappingProvider.h"
#include "I_SoulResolver.h"

// -----------------------------------------------
// C_SoulList — WUID-to-soul lookup and management
// -----------------------------------------------
// RTTI: .?AVC_SoulList@rpgmodule@wh@@
// Constructor: sub_1811F1490
// Accessed via: *(C_RPGModule + 0x548)
// Soul lookup wrapper: sub_180284AE8(this, wuid)
// Soul lookup core:    sub_180284B04(this + 0x48, &wuid)
//
// WUID (World Unique ID) is a Warhorse-specific 64-bit persistent soul identifier,
// separate from CryEngine's transient entity IDs. Stored on entities as
// `entity.soul.__ThisWUID` in Lua.
//
// WUID format (64-bit):
//   HIBYTE  = 0x05 (soul type marker, validated by lookup)
//   WORD1   = generation counter (validated against slot)
//   LOWORD  = slot index into m_slots (0x0000–0xFFFF)
//
// Three vtables (multiple inheritance, from RTTI base class array):
//   +0x00: 0x1826d9fc0  I_SoulResolver@rpgmodule@wh        (primary — big vtable)
//   +0x08: 0x1826da080  I_WUIDMappingProvider@framework@wh (secondary — adjustor thunk)
//   +0x10: 0x1826da070  I_DatabaseListener@databasemodule@wh (secondary — adjustor thunk)
//
// Size: 0x1000F0 (confirmed: RPGModule ctor allocates exactly 0x1000F0)
//   Most of the size is the inline S_WUIDSlot[0x10000] array at +0x70.
//   LOWORD of WUID is 16-bit, so 65536 slots covers all possible indices.
//
// Constructor registers database listeners for:
//   "soul", "v_soul_character_data", "soul_slot2health",
//   "soul_slot2weapon_health", "v_soul2role_metarole"

namespace wh::rpgmodule {

class C_Soul;
class I_Soul;

// -----------------------------------------------
// S_WUIDSlot — one slot in the generation-counted lookup table
// -----------------------------------------------
struct S_WUIDSlot {
    uint16_t    generation;             // +0x00  generation counter (validated against WORD1 of WUID)
    uint8_t     _pad02[6];              // +0x02
    C_Soul*     pSoul;                  // +0x08  pointer to soul (nullptr if empty)
};
static_assert(sizeof(S_WUIDSlot) == 0x10);

// -----------------------------------------------
// S_SlotMapHeader — header before the slot array
// -----------------------------------------------
// Located at C_SoulList + 0x48. Passed as first arg to sub_180284B04.
// Slots begin at header + 0x28 (= C_SoulList + 0x70).
struct S_SlotMapHeader {
    uint64_t    _fields[5];             // +0x00  (capacity, count, free list, etc. — zeroed in ctor)
    // S_WUIDSlot slots[0x10000] follows immediately at +0x28
};

// -----------------------------------------------
// C_SoulList
// -----------------------------------------------
// Lookup algorithm (sub_180284B04, called with this+0x48):
//   1. HIBYTE(wuid) must be 0x05  (soul type marker)
//   2. LOWORD(wuid) must be nonzero
//   3. slots[LOWORD(wuid)].generation must match WORD1(wuid)
//   4. slots[LOWORD(wuid)].pSoul->wuid must match wuid
//   5. Returns soul pointer, or nullptr on any check failure
//
// NOTE: WUID != CryEngine entity ID. Entity ID (player.id) is CryEngine's
// transient runtime ID. WUID (player.soul.__ThisWUID) is Warhorse's persistent
// soul identifier. The soul lookup only works with WUIDs.

class C_SoulList : public I_SoulResolver,                        // vtable at +0x00 (primary)
                   public wh::framework::I_WUIDMappingProvider,  // vtable at +0x08
                   public wh::databasemodule::I_DatabaseListener // vtable at +0x10
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SoulList;
    // Signal fires when souls are added/removed
    // Type: C_Signal<I_Soul&, I_Soul&, E_AddRemove>
    wh::shared::C_Signal<I_Soul&, I_Soul&> m_soulChangedSignal;  // +0x18  (0x30 bytes)

    // Inline slot map — generation-counted entity lookup
    S_SlotMapHeader m_slotMapHeader;    // +0x48  (0x28 bytes header)
    S_WUIDSlot      m_slots[0x10000];   // +0x70  (0x100000 bytes — 65536 × 0x10)
    // End of slot array: +0x100070
    // +0x100068 is slots[0xFFFF].pSoul, not a post-slot field.

    // Post-slot-array fields (from constructor):
    uint64_t    m_unk100070;            // +0x100070
    uint64_t    m_unk100078;            // +0x100078
    uint64_t    m_unk100080;            // +0x100080
    uint32_t    m_unk100088;            // +0x100088  (zeroed)
    uint32_t    _pad10008C;             // +0x10008C
    float       m_unk100090;            // +0x100090  (init 1.0f, then sub_18071265C scales)
    uint32_t    _pad100094;             // +0x100094
    void*       m_pSoulDatabase;        // +0x100098  (from sub_180255920)
    uint64_t    m_unk1000A0;            // +0x1000A0
    uint64_t    m_unk1000A8;            // +0x1000A8
    uint64_t    m_unk1000B0;            // +0x1000B0
    uint64_t    m_unk1000B8;            // +0x1000B8
    // sub_18071265C writes more at +0x100090 range (8 entries)
    char        _pad1000C0[0x10];       // +0x1000C0
    uint32_t    m_unk1000D0;            // +0x1000D0  (zeroed)
    uint32_t    _pad1000D4;             // +0x1000D4
    uint64_t    m_unk1000D8;            // +0x1000D8
    uint64_t    m_unk1000E0;            // +0x1000E0
    uint64_t    m_unk1000E8;            // +0x1000E8
};
static_assert(sizeof(C_SoulList) == 0x1000F0);

}  // namespace wh::rpgmodule
