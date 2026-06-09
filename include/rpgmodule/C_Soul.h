#pragma once

#include <cstdint>
#include <vector>
#include <set>
#include <utility>

#include "../framework/CryDeferrable.h"
#include "../framework/C_Signal.h"
#include "../framework/WUID.h"
#include "../entitymodule/I_InventoryListener.h"
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"
#include "../CryEngine/CryCommon/CryString.h"   // CryStringT<char> (8-byte refcounted string handle)

#include "I_Soul.h"
#include "I_CombatSoul.h"
#include "C_SoulPropertyNotifier.h"
#include "S_PerkManagement.h"
#include "S_SoulArchetype.h"
#include "buff/S_ModifierNode.h"

// -----------------------------------------------
// Forward declarations (pointer members only)
// -----------------------------------------------
namespace Offsets { struct IEntity; }
namespace wh { namespace entitymodule { class C_Inventory; class C_EquipmentManager; } }

namespace wh::rpgmodule {

class C_BuffInstanceBase;   // owned (move-only) combat buff instance, C_CombatSoul+0x70
class C_DogSoulComponent;   // lazily-created dog-soul extension, C_Soul+0x160 (partial RE; size 0x18)
struct S_SocialClass;       // POD row from rpg/social_class (C_SocialClassDatabase), C_Soul+0xBD0

// ===========================================================================
// C_Soul -- the RPG "soul": stats, skills, perks, buffs, faction, inventory,
//           combat and movement state of any actor/horse/animal in the world.
// ===========================================================================
// RTTI:  .?AVC_Soul@rpgmodule@wh@@
// Ctor:  wh::rpgmodule::C_Soul::Ctor_1804A1B98
// Dtor:  sub_180590A78 (scalar-deleting/teardown; verified for member ownership)
//
// vtable (I_Soul, primary):       0x182228260  (+0x00, slot0 GetWUID = lea rax,[rcx+0x20])
// vtable (CryDeferrable):         0x182228ba0  (+0x08)
// vtable (I_InventoryListener):   0x182228b78  (+0x18 — all 4 slots -> sub_1806A1144,
//                                  "mark derived-stat cache dirty": inc m_generation,
//                                  sub_1806699C8(&m_computed,2) — see m_derivedStatCache)
//
// NOT a singleton. Stored in the C_SoulList slot table keyed by WUID (tag byte 5),
// looked up via C_SoulList::LookupByWUID_180284B04. In Lua: player.soul, with the
// WUID exposed as player.soul.__ThisWUID.
//
// Total size: 0xC38.
// ===========================================================================

// Modifier-list category (index into C_Soul::m_modifierLists). Names cross-referenced
// from the 7 staging lists of C_SoulBuffInstance (m_statMods..m_soulLevelMods), which
// C_SoulBuffInstance::CommitModifiers moves into the soul's sorted lists at +0x98..+0xC8.
enum class E_ModifierCategory : int32_t {
    Stat       = 0,   // base stats        (walked by GetModifiedStatValue sub_180229880)
    Skill      = 1,
    DerivedStat= 2,   // (fed to C_RPGParams::AccumulatePerkStat_180229980)
    Detail     = 3,
    Movement   = 4,
    Special    = 5,   // (walked with wildcard query 0xFFFFFFFF by sub_180AA0770)
    SoulLevel  = 6,
    Count      = 7,
};

// -----------------------------------------------
// C_CombatSoul -- combat-state sub-object embedded at C_Soul+0xD8 (size 0x88)
// -----------------------------------------------
// RTTI: .?AVC_CombatSoul@rpgmodule@wh@@ ; ctor sub_18058EA84(this, owningSoul)
class C_CombatSoul : public I_CombatSoul                 // +0x00 I_CombatSoul vtable (0x182229ac0)
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatSoul;
    wh::shared::C_Signal<bool>  m_signal0;               // +0x08  (connect/disconnect via I_CombatSoul slots 2/3)
    wh::shared::C_Signal<bool>  m_signal1;               // +0x38  (connect/disconnect via I_CombatSoul slots 0/1)
    C_Soul*                     m_owner;                 // +0x68  owning soul (ctor arg)
    C_BuffInstanceBase*         m_combatBuff;            // +0x70  owning, MOVE-ONLY combat buff instance
                                                         //        (create sub_18044A448; move-assign sub_18044B89C;
                                                         //         release sub_180448C00 = virtual destroy). lazy/null.
    float                       m_floatA;                // +0x78  init 0.0f  (semantics UNVERIFIED)
    float                       m_floatB;                // +0x7C  init 0.0f  (semantics UNVERIFIED)
    uint32_t                    m_flags;                 // +0x80  init 0     (semantics UNVERIFIED)
    char                        _pad84[4];               // +0x84  tail padding -> size 0x88
};
static_assert(sizeof(C_CombatSoul) == 0x88);

