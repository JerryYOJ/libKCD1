#pragma once

#include <array>
#include <cstdint>

// -----------------------------------------------
// VTABLE offsets for RE'd classes (from WHGame.dll base)
// -----------------------------------------------
// Pattern: VTABLE_ClassName is an array of offsets, one per MI vtable.
//   [0] = primary vtable
//   [1+] = secondary vtables (MI bases)
//
// Usage in class headers:
//   inline static constexpr auto VTABLE = VTABLE_C_CombatActorHuntAttack;
//
// Usage in plugin code:
//   auto vtable = Offsets::GetBase() + MyClass::VTABLE[1];  // secondary vtable address
//   auto* slot = reinterpret_cast<uintptr_t*>(vtable + slotIndex * 8);

namespace Offsets {

// ---- combatmodule ----

// C_CombatActorHuntAttack: C_CombatActorObject + I_CombatActorHuntAttack
//   [0] primary  (C_CombatActorObject)       vtable @ WHGame+0x21CB380
//     [0] dtor [1] Reset [2] GetSubsystemId(0x1C) [3] GetName [4] GetDebugLabel [5] GetDebugInfo
//   [1] secondary (I_CombatActorHuntAttack)  vtable @ WHGame+0x21CB3B8
//     [0] dtor  [1] TryHuntAttack  [2] Request
inline constexpr std::array<uintptr_t, 2> VTABLE_C_CombatActorHuntAttack{ 0x21CB380, 0x21CB3B8 };

// C_CombatActorMercyKill: C_CombatActorObject + I_CombatActorMercyKill
//   [0] primary  (C_CombatActorObject)       vtable @ WHGame+0x21CB3D8
//     [0] dtor [1] Reset [2] GetSubsystemId(0x1D) [3] GetName [4] GetDebugLabel [5] GetDebugInfo
//   [1] secondary (I_CombatActorMercyKill)   vtable @ WHGame+0x21CB410
//     [0] dtor  [1] CanMercyKill  [2] RequestMercyKill
inline constexpr std::array<uintptr_t, 2> VTABLE_C_CombatActorMercyKill{ 0x21CB3D8, 0x21CB410 };

// C_CombatActorHorsePullDown: C_CombatActorObject + I_CombatActorHorsePullDown
//   [0] primary  (C_CombatActorObject)          vtable @ WHGame+0x21CB328
//     [0] dtor [1] Reset [2] GetSubsystemId(0x1B) [3] GetName [4] GetDebugLabel [5] GetDebugInfo
//   [1] secondary (I_CombatActorHorsePullDown)  vtable @ WHGame+0x21CB360
//     [0] dtor  [1] CanHorsePullDown  [2] RequestHorsePullDown
inline constexpr std::array<uintptr_t, 2> VTABLE_C_CombatActorHorsePullDown{ 0x21CB328, 0x21CB360 };

}  // namespace Offsets
