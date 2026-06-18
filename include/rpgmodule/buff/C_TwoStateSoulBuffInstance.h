#pragma once
#include <cstdint>
#include "C_SoulBuffInstance.h"

// -----------------------------------------------
// C_TwoStateSoulBuffInstance — buff that toggles between two modifier states
// -----------------------------------------------
// RTTI: .?AVC_TwoStateSoulBuffInstance@rpgmodule@wh@@   (TD RVA 0x2A54518)
// Abstract: it never has its own vtable/COL in the image — EvaluateState() is a pure
//           virtual, only implemented by concrete subclasses (the only known one is
//           C_WantedBuff). Its method implementations are observed inside C_WantedBuff's
//           vtable (0x1821cd970). AddNewModifier (base slot 9) is never overridden, so
//           this class stays abstract.
// Size: 0xD0 (adds NO data members over C_SoulBuffInstance — pinned by the C_WantedBuff
//        ctor operator new(0xD0), since C_WantedBuff = this + 0 bytes).
//
// Mechanism [CONFIRMED]:
//   Update / OnMaterialEffectStart / GetProgress all evaluate the predicate EvaluateState()
//   (vtable slot 26, offset 0xD0) and then apply two opposite modifier states via
//   sub_1802086CC(this, stateMask, active):
//       state 1 active = EvaluateState()        ("condition met" modifiers)
//       state 2 active = !EvaluateState()       ("condition not met" modifiers)
//   sub_1802086CC walks the 7 C_SoulBuffInstance modifier staging lists
//   (m_statMods @+0x90 .. m_soulLevelMods @+0xC0) and (de)activates each node whose
//   per-node state-tag byte (S_ModifierNode+0x13) matches stateMask via sub_180448850.
//   So a single buff carries both "on" and "off" modifier sets and swaps them as the
//   predicate flips — no extra storage is required.
//
// RTTI static member intentionally OMITTED: Offsets_RTTI.h has no RTTI_C_TwoStateSoulBuffInstance.

namespace wh::rpgmodule {

class C_TwoStateSoulBuffInstance : public C_SoulBuffInstance {
public:
    // ====== Overrides from the buff base chain ======

    // [CONFIRMED] slot 1, sub_180208684. Re-evaluates EvaluateState() and applies both
    // modifier states (state 1 = predicate, state 2 = !predicate). Returns 2 (active).
    bool Update() override;                                                            // [1] 0x180208684

    // [CONFIRMED] slot 19, thunk 0x1806F3060 -> sub_180208644. Same body as Update
    // (re-applies the current two-state selection when a material effect starts).
    void OnMaterialEffectStart() override;                                             // [19] 0x1806F3060 -> 0x180208644

    // [CONFIRMED] binary vtable slot [9] = sub_180210650. Writes a progress record to
    // pOutResult: {int32 progress=0, int32 _=0, uint8 valid = EvaluateState()}.
    // Declared NON-virtual to match the sibling convention (C_ConstantSoulBuffInstance.h /
    // C_TimedSoulBuffInstance.h); the base leaves slot 9 (AddNewModifier) pure.
    void* GetProgress(void* pOutResult);                                              // [9] 0x180210650

    // ====== New virtual introduced by this layer ======

    // [CONFIRMED] slot 26 (vtable offset 0xD0). The two-state predicate.
    // Pure here; concrete subclasses decide which modifier state is active.
    // [INFERRED] name (no RTTI for methods).
    virtual bool EvaluateState() = 0;                                                  // [26] +0xD0
};
// Size pinned by C_WantedBuff ctor sub_1806173BC: operator new(0xD0); this layer
// adds no fields, so it equals C_SoulBuffInstance's 0xD0.
static_assert(sizeof(C_TwoStateSoulBuffInstance) == 0xD0);

}  // namespace wh::rpgmodule
