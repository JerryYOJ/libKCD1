#pragma once

#include <cstdint>

// -----------------------------------------------
// Effect class hierarchy
// -----------------------------------------------
// C_Effect -> C_SoulEffect -> C_StatXPEffect
// C_Effect -> C_SoulEffect -> C_LearnPerkEffect

#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"

namespace wh::rpgmodule {

// RTTI: .?AVC_Effect@rpgmodule@wh@@
// vtable layout derived from C_SoulEffect (0x1821beb80),
//   C_StatXPEffect (0x1821c7a48), C_LearnPerkEffect (0x1826d97b8)
class C_Effect {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Effect;
    virtual ~C_Effect();                                // vfunc[0]
    virtual void Accept(void* visitor) = 0;             // vfunc[1] — visitor pattern, calls visitor->vtable[0xD8/8](visitor, this)
    virtual void AcceptConst(void* visitor) = 0;        // vfunc[2] — const overload of Accept
    virtual bool Apply() = 0;                           // vfunc[3] — main processing method (returns true on success)
    virtual void GetEntityId(uint64_t* outId) = 0;      // vfunc[4] — writes m_entityId to *outId
    virtual void OnScheduled() {}                       // vfunc[5] — no-op in most derived classes
    virtual void OnQueued() {}                          // vfunc[6] — CFG guard nop in derived classes
    virtual const char* GetName() = 0;                  // vfunc[7] — returns static string ("StatXP", "LearnPerk", etc.)

    uint64_t    _unk08;                     // +0x08
    uint64_t    m_entityId;                 // +0x10  target entity
};
static_assert(sizeof(C_Effect) == 0x18);

// RTTI: .?AVC_SoulEffect@rpgmodule@wh@@
// Constructor: sub_18056AC84
class C_SoulEffect : public C_Effect {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SoulEffect;
    // No additional members visible -- just type distinction
};
static_assert(sizeof(C_SoulEffect) == 0x18);

// -----------------------------------------------
// C_StatXPEffect
// -----------------------------------------------
// RTTI: .?AVC_StatXPEffect@rpgmodule@wh@@
// vtable: 0x1821c7a48
// Constructor: sub_1805A44FC  (creates effect, queued for processing)
// Inherits: C_SoulEffect -> C_Effect
//
// Intermediate template: C_SoulValueEffect<E_SoulStat> (between C_SoulEffect and this)
//
// Processing: lambda at sub_180A9AD90 (the perk point INCREMENT function)
//   Calls sub_181175AF0 to compute perk points for a level range.

class C_StatXPEffect : public C_SoulEffect {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_StatXPEffect;
    // Set at construction time:
    uint32_t    m_statId;               // +0x18  (E_SoulStat enum: 0=STR,1=AGI,2=VIT,3=SPC)
    int32_t     m_xpAmount;             // +0x1C  XP to add (or target XP delta)

    // Filled during processing (before visitor lambda runs):
    uint32_t    m_oldStatLevel;         // +0x20
    int32_t     m_statLevelDelta;       // +0x24  new_level - old_level
    uint32_t    m_oldMainLevel;         // +0x28
    int32_t     m_mainLevelDelta;       // +0x2C  new_main_level - old_main_level
    uint32_t    m_unk30;                // +0x30

    uint8_t     m_bIsAdvanceToLevel;    // +0x34  0=AddStatXP, 1=AdvanceToStatLevel
    char        _pad35[3];              // +0x35
};
static_assert(sizeof(C_StatXPEffect) == 0x38);

// -----------------------------------------------
// C_LearnPerkEffect
// -----------------------------------------------
// RTTI: .?AVC_LearnPerkEffect@rpgmodule@wh@@
// vtable: 0x1826d97b8
// Constructor: sub_1811ADB44
// Inherits: C_SoulEffect -> C_Effect
//
// Apply method: sub_18117E38C
//   Gets soul via entity lookup -> *(soul + 0x6E8) -> calls sub_181199EF4
//   sub_181199EF4 checks counter > 0, adds perk, decrements counter.

class C_LearnPerkEffect : public C_SoulEffect {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LearnPerkEffect;
    CryGUID     m_perkGuid;             // +0x18  perk to learn
    uint8_t     m_bResult;              // +0x28  set to 1 if successfully learned
    char        _pad29[7];              // +0x29
};
static_assert(sizeof(C_LearnPerkEffect) == 0x30);

}  // namespace wh::rpgmodule

// -----------------------------------------------
// Key function addresses (for hooking/patching)
// -----------------------------------------------
//
// Perk point INCREMENT (stat XP visitor lambda):
//   sub_180A9AD90
//   Increments: counter[2*stat_id + 0x10] += computed_stat_points
//   Increments: counter[0x66]             += computed_main_level_points
//   Calls sub_181175AF0(ctx, index, old_level, new_level) to compute point count
//     - index = stat_id + 0x22  for stat perk points
//     - index = 0x49            for main level perk points
//
// Perk point DECREMENT (learn perk):
//   sub_181199EF4
//   Index formula:
//     if (stat_selector < 0xA)  -> offset = 2 * stat_selector + 0x10
//     if (stat_selector == 0xA && skill_selector < 0x21) -> offset = 2 * skill_selector + 0x24
//     if (stat_selector == 0xA && skill_selector == 0x21) -> offset = 0x66 (MAIN LEVEL)
//   Checks: *(uint16_t*)(counter + offset) > 0
//   Decrements: --*(uint16_t*)(counter + offset)
//
// Soul Lua binding registration:       sub_1811CCC44
// AddPerk Lua binding:                 sub_1811BBC38  (bypasses perk point check!)
// RPG params singleton getter:         sub_18033A404
// Soul lookup by entity ID:            sub_180284B04
