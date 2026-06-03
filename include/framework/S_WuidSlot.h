#pragma once

#include <cstdint>

namespace wh { namespace framework {

// Generic generation-counted slot used by the WUID slot-table registries (0x10 bytes; the
// object pointer at +0x08). The slot is live when generation == (uint16)(WUID >> 0x11) AND
// object != null AND the object's own stored WUID matches. rpgmodule::S_WUIDSlot (in
// C_SoulList.h) is the soul-typed equivalent — it predates this and is the same layout as
// S_WuidSlot<C_Soul>. (Used by entitymodule::C_InventoryManager; C_ItemManager uses a wider
// 0x18-byte slot, S_ItemSlot, declared with that class.)
template<class T>
struct S_WuidSlot {
    uint16_t generation;        // +0x00  must match (WUID >> 0x11) & 0xFFFF
    uint8_t  _pad02[6];         // +0x02
    T*       object;            // +0x08  null = empty
};

}}  // namespace wh::framework
