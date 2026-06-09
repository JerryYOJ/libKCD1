#pragma once

#include <cstdint>
#include "../CryEngine/CryCommon/smartptr.h"
#include "../framework/I_Action.h"
#include "../framework/I_ActionImpl.h"
#include "../framework/C_Signal.h"

// ---------------------------------------------------------------------------
// Combat Action Type Hierarchy (from RTTI BaseClassArray of C_Action)
//
// Primary chain (+0x00, single vtable, 20 slots):
//   _i_multithread_reference_target<int>
//     └── wh::framework::I_Action
//           └── wh::combatmodule::I_CombatActorAction
//                 └── wh::combatmodule::I_CombatActorActionPrivate
//                       └── wh::framework::C_Action<I_CombatActorActionPrivate>
//
// Secondary MI (+0x10, I_ActionImpl vtable, 8 slots):
//   wh::framework::I_ActionImpl (lifecycle: Start/Stop/Update/Tick/Complete)
//
// The full concrete action chain extends further:
//   C_Action → C_ParamAction → C_CombatActorAction → C_CombatActorAnimatedAction → leaf
//
// Warhorse classes are NOT interfuscator-shuffled — slot indices are stable.
// ---------------------------------------------------------------------------

namespace wh::combatmodule {

class C_CombatActor;

// ---------------------------------------------------------------------------
// I_CombatActorAction — extends I_Action with combat-specific methods.
//
// RTTI: .?AVI_CombatActorAction@combatmodule@wh@@
// Part of primary vtable chain at +0x00. No new data members.
// Adds combat-specific pure virtual methods to I_Action.
// ---------------------------------------------------------------------------
class I_CombatActorAction : public wh::framework::I_Action {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatActorAction;
    // Methods added by I_CombatActorAction (exact set unknown due to shuffling).
    // All are purecall in the interface vtable.
    // Known from C_Action implementations:
    virtual bool IsStarted() const = 0;                             // sub_1806F96D0
    virtual bool IsRunning() const = 0;                             // sub_1806F9700
    virtual bool IsCompleted() const = 0;                           // sub_1806FAC10
    virtual bool CanInterrupt(const _smart_ptr<wh::framework::I_Action>& other) const = 0; // sub_1806CB834
    virtual int32_t GetActionTypeId() const = 0;                    // sub_1806F83D0
    virtual int32_t GetPriority() const = 0;                        // sub_1806FA990
    virtual int32_t GetActionSequenceId() const = 0;                // sub_1806FA9B0
    virtual int32_t GetContextPriority() const = 0;                 // sub_1806F9A80
    virtual const char* GetActionName() const = 0;                  // sub_1806F8800
    virtual void unk_12() = 0;                                      // sub_180F46D7C
    virtual void unk_13() = 0;                                      // sub_180F47494
    virtual void ConnectOnChanged(void* callback) = 0;              // sub_18043209C
    virtual void DisconnectOnChanged(void* callback) = 0;           // sub_180432074
    virtual void unk_16() = 0;                                      // sub_180F46F64
    virtual void unk_17() = 0;                                      // sub_180F4767C
    virtual void* GetLock() = 0;                                    // sub_1806F8BD0
    virtual int32_t unk_19() const = 0;                             // sub_1806F83D0
};

// ---------------------------------------------------------------------------
// I_CombatActorActionPrivate — extends I_CombatActorAction.
//
// RTTI: .?AVI_CombatActorActionPrivate@combatmodule@wh@@
// Still in the primary vtable chain at +0x00. No new data members.
// C_Action<TPrivate> uses TPrivate = I_CombatActorActionPrivate as template arg.
// The "Private" likely adds implementation-facing methods to the chain.
// ---------------------------------------------------------------------------
class I_CombatActorActionPrivate : public I_CombatActorAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatActorActionPrivate;
    // No additional methods identified beyond I_CombatActorAction.
    // If C_Action adds more primary vtable slots, they would go here.
};

typedef _smart_ptr<I_CombatActorAction> I_CombatActorActionPtr;

}  // namespace wh::combatmodule
