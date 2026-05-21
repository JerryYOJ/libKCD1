#pragma once

#include <cstdint>

namespace wh::shared {

// -----------------------------------------------
// S_ConnectionNode — intrusive linked-list node for signal connections
// -----------------------------------------------
// Heap-allocated by Connect, freed by Disconnect.
// Created in sub_1802AD1E0 and variants, walked in sub_180448CC8.
// Nodes are sorted by priority within each category list.
struct S_ConnectionNode {
    uint64_t    m_callbackFunc;         // +0x00  function pointer / std::function storage
    uint64_t    m_callbackCtx;          // +0x08  captured context for the callback
    int32_t     m_type;                 // +0x10  connection type (determines which list)
    uint8_t     m_flags;                // +0x13  (e.g. active flag, set from source+0x18)
    // gap at +0x14
    int32_t     m_extraData;            // +0x14  additional data from connection source
    S_ConnectionNode* m_next;           // +0x18  next node in pending/staging list
    S_ConnectionNode* m_nextSorted;     // +0x20  next node in sorted active list
    int32_t     m_category;             // +0x28  category (used for list routing in Emit)
    int32_t     m_priority;             // +0x2C  sort key for insertion ordering
};

// -----------------------------------------------
// C_Signal<Args...> — observer/delegate for event notifications
// -----------------------------------------------
// Inheritance chain (from RTTI):
//   C_Signal<Args...>
//     C_EmitingSignal<S_SignalTraits<Args...>, C_BypassedConnections<...>, Args...>
//       C_SignalBase<S_SignalTraits<Args...>, C_BypassedConnections<...>>
//
// C_BypassedConnections is a policy template parameter to C_SignalBase, not a base class.
// It controls how connections can be temporarily suppressed ("bypassed") without
// being fully disconnected — useful for muting UI updates during bulk operations
// or preventing re-entrant signal firing.
//
// Size: 0x30 bytes (single vtable, single inheritance chain)
//
// C_Signal<I_Soul&> vtable:     0x182208ce8
// C_SignalBase<I_Soul&> vtable: 0x182208d20 (intermediate, set during construction)
//
// Construction order (from C_Soul/C_CombatSoul constructors):
//   1. vtable = C_SignalBase vtable  (base ctor)
//   2. Zero members, set slot sentinels to -1
//   3. vtable = C_Signal vtable      (derived ctor overwrites)
//
// Two internal regions:
//   +0x08: C_BypassedConnections data (0x18 bytes) — manages bypass/active lists
//          vtable[2-3] (Connect/Disconnect) forward to this+0x08
//   +0x20: emit state (0x10 bytes) — tracks currently-firing state
//          vtable[4-5] (ConnectDirect/DisconnectDirect) forward to this+0x20
//
// C_Signal vtable (at 0x182208ce8 for <I_Soul&>):
//   [0]  = destructor
//   [1]  = Emit — walks active connection lists, invokes each callback with Args...
//   [2]  = Connect — adds a S_ConnectionNode via BypassedConnections at this+0x08
//   [3]  = Disconnect — removes from BypassedConnections at this+0x08
//   [4]  = ConnectDirect — adds directly to emit list at this+0x20
//   [5]  = DisconnectDirect — removes from emit list at this+0x20
//   [6]  = Reset — clears all connections
//   [7-15] = C_SignalBase methods (flush pending→active, iterate, etc.)

template<typename... Args>
class C_Signal {
public:
    virtual ~C_Signal() = default;                          // [0]
    virtual void Emit(Args...) {}                           // [1]
    virtual void Connect(int slot, void* callback) {}       // [2]
    virtual void Disconnect(void* callback) {}              // [3]
    virtual void ConnectDirect(void* callback) {}           // [4]
    virtual void DisconnectDirect(void* callback) {}        // [5]
    virtual void Reset() {}                                 // [6]

    // C_BypassedConnections storage — manages subscription lists
    // Connections here can be temporarily bypassed (suppressed) without disconnecting.
    S_ConnectionNode*   m_pBypassedHead;    // +0x08  head of bypassed connection list (set by bypass logic)
    S_ConnectionNode*   m_pActiveHead;      // +0x10  head of active connection list (init 0)
    S_ConnectionNode*   m_pPendingHead;     // +0x18  head of pending-connect list (init 0, flushed to active on Emit)

    // Emit state — tracks direct connections and re-entrancy
    S_ConnectionNode*   m_pDirectHead;      // +0x20  head of direct (non-bypassable) connections (init 0)
    int32_t             m_currentSlot;      // +0x28  slot index currently emitting, -1 = idle
    int32_t             m_reentrancyGuard;  // +0x2C  re-entrancy depth sentinel, -1 = not firing
};
static_assert(sizeof(C_Signal<>) == 0x30);

}  // namespace wh::shared
