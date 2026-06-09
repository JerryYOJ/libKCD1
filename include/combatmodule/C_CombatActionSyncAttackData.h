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
// C_CombatActionSyncAttackData — runtime data row for sync-attack actions.
//
// POLYMORPHIC. vtable @ 0x1826B0858. Size 0x1E0.
// Loader sub_180F89458 (from S_CombatActionSyncAttackTableRow).
// Pointed to by action->m_params.m_pDataRow.
//
// The +0xD8..+0x180 block holds the FK columns, each resolved by the loader
// into a pointer to its lookup-table Data row (see C_CombatLookupData.h).
// FK offsets/types VERIFIED via the per-column resolver in sub_180F89458.
// ---------------------------------------------------------------------------
#pragma pack(push, 4)
class C_CombatActionSyncAttackData {
public:
    virtual ~C_CombatActionSyncAttackData() = default;  // +0x00 vtable

    int32_t     actor_class_hash;       // +0x08
    int32_t     _field0C;               // +0x0C
    std::map<int32_t, void*> m_oppActorClasses;  // +0x10  resolved opp_actor_classes
                                                 //        ({_Myhead,_Mysize}; _Mysize was the "0x0002")
    bool        mounted;                // +0x20
    bool        opp_mounted;            // +0x21
    uint8_t     _pad22[6];              // +0x22
    uint64_t    timestamp;              // +0x28
    float       animation_duration;     // +0x30
    float       fade_in;                // +0x34
    float       _field38;               // +0x38
    float       _field3C;               // +0x3C
    float       _field40;               // +0x40
    float       _field44;               // +0x44
    uint64_t    _field48;               // +0x48
    float       _field50;               // +0x50
    float       _field54;               // +0x54
    float       _field58;               // +0x58
    float       _field5C;               // +0x5C
    float       hit_distance;           // +0x60
    uint32_t    _field64;               // +0x64
    uint32_t    _field68;               // +0x68
    uint32_t    _field6C;               // +0x6C
    uint32_t    _field70;               // +0x70
    uint32_t    _field74;               // +0x74
    uint32_t    _field78;               // +0x78
    uint32_t    _field7C;               // +0x7C
    uint64_t    _field80;               // +0x80
    uint32_t    _field88;               // +0x88
    uint32_t    _field8C;               // +0x8C
    uint32_t    _field90;               // +0x90
    uint32_t    _field94;               // +0x94
    uint32_t    _field98;               // +0x98
    uint64_t    _field9C;               // +0x9C
    uint32_t    _fieldA4;               // +0xA4
    uint32_t    _fieldA8;               // +0xA8
    uint32_t    _fieldAC;               // +0xAC
    uint32_t    _fieldB0;               // +0xB0
    uint32_t    _fieldB4;               // +0xB4
    uint32_t    _fieldB8;               // +0xB8
    uint32_t    _fieldBC;               // +0xBC
    uint32_t    _fieldC0;               // +0xC0
    uint32_t    _fieldC4;               // +0xC4
    uint32_t    _fieldC8;               // +0xC8
    uint32_t    _fieldCC;               // +0xCC
    int32_t     side_id_raw;            // +0xD0  raw side_id (also resolved into m_pSide)
    bool        virtual_dagger;         // +0xD4
    uint8_t     _padD5[3];              // +0xD5

    // FK-resolved pointers (offsets/types VERIFIED via sub_180F89458).
    C_CombatSideData*        m_pSide;             // +0xD8  side_id
    C_CombatZoneData*        m_pAttackZone;       // +0xE0  attack_zone_id
    C_CombatAttackTypeData*  m_pAttackType;       // +0xE8  attack_type_id
    C_CombatInputClassData*  m_pInputClass;       // +0xF0  input_class_id
    void*                    m_pPoseData0;        // +0xF8  resolved via runtime global manager (qword_18359FE48, gated on C_EntityModule); UNVERIFIED column/target type
    void*                    m_pPoseData1;        // +0x100 resolved via the same manager; UNVERIFIED
    entitymodule::S_WeaponClassDBData* m_pRWeaponClass;     // +0x108 r_weapon_class_id
    entitymodule::S_WeaponClassDBData* m_pLWeaponClass;     // +0x110 l_weapon_class_id
    C_CombatWeaponGroupData* m_pRWeaponGroup;     // +0x118 r_weapon_group_id
    C_CombatWeaponGroupData* m_pLWeaponGroup;     // +0x120 l_weapon_group_id
    entitymodule::S_WeaponClassDBData* m_pOppRWeaponClass;  // +0x128 opp_r_weapon_class_id
    entitymodule::S_WeaponClassDBData* m_pOppLWeaponClass;  // +0x130 opp_l_weapon_class_id
    C_CombatWeaponGroupData* m_pOppRWeaponGroup;  // +0x138 opp_r_weapon_group_id
    C_CombatWeaponGroupData* m_pOppLWeaponGroup;  // +0x140 opp_l_weapon_group_id
    C_CombatGuardTypeData*   m_pGuardType;        // +0x148 guard_type_id
    C_CombatGuardStanceData* m_pGuardStance;      // +0x150 guard_stance_id
    C_CombatGuardStanceData* m_pOppGuardStance;   // +0x158 opp_guard_stance_id
    C_CombatZoneData*        m_pGuardZone;        // +0x160 guard_zone_id
    C_CombatActionTypeData*  m_pActionType;       // +0x168 action_type_id
    C_CombatGuardTypeData*   m_pEndGuardType;     // +0x170 end_guard_type_id
    C_CombatZoneData*        m_pEndGuardZone;     // +0x178 end_guard_zone_id
    C_CombatGuardStanceData* m_pEndGuardStance;   // +0x180 end_guard_stance_id

    int32_t     combat_class_id;        // +0x188
    uint32_t    _pad18C;                // +0x18C
    uint64_t    m_mnFragment;           // +0x190 CryStringT<char> (mn_fragment_id)
    int32_t     _field198;              // +0x198
    uint32_t    _pad19C;                // +0x19C
    int32_t     m_mnOptionIndex;        // +0x1A0
    int32_t     _field1A4;              // +0x1A4
    uint8_t     m_animScopeData[0x18];  // +0x1A8
    uint64_t    m_mnTags;               // +0x1C0 CryStringT<char> (mn_tags)
    int32_t     _field1C8;              // +0x1C8
    uint32_t    _pad1CC;                // +0x1CC
    int32_t     _field1D0;              // +0x1D0
    bool        sync_hit_start_by_pc;   // +0x1D4
    bool        has_hit_animevents;     // +0x1D5
    uint8_t     _pad1D6[2];             // +0x1D6
    int32_t     _field1D8;              // +0x1D8
    int32_t     _field1DC;              // +0x1DC

    int GetActionTypeId() const { return m_pActionType ? m_pActionType->combat_action_type_id : -1; }
};
#pragma pack(pop)
static_assert(sizeof(C_CombatActionSyncAttackData) == 0x1E0);

}  // namespace wh::combatmodule
