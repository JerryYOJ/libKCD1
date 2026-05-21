#pragma once

#include <cstdint>
#include "../framework/CryDeferrable.h"
#include "../framework/C_Signal.h"
#include "../entitymodule/I_InventoryListener.h"
#include "I_Soul.h"
#include "C_SoulPropertyNotifier.h"
#include "S_PerkManagement.h"
#include "S_SoulArchetype.h"

// -----------------------------------------------
// C_Soul -- The main soul class
// -----------------------------------------------
// RTTI: .?AVC_Soul@rpgmodule@wh@@
// Constructor: sub_1804A1B98
// vtable (I_Soul):          0x182228260  (+0x00)
// vtable (CryDeferrable):   0x182228ba0  (+0x08)
// vtable (I_InventoryListener): 0x182228b78  (+0x18)
//
// NOT a singleton. Stored in C_SoulList slot table, keyed by WUID (NOT entity ID).
// Player soul accessed via WUID lookup:
//   sub_180284B04(soulList + 0x48, &wuid)
// In Lua: player.soul (WUID at player.soul.__ThisWUID)
//
// Total size: 0xC38 (last ctor write at +0xC34)

#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"

namespace wh::rpgmodule {

// -----------------------------------------------
// C_CombatSoul -- combat state sub-object
// -----------------------------------------------
// RTTI: .?AVC_CombatSoul@rpgmodule@wh@@
// Constructor: sub_18058EA84
// Embedded at C_Soul + 0xD8, size = 0x88
class C_CombatSoul {
public:
    virtual ~C_CombatSoul();

    // Two C_Signal<bool> members (each 0x30 bytes)
    wh::shared::C_Signal<bool> m_signal1;  // +0x08  combat state signal
    wh::shared::C_Signal<bool> m_signal2;  // +0x38  second combat signal

    // Combat soul data:
    void*       m_pOwnerSoul;           // +0x68  back-pointer to C_Soul
    uint64_t    m_combatTarget;         // +0x70  (zeroed — current target entity?)
    float       m_combatParams[2];      // +0x78  (init via _mm_unpacklo_ps)
    uint32_t    m_combatFlags;          // +0x80  (init 0)
    char        _pad84[4];              // +0x84
};
static_assert(sizeof(C_CombatSoul) == 0x88);

// -----------------------------------------------
// S_SoulStatBlock -- stat/attribute tracking
// -----------------------------------------------
// Constructor: sub_1806C5924
// Embedded at C_Soul + 0x1A0, size = 0x1E0
// Contains base stats, faction, derived stat cache
struct S_SoulStatBlock {
    // Initialization from xmmword constants (base stat values / archetype template)
    uint8_t     m_baseData[0x34];       // +0x00  (3 xmmwords + 1 dword; base stats, template)
    char        _pad34[4];              // +0x34

    // Sub-init at +0x38 (sub_1806C5B7C) — stat modifiers container (size ~0x90)
    char        m_modifiers[0x90];      // +0x38

    // Cached derived values
    uint8_t     m_cachedData[0x10];     // +0xC8  (xmmword_1834F7B50)

    // Timer/cooldown (sub_18061A378)
    uint64_t    m_timer;                // +0xD8

    int32_t     m_unkE0;                // +0xE0  (init -1)
    int32_t     m_unkE4;                // +0xE4  (init 0)
    int32_t     m_unkE8;                // +0xE8  (init -1)
    int32_t     m_unkEC;                // +0xEC  (init 1)
    int32_t     m_unkF0;                // +0xF0  (init -1)
    uint32_t    m_factionId;            // +0xF4  (init 0) — accessed via sub_18064D750 as soul+0x294
    uint32_t    m_unkF8;                // +0xF8  — accessed as soul+0x298 in GetDerivedStat
    uint32_t    m_unkFC;                // +0xFC  (init 0)
    uint8_t     m_unk100;               // +0x100 (init 0)
    char        _pad101[3];             // +0x101
    uint32_t    m_unk104;               // +0x104 (init 0, written as QWORD with +0x108)
    uint32_t    m_baseStatValue;        // +0x108 (init 0) — accessed as soul+0x2A8 in GetDerivedStat case 0

    // 8 derived-stat base values (init 0xA = 10 each)
    // Covers: +0x10C, +0x110, +0x114, +0x118, +0x11C, +0x120, +0x124, +0x128
    uint32_t    m_derivedStatBase[8];   // +0x10C

