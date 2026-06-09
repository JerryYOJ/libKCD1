#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActionSyncAttackData — runtime data row for sync-attack actions.
//
// RTTI: .?AVC_CombatActionSyncAttackData@combatmodule@wh@@
// Base: I_CombatAttackData (abstract, no own vtable found)
// Vtable: 0x1826B0858 (1 virtual: [0] returns +0xE8)
// Size: 0x1E0
//
// Constructed by sub_180F89458 (loader from S_CombatActionSyncAttackTableRow).
// Copy-ctor: sub_180F89024. Another copy variant: sub_180F899E4.
//
// Pointed to by action->m_params.m_data (+0xD8 in C_CombatActorActionSyncAttack).
// Contains the resolved table row from combat_action_sync_attack.xml, with
// foreign-key integer columns resolved to pointers (0xD8..0x180 region).
//
// Field names derived from the loader's source→dest mapping against the
// S_CombatActionSyncAttackTableRow XML column order.
// ---------------------------------------------------------------------------
#pragma pack(push, 4)
class C_CombatActionSyncAttackData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActionSyncAttackData;

    virtual ~C_CombatActionSyncAttackData() = default;  // [0] sub_1806FBF90 returns +0xE8

    // NOTE: action_type_id is FK-resolved into an interned pointer at +0x158
    // (m_pActionType); read the id via GetActionTypeId(). +0x08 is the class hash.
    int32_t     actor_class_hash;       // +0x08  hash lookup key
    int32_t     _field0C;               // +0x0C
    void*       m_pAlignData;           // +0x10  quatt/init_align resolved data
    void*       m_pAlignData2;          // +0x18  (second align block)
    bool        mounted;                // +0x20
    bool        opp_mounted;            // +0x21
    uint8_t     _pad22[6];              // +0x22
    uint64_t    timestamp;              // +0x28
    float       animation_duration;     // +0x30
    float       fade_in;                // +0x34
    float       attack_time_to_spb_start; // +0x38
    float       attack_time_to_start;   // +0x3C
    float       attack_time_to_hit;     // +0x40
    float       attack_time_to_withdraw; // +0x44
    uint64_t    _field48;               // +0x48
    float       attack_time_to_end;     // +0x50
    float       dodge_window;           // +0x54
    float       perfect_block_window;   // +0x58
    float       sync_riposte_window;    // +0x5C
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
    int32_t     side_id;                // +0xD0
    bool        virtual_dagger;         // +0xD4
    uint8_t     _padD5[3];              // +0xD5

    // FK-resolved pointers (integer IDs -> runtime objects)
    void*       m_pAttackType;          // +0xD8  attack_type_id resolved
    void*       m_pAttackZone;          // +0xE0  attack_zone_id resolved
    void*       m_pInputClass;          // +0xE8  input_class_id resolved (vtable[0] returns this)
    void*       m_pAttackingHand;       // +0xF0  attacking_hand resolved
    void*       m_pGuardType;           // +0xF8  guard_type_id resolved
    void*       m_pGuardStance;         // +0x100 guard_stance_id resolved
    void*       m_pField108;            // +0x108
    void*       m_pEndGuardType;        // +0x110 end_guard_type_id resolved
    void*       m_pGuardZone;           // +0x118 guard_zone_id resolved
    void*       m_pEndGuardZone;        // +0x120 end_guard_zone_id resolved
    void*       m_pEndGuardStance;      // +0x128 end_guard_stance_id resolved (UNVERIFIED)
    void*       m_pField130;            // +0x130
    void*       m_pOppGuardStance;      // +0x138 opp_guard_stance_id resolved
    void*       m_pField140;            // +0x140
    void*       m_pRWeaponClass;        // +0x148 r_weapon_class_id resolved
    void*       m_pField150;            // +0x150
    void*       m_pField158;            // +0x158
    void*       m_pField160;            // +0x160
    const int*  m_pActionType;          // +0x168 action_type_id -> interned int (sub_180F51EC8).
                                        //        *m_pActionType == action_type_id (51 = huntAttackMaster, -1 if unresolved)
    void*       m_pField170;            // +0x170
    void*       m_pField178;            // +0x178
    void*       m_pField180;            // +0x180

    int32_t     combat_class_id;        // +0x188 from actor_class_hash lookup
    uint32_t    _pad18C;                // +0x18C
    uint64_t    m_mnFragmentHash;       // +0x190 StringHash of mn_fragment_id
    int32_t     _field198;              // +0x198
    uint32_t    _pad19C;                // +0x19C
    int32_t     m_mnOptionIndex;        // +0x1A0
    int32_t     _field1A4;              // +0x1A4
    uint8_t     m_animScopeData[0x18];  // +0x1A8 anim scope/tag resolved block
    uint64_t    m_mnTagsHash;           // +0x1C0 StringHash of mn_tags
    int32_t     _field1C8;              // +0x1C8
    uint32_t    _pad1CC;                // +0x1CC
    int32_t     _field1D0;              // +0x1D0
    bool        sync_hit_start_by_pc;   // +0x1D4
    bool        has_hit_animevents;     // +0x1D5
    uint8_t     _pad1D6[2];             // +0x1D6
    int32_t     _field1D8;              // +0x1D8
    int32_t     _field1DC;              // +0x1DC

    // action_type_id (51/…) lives behind the FK-resolved m_pActionType pointer.
    int GetActionTypeId() const { return m_pActionType ? *m_pActionType : -1; }
};
#pragma pack(pop)
static_assert(sizeof(C_CombatActionSyncAttackData) == 0x1E0);

}  // namespace wh::combatmodule
