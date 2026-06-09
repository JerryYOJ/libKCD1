#pragma once

#include <cstdint>
#include <map>
#include "C_CombatActionTypeData.h"
#include "C_CombatAttackTypeData.h"
#include "C_CombatInputClassData.h"
#include "C_CombatSideData.h"
#include "C_CombatWeaponGroupData.h"
#include "C_CombatGuardTypeData.h"
#include "C_CombatGuardStanceData.h"
#include "C_CombatZoneData.h"
#include "../entitymodule/S_WeaponClassDBData.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActionSyncHitData — runtime data row for sync-hit (victim) actions.
//
// NON-polymorphic. Size 0x180. Loader sub_180F8A0E0 (from
// S_CombatActionSyncHitTableRow). Pointed to by action->m_params.m_pDataRow.
//
// The +0xA0..+0x140 block holds the FK columns from combat_action_sync_hit.xml,
// each resolved by the loader into a pointer to its lookup-table Data row
// (see C_CombatLookupData.h). All FK types VERIFIED via the per-column resolver.
// ---------------------------------------------------------------------------
#pragma pack(push, 4)
struct C_CombatActionSyncHitData {
    int32_t     actor_class_hash;       // +0x00
    int32_t     _field04;               // +0x04
    std::map<int32_t, void*> m_oppActorClasses;  // +0x08  resolved opp_actor_classes
    bool        mounted;                // +0x18
    bool        opp_mounted;            // +0x19
    uint8_t     _pad1A[6];              // +0x1A
    uint64_t    timestamp;              // +0x20
    float       animation_duration;     // +0x28
    float       fade_in;                // +0x2C
    float       _field30;               // +0x30
    float       _field34;               // +0x34
    float       _field38;               // +0x38
    float       _field3C;               // +0x3C
    uint64_t    _field40;               // +0x40
    uint32_t    _field48;               // +0x48
    uint32_t    _field4C;               // +0x4C
    uint32_t    _field50;               // +0x50
    uint32_t    _field54;               // +0x54
    uint32_t    _field58;               // +0x58
    uint64_t    _field5C;               // +0x5C
    uint32_t    _field64;               // +0x64
    uint32_t    _field68;               // +0x68
    uint32_t    _field6C;               // +0x6C
    uint32_t    _field70;               // +0x70
    uint32_t    _field74;               // +0x74
    uint64_t    _field78;               // +0x78
    uint32_t    _field80;               // +0x80
    uint32_t    _field84;               // +0x84
    uint32_t    _field88;               // +0x88
    uint32_t    _field8C;               // +0x8C
    uint32_t    _field90;               // +0x90
    uint32_t    _field94;               // +0x94
    uint32_t    _field98;               // +0x98
    uint32_t    _field9C;               // +0x9C

    // FK columns, resolved by sub_180F8A0E0 (offsets/types VERIFIED).
    C_CombatZoneData*        m_pAttackZone;       // +0xA0  attack_zone_id
    C_CombatAttackTypeData*  m_pAttackType;       // +0xA8  attack_type_id
    C_CombatInputClassData*  m_pInputClass;       // +0xB0  input_class_id
    C_CombatSideData*        m_pSide;             // +0xB8  side_id
    entitymodule::S_WeaponClassDBData* m_pRWeaponClass;     // +0xC0  r_weapon_class_id
    entitymodule::S_WeaponClassDBData* m_pLWeaponClass;     // +0xC8  l_weapon_class_id
    C_CombatWeaponGroupData* m_pRWeaponGroup;     // +0xD0  r_weapon_group_id
    C_CombatWeaponGroupData* m_pLWeaponGroup;     // +0xD8  l_weapon_group_id
    entitymodule::S_WeaponClassDBData* m_pOppRWeaponClass;  // +0xE0  opp_r_weapon_class_id
    entitymodule::S_WeaponClassDBData* m_pOppLWeaponClass;  // +0xE8  opp_l_weapon_class_id
    C_CombatWeaponGroupData* m_pOppRWeaponGroup;  // +0xF0  opp_r_weapon_group_id
    C_CombatWeaponGroupData* m_pOppLWeaponGroup;  // +0xF8  opp_l_weapon_group_id

    int32_t     blocking_hand;          // +0x100
    bool        virtual_dagger;         // +0x104
    uint8_t     _pad105[3];             // +0x105

    C_CombatGuardTypeData*   m_pGuardType;        // +0x108 guard_type_id
    C_CombatGuardStanceData* m_pGuardStance;      // +0x110 guard_stance_id
    C_CombatGuardStanceData* m_pOppGuardStance;   // +0x118 opp_guard_stance_id
    C_CombatZoneData*        m_pGuardZone;        // +0x120 guard_zone_id
    C_CombatActionTypeData*  m_pActionType;       // +0x128 action_type_id
    C_CombatGuardTypeData*   m_pEndGuardType;     // +0x130 end_guard_type_id
    C_CombatZoneData*        m_pEndGuardZone;     // +0x138 end_guard_zone_id
    C_CombatGuardStanceData* m_pEndGuardStance;   // +0x140 end_guard_stance_id

    int32_t     combat_class_id;        // +0x148
    uint32_t    _pad14C;                // +0x14C
    uint64_t    m_mnFragment;           // +0x150 CryStringT<char> (mn_fragment_id)
    int32_t     m_mnOptionIndex;        // +0x158
    uint32_t    _field15C;              // +0x15C
    uint8_t     m_animScopeData[0x18];  // +0x160
    uint64_t    m_mnTags;               // +0x178 CryStringT<char> (mn_tags)

    int GetActionTypeId() const { return m_pActionType ? m_pActionType->combat_action_type_id : -1; }
};
#pragma pack(pop)
static_assert(sizeof(C_CombatActionSyncHitData) == 0x180);

}  // namespace wh::combatmodule
