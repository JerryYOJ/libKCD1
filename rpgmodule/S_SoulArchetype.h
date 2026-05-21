#pragma once

#include <cstdint>

// -----------------------------------------------
// S_SoulArchetype -- POD row from soul_archetype.xml
// -----------------------------------------------
// Namespace: wh::rpgmodule
// RTTI (in template): US_SoulArchetype@rpgmodule@wh@@
//
// Loaded by C_SoulArchetypeDatabase (wh::rpgmodule, global at 0x1835AB090).
// Lookup by name: sub_18117EBCC (lowercases input, searches sorted container).
//
// Column layout confirmed from sub_180124390 (column descriptor registration)
// and sub_1802B686C (Lua export of archetype fields).
//
// Referenced by C_Soul at offset +0xBC8 (borrowed pointer into database storage).
// Modifying a field here affects ALL souls sharing that archetype.
//
// Database hierarchy:
//   C_SoulArchetypeDatabase (wh::rpgmodule)
//     : C_ObjectDatabaseIdIndexed<C_ObjectTableDatabase<S_SoulArchetype, S_SoulArchetypeDBData>, int>
//       (wh::databasemodule)
//
// Known archetypes (from soul_archetype.xml):
//   id=0  "NPC"         multiplier=3, weight=160
//   id=1  "NPC_Female"  multiplier=3, weight=120
//   id=2  "NPC_Child"   multiplier=1, weight=80
//   id=3  "Horse"       multiplier=2, weight=1000
//   id=13 "Hero"        multiplier=1, weight=160  <-- player
//   id=15 "Hero_female" multiplier=1, weight=120

namespace wh::rpgmodule {

struct S_SoulArchetype {
    int32_t     soul_archetype_id;              // +0x00  PK (integer)
    char        _pad04[4];                      // +0x04  alignment
    const char* soul_archetype_name;            // +0x08  CryStringT ptr
    int32_t     race_id;                        // +0x10  FK → race table
    int32_t     gender_id;                      // +0x14  FK → gender table (1=male, 2=female)
    float       normal_body_weight;             // +0x18  body weight in kg(?)
    float       body_base_armor;                // +0x1C  base armor rating
    float       body_base_visibility;           // +0x20  base visibility
    float       body_base_conspicuousness;      // +0x24  base conspicuousness
    float       inventory_capacity_multiplier;  // +0x28  multiplier for DerivStat_InventoryCapacity
    float       base_stamina;                   // +0x2C  base stamina value
    float       relative_vitality_to_stamina;   // +0x30  VIT-to-stamina conversion factor
    float       unarmed_attack_base;            // +0x34  base unarmed damage
};
static_assert(sizeof(S_SoulArchetype) == 0x38);

}  // namespace wh::rpgmodule
