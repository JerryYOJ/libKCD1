#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_zone lookup row. ctor sub_180F99A18; column->offset map from the
// combat_zone binder sub_1800D9EC0. mn-tag-backed (each string but the first two
// is preceded by a runtime block). VERIFIED.
// attack_zone_id / guard_zone_id / end_guard_zone_id all resolve to this type.
struct C_CombatZoneData {
    int32_t          combat_zone_id;            // +0x00
    int32_t          _pad04;                    // +0x04
    CryStringT<char> combat_zone_name;          // +0x08
    CryStringT<char> attack_mn_tag;             // +0x10
    uint8_t          _runtime18[0x10];          // +0x18  zero-init runtime
    CryStringT<char> defense_mn_tag;            // +0x28
    uint8_t          _runtime30[0x10];          // +0x30
    CryStringT<char> start_mn_tag;              // +0x40
    uint8_t          _runtime48[0x10];          // +0x48
    CryStringT<char> end_mn_tag;                // +0x58
    uint8_t          _runtime60[0x10];          // +0x60
    CryStringT<char> riposte_mn_tag;            // +0x70
    uint8_t          _runtime78[0x0C];          // +0x78
    float            radius_from;               // +0x84
    float            radius_to;                 // +0x88
    float            angle_from;                // +0x8C
    float            angle_to;                  // +0x90
    int32_t          cursor_idx;                // +0x94
    bool             default_zone;              // +0x98
    uint8_t          _pad99[3];                 // +0x99
    int32_t          _idCopy;                   // +0x9C  duplicate of combat_zone_id
};
static_assert(sizeof(C_CombatZoneData) == 0xA0);

}  // namespace wh::combatmodule
