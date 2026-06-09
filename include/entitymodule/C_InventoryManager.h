#pragma once

#include <cstdint>
#include "../framework/WUID.h"
#include "../framework/S_WuidSlot.h"
#include "../framework/I_WUIDMappingProvider.h"
#include "I_InventoryListener.h"

// ===========================================================================
// wh::entitymodule::C_InventoryManager  -  the Inventory (tag 3) WUID registry.
//
// RTTI .?AVC_InventoryManager@entitymodule@wh@@. ctor sub_181056A28 (operator new(0x100120),
// from the C_EntityModule ctor sub_18103F5B0). Reached via *(*(S_GameContext+0xB0)+0x108);
// also the global qword_183785920.
//
// It is a BROADCAST HUB: as an I_InventoryListener it re-fires each inventory event to every
// listener registered in m_listeners; as an I_WUIDMappingProvider it answers WUID<->entity.
//   primary vtable (I_InventoryListener, +0x00) — resolved:
//     [0] OnItemAdded         sub_180452370   [1] OnItemRemoved        sub_180451B10
//     [2] OnItemAmountChanged sub_180451554   [3] OnItemAmountChanged2 sub_180450DD4
//     [4] ~C_InventoryManager sub_181058494 (body sub_181057800)
//   secondary vtable (I_WUIDMappingProvider, +0x08) — resolved:
//     [0] GetWuidForKey sub_1810653BC         [1] GetValueForWuid sub_181065380
//
// The WUID slot table is embedded at +0x10 (5-qword header + S_WuidSlot<C_Inventory>[0x10000]
// indexed by WUID::slot()). A C_Inventory stores its own WUID at +0x00 (the lookup
// sub_18055E7D8 validates *object == wuid).
// ===========================================================================

namespace wh { namespace entitymodule {

class C_Inventory;

class C_InventoryManager : public I_InventoryListener,                  // +0x00 vtable
                           public wh::framework::I_WUIDMappingProvider { // +0x08 vtable
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InventoryManager;
    // engine-function forwarder (impl in RE/src/entitymodule/C_InventoryManager.cpp)
    C_Inventory* LookupByWUID(wh::framework::WUID w) const;             // sub_18055E7D8(this+0x10, &w)

    uint64_t  _slotMapHeader[5];                              // +0x10     capacity / count / free-list
    wh::framework::S_WuidSlot<C_Inventory> m_slots[0x10000];  // +0x38     indexed by WUID::slot() (low 16)
    // --- post-array fields (ctor sub_181056A28) ---
    uint8_t   _gap100038[0x58];                               // +0x100038
    uint8_t   m_listeners[0x28];                              // +0x100090 std::vector<I_InventoryListener*> + re-entrancy
                                                              //           guard — the broadcast targets (init sub_18030DF94)
    float     m_unk1000B8;                                    // +0x1000B8 (1.0f; sub_18071265C inits 8 entries)
    uint8_t   _pad1000BC[4];                                  // +0x1000BC
    void*     m_pInventoryDatabase;                           // +0x1000C0 (sub_180255920)
    uint8_t   _tail1000C8[0x58];                              // +0x1000C8 (sub-obj @+0x1000F8)
};
static_assert(sizeof(C_InventoryManager) == 0x100120);

}}  // namespace wh::entitymodule
