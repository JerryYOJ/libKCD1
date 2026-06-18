#pragma once

#include <cstdint>
#include "S_TimedFactionEvent.h"

// ===========================================================================
// wh::rpgmodule::S_TimedFactionEventPool  -  inline arena for the timed-event
// vector (embedded at C_Faction+0x1F0).
// ===========================================================================
// VERIFIED by the pool allocator sub_1811A724C: a single inline S_TimedFactionEvent
// slot served before heap fallback, plus a used flag. The flag byte is zeroed by the
// C_Faction ctor sub_18118D490 (writes 0 to C_Faction+0x230 == pool+0x40).
namespace wh::rpgmodule {

struct S_TimedFactionEventPool {
    S_TimedFactionEvent m_slot;        // +0x00  inline storage for one timed event
    bool                m_slotUsed;    // +0x40  slot-occupied flag
    uint8_t             _pad41[7];     // +0x41  align to 0x48
};
static_assert(sizeof(S_TimedFactionEventPool) == 0x48, "timed-event pool arena");

}  // namespace wh::rpgmodule
