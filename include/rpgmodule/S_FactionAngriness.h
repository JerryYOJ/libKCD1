#pragma once

#include <cstdint>
#include <vector>
#include "S_AngrinessContribution.h"
#include "S_AngrinessContributionPool.h"
#include "../framework/C_InlinePoolAllocator.h"

// ===========================================================================
// wh::rpgmodule::S_FactionAngriness  -  the angriness/morale sub-object embedded
// at C_Faction+0x18 (size 0x1D8).
// ===========================================================================
// VERIFIED: ctor sub_18118D524(this, owner) stores the owner back-ptr and zeroes the
// arena; m_value clamped [0,1] by SetAngriness sub_1811A4300; contributions pushed by
// sub_18118F188 (stride 0x18). The two contribution vectors are std::vectors using the
// inline-pool allocator (alloc ptr = &m_pool), so each is 0x20; their end/cap land at
// C_Faction+0x1C0/+0x1C8, matching the previously-verified offsets.
namespace wh::rpgmodule {

struct C_Faction;  // m_pOwner

struct S_FactionAngriness {
    // The contribution vectors draw from the inline m_pool (a stateful allocator -> 0x20 each).
    using ContributionVector =
        std::vector<S_AngrinessContribution,
                    wh::framework::C_InlinePoolAllocator<S_AngrinessContribution, S_AngrinessContributionPool>>;

    C_Faction*                  m_pOwner;               // +0x000  back-ptr to owning C_Faction (ctor sub_18118D524)
    float                       m_value;                // +0x008  angriness [0,1] (SetAngriness sub_1811A4300)
    uint8_t                     _pad00C[4];             // +0x00C
    S_AngrinessContributionPool m_pool;                 // +0x010  inline arena (0x188)
    ContributionVector          m_contributions;        // +0x198  active contributions (end/cap @ owner+0x1C0/+0x1C8)
    ContributionVector          m_contributionsScratch; // +0x1B8  second pool-backed vector [purpose INFERRED]
};
static_assert(sizeof(S_FactionAngriness) == 0x1D8, "faction angriness sub-object (ctor sub_18118D524)");

}  // namespace wh::rpgmodule
