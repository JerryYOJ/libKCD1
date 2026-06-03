#pragma once

#include <cstdint>
#include "../framework/WUID.h"
#include "../framework/I_WUIDMappingProvider.h"

// ===========================================================================
// wh::entitymodule::C_ItemManager  -  the Item (tag 2) WUID registry.
//
// RTTI .?AVC_ItemManager@entitymodule@wh@@. Single base I_WUIDMappingProvider (vtable +0x00).
// ctor sub_18107F354 (operator new(0x2A1E88), from the C_EntityModule ctor sub_18103F5B0);
// the global qword_183785918. vtable — resolved:
//     [0] GetWuidForKey  sub_18108BB9C        [1] GetValueForWuid sub_18108BB5C (-> sub_180454638)
//     [2] ~C_ItemManager sub_181081EA0 (body sub_181080C84)
//
// The WUID slot table is a sub-object at +0x18 (the forward map does sub_180454638(this+0x18,
// &wuid)), so slots begin at +0x40. 17-bit slot, wider 0x18-byte slot (S_ItemSlot). A C_Item
// stores its own WUID at +0x08 (the lookup validates item+0x08 == wuid; slot guard
// sub_18045469C; insert sub_1804535E0, live count @+0x2A1DB0).
// ===========================================================================

namespace wh { namespace entitymodule {

class C_Item;

// One slot of the item registry's table (gen @+0x00, item @+0x10; stride 0x18).
struct S_ItemSlot {
    uint16_t generation;        // +0x00  must match (WUID >> 0x11) & 0xFFFF
    uint8_t  _pad02[0x0E];      // +0x02  extra per-slot data  [not fully RE'd]
    C_Item*  pItem;             // +0x10
};
static_assert(sizeof(S_ItemSlot) == 0x18);

class C_ItemManager : public wh::framework::I_WUIDMappingProvider {     // +0x00 vtable
public:
    // engine-function forwarder (impl in RE/src/entitymodule/C_ItemManager.cpp)
    C_Item* LookupByWUID(wh::framework::WUID w) const;                 // sub_180454638(this+0x18, &w)
    // (vtable slot [2] is the virtual dtor sub_181081EA0 — not declared here; the class is
    //  abstract via the two inherited I_WUIDMappingProvider pure virtuals.)

    uint64_t   m_unk08;                     // +0x08
    uint64_t   m_unk10;                     // +0x10
    uint64_t   _slotMapHeader[5];           // +0x18  slot-table sub-object header (cursors + free-list vector)
    S_ItemSlot m_slots[0x1C13A];            // +0x40  indexed by WUID::slot() (17 bits); ends +0x2A1DB0
    // --- post-array fields (ctor sub_18107F354; insert sub_1804535E0) ---
    uint8_t    _tail2A1DB0[0x58];           // +0x2A1DB0 (live count @+0x2A1DB0; 1.0f @+0x2A1E00)
    void*      m_pItemDatabase;             // +0x2A1E08 (sub_18072FFE0)
    uint8_t    _tail2A1E10[0x78];           // +0x2A1E10 (0x7FFFFFFF @+0x2A1E80)
};
static_assert(sizeof(C_ItemManager) == 0x2A1E88);

}}  // namespace wh::entitymodule
