#pragma once

#include <cstdint>
#include "Callbacks.h"
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::T_ObjectManagerBase<TObject, TManager> — the CRTP base shared by the per-type
// WUID->object registries. It IS a notification source (the Callbacks chain, see Callbacks.h) and
// EMBEDS exactly the primary WUID->object hash map. Two instantiations are known:
//   * C_LinkablesManager       (for C_LinkableObject; adds its OWN 0x148 secondary index -> 0x1A8)
//   * C_IntelligentObjectManager (for C_IntelligentObject; adds a virtual I_DebugDraw base -> 0x68)
//
// SIZE 0x58 = Callbacks chain (0x18) + T_WuidHashMap (0x40). VERIFIED by C_IntelligentObjectManager,
// whose total size is 0x68 (= 0x58 + vbptr 0x08 + I_DebugDraw vbase 0x08): this proves the template
// itself is 0x58 and that the 0x148 secondary index belongs to C_LinkablesManager, NOT the template.
//   ctor   sub_181676778 (C_LinkablesManager) / sub_1815A60A8 (C_IntelligentObjectManager)
//   find   sub_18024D6E4 / sub_1802B620C        insert/Register sub_180450678 / sub_1802782D0
//   erase  sub_180450130 / sub_180278644         clear sub_1815A7308 (COMDAT-folded, shared)
// ===========================================================================

namespace wh::xgenaimodule {

// Warhorse pooled, open-chaining hash map keyed by WUID. An inline 8-node pool (sub_18071265C(.,8))
// feeds a node list threaded through a bucket vector. Node = S_Node (0x20). Field offsets VERIFIED
// from find/insert: head@+0x08, buckets@+0x18, mask@+0x30 (map-relative). Total 0x40.
template<class TValue>
struct T_WuidHashMap {
    struct S_Node {
        S_Node*             m_next;    // +0x00
        S_Node*             m_prev;    // +0x08
        wh::framework::WUID m_key;     // +0x10  the WUID
        TValue              m_value;   // +0x18  the registered object pointer
    };  // 0x20

    uint8_t  m_flags;          // +0x00
    uint8_t  _pad01[3];
    float    m_maxLoadFactor;  // +0x04  = 1.0f (ctor)
    S_Node*  m_listHead;       // +0x08  list end-sentinel (returned as the "not found" result)
    uint64_t m_size;           // +0x10  element count
    S_Node** m_buckets;        // +0x18  bucket array base (each bucket = {first,last}, 0x10 bytes)
    S_Node** m_bucketsLast;    // +0x20
    S_Node** m_bucketsEnd;     // +0x28
    uint64_t m_mask;           // +0x30  bucket mask = m_bucketCount - 1 (sub_18071265C: a2-1, @0x1807126DE)
    uint64_t m_bucketCount;    // +0x38  number of buckets (sub_18071265C: a2, @0x1807126E2). NOTE: the
                               //        bucket-INDEX math uses m_mask@+0x30, not this field (was
                               //        mislabeled "m_maxIndex"; corrected per verdict @0x1807126E2).
};  // 0x40

template<class TObject, class TManager>
class T_ObjectManagerBase
    : public Callbacks::C_NoDataExtension<Functor2<E_AIONotifyEvent::Type, const wh::framework::WUID&>, 1>
{
public:
    // --- virtual interface (extends the Callbacks vtable; slots [2]/[3] of the primary vtable) ---
    // Slot [2] is keyed by WUID at the engine level: C_IntelligentObjectManager's override
    // (sub_180278644) takes a WUID* directly; C_LinkablesManager's (sub_180450100) extracts the
    // WUID from the object then additionally drops it from its own secondary index. Modeled as a
    // WUID& here (reconciles both); [name Unregister inferred].
    virtual void Unregister(const wh::framework::WUID& key);  // [2]  erase from map + Notify(Removed)
    virtual void Clear();                                     // [3]  sub_1815A7308: Notify(Removed) per object, wipe map, reset pool

    // Non-virtual engine ops (realized per concrete manager as address forwarders — see the .cpp):
    //   TObject* Find(WUID)            sub_18024D6E4 / sub_1802B620C  — hash the WUID, walk the bucket chain
    //   bool     Register(WUID, T*)    sub_180450678 / sub_1802782D0  — insert (if absent) then Notify(Added)

    T_WuidHashMap<TObject*>  m_objects;        // +0x18  primary WUID -> object* map (0x40)
};  // 0x58  (Callbacks 0x18 + T_WuidHashMap 0x40)

}  // namespace wh::xgenaimodule
