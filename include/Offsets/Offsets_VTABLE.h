#pragma once

#include <array>

#include "REL/ID.h"  // REL::ID — each VTABLE entry IS a Steam-RVA id

// -----------------------------------------------
// VTABLE offsets for RE'd classes (from WHGame.dll base)
// -----------------------------------------------
// Pattern: VTABLE_ClassName is an array of REL::ID, one per MI vtable.
//   [0] = primary vtable
//   [1+] = secondary vtables (MI bases)
//
// Usage in class headers:
//   inline static constexpr auto VTABLE = VTABLE_C_CombatActorHuntAttack;
//
// Usage in plugin code (VTABLE[i] is a REL::ID, resolved per-distribution):
//   auto vtable = MyClass::VTABLE[1].address();  // secondary vtable address
//   auto* slot = reinterpret_cast<uintptr_t*>(vtable + slotIndex * 8);

namespace Offsets {

// ---- combatmodule ----

// C_CombatActorHuntAttack: C_CombatActorObject + I_CombatActorHuntAttack
//   [0] primary  (C_CombatActorObject)       vtable @ WHGame+0x21CB380
//     [0] dtor [1] Reset [2] GetSubsystemId(0x1C) [3] GetName [4] GetDebugLabel [5] GetDebugInfo
//   [1] secondary (I_CombatActorHuntAttack)  vtable @ WHGame+0x21CB3B8
//     [0] dtor  [1] TryHuntAttack  [2] Request
inline constexpr std::array<::REL::ID, 2> VTABLE_C_CombatActorHuntAttack{ ::REL::ID(51), ::REL::ID(52) };

// C_CombatActorMercyKill: C_CombatActorObject + I_CombatActorMercyKill
//   [0] primary  (C_CombatActorObject)       vtable @ WHGame+0x21CB3D8
//     [0] dtor [1] Reset [2] GetSubsystemId(0x1D) [3] GetName [4] GetDebugLabel [5] GetDebugInfo
//   [1] secondary (I_CombatActorMercyKill)   vtable @ WHGame+0x21CB410
//     [0] dtor  [1] CanMercyKill  [2] RequestMercyKill
inline constexpr std::array<::REL::ID, 2> VTABLE_C_CombatActorMercyKill{ ::REL::ID(53), ::REL::ID(54) };

// C_CombatActorDirector: C_ActionDirector + C_CombatActorObject
//   [0] primary  (C_ActionDirector)      vtable @ WHGame+0x21EB718
//     [0] dtor  [1] IsActive
//   [1] secondary (C_CombatActorObject)  vtable @ WHGame+0x21EB6E0
//     [1] Reset(no-op) [2] GetSubsystemId(2) [3] GetName("Director")
inline constexpr std::array<::REL::ID, 2> VTABLE_C_CombatActorDirector{ ::REL::ID(56), ::REL::ID(55) };

// C_CombatActorHorsePullDown: C_CombatActorObject + I_CombatActorHorsePullDown
//   [0] primary  (C_CombatActorObject)          vtable @ WHGame+0x21CB328
//     [0] dtor [1] Reset [2] GetSubsystemId(0x1B) [3] GetName [4] GetDebugLabel [5] GetDebugInfo
//   [1] secondary (I_CombatActorHorsePullDown)  vtable @ WHGame+0x21CB360
//     [0] dtor  [1] CanHorsePullDown  [2] RequestHorsePullDown
inline constexpr std::array<::REL::ID, 2> VTABLE_C_CombatActorHorsePullDown{ ::REL::ID(49), ::REL::ID(50) };

// ---- dialogmodule ----

// C_DialogCameraManager: I_DialogCameraManager + IEntitySystemSink
//   [0] primary  (I_DialogCameraManager)  vtable @ WHGame+0x26B3820
//     [0] IsActive [1] _vf1(nop) [2] FillViewParams [3] Activate [4] Deactivate [5] _vf5 [6] _vf6
//   [1] secondary (IEntitySystemSink)      vtable @ WHGame+0x26B3860
inline constexpr std::array<::REL::ID, 2> VTABLE_C_DialogCameraManager{ ::REL::ID(57), ::REL::ID(58) };
inline constexpr std::array<::REL::ID, 3> VTABLE_CViewSystem{ ::REL::ID(61), ::REL::ID(59), ::REL::ID(60) };  // IViewSystem / IMovieUser / ILevelSystemListener
inline constexpr std::array<::REL::ID, 1> VTABLE_CMovieSystem{ ::REL::ID(62) };  // IMovieSystem

}  // namespace Offsets
