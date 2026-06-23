#pragma once
#include <cstdint>
#include "I_CombatAttackData.h"
#include "C_CombatZoneMappingData.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActionAttackData -- the FK-resolved runtime "Data" for one attack
// candidate (built from S_CombatActionAttackTableRow by loader sub_180F66288).
//
// RTTI: .?AVC_CombatActionAttackData@combatmodule@wh@@ (vtable 0x1826b0628,
// COL 0x182483e00). Size 0x1F8 (factory sub_180F7DBAC strides 0x1F8). Single
// inheritance from I_CombatAttackData (one vtable slot at offset 0).
//
// This is what sub_18045FD18 enumerates (as records {this*, u8, u8}) and what
// CreateAndDispatch bakes into the built action at action+0xD8.
//
// PER-CANDIDATE DIRECTION (runtime-confirmed): m_selectionKeyZone->m_matchKey
// (+0xD8 -> +0x00) is the swing zone -- the 5 directional rows enumerate with
// matchKey = 0,1,2,3,4 (Head/UL/UR/LL/LR), one candidate per direction. By contrast
// m_executedZone/m_aimZone point at SHARED default mappings (m_zoneId == 1 on every
// directional candidate), so they are NOT the direction; the earlier
// "GetExecutedZone() picks the direction" model was wrong (proven in-game).
//
// The three zone FKs resolve from three different registries during ctor:
//   +0xD8 m_selectionKeyZone <- row+0xC4 (xmmword_18359D290)  -- selection-match key
//   +0xE0 m_aimZone          <- row+0xC8 (qword_18359B7E0)    -- aim zone (-> state+0xC10); vtable[0] getter
//   +0xE8 m_executedZone     <- row+0xCC (xmmword_18359C2D0)  -- EXECUTED/visible zone (-> state+0xBF4)
// [V] workflow wf_05aec32f (candidate-class verdict: confirmed).
// ---------------------------------------------------------------------------
class C_CombatActionAttackData : public I_CombatAttackData {
public:
    // ---- known members (offsets are from the class base = the vtable ptr) ----
    uint32_t        m_id;                    // +0x08  row+0x00 (also a registry key)
    uint32_t        m_field0C;               // +0x0C  row+0x04
    uint8_t         m_subItems[0x10];        // +0x10  2-qword container (alloc sub_180208FD8) -- element type unresolved
    uint8_t         m_flag20;                // +0x20  row+0x10
    uint8_t         m_flag21;                // +0x21  row+0x11
    uint8_t         _pad22[6];               // +0x22
    uint64_t        m_field28;               // +0x28  row+0x18
    uint8_t         m_tuning[0xA0];          // +0x30  scalar tuning block copied from row+0x20..0xBC (damage/timing/cost; not individually decoded)
    uint32_t        m_weaponAimConfigIndex;  // +0xD0  row+0xC0; indexes state weapon-aim config: *(state+0xC80 + 4*this)
    uint8_t         m_flagD4;                // +0xD4  row+0x118
    uint8_t         _padD5[3];               // +0xD5
    C_CombatZoneMappingData* m_selectionKeyZone; // +0xD8  selection-match FK (compared at ->m_matchKey)
    C_CombatZoneMappingData* m_aimZone;          // +0xE0  aim zone FK (-> state+0xC10); returned by vtable[0]
    C_CombatZoneMappingData* m_executedZone;     // +0xE8  EXECUTED/visible zone FK (-> state+0xBF4); the directional lever
    void*           m_dataF0;                // +0xF0  entity-module Data* (row+0xD0)
    void*           m_dataF8;                // +0xF8  entity-module Data* (row+0xD4)
    void*           m_data100;               // +0x100 sub_180F7430C(row+0xD8)
    void*           m_data108;               // +0x108 sub_180F7430C(row+0xDC)
    void*           m_data110;               // +0x110 sub_180F72C20(row+0xE0)
    void*           m_data118;               // +0x118 sub_180F72C20(row+0xE4)
    void*           m_data120;               // +0x120 sub_180F7430C(row+0xE8)
    void*           m_data128;               // +0x128 sub_180F7430C(row+0xEC)
    void*           m_data130;               // +0x130 sub_180F72C20(row+0xF0)
    void*           m_data138;               // +0x138 sub_180F72C20(row+0xF4)
    void*           m_data140;               // +0x140 sub_18045CF9C() default-ptr
    void*           m_data148;               // +0x148 sub_180F51F70()
    void*           m_data150;               // +0x150 sub_180F51F70()
    C_CombatZoneMappingData* m_zone158;      // +0x158 sub_18045F6E8() (default-zone registry, as +0xD8)
    void*           m_attackCategory;        // +0x160 C_*Data* attack-category (id at +0); filtered via sub_1802195AC
    void*           m_data168;               // +0x168 sub_18045CF9C()
    C_CombatZoneMappingData* m_zone170;      // +0x170 sub_18045F6E8()
    void*           m_data178;               // +0x178 sub_180F51F70()
    uint32_t        m_field180;              // +0x180 init 0; later set from per-action registry record
    uint8_t         _pad184[4];              // +0x184
    uint8_t         m_nameHash[0x10];        // +0x188 StringHash handle (row+0x120 string)
    uint32_t        m_animFragmentId;        // +0x198 animation-set enum id (row+0x120)
    uint32_t        m_field19C;              // +0x19C row+0x128
    uint8_t         m_resolutions[0x18];     // +0x1A0 boost::container::vector-like (resolution/info list; sub_180478FC8)
    uint8_t         m_nameHash2[0x10];       // +0x1B8 StringHash handle (row+0x130 string)
    uint32_t        m_field1C8;              // +0x1C8 row+0x138
    uint32_t        m_field1CC;              // +0x1CC row+0x13C
    uint32_t        m_field1D0;              // +0x1D0 row+0x140
    uint32_t        m_field1D4;              // +0x1D4 row+0x144
    uint32_t        m_field1D8;              // +0x1D8 row+0x148
    uint8_t         m_flag1DC;               // +0x1DC row+0x14C
    uint8_t         m_flag1DD;               // +0x1DD row+0x14D
    uint8_t         _pad1DE[2];              // +0x1DE
    uint8_t         m_obj1E0[0x10];          // +0x1E0 16-byte sub-object (sub_180F65B44, row+0x150)
    uint8_t         m_flag1F0;               // +0x1F0 row+0x158 (LAST field)
    uint8_t         _pad1F1[7];              // +0x1F1

