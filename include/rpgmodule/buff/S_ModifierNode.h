#pragma once
#include <cstdint>
#include "E_ModifierOp.h"
#include "E_BuffStat.h"                // E_SoulStat, E_MovementType, E_SoulLevel
#include "../E_ModifierCategory.h"
#include "../E_SoulSkill.h"
#include "../E_PerkStat.h"
#include "../E_DerivedStat.h"

namespace wh::rpgmodule {

class C_BuffInstanceBase;
class C_Soul;

// A single stat modifier node. Buffs own linked lists of these, one per modifier category.
// Allocated from pool allocator at sub_1803D62EC (stride 0x40).
//
// The node is templated on its modifier CATEGORY (E_ModifierCategory) and that category's
// target-id namespace T -- so nTargetId is strongly typed and a category's list is a
// homogeneous chain of one concrete instantiation. (In the binary all categories share the
// same 0x40 layout; the template only types nTargetId, which is a 4-byte int32-backed enum.)
//
// Lifecycle:
//   1. Created by DispatchModifier (sub_1802AD9B0) during Init, placed in staging list. That
//      function also CHOOSES the category by resolving the buff-param code against each
//      category's code->id registry (Skill vtbl+0x70, Stat vtbl+0x50, ...) in turn.
//   2. CommitModifiers moves from staging into C_Soul's sorted main lists
//   3. GetModifiedStatValue (sub_180229880) / AccumulatePerkStat (sub_180229980) walk the main
//      list applying each node
//   4. Terminate deactivates all nodes and unlinks them
//
// CreateModifierNode: sub_1802AD1E0
// ApplyModifier:      sub_180229BD0
// GetEffectiveness:   sub_180229C60
template <E_ModifierCategory Category, typename TTargetId>
struct S_ModifierNode {
    static constexpr E_ModifierCategory kCategory = Category;
    using TargetId = TTargetId;

    C_BuffInstanceBase* pOwner;         // +0x00  owning buff instance
    C_Soul*             pSoul;          // +0x08  associated soul (set during CommitModifiers)
    uint8_t             bActive;        // +0x10  1 = active, 0 = deactivated
    uint8_t             bTimeBased;     // +0x11  has time-based effectiveness callback
    uint8_t             bNonWearing;    // +0x12  true when buff_lifetime_id == 0
    uint8_t             bExtraFlag;     // +0x13  from modifier descriptor
    uint8_t             _pad14[4];      // +0x14
    S_ModifierNode*     pNextStaging;   // +0x18  next in staging linked list (pre-commit)
    S_ModifierNode*     pNextSorted;    // +0x20  next in main sorted linked list (on soul)
    TTargetId           nTargetId;      // +0x28  target ID in this category's namespace (T)
    E_ModifierOp        eOp;            // +0x2C  operation type (also used as sort key)
    float               fValue;         // +0x30  current modifier value
    float               fOrigValue;     // +0x34  original/base modifier value
    int32_t             nExtra;         // +0x38  extra data (movement bool for perk mods)
    uint8_t             bSpecialFlag;   // +0x3C  used by perk movement modifiers
    uint8_t             _pad3D[3];      // +0x3D
};

// One concrete node type per modifier category (T = that category's target-id namespace).
using S_StatModifierNode        = S_ModifierNode<E_ModifierCategory::Stat,        E_SoulStat>;
using S_SkillModifierNode       = S_ModifierNode<E_ModifierCategory::Skill,       E_SoulSkill>;
using S_PerkStatModifierNode    = S_ModifierNode<E_ModifierCategory::DerivedStat, E_PerkStat>;     // cat2 perk-stat hook (Pbs=8, Dsl=0x20); category enum value is named DerivedStat
using S_DerivedStatModifierNode = S_ModifierNode<E_ModifierCategory::Detail,      E_DerivedStat>;
using S_MovementModifierNode    = S_ModifierNode<E_ModifierCategory::Movement,    E_MovementType>;
using S_SpecialModifierNode     = S_ModifierNode<E_ModifierCategory::Special,     int32_t>;          // no code registry (ids set in C++)
using S_SoulLevelModifierNode   = S_ModifierNode<E_ModifierCategory::SoulLevel,   E_SoulLevel>;

static_assert(sizeof(S_StatModifierNode)        == 0x40);
static_assert(sizeof(S_SkillModifierNode)       == 0x40);
static_assert(sizeof(S_PerkStatModifierNode)    == 0x40);
static_assert(sizeof(S_DerivedStatModifierNode) == 0x40);
static_assert(sizeof(S_MovementModifierNode)    == 0x40);
static_assert(sizeof(S_SpecialModifierNode)     == 0x40);
static_assert(sizeof(S_SoulLevelModifierNode)   == 0x40);

}  // namespace wh::rpgmodule
