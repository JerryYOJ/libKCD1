#pragma once

#include <cstdint>
#include <cstddef>

#include "../CryEngine/CryCommon/BaseTypes.h"            // uint64 (needed by CryGUID.h)
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h" // CryGUID (location_id uuid column)
// CryStringT<char> is provided by the PCH prelude (CryString.h is in PCH.h), as in
// S_InformationRecord.h. The string fields below use it without a per-header include.
//
// NOTE: the binary RTTI/template names this table-row type wh::rpgmodule::S_FactionDBData
// (C_FactionDatabase = C_ObjectDatabaseIdIndexed<C_ObjectTableDatabase<S_Faction, S_FactionDBData>>);
// the project keeps the descriptive name S_FactionDef. The +0x18 column is literally
// "player_reputation" in the SQL schema (named baseReputation here to match GetBaseReputation).

// ===========================================================================
// wh::rpgmodule::S_FactionDef  (a.k.a. S_FactionData)  -  the static faction
// definition loaded from the `faction` table, pointed to by C_Faction+0x278.
// ===========================================================================
// Source table: xmmword_1835A7D20 (loader sub_18119B144 walks it with a 0x38-byte
// stride and uses *def (the +0x00 dword) as the faction id sort-key). The id at
// +0x00 is independently re-confirmed by sub_18118F188 which reads
// **(_DWORD**)(faction+0x278) as the source faction id.
//
// DISCREPANCY (intentional, do not "fix" HERE): the auto-generated alphabetized-XML
// schema struct wh::databasemodule::S_Faction currently places faction_id at +0x04
// (after a phantom 4-byte _rowbase) -- that is a GENERATOR BUG (the column descriptor
// sub_180119F00 sets faction_id m_offset=0). This runtime def packs the id at +0x00;
// everything from name (+0x08) onward matches the DB row. Trust THIS layout for
// runtime reads. (See deferred: fix databasemodule/tables/S_Faction.h + the generator.)
//
// Confirmed runtime reads this session:
//   +0x18 baseReputation  (sub_1811C07C0 GetBaseReputation; deser sub_18119A218 reads as float)
//   +0x1C superfactionId   (sub_18118F47C superfaction branch)
//   +0x20 16-byte location resolver key (sub_181197BB0 reads the full _OWORD and hands it
//         to the location manager resolver vtbl+0x40; consumers compare it half-by-half
//         as two opaque 8-byte halves, e.g. sub_18044A534 `*i==v2 && i[1]==a2[1]`).
//
// Column TYPES are pinned by modding.sql:3646 (faction): faction_name varchar(31),
// description varchar(31), player_reputation real, superfaction_id int, location_id uuid,
// visible boolean.
namespace wh::rpgmodule {

struct S_FactionDef {
    uint32_t            id;                 // +0x00  [CONFIRMED] faction id (map key; **(faction+0x278))
    uint32_t            _pad04;             // +0x04
    CryStringT<char>    name;               // +0x08  [CONFIRMED offset; type INFERRED CryString vs char*] interned name (ui_fac_*); GetName reads *(def+8)
    CryStringT<char>    description;        // +0x10  [INFERRED] DB column faction.description; not re-read in code this session
    float               baseReputation;     // +0x18  [CONFIRMED] base (XML) reputation; GetBaseReputation / deser
    uint32_t            superfactionId;     // +0x1C  [CONFIRMED] stored grouping id
    CryGUID             locationId;         // +0x20  [CONFIRMED] SQL "location_id" uuid column (16 bytes; column type-tag 3 / sub_180726144); read whole by resolver sub_181197BB0
    bool                visible;            // +0x30  [INFERRED] DB column faction.visible; not re-read in code this session
    uint8_t             _pad31[7];          // +0x31  (loader table stride is 0x38; trailing bytes not mapped)
};
// size 0x38 [CONFIRMED] by the faction-def loader sub_18119B144: it walks the
// source table xmmword_1835A7D20 with element stride 0x38 (DWORD cursor `v3 += 0xE`
// == 0x38 bytes; OWORD cursor `v5 += 0x38`). The table stride IS the element size.
static_assert(sizeof(S_FactionDef) == 0x38, "faction-def table stride (sub_18119B144)");

}  // namespace wh::rpgmodule
