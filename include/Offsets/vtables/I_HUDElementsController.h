#pragma once
#include <cstdint>

// -----------------------------------------------
// I_HUDElementsController — HUD operations interface
// -----------------------------------------------
// Warhorse: wh::guimodule::I_HUDElementsController
// RTTI: .?AVI_HUDElementsController@guimodule@wh@@
//
// PRIMARY (+0x00) base of C_UIHUDElements. This is the abstract HUD-operations
// interface that game/Lua code calls. It is a wh:: type, so the vtable is NOT
// interfuscated — slot order == declaration order (trust it). Modeled in the
// Offsets:: namespace for layout reuse, exactly like Offsets::I_LocationListener.
//
// Binary vtable for C_UIHUDElements @ 0x1826cf658 (38 slots). Method names are
// derived from the fc_*/string each method drives (decompiled); unresolved
// slots are kept as _vfN with their resolved address. Slots [1]/[32]/[36] are
// cross-confirmed against the Game.* Lua scriptbind:
//   Game.SendInfoText            -> [1]  ShowInfoText
//   Game.ShowCaptionObjectMessage-> [32] ShowCaptionObjectMessage
//   Game.ShowNotification        -> [36] ShowNotification

namespace Offsets {

struct I_HUDElementsController {
    virtual void Dtor(char flags) = 0;                 // [0]  0x000  sub_18111A39C
    virtual void ShowInfoText() = 0;                   // [1]  0x008  sub_18111FD4C  -> fc_showInfoText   [Game.SendInfoText]
    virtual void HideInfoText() = 0;                   // [2]  0x010  sub_18111B5A4  -> fc_hideInfoText   [Game.HideInfoText]
    virtual void _vf3() = 0;                           // [3]  0x018  sub_18111A680
    virtual void _vf4() = 0;                           // [4]  0x020  sub_18111B668  (InfoText queue mgmt; uihudelements.cpp)
    virtual void _vf5() = 0;                           // [5]  0x028  sub_18111FEA0
    virtual void ShowRandomEventResult() = 0;          // [6]  0x030  sub_18111FEC0  -> fc_showRandomEventResult
    virtual void ShowReputationNotification() = 0;     // [7]  0x038  sub_18111F1B8  (OnShowReputationNotification)
    virtual void _vf8() = 0;                           // [8]  0x040  sub_18111F720
    virtual void _vf9() = 0;                           // [9]  0x048  sub_18111EFAC
    virtual void _vf10() = 0;                          // [10] 0x050  sub_18111A524
    virtual void _vf11() = 0;                          // [11] 0x058  sub_18111EB30
    virtual void _vf12() = 0;                          // [12] 0x060  sub_18111FF58
    virtual void ShowDiceScore() = 0;                  // [13] 0x068  sub_18111FB08  (ShowDiceScore)
    virtual void HideDiceScore() = 0;                  // [14] 0x070  sub_18111B4E0  (HideDiceScore)
    virtual void AddDiceSelector() = 0;                // [15] 0x078  sub_18111A53C  (AddDiceSelector)
    virtual void RemoveDiceSelector() = 0;             // [16] 0x080  sub_18111EB90  (RemoveDiceSelector)
    virtual void ShowDiceCursor() = 0;                 // [17] 0x088  sub_18111FA84  (ShowDiceCursor)
    virtual void MoveDiceCursor() = 0;                 // [18] 0x090  sub_18111DA6C  (MoveDiceCursor)
    virtual void HideDiceCursor() = 0;                 // [19] 0x098  sub_18111B488  (HideDiceCursor)
    virtual void _vf20() = 0;                          // [20] 0x0A0  sub_18111F034
    virtual void _vf21() = 0;                          // [21] 0x0A8  sub_1811201B0
    virtual void _vf22() = 0;                          // [22] 0x0B0  sub_1811201E8
    virtual void _vf23() = 0;                          // [23] 0x0B8  sub_18111B5F4
    virtual void _vf24() = 0;                          // [24] 0x0C0  sub_18111FE94
    virtual void _vf25() = 0;                          // [25] 0x0C8  sub_1805B7E18
    virtual void _vf26() = 0;                          // [26] 0x0D0  sub_18111EBF4
    virtual void _vf27() = 0;                          // [27] 0x0D8  sub_18111AC14
    virtual void _vf28() = 0;                          // [28] 0x0E0  sub_18111B278
    virtual void HorseInspect() = 0;                   // [29] 0x0E8  sub_18111FC6C  (horse_inspect)
    virtual void _vf30() = 0;                          // [30] 0x0F0  sub_18111B538
    virtual void _vf31() = 0;                          // [31] 0x0F8  sub_18111FFEC  (@ui_hint_surrender)
    virtual void ShowCaptionObjectMessage() = 0;       // [32] 0x100  sub_18111F7AC  [Game.ShowCaptionObjectMessage]
    virtual void ShowHelpScreen() = 0;                 // [33] 0x108  sub_18111B338  (open_help_screen / @ui_hint_helpscreen)
    virtual void _vf34() = 0;                          // [34] 0x110  sub_18111FE10
    virtual void _vf35() = 0;                          // [35] 0x118  sub_18111E9F0
    virtual void ShowNotification() = 0;               // [36] 0x120  sub_18111FE6C  [Game.ShowNotification]
    virtual void SetTrespassing() = 0;                 // [37] 0x128  sub_18111F5E8  ("SetTresspasing")
};

}  // namespace Offsets
