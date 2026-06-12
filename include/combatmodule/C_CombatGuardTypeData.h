#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_guard_type lookup row. OnPostLoad ctor sub_180F9DC04 (mn-tag-backed).
// Field order matches S_CombatGuardTypeTableRow. VERIFIED.
struct C_CombatGuardTypeData {
    int32_t          combat_guard_type_id;      // +0x00
    CryStringT<char> combat_guard_type_name;    // +0x08
    CryStringT<char> mn_tag;                     // +0x10
    uint8_t          _runtime18[0x10];           // +0x18  zero-init runtime (mn fragment data)
    CryStringT<char> end_mn_tag;                 // +0x28
    uint8_t          _runtime30[0x0C];           // +0x30  zero-init runtime
    bool             move_restriction;           // +0x3C
    uint8_t          _pad3D[3];                  // +0x3D
};
static_assert(sizeof(C_CombatGuardTypeData) == 0x40);

}  // namespace wh::combatmodule
