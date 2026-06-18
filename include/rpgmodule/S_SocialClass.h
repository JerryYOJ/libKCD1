#pragma once

#include <cstdint>
#include "E_CrimeSystemRole.h"

namespace wh::rpgmodule {

// -----------------------------------------------
// S_SocialClass -- one row of the rpg/social_class table.
// -----------------------------------------------
// This is the RUNTIME object the C_SocialClassDatabase hands out, NOT the raw load
// recipe. The database is C_ObjectTableDatabase<S_SocialClass, S_SocialClassDBData>
// (RTTI at 0x182a5dd70): the 1st template param S_SocialClass is the stored object,
// the 2nd S_SocialClassDBData is the table-row deserialization recipe used only at load.
// (The DBData type is distinct and not RE'd here.) This being a flat table, the runtime
// object does NO foreign-key resolution -- it is effectively POD, a near-copy of the row.
//
// The soul caches a pointer to its row at C_Soul::m_pSocialClass (+0xBD0), resolved by
// sub_180656F0C: m_pSocialClass = GetById(socialClassDB, soul.socialClassId@+0x288). A
// missed lookup stores the static sentinel &dword_1835ACE80, so the pointer is NEVER null.
//
// Layout from the DB column descriptors (built in sub_180123940; row stride 0x20 set in
// sub_1811813B0) and the field reads in sub_1802B5270. Size 0x20.
struct S_SocialClass {
    int32_t           m_id;                // +0x00  social_class_id (primary key)
    char              _pad04[4];           // +0x04  alignment (no column maps here)
    CryStringT<char>  m_name;              // +0x08  social_class_name
    int32_t           m_wealth;            // +0x10  wealth
    E_CrimeSystemRole m_crimeRoleId;       // +0x14  soul_crime_role_id -- the guard determinant
    float             m_itemHealthBase;    // +0x18  preset_items_health_base (DB default 1.0)
    float             m_itemHealthRandom;  // +0x1C  preset_items_health_random (DB default 0.0)
};
static_assert(sizeof(S_SocialClass) == 0x20);

}  // namespace wh::rpgmodule
