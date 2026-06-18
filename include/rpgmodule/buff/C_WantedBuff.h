#pragma once
#include "C_TwoStateSoulBuffInstance.h"

// -----------------------------------------------
// C_WantedBuff — soul buff whose modifiers depend on the local crime/wanted level
// -----------------------------------------------
// RTTI: .?AVC_WantedBuff@rpgmodule@wh@@   (TD @ 0x182a568a0, RVA 0x2A568A0;
//        COL @ 0x1824472f8, CHD @ 0x1824d2450)
// vtable: 0x1821cd970   (27 slots, 0..26; ends at next COL 0x182447320)
// Ctor:   sub_1806173BC  (operator new(0xD0) + memset(0,0xD0) -> size 0xD0; calls
//          C_SoulBuffInstance ctor sub_180617B58, then sub_180617DC4 to register)
// Factory key: "wh.rpgmodule.buff.Wanted"  (registered by sub_180115FD0:
//          type object &unk_1835A6C90, creator sub_18044B450, ctor thunk sub_1806173B4)
// Size: 0xD0 (adds NO data members over C_TwoStateSoulBuffInstance / C_SoulBuffInstance)
//
// Base chain [CONFIRMED via RTTI base-class array of TD 0x182a568a0, 5 BCDs, all PMD{0,-1,0}]:
//   C_WantedBuff -> C_TwoStateSoulBuffInstance -> C_SoulBuffInstance
//                -> C_BuffInstance<C_Soul> -> C_BuffInstanceBase
//
// Abstract: AddNewModifier (base slot 9) is never overridden in this chain -> not
// instantiated in this TU (same as sibling Constant/Timed buffs).
//
// Purpose [CONFIRMED]: a two-state buff (see C_TwoStateSoulBuffInstance) whose predicate
// reports whether the owning soul's current crime location is "wanted enough". When true,
// the buff's state-1 modifiers apply; when false, its state-2 modifiers apply. In the
// shipped Wanted buff these gate perks such as perk_daring_debonair (str+1, vit+1) and
// perk_ordinary_mug (con-1) on the location wanted level.
//
// RTTI static member intentionally OMITTED: Offsets_RTTI.h has no RTTI_C_WantedBuff.

namespace wh::rpgmodule {

class C_WantedBuff : public C_TwoStateSoulBuffInstance {
public:
    // [CONFIRMED] slot 26, sub_180208898. Two-state predicate override.
    // Resolves the soul's crime-location key (sub_180208C04(m_pSoul@+0x88) -> IntelligentObject+0xA7C),
    // looks it up in C_RPGLocationManager (*(qword_1835AC728+0x580), vtable+0x18 enumerate),
    // and via lambda sub_180A906D0 returns true iff
    //     I_Location->GetWantedLevel()  (I_Location vtable+0xA8)
    //       >=  C_RPGParams::GetInstance()[+0x908]  (float index 0x242, default 1.0).
    // Threshold domain = E_CrimeIconLevel {none=0, fine=1, jail=2}; default 1.0 = "fine or higher".
    bool EvaluateState() override;                                                     // [26] +0xD0  0x180208898

    // [CONFIRMED] slot 13, sub_1806FF080. Returns the Wanted type object (&unk_1835A6C90),
    // i.e. the "wh.rpgmodule.buff.Wanted" type name used for string-based RTTI.
    void* GetTypeName(void* pOutStr) override;                                         // [13] 0x1806FF080

    // [CONFIRMED] slot 14/15, sub_18116BD4C. Matches the Wanted type object, else chains
    // to C_SoulBuffInstance::CastTo (sub_18115EC04).
    C_BuffInstanceBase* CastTo(const void* pTypeName) override;                        // [14] 0x18116BD4C
    C_BuffInstanceBase* CastToConst(const void* pTypeName) override;                   // [15] 0x18116BD4C

    // No data members: sizeof == C_TwoStateSoulBuffInstance == C_SoulBuffInstance == 0xD0.
};
// Pinned by ctor sub_1806173BC: operator new(0xD0) + memset(this,0,0xD0).
static_assert(sizeof(C_WantedBuff) == 0xD0);

}  // namespace wh::rpgmodule
