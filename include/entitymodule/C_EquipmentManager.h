#pragma once

#include <cstdint>

// ===========================================================================
// wh::entitymodule::C_EquipmentManager  -  tracks which of a soul's OWNED items
//                                          are currently EQUIPPED (worn / held).
//
// Reverse-engineered from WHGame.dll (KCD1 retail). Every claim cites the
// instruction/access that proves it; unproven points tagged [UNVERIFIED].
//
// One per soul, at C_Soul+0xC10 (allocated by sub_1806ED0EC, 0xB8 bytes; ctor
// sub_18030AB40 installs the vtable + back-pointer to the C_Inventory). Distinct
// from C_Inventory (what you OWN) — this is the EQUIPPED subset.
//
// RTTI/vtable: ??_7C_EquipmentManager@entitymodule@wh@@ @ 0x1821a6c78
//   (multiple-inheritance; primary slots 0..4, then interleaved base COLs).
// ctor:  sub_18030AB40 ; slot-array fill sub_18030AD20 ; weight calc sub_180451944.
//
// EQUIPMENT MODEL (VERIFIED):
//   Equipment is split by item kind:
//     * WEAPON / HAND items (single-instance, one per slot): a FIXED array of 6
//       item WUIDs at +0x50 (slot index -> WUID). Filled with the invalid-WUID
//       sentinel qword_18300F8D8 in the ctor (sub_18030AD20: `do{*p++=sentinel}
//       while(--n)` with n=6); iterated as `while(i != 6)` in the equip-apply
//       worker sub_18044B8F8. A slot index 0..5 comes from the item-class's
//       weapon/equip-data: item_def->vtable[0x88](0)->vtable[0x130]() (GetSlotId).
//       Item categories routed here: 0x2CF / 0x4CF / 0x88F.
//     * CLOTHING / ARMOR (many layered pieces): a WUID-keyed std::unordered_set
//       at +0x10 (insert via sub_180450F78). Item category 0x100F (the armor/
//       clothing class — sub_180451944 sums `& 0x100F` items into +0x84).
//   Categories are read from the item-class definition (C_Item+0x20 ->
//   vtable[8] = GetCategory).
//
// SLOT NAMES (VERIFIED 2026-06): the 6 weapon/hand slots are the `weapon_equip_slot`
//   enum (wh::entitymodule::E_HandSlot), from Libs/Tables/item/weapon_equip_slot.xml:
//     0 primary_main_hand   1 primary_off_hand   2 secondary_main_hand
//     3 secondary_off_hand  4 oversized          5 oversized_off
//   E_HandSlot confirmed in RTTI (C_Signal<I_CombatActor&, E_HandSlot>, vtable
//   0x1821b6e48). weapon_equip_slot_id is a PK column of the weapon_class table
//   (schema builder sub_1801439A0, descriptor @ qword_1834F7DE8). GetSlotId base
//   (S_WeaponEquipData vtable 0x1822e1460 slot 0x130 = sub_1806FA690) returns 6 (the
//   count); per-weapon-class subclasses override it to the DB slot id 0..5.
//   The CLOTHING/ARMOR set at +0x10 is the SEPARATE `equipment_slot` table (21 rows:
//   boot, leg_*, body_cloth/chainmail/plate/coat, sleeves, gloves, ring, necklace,
//   head_liner/hood/helmet, spur, horse_*) — keyed by item WUID (many layered pieces).
// ===========================================================================

#include "../framework/WUID.h"
// <unordered_set> + std::hash<WUID> come from PCH.h.

namespace wh { namespace entitymodule {

class C_Inventory;

// weapon/hand equipment slot index (Libs/Tables/item/weapon_equip_slot.xml). VERIFIED.
// NOTE: unscoped `enum E_HandSlot : int32_t` to match the forward-declarations in
// combatmodule/C_CombatActor.h + S_CombatActorState.h (this header supplies the values).
enum E_HandSlot : int32_t {
    HandSlot_PrimaryMainHand   = 0,
    HandSlot_PrimaryOffHand    = 1,
    HandSlot_SecondaryMainHand = 2,
    HandSlot_SecondaryOffHand  = 3,
    HandSlot_Oversized         = 4,
    HandSlot_OversizedOff      = 5,
    HandSlot_Count             = 6,   // GetSlotId base returns this; m_weaponSlots length
};

class C_EquipmentManager {
public:
    virtual ~C_EquipmentManager();                          // +0x00  MI vtable @ 0x1821a6c78 (primary slots 0..4)

    C_Inventory*  m_pInventory;                             // +0x08  owning inventory (item iterator via vtable[0x260])
    std::unordered_set<wh::framework::WUID> m_clothing;     // +0x10  equipped clothing/armor (category 0x100F), to +0x50
    wh::framework::WUID m_weaponSlots[6];                  // +0x50  hand/weapon slots (E_HandSlot 0..5; invalid WUID = empty)
    float         m_totalWeight;                            // +0x80  total carried weight (sub_180451944)
    float         m_clothingWeight;                         // +0x84  equipped-clothing weight (sum of &0x100F items)
    // +0x88  secondary dynamic-array region (init sub_18030A980): begin/end/cap +
    //   2 trailing qwords + a word. Element type [UNVERIFIED] — modeled as raw.
    void*         m_arr2Begin;                              // +0x88
    void*         m_arr2End;                                // +0x90
    void*         m_arr2Cap;                                // +0x98
    uint64_t      m_arr2ExtraA0;                            // +0xA0
    uint64_t      m_arr2ExtraA8;                            // +0xA8  (low word zeroed in ctor)
    uint32_t      m_guard;                                  // +0xB0  re-entrancy guard (around sub_180451DFC)
    uint8_t       _padB4[4];                                // +0xB4
};
static_assert(sizeof(C_EquipmentManager) == 0xB8);

}} // namespace wh::entitymodule
