#pragma once

#include <cstdint>
#include "C_CombatModule.h"  // for E_CombatSubsystem

namespace wh::combatmodule {

class C_CombatActor;

// ---------------------------------------------------------------------------
// C_CombatActorObject — base class for combat actor subsystem objects.
//
// RTTI: .?AVC_CombatActorObject@combatmodule@wh@@
// vtable @ 0x1821ab398
// Scalar deleting dtor: sub_1806E4F5C (frees 0x10)
// Size: 0x10 bytes
// Constructor: sub_180431258(this, combatActor)
//
// Each C_CombatActorObject registers itself into the owning C_CombatActor's
// subsystem vectors at offsets +0x568 or +0x588, depending on whether
// the actor is fully initialized (flag at +0x580).
//
// vtable layout (interfuscator-shuffled, 7 slots):
//   [0] sub_1806E4F5C  scalar deleting destructor (frees 0x10)
//   [1] purecall
//   [2] sub_180F54EF4  GetSubsystemId -> returns E_CombatSubsystem
//   [3] purecall       GetName -> returns const char*
//   [4] sub_180F54A30  GetDebugLabel
//   [5] sub_180F4BE34  GetDebugInfo
//   [6] (additional method)
//
// Subclass: C_CombatActorUpdatedObject (adds Update tick).
// ---------------------------------------------------------------------------
class C_CombatActorObject {
public:
    virtual ~C_CombatActorObject() = default;                       // [0]
    virtual void unk_1() = 0;                                       // [1] purecall
    virtual E_CombatSubsystem GetSubsystemId() const = 0;           // [2] VERIFIED via GetDebugLabel
    virtual const char* GetName() const = 0;                        // [3] VERIFIED via GetDebugLabel
    virtual void GetDebugLabel(void* outLabel) {}                   // [4] sub_180F54A30
    virtual void GetDebugInfo(void* outInfo) {}                     // [5] sub_180F4BE34
    virtual void unk_6() {}                                         // [6]

    C_CombatActor* m_pOwner;                                        // +0x08
};
static_assert(sizeof(C_CombatActorObject) == 0x10);

}  // namespace wh::combatmodule
