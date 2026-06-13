#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include <map>
// consolidated into IFlashUI.h
#include "Offsets/vtables/I_InventoryListener.h"
#include "Offsets/vtables/I_EquipmentManagerListener.h"
// (individual UI includes consolidated into IFlashUI.h)

// -----------------------------------------------
// C_UIInventoryActions 鈥?inventory/shop flash <-> game bridge
// -----------------------------------------------
// RTTI: .?AVC_UIInventoryActions@guimodule@wh@@  (3 vtables: +0x00/+0x08/+0x10)
//   0x1822e8978 IUIModule (9 slots: 8 IUIModule + own [8], see below) 鈥?//               overrides: [0] dtor sub_181129BC8, [1] Init sub_18112D64C
//   0x1822e89c8 I_InventoryListener        (4 slots)
//   0x1822e89f0 I_EquipmentManagerListener (3 slots)
// Constructor: sub_181126124 鈥?called by CUIManager ctor sub_181125C08
//              (allocation 0x70)
// Size:        0x70
//
// Registered as FlashUI module:
//   pFlashUI->RegisterModule(this, "C_UIInventoryActions") (IFlashUI [21]).
// NOTE the event-system name asymmetry (Warhorse's own):
//   sender   system = "InventoryActions" (eEST_SYSTEM_TO_UI)
//   receiver system = "InventoryAction"  (eEST_UI_TO_SYSTEM, singular!)
//
// IUIModule::Init (sub_18112D64C) 鈥?run once game systems exist:
//   m_pUnk48 = *(*(S_GameContext+0xB0)+0x110), m_pUnk50 = *(...+0x108);
//   registers delegate callbacks (wrapper sub_1802E7190(this), fns
//   sub_1804FA2B0/sub_1804FA280) into the lists returned by sub_1806308B0()
//   and into *(S_GameContext+0xE8)+0xB0 at +0x10/+0x50 (inventory add/remove
//   notification sources feeding OnItemAdded/OnItemRemoved 鈥?exact system
//   identity UNVERIFIED).

namespace wh::guimodule {

// Sender events on "InventoryActions" (eEST_SYSTEM_TO_UI). Keys of
// m_eventSenderMap; note OnItemCombinations was assigned id 7 even though it
// is registered 5th (ids verified per-registration in the ctor).
enum class E_UIInventoryEvent {
    OnItemAdded            = 0,  // InventoryId, ItemId
    OnItemRemoved          = 1,  // InventoryId, ItemId ("removed from watched inventory")
    OnGetInventoryItems    = 2,  // Items, InventoryIdx
    OnItemInfoAll          = 3,  // ItemInfos, InventoryId
    OnItemInfoExAll        = 4,  // ItemInfo, InventoryId
    OnShopProperties       = 5,  // ShopId, Reputation, Bonus, Discount, CanHaggle, BasketInventoryId
    OpenInventoryTab       = 6,  // TabId, IsLast
    OnItemCombinations     = 7,  // CombinableItems, InventoryId, ItemId
    OnQuestDeliveryDetails = 8,  // Details ("text|count|total")
};

class C_UIInventoryActions
    : public Offsets::IUIModule                   // +0x00
    , public Offsets::I_InventoryListener         // +0x08
    , public Offsets::I_EquipmentManagerListener  // +0x10
{
public:
    // Own virtual appended after IUIModule's 8 slots (primary vtable slot [8],
    // empty impl _guard_check_icall_nop; purpose UNVERIFIED).
    virtual void _ownVf8() {}

    void*                                        m_unk18;            // +0x18  zero-init (never written in ctor)
    SUIEventReceiverDispatcher<C_UIInventoryActions>* m_pEventDispatcher; // +0x20  heap 0x28 (vtbl 0x1822e88f0)
    Offsets::IUIEventSystem*                     m_pUIEvents;        // +0x28  "InventoryAction" eEST_UI_TO_SYSTEM (listener "C_UIInventoryActions")
    Offsets::IUIEventSystem*                     m_pUIFunctions;     // +0x30  "InventoryActions" eEST_SYSTEM_TO_UI
    std::map<E_UIInventoryEvent, unsigned int>   m_eventSenderMap;   // +0x38
    void*                                        m_pUnk48;           // +0x48  set in Init: *(*(S_GameContext+0xB0)+0x110) (UNVERIFIED system)
    void*                                        m_pUnk50;           // +0x50  set in Init: *(*(S_GameContext+0xB0)+0x108) (UNVERIFIED system)
    uint8_t                                      m_unk58;            // +0x58  init 0
    char                                         _pad59[0x7];        // +0x59
    uint64_t                                     m_unk60;            // +0x60  init 0xFFFFFFFFFFFFFFFF (qword_1830107C8)
    uint64_t                                     m_unk68;            // +0x68  init 0

    // Receiver events on "InventoryAction" (UI -> system), listener
    // "C_UIInventoryActions" (registered in ctor; handler per event):
    //   GetInventoryItems(InventoryOwnerId)                    -> sub_181134C78
    //   WatchInventory(InventoryOwnerId, Enable)               -> sub_181136CD0
    //   RequestItemInfoAll(InventoryOwnerId, ItemIds)          -> sub_181135B90
    //   RequestItemInfoExAll(InventoryOwnerId, ItemIds)        -> sub_181135DD0
    //   DropItem(ItemId, Count)                                -> sub_1811346E0
    //   UseItem(InventoryOwnerId, ItemId, Amount, BodyPartId)  -> sub_181136BF4
    //   GetCombinableItems(SourceInventoryId, SourceItemId, TargetInventoryId) -> sub_181134894
    //   CombineItems(SourceInventoryId, SourceItemId, TargetInventoryId, TargetItemId) -> sub_1811342C4
    //   StealItem(ItemId)                                      -> sub_181136270
    //   OnItemBetweenBasket(FromId, ToId, ItemId, Count)       -> sub_1811351C8
    //   ShoppingCheckout(PlayerId, ShopId, Bargain)            -> sub_181136118
    //   QuestDeliveryCheckout                                  -> sub_181135B08
    //   OnItemMove(FromId, ToId, ItemId, Count)                -> sub_1811355F4
    //   OnTryItem(Equip, ItemId, Preview)                      -> sub_181136808
    //   OnShowSkipTime                                         -> sub_1811361F0
    //   PauseGame                                              -> sub_181135018
    //   ResumeGame                                             -> sub_181135108
};
static_assert(sizeof(C_UIInventoryActions) == 0x70);

}  // namespace wh::guimodule
