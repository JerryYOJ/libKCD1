#pragma once

#include <cstdint>
#include "../framework/C_Signal.h"   // wh::shared::S_Delegate<bool>

// -----------------------------------------------
// I_CombatSoul -- combat-state interface implemented by C_CombatSoul
// -----------------------------------------------
// RTTI: .?AVI_CombatSoul@rpgmodule@wh@@
// vtable (C_CombatSoul implementation): 0x182229ac0  (exactly 5 slots)
//
// C_CombatSoul (embedded in C_Soul at +0xD8) owns two C_Signal<bool> combat-state
// signals; this interface exposes connect/disconnect for each plus a combat-active
// toggle. There is NO virtual destructor in the vtable (the 5 dumped slots are all
// the methods below; the embedded sub-object is torn down inline by ~C_Soul), so
// this interface must NOT declare a virtual dtor.
//
// Slot map (VERIFIED from the concrete vtable dump @0x182229ac0 — order is as the
// interfuscator laid it out for this class, taken from the dump, not assumed):
//   [0] sub_1811BE440  -> sub_180246C80(combat+0x38, slot) : subscribe   m_signal1
//   [1] sub_180246DE8  -> sub_180246D1C(combat+0x38, slot) : unsubscribe m_signal1
//   [2] sub_1802764D8  -> sub_180246C80(combat+0x08, slot) : subscribe   m_signal0
//   [3] sub_180246DC0  -> sub_180246D1C(combat+0x08, slot) : unsubscribe m_signal0
//   [4] sub_1811CF36C  : true  -> create+attach a combat buff at m_combatBuff;
//                        false -> clear+release it.

namespace wh::rpgmodule {

// Methods are declared non-pure (empty bodies) so that the concrete C_CombatSoul,
// which is embedded by value in C_Soul, is not an abstract type. This matches the
// I_Soul convention and does not change the 5-slot vtable layout.
class I_CombatSoul {
public:
    // The connect/disconnect helpers append/remove a 16-byte {object, member-fn}
    // delegate (wh::shared::S_Delegate<bool>) on the matching C_Signal<bool>.
    virtual void ConnectSignal1(const wh::shared::S_Delegate<bool>& slot) {}     // [0] 0x1811be440
    virtual void DisconnectSignal1(const wh::shared::S_Delegate<bool>& slot) {}  // [1] 0x180246de8
    virtual void ConnectSignal0(const wh::shared::S_Delegate<bool>& slot) {}     // [2] 0x1802764d8
    virtual void DisconnectSignal0(const wh::shared::S_Delegate<bool>& slot) {}  // [3] 0x180246dc0
    virtual void SetCombatActive(bool active) {}                                 // [4] 0x1811cf36c
};

}  // namespace wh::rpgmodule
