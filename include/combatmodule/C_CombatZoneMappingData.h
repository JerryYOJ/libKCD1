#pragma once
#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatZoneMappingData -- FK-resolved zone-mapping row (the runtime "Data"
// for S_CombatZoneMappingTableRow). 0x18-byte POD, NO vtable.
//
// All rows live in one shared, read-only array owned by the zone-mapping
// database (begin @ qword_18359AF60, end @ qword_18359AF68, stride 0x18).
// A C_CombatActionAttackData carries three FK pointers INTO this array
// (m_selectionKeyZone/+0xD8, m_aimZone/+0xE0, m_executedZone/+0xE8); reading
// a candidate's zone id is `*(uint32_t*)((char*)mapping + 8)` (= m_zoneId).
//
// Field roles are derived from the matcher sub_180A5DF20 (reads +0,+8,+0xC,
// +0x10,+0x14 as criteria, returns +4) and the candidate-side reads in the
// selection predicate sub_18045F3AC (cand+0xD8 compared at +0; cand+0xE0/+0xE8
// zone ids read at +8). [V] workflow wf_05aec32f (zone-mapping verdict: partial
// -- struct/size confirmed; field NAMES are usage-derived, not XML-confirmed.)
// ---------------------------------------------------------------------------
struct C_CombatZoneMappingData {
    uint32_t m_matchKey;     // +0x00  selection compare value (cand+0xD8 read at +0); matcher criterion[0]
    uint32_t m_outputZone;   // +0x04  resolver OUTPUT zone (sub_18045F430 returns this on a match)
    uint32_t m_zoneId;       // +0x08  THE zone id (head/UL/UR/LL/LR/center); read for cand+0xE0/+0xE8
    uint32_t m_curZoneKey;   // +0x0C  current-zone criterion
    uint32_t m_execZoneKey;  // +0x10  executed-zone criterion
    uint32_t m_rawStanceKey; // +0x14  rawStance relation key (sub_1802195AC graph test)
};
static_assert(sizeof(C_CombatZoneMappingData) == 0x18, "C_CombatZoneMappingData must be 0x18");

}  // namespace wh::combatmodule
