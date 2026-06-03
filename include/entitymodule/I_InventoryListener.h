#pragma once

#include "../framework/WUID.h"   // <cstdint> comes from PCH.h

// ===========================================================================
// wh::entitymodule::I_InventoryListener  -  inventory-change callback interface.
//
// RTTI: .?AVI_InventoryListener@entitymodule@wh@@  (type-descriptor @ 0x182a1ba68)
//
// Reverse-engineered from WHGame.dll (KCD1 retail). VERIFIED 2026-06.
//
// C_Inventory keeps a vector of listeners at inv+0x30 and fires them via
// C_Inventory::FireListeners (sub_1804524B8): it iterates the vector and, per
// listener, invokes a captured std::function<void(I_InventoryListener*)>
// (functor->vtable[0x10] = operator(); cleanup via functor->vtable[0x20]). Each
// lambda calls ONE fixed slot of this interface on the listener. There are
// exactly 4 virtual methods (vtable +0x00/+0x08/+0x10/+0x18 beyond the dtor group).
//
// SLOT MAP (VERIFIED behaviour from the firing call sites; lambda bodies decompiled):
//   [+0x00] OnItemAdded(WUID item)            : lambda sub_180A7A1F0; fired by
//             C_Inventory::AddItem core sub_180451D08 only when a NEW item instance
//             enters (NOT on a stack merge). builder sub_18045232C.
//   [+0x08] OnItemRemoved(WUID item)          : lambda sub_180A7A4A0; fired by the
//             remove core sub_18044F718 and clear-all sub_180451A68. builder sub_180452474.
//   [+0x10] OnItemAmountChanged(WUID item, uint32 amount) : lambda sub_180A7A3C0;
//             builder sub_180452AC0 (via sub_180451FE4, item-owner notify).
//   [+0x18] OnItemAmountChanged2(WUID item, uint32 amount): lambdas sub_180A7A220 /
//             sub_180A7A350; fired by the ADD core sub_1802D0084 (with the added
//             amount), sub_18044F47C, and sub_1804526EC.
//   [INFERRED, not byte-proven] slots [+0x10]/[+0x18] are the amount-delta pair
//   (decrease vs increase). Slot [+0x18] is fired by the add path with the just-added
//   amount, so [+0x18]~increase and [+0x10]~decrease; the exact polarity is unproven
//   (the two builders sub_180451FE4/sub_1804526EC are adjacent notifier vtable slots
//   0x1826bea38/0x1826bea40, structurally identical apart from the target slot).
//
// IMPLEMENTORS: C_Soul implements this (its secondary subobject vtable
//   ??_7C_Soul@rpgmodule@wh@@6B@_1 @ 0x182228b78 — installed at C_Soul+0x18). All
//   FOUR of C_Soul's listener slots (0x182228b78/b80/b88/b90) point to the SAME
//   handler sub_1806A1144 — a "mark-dirty / deferred-recompute" that bumps a counter
//   at subobj+0xAC0 and calls sub_1806699C8(subobj+0xABC, 2, &flag). So the soul
//   collapses all inventory events into one recompute request (e.g. recalc carry
//   weight / encumbrance / stat effects) and does NOT distinguish the event type.
//   The C_InventoryManager also registers itself as a listener (broadcast hub).
// ===========================================================================

namespace wh { namespace entitymodule {

class I_InventoryListener {
public:
    virtual ~I_InventoryListener() {}

    // amount is the stack delta / new count.
    virtual void OnItemAdded(wh::framework::WUID item) = 0;                        // [+0x08 from dtor]
    virtual void OnItemRemoved(wh::framework::WUID item) = 0;                      // [+0x10]
    virtual void OnItemAmountChanged(wh::framework::WUID item, uint32_t amount) = 0;   // [+0x18]
    virtual void OnItemAmountChanged2(wh::framework::WUID item, uint32_t amount) = 0;  // [+0x20] (add-side; polarity INFERRED)
};

}}  // namespace wh::entitymodule
