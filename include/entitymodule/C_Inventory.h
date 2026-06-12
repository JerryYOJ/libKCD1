#pragma once

#include "I_InventoryListener.h"
#include "../framework/WUID.h"
// <cstdint>/<vector>/<unordered_set>/<functional> + std::hash<WUID> come from PCH.h.

// ===========================================================================
// wh::entitymodule::C_Inventory  -  a per-owner item container.
//
// Reverse-engineered from WHGame.dll (KCD1 retail). Every claim cites the
// instruction/access that proves it; unproven points tagged [UNVERIFIED].
//
// MODEL (VERIFIED):
//   An inventory does NOT store items. It stores a std::unordered_set of item
//   WUIDs (+0x60); each WUID resolves to a C_Item in the global item registry
//   (qword_183785918) via sub_180454638. Operations (count/find/add/remove) walk
//   or hash this set and resolve each WUID on demand.
//
//   C_Inventory objects are NOT independently heap-allocated and have NO RTTI of
//   their own (no C_Inventory type-descriptor exists). They are created/owned by
//   the C_InventoryManager pool (find-or-create sub_18055DDDC) and keyed by the
//   owner's WUID. A soul reaches its inventory through a cached pointer at
//   C_Soul+0xC08 (set by sub_18030EBE0; see C_Soul.h), NOT a per-frame lookup.
//
// OWNERSHIP CHAIN (VERIFIED):
//   C_Actor+0x650 -> C_Soul* ; C_Soul+0xC08 -> C_Inventory* ;
//   C_Inventory+0x60 (WUID set) -> C_Item* via registry ; C_Soul+0xC10 ->
//   C_EquipmentManager* (which owned items are equipped).
//
// LAYOUT EVIDENCE:
//   +0x00 objWuid   : pool create sub_18055DDDC — first qword is the inventory's
//                     own WUID (from the manager's WUID allocation).
//   +0x08 ownerWuid : sub_18055DDDC `*(inv+8) = *a2` (128-bit owner WUID).
//   +0x18 ownerClass: sub_18055DDDC `*(inv+0x18) = a3` (owner entity-class id).
//   +0x28 name      : sub_18055DDDC sub_18028F7CC(inv+0x28, name) (CryString).
//   +0x30 listeners : listener std::vector; sub_1804524B8 iterates [+0x30..+0x38)
//                     and invokes std::function<void(I_InventoryListener*)> per slot,
//                     with a re-entrancy guard at +0x48. The InventoryManager and
//                     the owning C_Soul register here.
//   +0x60 itemIds   : std::unordered_set<WUID>; GetInventoryTable's iterator factory
//                     (sub_18030ADEC) sets iter[1]=inv+0x60 and names the element
//                     type wh::framework::WUID. find/insert/erase =
//                     sub_18044F69C / sub_180450F78 / sub_180450EF4 on inv+0x60.
//   +0x70 count     : GetCount (sub_1810C8570) reads *(uint32*)(inv+0x70) — the
//                     unordered_set _Mysize. (Bucket/list internals at +0x68/+0x78..+0xA0.)
//   +0xA0 proxy     : sub_18055DDDC `*(inv+0xA0)=a6`; branched on in add/remove/money
//                     cores — a delegating/"virtual" inventory (horse, shop, linked).
//   +0xA4 flag2     : sub_18055DDDC `*(inv+0xA4)=0` (cleared on create).
//
// API (Lua C_ScriptBindInventory @ vtable 0x1822E44D8; each forwarder resolves the
//   bound C_Inventory* via scriptbind vtable[+0x10] = sub_180F19D04): AddItem,
//   CreateItem, RemoveItem, DeleteItem, RemoveAllItems, MoveItemOfClass, HasItem,
//   FindItem, GetCount, GetCountOfClass/Category, GetMoney, RemoveMoney,
//   GetInventoryTable, Dump, Validate. (Full address map in 01_entity_inventory.md.)
// ===========================================================================

namespace wh { namespace entitymodule {

class C_Inventory {
public:
    wh::framework::WUID  m_objWuid;        // +0x00  this inventory's own WUID
    wh::framework::WUID  m_ownerWuid;      // +0x08  owner WUID
    uint64_t             _ownerWuidHi;     // +0x10  (owner stored as 128-bit; high half)
    uint64_t             m_ownerClassId;   // +0x18  owner entity-class id
    uint64_t             _pad20;           // +0x20
    CryStringT<char>     m_name;           // +0x28  CryString (inventory/owner name; ctor sub_18028F7CC)

    // +0x30  listener callbacks (begin/end/cap +0x30/+0x38/+0x40); guard at +0x48.
    std::vector<std::function<void(I_InventoryListener*)>> m_listeners;  // +0x30
    uint32_t             m_listenerGuard;  // +0x48  ++ on dispatch, -- after (sub_1804524B8)
    uint8_t              _pad4C[0x14];     // +0x4C

    // +0x60  the item set (_Mysize @+0x70); models +0x60..+0xA0.
    std::unordered_set<wh::framework::WUID> m_itemIds;  // +0x60

    uint8_t              m_isProxy;        // +0xA0  delegating/virtual inventory flag (set from create arg a6)
    uint8_t              _padA1[3];        // +0xA1
    uint8_t              m_flag2;          // +0xA4  cleared on create (init sub_18030DF04 sets 1, create clears to 0)
    uint8_t              _padA5[3];        // +0xA5
    uint64_t             m_unkA8;          // +0xA8  (=0 in ctor) [role UNVERIFIED]
    uint64_t             m_unkB0[2];       // +0xB0  16-byte sentinel (init = xmmword_1834F6360) [role UNVERIFIED — looks like a GUID/WUID-pair]
    uint64_t             m_unkC0;          // +0xC0  (=0 in ctor) [role UNVERIFIED]
};
// SIZE VERIFIED: the C_Inventory pool strides entries by 0xC8 (sub_18030E0C0:
// base + 0xC8*index); the member-initializer sub_18030DF04 writes fields out to +0xC0.
static_assert(sizeof(C_Inventory) == 0xC8);

}} // namespace wh::entitymodule
