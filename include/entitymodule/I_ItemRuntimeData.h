#pragma once

// <cstdint> / <vector> come from PCH.h.

// ===========================================================================
// wh::entitymodule::I_ItemRuntimeData  -  abstract root of every item runtime-data
//                                          record (per-instance dynamic item state).
//
// Reverse-engineered from WHGame.dll (KCD1 retail). VERIFIED 2026-06.
//
// RTTI (VERIFIED via the class-hierarchy descriptor at COL 0x1824478E8):
//   type descriptor 0x182A45C78 = ".?AVI_ItemRuntimeData@entitymodule@wh@@" (a class);
//   numBaseClasses = 1 (self only) -> NO base classes; it is the root.
//   vtable 0x1821cf828 ; ctor sub_18062B7D8.
//
// Despite the I_ prefix this is an ABSTRACT BASE CLASS, not a pure interface: slot0
// is _purecall (a pure virtual), but the class carries its own data (+0x08..+0x58),
// so it is instantiable only through a concrete subclass (C_WeaponRuntimeData, ...).
//
// THE +0x08..+0x50 REGION IS AN EMBEDDED CHANGE-NOTIFICATION SIGNAL (Warhorse signal):
//   subscribers register a delegate {instance, fn}; on a state change the owner walks
//   the std::vector of delegates and fires each. VERIFIED from the dispatch in
//   sub_1806C5114 (the weapon slot1 override):
//       if (this->m_emitGuard == 0)                       // +0x50 re-entrancy guard
//           for (e = m_subscribers.begin; e != end; ++e)  // +0x30 std::vector
//               (*(fn @ e+8))(*(instance @ e+0), &arg);   // fire each delegate
//   The {begin,end,cap} triple at +0x30/+0x38/+0x40 is exactly a std::vector; the
//   size helper sub_18062B844 computes (end-begin)>>4, and the grow path
//   sub_18062B864/sub_18062B944/sub_18062B8E8 is std::vector reallocation.
// ===========================================================================

namespace wh { namespace entitymodule {

// S_RuntimeDataDelegate — one subscriber slot in the runtime-data change signal.
// FIELD ORDER VERIFIED at the instruction level (sub_1806C5114 dispatch:
//   `mov rcx,[elem+0]` = instance, `call qword ptr [elem+8]` = fn -> fn(instance, arg)).
//
// DELEGATE-ORDER NOTE (investigated 2026-06): this {instance, fn} order is the opposite
// of wh::shared::S_Delegate in framework/C_Signal.h ({fn @0, instance @8}) — but that is
// a DIFFERENT signal type, so there is no contradiction. wh::shared::C_Signal<> is a
// 0x30-byte vtable'd signal {vtable, field08, std::vector<delegate>, emitSlot=-1,
// depth=-1}; it is genuinely used (verified: C_Soul ctor sub_1804A1B98 embeds a
// C_Signal<wh::rpgmodule::I_Soul&> at C_Soul+0x68). This embedded observer is a
// SEPARATE 0x50-byte structure (intrusive connection list + delegate vector + guard,
// no vtable of its own). The order here is the instruction-verified truth for THIS type.
struct S_RuntimeDataDelegate {
    void* m_pInstance;                              // +0x00  callback 'this'
    void (*m_pInvoke)(void* self, void* eventArg);  // +0x08  callback function [arg type UNVERIFIED]
};
static_assert(sizeof(S_RuntimeDataDelegate) == 0x10);

// CORRECTION (RE'd 2026-06): the 0x30-byte heap node allocated by sub_180208FD8 is NOT
// a bespoke "connection" node — it is an MSVC std::_Tree HEAD/sentinel node (the node
// type behind std::map / std::set):
//     {_Left@0, _Parent@8, _Right@0x10, _Color@0x18, _Isnil@0x19, _Myval@0x20}  (0x30)
// sub_180208FD8 = std::_Tree::_Buyheadnode (self-links _Left/_Parent/_Right, sets
// _Color/_Isnil = 0x101). PROVEN by the textbook red-black-tree recursion: copy
// (sub_180207CEC: alloc node from key @+0x20, recurse _Left/_Right) and erase
// (sub_180218604: recurse _Right, iterate _Left, free 0x30). That is why it has 100+
// callers — every std::map/std::set in the binary allocates its head this way. So the
// heap "conn heads" in these classes are std::map/std::set members (modeled as such below).
//
// The INLINE part of the observer (sentinel + head/tail) is a SEPARATE intrusive doubly-
// linked list (it does NOT call sub_180208FD8 — its sentinel is embedded). Its node is
// just {next, prev}:
struct S_IntrusiveListNode {
    S_IntrusiveListNode* m_next;                    // +0x00  (points to the sentinel when empty)
    S_IntrusiveListNode* m_prev;                    // +0x08
};

class I_ItemRuntimeData {
public:
    // slot0 — deep-copy this record into a fresh pool instance (pure here; the runtime-
    //   data table acquires entries through it). C_WeaponRuntimeData::Clone = sub_18062BB00
    //   (allocate from pool qword_183785930, copy every field, return the new object).
    virtual I_ItemRuntimeData* Clone() = 0;                 // +0x00  vtable slot 0
    // slots 1.. are per-type virtuals (e.g. the weapon's slot1 = sub_1806C5114 sets a
    //   field and emits the change signal); not enumerated here — purpose UNVERIFIED.

    // ---- embedded change-notification signal (+0x08..+0x50) ----
    S_IntrusiveListNode  m_sentinel;                        // +0x08  embedded intrusive-list sentinel {next, prev} (self when empty)
    uint16_t m_signalFlags;                                 // +0x18
    uint8_t  _pad1A[6];                                     // +0x1A
    S_IntrusiveListNode* m_listHead;                        // +0x20  -> &m_sentinel
    S_IntrusiveListNode* m_listTail;                        // +0x28  -> &m_sentinel
    std::vector<S_RuntimeDataDelegate> m_subscribers;       // +0x30  active change-callbacks (fired on emit)
    void*    m_pOwner;                                      // +0x48  signal owner/source (base-ctor 2nd arg) [role UNVERIFIED — Create/Clone path passes no clear value]
    uint8_t  m_emitGuard;                                   // +0x50  re-entrancy guard (0 = idle, !=0 = firing)
    uint8_t  _pad51[7];                                     // +0x51
};
static_assert(sizeof(I_ItemRuntimeData) == 0x58);

}} // namespace wh::entitymodule
