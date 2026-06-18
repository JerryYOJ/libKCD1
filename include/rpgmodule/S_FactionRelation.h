#pragma once

#include <cstdint>
#include "S_FactionRelationDef.h"

// ===========================================================================
// wh::rpgmodule::S_FactionRelation  -  the live faction-to-faction reputation
// record; pointee of C_FactionManager::m_relations (the +0x40 flat_map value).
// ===========================================================================
// VERIFIED: allocated 0x10 by sub_18118B8D4 (rec[0] = def->m_baseRelationship, rec[8] = def);
// the live relationship at +0x00 is written by sub_18118F47C (*(float*)rec = clampAdd(...)) and
// read by GetRelationship sub_180228414 (v17 = *rec) and the f2f command. Owned raw pointer
// (no shared_ptr/control block); freed on replace via sub_18118E894.
namespace wh::rpgmodule {

struct S_FactionRelation {
    float                 m_relationship;  // +0x00  live A<->B reputation (init from def, written by sub_18118F47C)
    uint8_t               _pad04[4];       // +0x04
    S_FactionRelationDef* m_pDefinition;   // +0x08  source table row (base relationship at def+0x08)
};
static_assert(sizeof(S_FactionRelation) == 0x10, "f2f relation record (sub_18118B8D4 alloc 0x10)");

}  // namespace wh::rpgmodule
