#pragma once

#include <cstdint>
#include <map>
#include "../framework/C_ActionDirector.h"
#include "../Offsets/Offsets_VTABLE.h"
#include "C_CombatActorObject.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActorDirector — per-actor action-director combat subsystem.
//
// RTTI: .?AVC_CombatActorDirector@combatmodule@wh@@
// Created by sub_1805FD214, stored at C_CombatActor+0x4A8. Size: 0xD8.
// Bases: wh::framework::C_ActionDirector (+0x00) + C_CombatActorObject (+0xB0).
//
// Holds the actor's active actions (inherited m_actions @ +0x68). Reading a
// hunt in progress = scan m_actions for a C_CombatActorActionSyncAttack whose
// +0xF9 hunt-master bool is set.
//
// vtables: primary @ 0x21EB718 ([0]dtor [1]IsActive),
//          C_CombatActorObject base @ 0x21EB6E0 (id=2, name="Director";
//          Reset is an ICF-folded no-op).
// ---------------------------------------------------------------------------
class C_CombatActorDirector : public wh::framework::C_ActionDirector,
                              public C_CombatActorObject {
public:
    inline static constexpr auto VTABLE = Offsets::VTABLE_C_CombatActorDirector;

    bool IsActive() override;  // sub_18043423C: owner state.m_isInCombat || sub_1805637FC
    void Reset() override;     // ICF no-op
    E_CombatSubsystem GetSubsystemId() const override { return static_cast<E_CombatSubsystem>(2); }
    const char* GetName() const override { return "Director"; }

    std::map<int32_t, void*> m_channelSubscriptions;  // +0xC0  channel id -> signal connection
    int32_t  m_fieldD0;                               // +0xD0
    uint32_t _padD4;                                  // +0xD4
};
static_assert(sizeof(C_CombatActorDirector) == 0xD8, "C_CombatActorDirector must be 0xD8 bytes");

}  // namespace wh::combatmodule