// -----------------------------------------------
// S_SoulStatBlock sub-structures (POD; ctor writes no vtable)
// -----------------------------------------------

// 16-byte pair of CryString handles, default-constructed by sub_1806E06D8.
// Each handle is interned/assigned via sub_18061A378 (GameContext string manager).
// e.g. wait-config slot[0] = {"dummyWait", "6:30"}.
using S_StringPair = std::pair<CryStringT<char>, CryStringT<char>>;  // +0x00 first, +0x08 second
static_assert(sizeof(S_StringPair) == 0x10);

// statblock+0x38 .. +0xC7 ; ctor sub_1806C5B7C -> sub_1806C5BE0.
struct S_StatModifierBlock {
    wh::framework::WUID m_keys[8];       // +0x00  all null (0xFFFFFFFFFFFFFFFF)
    int32_t             m_flags;         // +0x40  = 1
    float               m_baseValue;     // +0x44  = 1.0f
    // +0x48..+0x8F: 18 dwords interleaving float scale (1.0f) / 0 / invalid-id sentinel
    // (0x00808080 == dword_1829D2AB8). No clean repeating stride is provable from the
    // ctor writes, so this tail is modelled as a dword array. [UNVERIFIED sub-structure]
    uint32_t            m_modData[18];   // +0x48
};
static_assert(sizeof(S_StatModifierBlock) == 0x90);

// statblock+0x130 .. +0x1DF ; ctor sub_1806C5A54 (slot array built by sub_1804217C8).
struct S_SoulWaitConfig {
    wh::framework::WUID m_ids[4];        // +0x00  all null
    S_StringPair        m_slots[9];      // +0x20  slot[0] = {"dummyWait","6:30"}, rest empty
};
static_assert(sizeof(S_SoulWaitConfig) == 0xB0);

// -----------------------------------------------
// S_SoulStatBlock -- embedded at C_Soul+0x1A0 (size 0x1E0). Ctor sub_1806C5924.
// -----------------------------------------------
// Holds base stat/skill bookkeeping, faction id, derived-stat inputs, the stat
// modifier block, and the per-soul "wait" string table. POD (no vtable).
struct S_SoulStatBlock {
    int64_t             m_unk000;        // +0x000 = 0                     [UNVERIFIED]
    int64_t             m_unk008;        // +0x008 = 0                     [UNVERIFIED]
    wh::framework::WUID m_unk010;        // +0x010 = null WUID             [UNVERIFIED]
    wh::framework::WUID m_unk018;        // +0x018 = null WUID             [UNVERIFIED]
    wh::framework::WUID m_unk020;        // +0x020 = null WUID             [UNVERIFIED]
    wh::framework::WUID m_unk028;        // +0x028 = null WUID             [UNVERIFIED]
    int32_t             m_unk030;        // +0x030 = 0                     [UNVERIFIED]
    char                _pad034[4];      // +0x034 alignment
    S_StatModifierBlock m_statModifiers; // +0x038
    wh::framework::WUID m_cachedKey0;    // +0x0C8 = null WUID             [UNVERIFIED]
    wh::framework::WUID m_cachedKey1;    // +0x0D0 = null WUID             [UNVERIFIED]
    CryStringT<char>    m_strD8;         // +0x0D8 ("" via sub_18061A378)
    int32_t             m_unkE0;         // +0x0E0 = -1                    [UNVERIFIED]
    int32_t             m_unkE4;         // +0x0E4 = 0                     [UNVERIFIED]
    int32_t             m_unkE8;         // +0x0E8 = -1                    [UNVERIFIED]
    int32_t             m_unkEC;         // +0x0EC = 1                     [UNVERIFIED]
    int32_t             m_unkF0;         // +0x0F0 = -1                    [UNVERIFIED]
    uint32_t            m_factionId;     // +0x0F4 = 0   (GetFactionIDInternal sub_18064D750, soul+0x294)
    int32_t             m_derivedStatInputA; // +0x0F8 = 0 (GetDerivedStat input, soul+0x298) [LIKELY]
    int32_t             m_unkFC;         // +0x0FC = 0                     [UNVERIFIED]
    uint8_t             m_unk100;        // +0x100 = 0                     [UNVERIFIED]
    char                _pad101[3];      // +0x101
    int32_t             m_unk104;        // +0x104 = 0                     [UNVERIFIED]
    int32_t             m_derivedStatInputB; // +0x108 = 0 (GetDerivedStat input, soul+0x2A8) [LIKELY]
    int32_t             m_derivedStatBase[8]; // +0x10C = {10,10,10,10,10,10,10,10}
    int32_t             m_unk12C;        // +0x12C = 0                     [UNVERIFIED]
    S_SoulWaitConfig    m_waitConfig;    // +0x130
};
static_assert(sizeof(S_SoulStatBlock) == 0x1E0);

