#pragma once

#include <cstdint>
#include "../CryEngine/CryCommon/BaseTypes.h"   // uint64 etc. — required by CryGUID.h
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"
#include "../framework/WUID.h"
#include "S_ItemRuntimeDataTable.h"

// ===========================================================================
// wh::entitymodule::C_Item  -  a single physical item instance.
//   RTTI .?AVC_Item@entitymodule@wh@@ (td 0x182a46af0); vtable 0x1821ad748 (slot0 =
//   scalar-deleting dtor sub_180453974; also an I_BindableObject secondary subobject).
//   ctor sub_180453678. SIZE 0xE0 (item-registry slab stride; allocator sub_1804538B4).
//   m_classGuid is the TYPE (many C_Items share one); stackables = one C_Item, amount>1.
//   C_Items live in the global registry (WUID -> C_Item*, lookup sub_180454638), not
//   heap-allocated individually. Field offsets/types verified from the ctor.
// ===========================================================================

namespace wh { namespace entitymodule {

// wh::entitymodule::S_ItemData — the item-CLASS table row (from item.xml). Holds the
// CLASS-LEVEL properties (Price/Weight/ConsumableBuff/WeaponBuff/category, ...) shared by
// every item of the class — which is why they are not C_Item fields. vtable 0x1822E15D0;
// GetClassDef = sub_1802D02D0. The base is an accessor interface (the default singleton
// qword_1836DF840 / ctor sub_181080034 returns defaults); the concrete per-class fields are
// the runtime item-class hierarchy (S_ItemData + derived) is RE'd in S_ItemData.h.
struct S_ItemData;

// Property-id keys for the EXTERNAL GetItemProperty/SetItemProperty accessors (the BT
// nodes + Lua ItemManager) — not C_Item methods, which is why nothing here uses it.
// Verbatim from the name registrar sub_18016CA30. Per-instance ids read the C_Item
// fields below; Price/Weight/ConsumableBuff/WeaponBuff are class-level (via m_pClassData).
enum class E_ItemProperty : int {
    Price = 0, Weight = 1, Owner = 2, Guid = 3, Amount = 4, Health = 5,
    ConsumableBuff = 6, WeaponBuff = 7, InHand = 8, ManipulationId = 9,
    CookedItemId = 10, InInventory = 11,
};

class C_Item {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Item;
    virtual ~C_Item();                              // +0x00  scalar deleting dtor (sub_180453974)

    wh::framework::WUID  m_wuid;                    // +0x08  own WUID (registry key)
    CryGUID              m_itemClass;               // +0x10  item-class GUID (set on creation)
    S_ItemData*          m_pClassData;              // +0x20  item-class table row (class-level props) — GetClassDef()
    CryGUID              m_classGuid;               // +0x28  class GUID (the "Guid" property)
    int32_t              m_amount;                  // +0x38  stack count (default 1)
    float                m_health;                  // +0x3C  condition 0.0..1.0 (default 1.0)
    I_ItemRuntimeData*   m_pRuntimeData;            // +0x40  primary ExtraProperties (lazy; coating) — GetRuntimeData()
    uint32_t             m_flags;                   // +0x48  bitmask (InHand/InInventory/stolen; sub_180451DFC)
    uint32_t             m_flags2;                  // +0x4C
    uint64_t             m_ownershipTime;           // +0x50  world-time of last ownership change (0 = none)
    int64_t              m_expiry;                  // +0x58  = INT64_MAX in ctor (TTL sentinel?) [UNVERIFIED]
    uint32_t             m_entityId;                // +0x60  spawned-world EntityId (0 = not in world)
    uint32_t             _pad64;                    // +0x64
    wh::framework::WUID  m_owner;                   // +0x68  owner WUID (sentinel = none)
    S_ItemRuntimeDataTable m_runtimeData;           // +0x70  per-item runtime-data store (0x70 bytes)

    // engine-function forwarders (impl in RE/src/entitymodule/C_Item.cpp)
    I_ItemRuntimeData* GetRuntimeData();                                          // sub_1806B2D8C: get-or-create +0x40 ExtraProperties
    void               SetRuntimeData(uint32_t typeId, I_ItemRuntimeData* obj);   // sub_1804544CC: +0x70 keyed table
};
static_assert(sizeof(C_Item) == 0xE0);

// Item registry: qword_183785918 (WUID -> C_Item*; direct-indexed slot table, stride 0x18,
// generation-checked; lookup sub_180454638). qword_183785920 = owner-side index. C_Item
// slab = 0xE0-byte freelist (sub_1804538B4).

}} // namespace wh::entitymodule
