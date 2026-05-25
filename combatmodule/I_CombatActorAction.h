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
// NOTE: vtable is interfuscator-shuffled. Slot indices are NOT stable.
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
    // No additional methods identified beyond I_CombatActorAction.
    // If C_Action adds more primary vtable slots, they would go here.
};

// ---------------------------------------------------------------------------
// C_Action<I_CombatActorActionPrivate> — concrete action base with data.
//
// RTTI: .?AV?$C_Action@VI_CombatActorActionPrivate@combatmodule@wh@@@framework@wh@@
// Primary vtable:   0x1821aab38 (20 slots, I_CombatActorActionPrivate chain)
// Secondary vtable: 0x1821aaaf0 (8 slots, I_ActionImpl at +0x10)
// Constructor: sub_180430230
// Destructor:  sub_180430138
// Size: 0xD0 bytes
//
// Layout:
//   +0x00: primary vtable (I_CombatActorActionPrivate chain)
//   +0x08: m_nRefCounter (from _i_multithread_reference_target)
//   +0x0C: pad
//   +0x10: I_ActionImpl vtable (MI secondary)
//   +0x18: m_onActionChanged1 (C_Signal, 0x30 bytes)
//   +0x48: m_onActionChanged2 (C_Signal, 0x30 bytes)
//   +0x78: m_onActionCompleted (C_Signal, 0x30 bytes)
//   +0xA8: m_isStarted, m_isRunning, m_isCompleted (bools)
//   +0xB0: m_pActionParams (void*)
//   +0xB8: m_priority, m_actionSequenceId (int32)
//   +0xC0: m_pOwnerSubsystem (void*)
//   +0xC8: m_contextPriority (int32)
// ---------------------------------------------------------------------------
class C_CombatActorAction : public I_CombatActorActionPrivate,
                            public wh::framework::I_ActionImpl {
public:
    // ---- I_CombatActorAction overrides ----
    ~C_CombatActorAction() override = default;
    bool IsStarted() const override { return m_isStarted; }
    bool IsRunning() const override { return m_isRunning; }
    bool IsCompleted() const override { return m_isCompleted; }
    bool CanInterrupt(const _smart_ptr<wh::framework::I_Action>&) const override { return false; }
    int32_t GetActionTypeId() const override { return -1; }
    int32_t GetPriority() const override { return m_priority; }
    int32_t GetActionSequenceId() const override { return m_actionSequenceId; }
    int32_t GetContextPriority() const override { return m_contextPriority; }
    const char* GetActionName() const override { return ""; }
    void unk_12() override {}
    void unk_13() override {}
    void ConnectOnChanged(void*) override {}
    void DisconnectOnChanged(void*) override {}
    void unk_16() override {}
    void unk_17() override {}
    void* GetLock() override { return nullptr; }
    int32_t unk_19() const override { return -1; }

    // ---- I_ActionImpl overrides ----
    void Start() override {}
    void Stop() override {}
    void Update(float) override {}
    void Tick() override {}
    void Complete() override {}
    // IsStarted() already declared above (primary chain)
    void GetParams(void*) const override {}

    // ---- Data members (C_Action own fields) ----
    wh::shared::C_Signal<wh::framework::I_Action&, _smart_ptr<wh::framework::I_Action>&>
        m_onActionChanged1;                                         // +0x18

    wh::shared::C_Signal<wh::framework::I_Action&, _smart_ptr<wh::framework::I_Action>&>
        m_onActionChanged2;                                         // +0x48

    wh::shared::C_Signal<wh::framework::I_Action&>
        m_onActionCompleted;                                        // +0x78

    bool                m_isStarted;        // +0xA8
    bool                m_isRunning;        // +0xA9
    bool                m_isCompleted;      // +0xAA
    uint8_t             _padAB[5];          // +0xAB
    void*               m_pActionParams;    // +0xB0
    int32_t             m_priority;         // +0xB8  (init -1)
    int32_t             m_actionSequenceId; // +0xBC  (init -1)
    void*               m_pOwnerSubsystem;  // +0xC0
    int32_t             m_contextPriority;  // +0xC8  (init 0)
    uint32_t            _padCC;             // +0xCC
};
static_assert(sizeof(C_CombatActorAction) == 0xD0, "C_CombatActorAction must be 0xD0 bytes");

}  // namespace wh::combatmodule
