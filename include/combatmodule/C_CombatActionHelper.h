#pragma once

#include <cstdint>
#include "../CryEngine/CryCommon/smartptr.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActionHelperAttack — heap-allocated attack helper object.
//
// RTTI: .?AVC_CombatActionHelperAttack@combatmodule@wh@@
// Created via sub_180462224, alloc 0x38 bytes.
// Ref-counted (_i_reference_target<int> base).
// Owned by attack-capable actions (Attack, SyncAttack, PerfectBlock, etc.)
// ---------------------------------------------------------------------------
class C_CombatActionHelperAttack : public _i_reference_target<int> {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActionHelperAttack;
    uint8_t m_data[0x28];  // +0x10..+0x37
};
static_assert(sizeof(C_CombatActionHelperAttack) == 0x38);

typedef _smart_ptr<C_CombatActionHelperAttack> C_CombatActionHelperAttackPtr;

// ---------------------------------------------------------------------------
// C_CombatActionHelperBlock — heap-allocated block helper object.
//
// RTTI: .?AVC_CombatActionHelperBlock@combatmodule@wh@@
// Created via sub_1804E17A0, alloc 0x28 bytes.
// Ref-counted (_i_reference_target<int> base).
// Owned by block-capable actions (Block, PerfectBlock, etc.)
// ---------------------------------------------------------------------------
class C_CombatActionHelperBlock : public _i_reference_target<int> {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActionHelperBlock;
    uint8_t m_data[0x18];  // +0x10..+0x27
};
static_assert(sizeof(C_CombatActionHelperBlock) == 0x28);

typedef _smart_ptr<C_CombatActionHelperBlock> C_CombatActionHelperBlockPtr;

// ---------------------------------------------------------------------------
// C_CombatActionSyncHelper — heap-allocated sync helper object.
//
// Created via sub_180431144, alloc 0x18 bytes.
// Used by synced actions (SyncAttack, SyncHit, SyncTransition, etc.)
// ---------------------------------------------------------------------------
class C_CombatActionSyncHelper {
public:
    uint8_t m_data[0x18];  // +0x00..+0x17
};
static_assert(sizeof(C_CombatActionSyncHelper) == 0x18);

}  // namespace wh::combatmodule
