#pragma once

#include <cstdint>

// -----------------------------------------------
// Perk Definition (global table entry)
// -----------------------------------------------
// Global array: xmmword_1835A8F60 (begin), xmmword_1835A8F60+8 (end)
// Each entry: 0x68 bytes
// Loaded from perk table via C_PerkDatabase

#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"

namespace wh::rpgmodule {

struct S_PerkDefinition {
    CryGUID     perkId;                 // +0x00
    CryGUID     metaperkId;             // +0x10  (parent perk GUID)
    CryGUID     conditionId;            // +0x20  (prerequisite/condition GUID)
    CryGUID     exclusiveGroupId;       // +0x30  (mutual exclusion group GUID)
    uint32_t    statSelector;           // +0x40  E_RPGStat (0..3 = STR/AGI/VIT/SPC; 0xA = none)
    uint32_t    skillSelector;          // +0x44  E_RPGSkill (0..32; 0x21 = Count = none -> main level)
    uint32_t    levelRequirement;       // +0x48
    uint32_t    visibility;             // +0x4C  (0=normal, 2=stat/skill, 3=obsolete; checked as *(dword+0x13))
    CryGUID     effectId;               // +0x50  (buff/effect GUID — used for perk-to-effect lookup)
    uint32_t    perkType;               // +0x60  (category/type enum)
    uint32_t    gameModeFlags;          // +0x64  (bitmask ANDed with current game mode)
};
static_assert(sizeof(S_PerkDefinition) == 0x68);

}  // namespace wh::rpgmodule