    uint32_t    m_unk12C;               // +0x12C (init 0)

    // Sub-init at +0x130 (sub_1806C5A54)
    char        m_unk130[0x20];         // +0x130

    // Tracker container at +0x150 (sub_1804217C8, 16 entries, 9 params)
    char        m_tracker[0x90];        // +0x150
};
static_assert(sizeof(S_SoulStatBlock) == 0x1E0);

class C_Soul : public I_Soul,                              // vtable at +0x00
               public UnsafeOp::CryDeferrable,             // vtable at +0x08, member at +0x10
               public wh::entitymodule::I_InventoryListener // vtable at +0x18
{
public:
    uint64_t                m_wuid;                  // +0x20  WUID (World Unique ID) — 64-bit key for C_SoulList slot lookup
                                                     //        Format: HIBYTE=0x05, WORD1=generation, LOWORD=slot index
                                                     //        Verified: Lua reads this as player.soul.__ThisWUID
    uint64_t                m_guidHigh;              // +0x28  Upper half of original CryGUID (constant, not used in lookups)

    // CryStringT — heap-allocated string
    void*                   m_soulName;              // +0x30  CryStringT ("<not-initialized-soul>")
    uint8_t                 m_soulNameData[8];       // +0x38  (xmmword init — CryStringT inline buffer?)
    char                    _pad40[8];               // +0x40

    // Embedded notifier (size 0x20)
    C_SoulPropertyNotifier  m_propertyNotifier;      // +0x48  (vtable at +0x48)

    // Signal: fires on soul property changes, connected to UI
    wh::shared::C_Signal<I_Soul&>  m_soulSignal;    // +0x68  (size 0x30, to +0x98)

    // Buff/modifier linked list head + related pointers
    // Walked in GetDerivedStat as: while(node) { ...; node = *(node+0x20); }
    // Each node has: +0x10 = active flag (byte), +0x28 = type (dword), +0x20 = next ptr
    void*                   m_pBuffListHead;         // +0x98  linked list of active buff/modifier nodes
    void*                   m_buffPtrs[6];           // +0xA0  (6 QWORDs zeroed, to +0xD0)
    uint8_t                 m_bBuffDirty;            // +0xD0  (flag byte)
    char                    _padD1[7];               // +0xD1

    // C_CombatSoul embedded object
    C_CombatSoul            m_combatSoul;            // +0xD8  (size 0x88, to +0x160)

    void*                   m_pCombatData;           // +0x160 (zeroed -- used by GetDerivedStat case 0xD)

    // Additional soul identity / parent chain
    uint8_t                 m_identityData[0x10];    // +0x168 (xmmword init from xmmword_1822ADA80)
    uint64_t                m_unk178;                // +0x178
    uint64_t                m_unk180;                // +0x180
    uint64_t                m_unk188;                // +0x188
    uint64_t                m_unk190;                // +0x190
    C_Soul*                 m_pParentSoulRef;        // +0x198 (= this in constructor; for soul hierarchy)

    // S_SoulStatBlock — base stats, faction, derived stat data
    S_SoulStatBlock         m_statBlock;             // +0x1A0  (size 0x1E0, to +0x380)

    // Buff/effect state (zeroed 0x40 bytes)
    uint64_t                m_buffState[6];          // +0x380  (48 bytes, zeroed)
    void*                   m_pTimeSource;           // +0x3B0  (init via sub_18023E8E0)
    uint64_t                m_buffState2;            // +0x3B8
    uint32_t                m_buffFlags;             // +0x3C0  (init 0)
    char                    _padC4[4];               // +0x3C4
    void*                   m_pBuffConfig;           // +0x3C8  (sub_18028D060() + 0xC)

    // ============================================
    // PERK MANAGEMENT
    // ============================================
    S_PerkManagement        m_perkMgmt;              // +0x3D0  (size 0x670, to +0xA40)

    // Within m_perkMgmt:
    //   +0x3D0 + 0x0D8 = +0x4A8 : S_PerkSubsystem m_statPerks
    //     +0x4A8 + 0x00C = +0x4B4 : stat levels array (accessed as soul+8*stat_id+0x4B4)
    //     +0x4A8 + 0x1E8 = +0x690 : C_PerkList (stat perks)
    //       +0x690 + 0x058 = +0x6E8 : S_PerkPointCounters* <- PERK POINT POINTER
    //
    //   +0x3D0 + 0x380 = +0x750 : S_PerkSubsystem m_skillPerks
    //     +0x750 + 0x1E8 = +0x938 : C_PerkList (skill perks)

    // ============================================
    // POST-PERK DATA (init via sub_1805937AC)
    // ============================================
    // Inventory/equipment-related state, size ~0x160
    uint64_t                m_equipPtrs[3];          // +0xA40  (zeroed)
    char                    m_equipData[0x08];       // +0xA58
    uint32_t                m_unkA60;                // +0xA60  (init -1)
    char                    _padA64[8];              // +0xA64
    uint32_t                m_unkA6C;                // +0xA6C  (used in GetDerivedStat case 2 — index into table)
    char                    _padA70[0x24];           // +0xA70
    // Cached derived stat array (sub_180549518 recomputes)
    // Accessed as soul+0xA94+offset:
    //   +0x00 = derived[0], +0x04 = derived[3], +0x08 = derived[5]
    //   +0x0C = derived['H'], +0x10 = derived[0x55], +0x14 = derived[0x1D]
    //   +0x18 = derived[0x25], +0x1C = derived[0x26], +0x20 = derived[0x62]
    //   +0x28 = derived[0x19], +0x2C = derived[0x63], +0x30 = derived[0x1A]
    char                    m_derivedStatCache[0x50];// +0xA94
    char                    _padAE4[0xBC];           // +0xAE4

    // ============================================
    // STATE & FLAGS
    // ============================================
    int32_t                 m_soulState;             // +0xBA0 (init = 2)
    char                    _padBA4[4];              // +0xBA4
    uint64_t                m_unkBA8_block[4];       // +0xBA8 (memset 0x20 bytes)
    S_SoulArchetype*        m_pArchetype;            // +0xBC8  borrowed ptr into C_SoulArchetypeDatabase (global 0x1835AB090)
                                                     //         GetGender: m_pArchetype->gender_id
                                                     //         GetDerivedStat uses: body_base_armor, base_stamina, relative_vitality_to_stamina
                                                     //         inventory_capacity_multiplier at m_pArchetype+0x28
    uint64_t                m_unkBD0;                // +0xBD0  (init: &dword_1835ACE80)
    uint64_t                m_unkBD8;                // +0xBD8  (init: &unk_1829CF9D8)
    uint64_t                m_unkBE0;                // +0xBE0 (zeroed)
    // Entity binding (set by sub_18030F274 during soul→entity binding)
    // 2 slots for compound entities (e.g. horse+rider)
    void*                   m_pBoundEntity;          // +0xBE8  IEntity* — primary bound CryEngine entity
    void*                   m_pBoundEntity2;         // +0xBF0  IEntity* — secondary entity (compound)
    uint32_t                m_soulFlagsExt;          // +0xBF8 (byte: bit6=stat_override, bit7=has_ability)
    char                    _padBFC[4];              // +0xBFC
    CryGUID                 m_unkGuidC00;            // +0xC00 (init to null GUID qword_183012EA0)
    uint64_t                m_unkC10;                // +0xC10 (zeroed)
    uint64_t                m_unkC18;                // +0xC18 (zeroed)
    void*                   m_unkPtrC20;             // +0xC20 (qword_183501028)

    // Self-reference and property callback
    C_Soul*                 m_pSelf;                 // +0xC28 (= this)
    uint8_t                 m_bIsPropertyDirty;      // +0xC30 (init 0)
    char                    _padC31[3];              // +0xC31
    uint32_t                m_propertyCallbackId;    // +0xC34 (init 0)

    // ============================================
    // Key accessor for perk points:
    //
    //   S_PerkPointCounters* GetStatPerkPoints() {
    //       return m_perkMgmt.m_statPerks.m_perkList.m_pPerkPoints;
    //       // = *(this + 0x6E8)
    //   }
    //
    //   uint16_t GetMainLevelPerkPoints() {
    //       return GetStatPerkPoints()->mainLevelPoints;
    //       // = *(uint16_t*)(*(this + 0x6E8) + 0x66)
    //   }
    // ============================================

    // ============================================
    // Parent soul chain (for compound entities like horse+rider):
    //   sub_18064D750 walks *(soul + 0x480) until null, then reads
    //   *(root + 0x294) as faction ID.
    //   +0x480 = soul+0x3D0+0xB0 = within S_PerkManagement._pad000
    //   This suggests S_PerkManagement+0xB0 is a parent-soul pointer.
    // ============================================
};
static_assert(sizeof(C_Soul) == 0xC38);

}  // namespace wh::rpgmodule
