#pragma once

#include <cstdint>
#include "S_AngrinessContribution.h"

// ===========================================================================
// wh::rpgmodule::S_AngrinessContributionPool  -  inline arena for the angriness
// contribution vectors (embedded at S_FactionAngriness+0x10).
// ===========================================================================
// VERIFIED by the pool allocator sub_1811A7174 / free sub_1811A79E0: 16 inline
// S_AngrinessContribution slots (two 0xC0 blocks of 8) served before falling back
// to the heap, plus a used-slot bitmap. Zeroed by the angriness ctor sub_18118D524.
namespace wh::rpgmodule {

struct S_AngrinessContributionPool {
    S_AngrinessContribution m_slots[16];   // +0x000  inline storage (2 x 0xC0 blocks, 8 each)
    uint64_t                m_usedBitmap;  // +0x180  one bit per slot in use
};
static_assert(sizeof(S_AngrinessContributionPool) == 0x188, "angriness contribution pool arena");

}  // namespace wh::rpgmodule
