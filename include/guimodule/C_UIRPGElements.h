#pragma once

#include <cstdint>
#include "Offsets/vtables/I_RPGElementsController.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "guimodule/C_UIEBase.h"
#include "guimodule/SUIEventSenderDispatcher.h"
#include "guimodule/SUIEventReceiverDispatcher.h"

// -----------------------------------------------
// C_UIRPGElements — buffs / bleeding / level-up / perk HUD ("UIRPG")
// -----------------------------------------------
// RTTI: .?AVC_UIRPGElements@guimodule@wh@@  (3 vtables: +0x00 0x1826d2880,
// +0x08 0x1826d28a8, +0x10 0x1826d28f0)
// Constructor:     sub_181143C38
// Factory:         sub_181148584  (SAutoRegUIEventSystem<C_UIRPGElements>
//                  vtable 0x1822ed120; allocates 0xB8, returns this+8 — the
//                  IUIGameEventSystem subobject CUIManager registers)
// GetName:         sub_1806FE860  -> "UIRPG"
// InitEventSystem: sub_18114F2FC  (IUIGameEventSystem slot [2])
// Deleting dtor:   sub_181146D8C  (IUIGES [0] thunk sub_180B1AF70; the
//                  primary I_RPGElementsController has NO virtual dtor)
// Size:            0xB8
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::guimodule::I_RPGElementsController       (4 slots, no dtor)
//   [+0x08] IUIGameEventSystem (: IUIPseudoRTTI)         ([3] UnloadEventSystem
//           = sub_181157F40)
//   [+0x10] wh::guimodule::uielement::C_UIEBase          (: IUIElementEventListener;
//           0x28 bytes incl. 4 data qwords; its GetElementName ([10]
//           sub_1806FE690) returns "Inventory" — the bound Flash element)
//
// InitEventSystem (sub_18114F2FC):
//   0. lazily creates the buff-event source singleton qword_183500F10 (0x80
//      bytes, ctor sub_181159BF0, mutex unk_1836E3C40) and registers the
//      callback {sub_1806F09C0, this} via its vfunc+0x48
//   1. system->UI IUIEventSystem "RPGElements" (dir 1) -> m_pUIEvents; events
//      = E_UIRPGElementsEvent below
//   2. UI->system IUIEventSystem "RPGElements" (dir 0) -> m_pUIFunctions;
//      m_eventRecvDispatcher.Init(es, this, "C_UIRPGElements") and registers:
//        "OnReAddAllBuffs"   "re-send the add event for all buffs"  -> sub_1805B7E70
//        "GetBleeding"       "send player bleeding info"            -> sub_181151EB8
//        "GetOintmentEffect" (desc copy-paste "send player bleeding info";
//            ItemId:Str, BodyPartId:Int, Amount:Int)                -> sub_18114A6F0
// Full param tables: analysis/ui_infra/ui_elements_batch2.md.

namespace wh::guimodule {

// System->UI events on the "RPGElements" event system (ids are the literal
// map-insert keys in sub_18114F2FC).
enum class E_UIRPGElementsEvent {
    OnBuffAdded      = 0x00,  // BuffId:Str (unique), IconId:Int, UiName:Str, UiDesc:Str, UIType:Int, UIOrder:Int, UIVisibility:Int (mask), PerkUiName:Str, PerkIconId:Str
    OnBuffRemoved    = 0x01,  // BuffId:Str
    OnBuffChanged    = 0x02,  // OldBuffId:Str, NewBuffId:Str (replaced)
    OnBuffUpdated    = 0x03,  // BuffId:Str, Progress:Float [0,1], Count:Int
    OnBleedingData   = 0x04,  // BleedingData:Str "body_part_id|ui_name|icon_id|bleeding" per part
    OnOintmentEffect = 0x05,  // ItemId:Str, BodyPartId:Int, Amount:Int, HealedBleeding:Float 0-1, FullHealAmount:Int 0-N
    OnLevelUp        = 0x06,  // Stat:Str, Text:Str (ui name), OnlyXp:Bool, PerkPoints:Int
    OnPerkUsed       = 0x07,  // iconId:Str, uiName:Str
};

class C_UIRPGElements
    : public Offsets::I_RPGElementsController   // +0x00
    , public Offsets::IUIGameEventSystem        // +0x08  (: IUIPseudoRTTI)
    , public uielement::C_UIEBase               // +0x10  (0x28: vptr + 4 data qwords, zero-inited by this ctor)
{
public:
    SUIEventSenderDispatcher<E_UIRPGElementsEvent>
                             m_eventSender;     // +0x38  (map @0x38, m_pEventSystem @0x48)

    // Embedded dispatcher (0x28: vtable 0x1826d2798, mFunctionMap @+0x58,
    // m_pEventSystem @+0x68 = "RPGElements" UI->system, m_pThis @+0x70).
    SUIEventReceiverDispatcher<C_UIRPGElements>
                             m_eventRecvDispatcher; // +0x50 .. 0x78

    Offsets::IUIEventSystem* m_pUIEvents;       // +0x78  "RPGElements" system->UI
    Offsets::IUIEventSystem* m_pUIFunctions;    // +0x80  "RPGElements" UI->system (same object as m_eventRecvDispatcher.m_pEventSystem)

    void*    _unk88;                            // +0x88  ctor-init 0
    void*    _unk90;                            // +0x90  ctor-init 0
    void*    _unk98;                            // +0x98  ctor-init 0
    void*    _unkA0;                            // +0xA0  ctor-init 0
    void*    _unkA8;                            // +0xA8  ctor-init 0
    void*    _unkB0;                            // +0xB0  ctor-init 0

    // Overrides (documented; vtables inherited, not re-declared here):
    //   IUIGameEventSystem::GetName          -> sub_1806FE860 ("UIRPG")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18114F2FC
    //   IUIGameEventSystem [3] (Unload)      -> sub_181157F40
    //   C_UIEBase [0]                        -> sub_180501E90
    //   C_UIEBase [8]                        -> sub_18114B164 ("RequestSkills",
    //     "RequestSkillPerks", "RequestSoulValues", "RequestStatPerks",
    //     "RequestLearnPerk", "GetStatisticsCategory", "GetStatistics")
    //   C_UIEBase::GetElementName [10]       -> sub_1806FE690 ("Inventory")
};
static_assert(sizeof(C_UIRPGElements) == 0xB8);

}  // namespace wh::guimodule
