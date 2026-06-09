#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_attack_type lookup row. POLYMORPHIC (vtable @ C_CombatAttackTypeData::`vftable').
// Default ctor sub_180F4F6A4; inline build in OnPostLoad sub_180F92B78. VERIFIED.
class C_CombatAttackTypeData {
public:
    virtual ~C_CombatAttackTypeData() = default;   // +0x00 vtable

    int32_t     combat_attack_type_id;      // +0x08
    const char* combat_attack_type_name;    // +0x10  CryStringT<char>
    int32_t     rpg_damage_type_id;         // +0x18
    float       relative_stamina_cost;      // +0x1C  (default 1.0)
    const char* mn_tag;                     // +0x20  CryStringT<char>
    uint8_t     _runtime28[0x10];           // +0x28  zero-init runtime
    const char* opp_mn_tag;                 // +0x38  CryStringT<char>
    uint8_t     _runtime40[0x0C];           // +0x40  zero-init runtime
    bool        cannot_kill;                // +0x4C
    uint8_t     _pad4D[3];                  // +0x4D
};
static_assert(sizeof(C_CombatAttackTypeData) == 0x50);

}  // namespace wh::combatmodule
