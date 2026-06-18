#pragma once

#include <cstdint>

// ===========================================================================
// wh::rpgmodule::E_ReputationChangeTarget  -  bitmask selecting which
// reputation layer(s) a `reputation_change` row affects.
// ===========================================================================
// [CONFIRMED] by code AND modding.sql ("the ID is actually a bit-mask, keep synced
// with the code (E_ReputationChangeTarget)").
//
// Stored in the DB column `reputation_change_target_id`. The runtime reads it as a
// single BYTE (e.g. `*(_BYTE *)(row + 0x14)` in sub_18117E2AC / sub_18118F47C),
// hence the uint8_t underlying type. Observed DB combinations: 1=npc only,
// 6=faction+superfaction, 7=npc+faction+superfaction, 14=faction+nearby+superfaction,
// 15=all. The Apply gate `(*(row+0x14) & 6)` matches "6 = faction+superfaction".
namespace wh::rpgmodule {

enum class E_ReputationChangeTarget : uint8_t {
    None           = 0,
    Npc            = 1 << 0,   // bit0 - individual NPC personal opinion (Soul path only)
    Faction        = 1 << 1,   // bit1 - faction's own reputation (C_Faction+0x10)
    Superfaction   = 1 << 2,   // bit2 - superfaction grouping reputation
    NearbyFactions = 1 << 3,   // bit3 - location/region spatial spread
};

}  // namespace wh::rpgmodule
