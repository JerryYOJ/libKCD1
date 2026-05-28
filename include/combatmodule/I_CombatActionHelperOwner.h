#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatActionHelperAttackOwner — MI interface for attack helper ownership.
//
// RTTI: .?AVI_CombatActionHelperAttackOwner@combatmodule@wh@@
// Embedded as a secondary vtable in attack-capable actions.
// 6 vtable slots (all purecall in abstract vtable).
//
// Present in: Attack(+0x108), StaticAttack(+0x100), SyncAttack(+0x108),
//             PerfectBlock(+0x120), ComposedRipostePB(+0x128)
// ---------------------------------------------------------------------------
class I_CombatActionHelperAttackOwner {
public:
    virtual ~I_CombatActionHelperAttackOwner() = default;   // [0]
    virtual void unk_atk1() = 0;                            // [1]
    virtual void unk_atk2() = 0;                            // [2]
    virtual void unk_atk3() = 0;                            // [3]
    virtual void unk_atk4() = 0;                            // [4]
    virtual void unk_atk5() = 0;                            // [5]
};

// ---------------------------------------------------------------------------
// I_CombatActionHelperBlockOwner — MI interface for block helper ownership.
//
// RTTI: .?AVI_CombatActionHelperBlockOwner@combatmodule@wh@@
// Embedded as a secondary vtable in block-capable actions.
// 4 vtable slots (all purecall in abstract vtable).
//
// Present in: Block(+0x108), PerfectBlock(+0x118),
//             ComposedRipostePB(+0x120), SyncPerfectBlock(+0x118)
// ---------------------------------------------------------------------------
class I_CombatActionHelperBlockOwner {
public:
    virtual ~I_CombatActionHelperBlockOwner() = default;    // [0]
    virtual void unk_blk1() = 0;                            // [1]
    virtual void unk_blk2() = 0;                            // [2]
    virtual void unk_blk3() = 0;                            // [3]
};

}  // namespace wh::combatmodule