// -----------------------------------------------
// Derived-stat cache -- C_Soul+0xA94 (size 0x48).
// -----------------------------------------------
// Lazily computed; recompute sub_180549518(&cache, soul); fillers sub_1802CEAF4 /
// sub_180549884 / sub_18054965C / sub_1806418E8. Read by GetDerivedStatFull
// sub_180339980. The float fields are E_DerivedStat values (id in comment).
struct S_SoulDerivedStatCache {
    float    m_derived0;          // +0x00  E_DerivedStat::Cha (charisma, 0x00)
    float    m_derived3;          // +0x04  E_DerivedStat::Evi (visibility, 0x03)
    float    m_derived5;          // +0x08  E_DerivedStat::Con (conspicuousness, 0x05)
    float    m_derived72;         // +0x0C  E_DerivedStat::Drt (0x48)
    float    m_derived85;         // +0x10  E_DerivedStat::Bld (0x55)
    float    m_derived29;         // +0x14  E_DerivedStat::Noi (noise, 0x1D)
    float    m_derived37;         // +0x18  E_DerivedStat::Aco (0x25) (= m_derived98 alias)
    float    m_derived38;         // +0x1C  E_DerivedStat::Caw (carry weight, 0x26)
    float    m_derived98;         // +0x20  E_DerivedStat::Eqw (equipped weight, 0x62; = equipMgr+0x80)
    float    m_equipField84;      // +0x24  internal (= equipMgr+0x84; not publicly returned)
    float    m_derived25;         // +0x28  E_DerivedStat::Oad (0x19)
    float    m_derived99;         // +0x2C  E_DerivedStat::Pla (0x63)
    float    m_derived26;         // +0x30  E_DerivedStat::Owa (0x1A)
    int32_t  m_dominantItemType;  // +0x34  item-type id (sub_1802CEAF4)
    int32_t  m_skillId;           // +0x38  skill enum id (sub_180549884); ctor inits -1
    uint8_t  m_flag3C;            // +0x3C
    uint8_t  m_flag3D;            // +0x3D
    uint8_t  m_flag3E;            // +0x3E  !(itemFlags & 2)
    uint8_t  m_flag3F;            // +0x3F  !(itemFlags & 4)
    uint8_t  m_computed;          // +0x40  main dirty/valid flag (cleared on inventory change)
    uint8_t  m_computed1A;        // +0x41  derived(0x1A) dirty flag
    char     _pad42[2];           // +0x42
    uint32_t m_generation;        // +0x44  bumped on each reset / inventory change
};
static_assert(sizeof(S_SoulDerivedStatCache) == 0x48);

// -----------------------------------------------
// Stat source slot -- C_Soul+0xAE0 inline array of 7 (element size 0x18).
// -----------------------------------------------
// m_source is a refcounted polymorphic handle (released via vtbl[0x10] then a
// deleting dtor vtbl[0x50](this,1)); concrete interface type UNVERIFIED.
struct S_SoulStatSource {
    void*               m_source;        // +0x00  polymorphic handle (default null)
    wh::framework::WUID m_id[2];         // +0x08  default all-0xFF (two null WUIDs) [LIKELY]
};
static_assert(sizeof(S_SoulStatSource) == 0x18);