    // vtable[0] override: returns the AIM zone-mapping (+0xE0). Matches the binary
    // getter sub_1806fbe30 ("mov rax,[rcx+0xE0]; ret").
    C_CombatZoneMappingData* GetAimZoneMapping() override { return m_aimZone; }

    // --- non-virtual helpers (direct field derefs; the engine reads these too) ---
    // The per-candidate DIRECTION zone (0..4 = Head/UL/UR/LL/LR); the directional-pick
    // key (m_selectionKeyZone->m_matchKey). -1 on the non-directional/special rows.
    // [runtime-confirmed: the 5 directional candidates carry matchKey 0..4.]
    uint32_t GetSelectionZone() const {
        return m_selectionKeyZone ? m_selectionKeyZone->m_matchKey : 0xFFFFFFFFu;
    }
    // The EXECUTED zone committed to state+0xBF4 at OnEnter -- a SHARED default (==1 on
    // every directional candidate); NOT the per-candidate direction. -1 if unset.
    uint32_t GetExecutedZone() const {
        return m_executedZone ? m_executedZone->m_zoneId : 0xFFFFFFFFu;
    }
    // The aim zone id (-> state+0xC10).
    uint32_t GetAimZone() const {
        return m_aimZone ? m_aimZone->m_zoneId : 0xFFFFFFFFu;
    }
};
static_assert(sizeof(C_CombatActionAttackData) == 0x1F8, "C_CombatActionAttackData must be 0x1F8");
// (offsets verified by layout-dump, not offsetof: this is a polymorphic type.)

}  // namespace wh::combatmodule
