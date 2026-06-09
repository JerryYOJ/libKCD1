#pragma once

#include "I_ItemRuntimeData.h"
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"
// <set> comes from PCH.h.

// ===========================================================================
// wh::entitymodule::C_EquippableItemRuntimeData  -  abstract intermediate base for
//                       equippable items' per-instance runtime state.
//
// Reverse-engineered from WHGame.dll (KCD1 retail). VERIFIED 2026-06.
//   vtable 0x1821cf6f8 ; ctor sub_18062B508 (calls the I_ItemRuntimeData ctor, then
//   builds its own state). Still ABSTRACT (slot0 stays _purecall — it does not
//   override Clone()); only the concrete leaf subclasses below are instantiable.
//
// On top of the I_ItemRuntimeData base, this adds (a) a second intrusive-list +
// std::vector<delegate> observer (+0x58..+0x90) and (b) a std::set<CryGUID> at +0x90.
// The +0x90 member was earlier mis-read as a "heap connection list"; it is actually a
// std::set<CryGUID> (VERIFIED): its head node is built by std::_Tree::_Buyheadnode
// (sub_180208FD8), and the load path (sub_1810789F8) inserts 0x10-byte CryGUID elements
// via the comparator sub_18044B1EC — a hi-qword/lo-qword lexicographic compare, i.e.
// exactly CryGUID::operator<. The whole 16-byte element is the key (no separate value),
// so it is a set, not a map. Serialized under save-tag 0x2125; most likely the set of
// buff/effect GUIDs applied to the item [type VERIFIED, semantic UNVERIFIED].
// ===========================================================================

namespace wh { namespace entitymodule {

class C_EquippableItemRuntimeData : public I_ItemRuntimeData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_EquippableItemRuntimeData;
    // ---- second embedded change-signal (equippable-specific events) ----
    S_IntrusiveListNode* m_sentinel58;                      // +0x58  intrusive-list sentinel anchor (head/tail below point here)
    uint8_t  m_flag60;                                      // +0x60
    uint8_t  _pad61[7];                                     // +0x61
    S_IntrusiveListNode* m_listHead;                        // +0x68  -> &m_sentinel58
    S_IntrusiveListNode* m_listTail;                        // +0x70  -> &m_sentinel58
    std::vector<S_RuntimeDataDelegate> m_subscribers;       // +0x78  active change-callbacks
    // +0x90  std::set<CryGUID> — the ON-EQUIP BUFF GUIDs the item grants while equipped.
    //   VERIFIED: exposed as the Lua ItemManager.AddOnEquipBuff(itemId, buff_id, add)
    //   (sub_1810BE0C4; buff_id parsed to a CryGUID by sub_18027C90C — "%x-%x-%x-%x-%llx"),
    //   which adds (sub_1810827D0) / removes (sub_18108F62C) the GUID on this RTD's set;
    //   item-class-gated; bulk-built from the class's named buff definitions (sub_18108B284).
    //   Serialized save-tag 0x2125. {_Myhead@+0x90, _Mysize@+0x98}.
    std::set<CryGUID> m_onEquipBuffs;                       // +0x90
    uint8_t  m_emitGuardA0;                                 // +0xA0  re-entrancy guard / flag
    uint8_t  _padA1[7];                                     // +0xA1
};
static_assert(sizeof(C_EquippableItemRuntimeData) == 0xA8);

}} // namespace wh::entitymodule
