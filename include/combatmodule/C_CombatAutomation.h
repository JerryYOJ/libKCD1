#pragma once

#include <cstdint>
#include "C_CombatActorUpdatedObject.h"
#include "I_CombatAutomation.h"
#include "../framework/C_Signal.h"
#include "C_CombatAutomationDirector.h"
#include "C_CombatAutomationDefense.h"
#include "C_CombatAutomationAttack.h"
#include "C_CombatAutomationRiposte.h"
#include "C_CombatAutomationCombo.h"
#include "C_CombatAutomationZoneChange.h"
#include "C_CombatAutomationGuard.h"
#include "C_CombatAutomationShout.h"
#include "C_CombatAutomationWeapons.h"
#include "C_CombatAutomationMissile.h"

namespace wh::combatmodule {

class I_CombatActor;
namespace E_SignalSource { enum Type : int32_t; }
namespace E_CombatAutomationMoveEvent { enum Type : int32_t; }
namespace E_CombatAutomationEvent { enum Type : int32_t; }

// Pointed-to heap block at C_CombatAutomation+0xB8 (0x168 bytes, built by sub_18058EB28):
// a non-polymorphic aggregate of ~4 C_Signal members (incl. an E_WeaponKind signal,
// vtable 0x182229558). It has no own class vtable and no RTTI, so its class name is
// unrecoverable -- forward-declared opaque; the pointer is typed, contents left undefined.
struct S_CombatAutomationWeaponSignals;

// ---------------------------------------------------------------------------
// C_CombatAutomation -- per-actor container of the combat "automation" behaviours
// (the native side of the <MeleeDefenseAutomation/> / <MeleeOffenseAutomation/> ...
// BT nodes). Lazily built by sub_1806533B8 (GetOrCreateAutomation) -> ctor
// sub_1804F44B0 and stored at C_CombatActor+0x4F0. Every sub-object below is embedded
// inline and the layout tiles the 0x758 block EXACTLY (offsets read from the ctor,
// sizes layout-confirmed; tiling verified end-to-end).
//
// RTTI: .?AVC_CombatAutomation@combatmodule@wh@@  (descriptor rva 0x2A01C18)
// Constructor: sub_1804F44B0(this, owner).  Subsystem id: COMBAT_SUB_AUTOMATION (0x18).
// Inherits: C_CombatActorUpdatedObject (primary, +0x00) and I_CombatAutomation
//   (MI secondary base, sub-object at +0x18). m_updateFlag init 9.
// Size: 0x758.
// ---------------------------------------------------------------------------
class C_CombatAutomation : public C_CombatActorUpdatedObject, public I_CombatAutomation {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomation;
    ~C_CombatAutomation() override = default;

    // +0x18: the I_CombatAutomation MI secondary-base sub-object (its vtable pointer).

    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type>
                            m_onAutomationSignal;   // +0x20
    wh::shared::C_Signal<E_CombatAutomationMoveEvent::Type>
                            m_onMoveEvent;          // +0x50
    wh::shared::C_Signal<E_CombatAutomationEvent::Type>
                            m_onEvent;              // +0x80

    bool                    m_flagB0;               // +0xB0
    uint8_t                 _padB1[7];              // +0xB1
    S_CombatAutomationWeaponSignals* m_pWeaponSignals;  // +0xB8  -> heap 0x168 (4-signal block)

    // Embedded automation behaviours (all C_CombatAutomationAction-derived):
    C_CombatAutomationDirector    m_director;       // +0xC0   (0x80)
    C_CombatAutomationDefense     m_defense;        // +0x140  (0x88)  owns the reaction-weight override
    C_CombatAutomationAttack      m_attack;         // +0x1C8  (0xC0)
    C_CombatAutomationRiposte     m_riposte;        // +0x288  (0x48)
    C_CombatAutomationCombo       m_combo;          // +0x2D0  (0x60)
    C_CombatAutomationZoneChange  m_zoneChange;     // +0x330  (0x228)
    C_CombatAutomationGuard       m_guard;          // +0x558  (0x60)
    C_CombatAutomationShout       m_shout;          // +0x5B8  (0x68)
    C_CombatAutomationWeapons     m_weapons;        // +0x620  (0xC8)
    C_CombatAutomationMissile     m_missile;        // +0x6E8  (0x70)
};
static_assert(sizeof(C_CombatAutomation) == 0x758);

}  // namespace wh::combatmodule
