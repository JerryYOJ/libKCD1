#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include "Offsets/vtables/I_HUDElementsController.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/I_LocationListener.h"
// consolidated into IFlashUI.h

// -----------------------------------------------
// C_UIHUDElements 鈥?in-game HUD controller ("UIHelpBar")
// -----------------------------------------------
// RTTI: .?AVC_UIHUDElements@guimodule@wh@@   (3 vtables: +0x00, +0x08, +0x10)
// Constructor:     sub_181119680
// Factory:         sub_18111AB18  (allocates 0x1A8, returns this+8 鈥?the
//                  IUIGameEventSystem subobject that CUIManager stores in its
//                  registry; CUIManager::Get("UIHelpBar")-8 recovers `this`)
// InitEventSystem: sub_18111C520  (IUIGameEventSystem slot [2]; registers the
//                  "HUDElements" Flash event system 鈥?see E_UIHUDElementEvent)
// GetName:         sub_1806FE780  -> "UIHelpBar"
// Size:            0x1A8
//
// Registered in CUIManager::m_eventSystemMap under "UIHelpBar". Backs
// Game.SendInfoText / ShowNotification / ShowCaptionObjectMessage and the
// item "ShowItemsTransfer" popup (via the I_HUDElementsController API and the
// "HUDElements" IUIEventSystem).
//
// Inheritance (binary layout, from RTTI class-hierarchy descriptor):
//   [+0x00] I_HUDElementsController 鈥?HUD operations API (38 slots)
//   [+0x08] IUIGameEventSystem      鈥?FlashUI plumbing (: IUIPseudoRTTI)
//   [+0x10] I_LocationListener      鈥?location-discovery callbacks (wh::rpgmodule)
// NOTE: SUIEventReceiverDispatcher<C_UIHUDElements> is an EMBEDDED MEMBER at
// +0x30 (NOT a base 鈥?it is absent from the class-hierarchy descriptor).

namespace wh::guimodule {

// Flash event-system ids registered by InitEventSystem (sub_18111C520), in
// registration order. These are the system->UI "HUDElements" events (distinct
// id space from the I_HUDElementsController vtable slots).
enum class E_UIHUDElementEvent {
    OnShowHelp                      = 0x00,
    ShowInfoText                    = 0x01,   // params: Text, ForceClearCurrentInfoTextQueue
    HideInfoText                    = 0x02,
    ShowBookmarks                   = 0x03,
    SelectBookmark                  = 0x04,
    ShowQuestEvent                  = 0x05,
    ShowStatCheckResult             = 0x06,
    ShowDiscoveryMessage            = 0x07,
    HideTutorialAndDiscoveryMessage = 0x08,
    AddOverlay                      = 0x09,
    RemoveOverlay                   = 0x0A,
    ChangeOverlay                   = 0x0B,
    ShowItemsTransfer               = 0x0C,   // uiName, IconId, Count, Direction (true=got / false=gave)
    HorseInspect                    = 0x0D,
    RequestHideHorseInspect         = 0x0E,
    ShowHelpScreen                  = 0x0F,
    ShowNotification                = 0x10,
};

class C_UIHUDElements
    : public Offsets::I_HUDElementsController      // +0x00
    , public Offsets::IUIGameEventSystem           // +0x08  (: IUIPseudoRTTI)
    , public Offsets::I_LocationListener           // +0x10
{
public:
    // +0x18/+0x20 look like a std::map (head sentinel from sub_180730B28 鈥?a
    // std::map sentinel-node allocator; the old "FlashEventDispatcher" label
    // was a misnomer). With +0x28 this matches a SUIEventSenderDispatcher
    // <E_UIHUDElementEvent> at +0x18..0x30 (that instantiation's RTTI exists
    // in the binary) 鈥?pairing UNVERIFIED, kept as raw members.
    void*    m_senderMapHead18;         // +0x18  std::map sentinel (sub_180730B28)
    uint64_t m_senderMapSize20;         // +0x20
    void*    _unk28;                    // +0x28  likely the sender's m_pEventSystem (UNVERIFIED)

    // Embedded dispatcher (0x28: vtable 0x1826cf5f0, mFunctionMap @+0x38,
    // m_pEventSystem @+0x40 = UI->system "HUDElements", m_pThis @+0x48).
    SUIEventReceiverDispatcher<C_UIHUDElements> m_eventRecvDispatcher; // +0x30 .. 0x58

    char     _pad58[0x10];              // +0x58
    uint8_t  _unk68[0x28];              // +0x68  embedded object (sub_1811192C4)
    void*    _unk90;                    // +0x90  back-ref (= this+0x18)
    void*    m_pIntrusiveListHead;      // +0x98  self-linked node (alloc 0x10)
    char     _padA0[0x20];              // +0xA0
    uint8_t  m_flagC0;                  // +0xC0  init = 1
    char     _padC1[0x7];               // +0xC1
    void*    _unkC8;                    // +0xC8
    void*    _unkD0;                    // +0xD0
    void*    _unkD8;                    // +0xD8
    uint32_t _unkE0;                    // +0xE0
    uint8_t  _unkE4;                    // +0xE4
    char     _padE5[0xB];               // +0xE5
    void*    _unkF0;                    // +0xF0
    void*    _unkF8;                    // +0xF8
    void*    _unk100;                   // +0x100
    void*    _unk108;                   // +0x108
    void*    _unk110;                   // +0x110
    uint8_t  _unk118;                   // +0x118
    char     _pad119[0x7];              // +0x119
    void*    _unk120;                   // +0x120
    void*    _unk128;                   // +0x128
    void*    _unk130;                   // +0x130
    void*    _unk138;                   // +0x138
    void*    _unk140;                   // +0x140
    uint8_t  _unk148;                   // +0x148
    char     _pad149[0x7];              // +0x149
    uint8_t  m_unk150[0x40];            // +0x150  array/container (sub_180F993F0)
    void*    _unk190;                   // +0x190
    uint32_t _unk198;                   // +0x198
    char     m_szFixed19C[0x6];         // +0x19C  CryFixedStringT (sub_1806699C8, len 6)
    char     _pad1A2[0x6];              // +0x1A2

    // Overrides (documented; vtables inherited, not re-declared here):
    //   IUIGameEventSystem::GetName          -> sub_1806FE780 ("UIHelpBar")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18111C520
};
static_assert(sizeof(C_UIHUDElements) == 0x1A8);

}  // namespace wh::guimodule
