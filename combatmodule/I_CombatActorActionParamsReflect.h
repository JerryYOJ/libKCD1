#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatActorActionParamsReflect — base interface for polymorphic params.
//
// All polymorphic S_CombatActorAction*Params structs inherit from this.
// Primary vtable has 25 slots: [0] dtor + [1]-[24] reflection/serialization.
// Verified from S_CombatActorActionAttackParams vtable at 0x1821AE6B8.
//
// PerfectBlock params also embed a SECONDARY copy of this vtable at +0x08
// as an adjustor (same TypeDescriptor, offset=8 in COL).
// ---------------------------------------------------------------------------
class I_CombatActorActionParamsReflect {
public:
    virtual ~I_CombatActorActionParamsReflect() = default;  // [0]
    virtual void unk_reflect_1() {}     // [1]
    virtual void unk_reflect_2() {}     // [2]
    virtual void unk_reflect_3() {}     // [3]
    virtual void unk_reflect_4() {}     // [4]
    virtual void unk_reflect_5() {}     // [5]
    virtual void unk_reflect_6() {}     // [6]
    virtual void unk_reflect_7() {}     // [7]
    virtual void unk_reflect_8() {}     // [8]
    virtual void unk_reflect_9() {}     // [9]
    virtual void unk_reflect_10() {}    // [10]
    virtual void unk_reflect_11() {}    // [11]
    virtual void unk_reflect_12() {}    // [12]
    virtual void unk_reflect_13() {}    // [13]
    virtual void unk_reflect_14() {}    // [14]
    virtual void unk_reflect_15() {}    // [15]
    virtual void unk_reflect_16() {}    // [16]
    virtual void unk_reflect_17() {}    // [17]
    virtual void unk_reflect_18() {}    // [18]
    virtual void unk_reflect_19() {}    // [19]
    virtual void unk_reflect_20() {}    // [20]
    virtual void unk_reflect_21() {}    // [21]
    virtual void unk_reflect_22() {}    // [22]
    virtual void unk_reflect_23() {}    // [23]
    virtual void unk_reflect_24() {}    // [24]
};

}  // namespace wh::combatmodule