// ===========================================================================
// C_Soul
// ===========================================================================
class C_Soul : public I_Soul,                              // +0x00 vtable
               public UnsafeOp::CryDeferrable,             // +0x08 vtable, +0x10 m_deferState
               public wh::entitymodule::I_InventoryListener // +0x18 vtable
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Soul;
    // ---------------------------------------------------------------- identity
    wh::framework::WUID     m_wuid;                  // +0x20  this soul's WUID (type tag 5); LookupByWUID key
    wh::framework::WUID     m_entityWuid;            // +0x28  owning entity's WUID; SearchByValue lookup key [LIKELY]
    CryStringT<char>        m_soulName;              // +0x30  ("<not-initialized-soul>")
    CryGUID                 m_guid;                  // +0x38  unique soul GUID (CoCreateGuid / entity-derived),
                                                     //        registered in the global GUID->C_Soul map
    C_SoulPropertyNotifier  m_propertyNotifier;      // +0x48  (size 0x20; subscribes property id 0x54)
    wh::shared::C_Signal<I_Soul&>  m_soulSignal;     // +0x68  (size 0x30) fires on soul property changes

    // ------------------------------------------------------- active modifiers
    // 7 sorted, non-owning intrusive list heads of S_ModifierNode (nodes chain via
    // S_ModifierNode::pNextSorted at +0x20). Buffs commit their staged modifiers here
    // via C_SoulBuffInstance::CommitModifiers. Index with E_ModifierCategory.
    S_ModifierNode*         m_modifierLists[7];      // +0x98 .. +0xC8
    bool                    m_modifiersDirty;        // +0xD0  participates in the activation gate (sub_180449568)
    char                    _padD1[7];               // +0xD1

    // -------------------------------------------------------------- combat soul
    C_CombatSoul            m_combatSoul;            // +0xD8  (size 0x88)

    // ----------------------------------------------------- identity (cont'd)
    C_DogSoulComponent*     m_dogSoulComponent;      // +0x160 lazily created for dog souls (archetype race==6);
                                                     //        used by GetDerivedStatFull case 0xD
    CryGUID                 m_sharedSoulGuid;        // +0x168 from entity Property "sharedSoulGuid"; metarole /
                                                     //        shared-soul-data lookup key
    void*                   m_unk178;                // +0x178 ptr to a 0x18-byte heap container owning a buffer
                                                     //        (referenced as owner+0x178 by the combat-buff path) [UNVERIFIED]
    std::vector<void*>      m_unk180;                // +0x180 {begin,end,cap}; element type UNVERIFIED
    C_Soul*                 m_self;                  // +0x198 self back-pointer (= this)

    // ----------------------------------------------------------- stat block
    S_SoulStatBlock         m_statBlock;             // +0x1A0  (size 0x1E0)

    // ----------------------------------------------------- buff / effect state
    std::vector<void*>      m_unk380;                // +0x380 buff/effect vector (element size 8; type UNVERIFIED)
    std::vector<void*>      m_unk398;                // +0x398 buff/effect vector (element STRIDE 0x10; type UNVERIFIED)
    std::set<uint64_t>      m_unk3B0;                // +0x3B0 std::set ({_Myhead,_Mysize}); key type UNVERIFIED
    uint32_t                m_buffStateFlags;        // +0x3C0 exposed by I_Soul slot[33] (sub_1804A67C0); meaning UNVERIFIED
    char                    _pad3C4[4];              // +0x3C4
    CryStringT<char>        m_str3C8;                // +0x3C8 (default empty); purpose UNVERIFIED

    // ---------------------------------------------------------- perk management
    S_PerkManagement        m_perkMgmt;              // +0x3D0  (size 0x670)
    // Within m_perkMgmt (soul-relative offsets):
    //   +0x480 = parent-soul pointer (compound entities; walked by GetFactionIDInternal)
    //   +0x4A8 = m_activePerks (S_PerkSubsystem) — the LIVE subsystem; holds BOTH
    //            stat levels (+0x4B4) AND skill levels (+0x540)
    //   +0x690 = m_activePerks.m_perkList (C_PerkList; returned by GetActivePerkList)
    //   +0x6E8 = m_activePerks' live S_PerkPointCounters* (stat + skill + main perk points)
    //   +0x750 = m_basePerks (S_PerkSubsystem) — the archetype-derived BASELINE: rebuilt from
    //            base stats + perk/skill tables (sub_1811F7FB0), then copied wholesale into
    //            m_activePerks (sub_1805A3F34) at soul create/reset/clone. Not serialized
    //            (recomputed on load); never the queried subsystem.

    // ----------------------------------------- RPG movement / locomotion state
    // Constructed by sub_1805937AC(soul+0xA40) (+ sub_180593854). The movement
    // updater sub_18033B73C and flag accessors sub_18033BCD4/sub_18033BF10 operate
    // on the object at soul+0xA40.
    std::vector<void*>      m_statListeners;         // +0xA40 non-owning listener ptrs (notified via vtbl[0x10])
    float                   m_unkA58;                // +0xA58 = 0     [UNVERIFIED]
    float                   m_unkA5C;                // +0xA5C = 0     [UNVERIFIED]
    float                   m_unkA60;                // +0xA60 = 0     [UNVERIFIED]
    float                   m_unkA64;                // +0xA64 = 0.0 (min-clamped)  [LIKELY]
    uint32_t                m_unkA68;                // +0xA68 = 0xFFFFFFFF (cached invalid id)  [UNVERIFIED]
    int32_t                 m_movementGaitIndex;     // +0xA6C index into the global C_RPGMovement table (-1 = none)
    float                   m_maxMoveSpeed;          // +0xA70 = 1.0 (from entity movement component)  [LIKELY]
    float                   m_moveVelocity;          // +0xA74 |dPos|/dt  [LIKELY]
    float                   m_distSqToListener;      // +0xA78 = FLT_MAX default  [LIKELY]
    float                   m_prevWorldPos[3];       // +0xA7C cached entity world position (Vec3 x,y,z)
    float                   m_unkVecA88[3];          // +0xA88 = {0,0,0} (Vec3-shaped)  [UNVERIFIED]
    S_SoulDerivedStatCache  m_derivedStatCache;      // +0xA94 (size 0x48)
    char                    _padADC[4];              // +0xADC
    S_SoulStatSource        m_statSources[7];        // +0xAE0 (7 * 0x18 = 0xA8)
    uint32_t                m_movementStateFlags;    // +0xB88 bits 0..0x15 = per-frame movement/combat state
    float                   m_unkB8C;                // +0xB8C = 0       [UNVERIFIED] (clamp-min?)
    float                   m_unkB90;                // +0xB90 = FLT_MAX [LIKELY] (clamp-max?)
    float                   m_unkB94;                // +0xB94 = 0       [UNVERIFIED]
    float                   m_unkB98;                // +0xB98 = FLT_MAX [LIKELY] (clamp-max?)
    char                    _padB9C[4];              // +0xB9C

    // -------------------------------------------------------------- state tail
    int32_t                 m_soulState;             // +0xBA0 init 2; activation gate (nonzero => stay registered).
                                                     //        E_SoulState enum unrecovered (setter not located).
    char                    _padBA4[4];              // +0xBA4
    uint64_t                m_unkBA8[4];             // +0xBA8 memset 0; possibly a std::vector + qword  [UNVERIFIED]
    S_SoulArchetype*        m_pArchetype;            // +0xBC8 init -> static all-0xFF sentinel archetype; resolved from
                                                     //        C_SoulArchetypeDatabase (rpg/soul_archetype). GetGender etc.
    S_SocialClass*          m_pSocialClass;          // +0xBD0 init -> static sentinel; from C_SocialClassDatabase (rpg/social_class)
    void*                   m_pRoleRow;              // +0xBD8 init -> sentinel; 0x38-byte RPG role row from C_RPGSystem+0x588
                                                     //        keyed by soul+0x280; concrete row type UNVERIFIED
    void*                   m_pFactionData;          // +0xBE0 faction object resolved from C_FactionManager by faction id
                                                     //        (soul+0x294); read via I_Soul slot[25]. Pointee type UNVERIFIED
    Offsets::IEntity*       m_boundEntities[2];      // +0xBE8 bound CryEngine entities (compound: e.g. horse+rider).
                                                     //        Set by SetBoundEntity_18030F274. [LIKELY IEntity*]
    uint32_t                m_flags;                 // +0xBF8 bit 0x20 = use m_overrideWUID; bits 0x08/0x40 set on clone.
                                                     //        RMW'd as a dword despite ctor zeroing only the low byte.
    char                    _padBFC[4];              // +0xBFC
    wh::framework::WUID     m_overrideWUID;          // +0xC00 alias/override WUID returned by GetEffectiveWUID when
                                                     //        (m_flags & 0x20); null-WUID sentinel by default
    wh::entitymodule::C_Inventory*        m_pInventory;  // +0xC08 lazily created/found (C_InventoryManager pool, by m_wuid)
    wh::entitymodule::C_EquipmentManager* m_pEquipment;  // +0xC10 lazily created (tracks which owned items are equipped)
    void*                   m_unkC18;                // +0xC18 = 0; no reader located  [UNVERIFIED]
    void*                   m_pActiveRegistration;   // +0xC20 C_SoulManager active-list pool node; 0xFFFF.. sentinel = not registered
    C_Soul*                 m_propCacheOwner;        // +0xC28 = this; owner arg of the lazy cached-property helper (sub_1811D3BC4)
    bool                    m_propCacheValid;        // +0xC30 1 = m_cachedPropValue valid; cleared by the property-change callback
    char                    _padC31[3];              // +0xC31
    float                   m_cachedPropValue;       // +0xC34 cached value of soul property 0x27
};
static_assert(sizeof(C_Soul) == 0xC38);

}  // namespace wh::rpgmodule
