#pragma once

#include <cstdint>
#include "Offsets/vtables/I_DialogUIController.h"
#include "Offsets/vtables/I_UIEntityDynText.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "guimodule/SUIEventSenderDispatcher.h"

// -----------------------------------------------
// C_UIInteractiveDialog — dialog topics / haggling / skill-check UI ("UIInteractiveDialog")
// -----------------------------------------------
// RTTI: .?AVC_UIInteractiveDialog@guimodule@wh@@  (3 vtables: +0x00
// 0x1826d17e8, +0x08 0x1826d1848, +0x10 0x1826d1870)
// Constructor:     sub_1811260B4
// Factory:         sub_18112A9F0  (SAutoRegUIEventSystem<C_UIInteractiveDialog>,
//                  allocates 0xA0, returns this+0x10 — the IUIGameEventSystem
//                  subobject CUIManager registers)
// GetName:         sub_1806FE7E0  -> "UIInteractiveDialog"
// InitEventSystem: sub_18112DEFC  (IUIGameEventSystem slot [2])
// Size:            0xA0
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::dialogmodule::I_DialogUIController  (11 slots)
//   [+0x08] wh::guimodule::I_UIEntityDynText        (4 slots; EntityFlashTag
//           dyn-texture bubbles)
//   [+0x10] IUIGameEventSystem (: IUIPseudoRTTI)    (8 slots)
//
// InitEventSystem (sub_18112DEFC) creates the system->UI IUIEventSystem
// "IDialog" (pFlashUI vtbl+0xC8, direction 1) and registers the events in
// E_UIInteractiveDialogEvent (ids are the literal map-insert keys). No
// UI->system functions (the class has NO SUIEventReceiverDispatcher).
// Full param tables: analysis/ui_infra/ui_elements_batch2.md.

namespace wh::guimodule {

// System->UI events on the "IDialog" event system (sub_18112DEFC).
enum class E_UIInteractiveDialogEvent {
    OnTopicChanged       = 0x00,  // dyn TopicList "(prompt, usedFlag)"; IsCleared:Bool, IsOnRight:Bool
    OnTopicInput         = 0x01,  // Title:Str, Message:Str, Min:Int, Max:Int, Value1..4:Int (Prev/Current/Your/Original), Progress1/2:Float, YourMoney:Float, HisMoeny:Float (sic), IsOnRight:Bool
    OnActiveTopicChanged = 0x02,  // Index:Int (zero-based), OnLimit:Int
    OnTimeLimitChanged   = 0x03,  // Limit:Float (percentage)
    SetDialogNumber      = 0x04,  // Value:Float
    ClearDialogNumber    = 0x05,
    OnSetSkillCheckParams= 0x06,  // IsOnRight:Bool, Name:Str (opponent), PlayerName:Str, Reputation:Float, {Speech,Charisma,Badassness}PlayerBase:Float, {Speech,Charisma,Badassness}{Player,NPC}:Float
};

class C_UIInteractiveDialog
    : public Offsets::I_DialogUIController       // +0x00
    , public Offsets::I_UIEntityDynText          // +0x08
    , public Offsets::IUIGameEventSystem         // +0x10  (: IUIPseudoRTTI)
{
public:
    SUIEventSenderDispatcher<E_UIInteractiveDialogEvent>
                             m_eventSender;     // +0x18  (map @0x18, m_pEventSystem @0x28)
    Offsets::IUIEventSystem* m_pUIEvents;       // +0x30  "IDialog" system->UI (set in InitEventSystem)

    uint8_t  m_flag38;                          // +0x38  ctor-init 0 (semantic UNVERIFIED)
    char     _pad39[0x7];                       // +0x39
    void*    _unk40;                            // +0x40  ctor-init 0
    void*    _unk48;                            // +0x48  ctor-init 0
    void*    _unk50;                            // +0x50  ctor-init 0

    // --- dialog/haggling state block, initialized by helper sub_181128AE0
    //     (this+0x58); likely an embedded struct in original source ---
    uint64_t _unk58;                            // +0x58  = 0
    uint32_t _unk60;                            // +0x60  = 0
    uint32_t _unk64;                            // +0x64  = 0
    uint32_t _unk68;                            // +0x68  = 0
    uint32_t _unk6C;                            // +0x6C  = 0
    float    m_vec70[3];                        // +0x70  = {-1.0f, -1.0f, -1.0f} (Vec3-like)
    char     _pad7C[0x4];                       // +0x7C
    CryStringT<char> m_str80;                   // +0x80  ctor-init "<unk>" (literal string in binary)
    CryStringT<char> m_str88;                   // +0x88  ctor-init "<unk>"
    uint32_t _unk90;                            // +0x90  = 0
    char     _pad94[0x4];                       // +0x94
    // --- end state block ---

    uint8_t  m_flag98;                          // +0x98  ctor-init 0; cleared by I_DialogUIController vf[10] (sub_1806FE7D0)
    char     _pad99[0x7];                       // +0x99

    // Overrides (documented; vtables inherited, not re-declared here):
    //   IUIGameEventSystem::GetName          -> sub_1806FE7E0 ("UIInteractiveDialog")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18112DEFC
    //   I_DialogUIController vf[5]           -> thunk sub_1811395E4 (this+0x18) -> sub_181122C9C
};
static_assert(sizeof(C_UIInteractiveDialog) == 0xA0);

}  // namespace wh::guimodule
