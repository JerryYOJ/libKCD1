#pragma once
#include <cstdint>
#include "E_ModifierOp.h"

namespace wh::rpgmodule {

class C_BuffInstanceBase;
class C_Soul;

// A single stat modifier node. Buffs own linked lists of these, one per modifier category.
// Allocated from pool allocator at sub_1803D62EC (stride 0x40).
//
// Lifecycle:
//   1. Created by DispatchModifier (sub_1802AD9B0) during Init, placed in staging list
//   2. CommitModifiers moves from staging into C_Soul's sorted main lists
//   3. GetModifiedStatValue (sub_180229880) walks main list applying each node
//   4. Terminate deactivates all nodes and unlinks them
//
// CreateModifierNode: sub_1802AD1E0
// ApplyModifier:      sub_180229BD0
// GetEffectiveness:   sub_180229C60
struct S_ModifierNode {
    C_BuffInstanceBase* pOwner;         // +0x00  owning buff instance
    C_Soul*             pSoul;          // +0x08  associated soul (set during CommitModifiers)
    uint8_t             bActive;        // +0x10  1 = active, 0 = deactivated
    uint8_t             bTimeBased;     // +0x11  has time-based effectiveness callback
    uint8_t             bNonWearing;    // +0x12  true when buff_lifetime_id == 0
    uint8_t             bExtraFlag;     // +0x13  from modifier descriptor
    uint8_t             _pad14[4];      // +0x14
    S_ModifierNode*     pNextStaging;   // +0x18  next in staging linked list (pre-commit)
    S_ModifierNode*     pNextSorted;    // +0x20  next in main sorted linked list (on soul)
    int32_t             nTargetId;      // +0x28  stat/skill/derived ID this modifier targets
    E_ModifierOp        eOp;            // +0x2C  operation type (also used as sort key)
    float               fValue;         // +0x30  current modifier value
    float               fOrigValue;     // +0x34  original/base modifier value
    int32_t             nExtra;         // +0x38  extra data (movement bool for perk mods)
    uint8_t             bSpecialFlag;   // +0x3C  used by perk movement modifiers
    uint8_t             _pad3D[3];      // +0x3D
};
static_assert(sizeof(S_ModifierNode) == 0x40);

}  // namespace wh::rpgmodule
