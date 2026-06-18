#pragma once

#include <cstdint>

// ===========================================================================
// wh::rpgmodule::S_FactionRelationDef  -  one row of the faction-to-faction
// relationship definition table (global xmmword_1835AB3A0).
// ===========================================================================
// VERIFIED: builder sub_18119B054 iterates the table with stride 0x0C (i[0],i[1],i[2])
// and keys each pair via sub_180228850(idA, idB); the relation record's float is copied
// from this row's +0x08 (sub_18118B8D4: rec[0] = *(float*)(def+8)); the f2f command
// sub_181192178 prints (rec->def)->m_baseRelationship as "%.2f".
namespace wh::rpgmodule {

struct S_FactionRelationDef {
    int32_t m_factionA;          // +0x00  first faction id  (key half)
    int32_t m_factionB;          // +0x04  second faction id (key half)
    float   m_baseRelationship;  // +0x08  base A<->B relationship
};
static_assert(sizeof(S_FactionRelationDef) == 0x0C, "f2f relation-def table row stride (sub_18119B054)");

}  // namespace wh::rpgmodule
