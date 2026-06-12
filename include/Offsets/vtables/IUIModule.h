#pragma once

// -----------------------------------------------
// IUIModule — Binary vtable order
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashUI.h:1452 (struct IUIModule, GLOBAL namespace,
// not interfuscator-tagged). RTTI: .?AUIUIModule@@
// Modules register with CFlashUI via gEnv->pFlashUI->RegisterModule
// (IFlashUI vtbl [21] +0xA8) / UnregisterModule ([22] +0xB0).
//
// The in-tree SDK header declares 7 virtuals:
//   ~IUIModule, Init, Shutdown, Reload, Reset, EditorAllowReload, EditorReload
// The binary has 8 slots: Warhorse INSERTED `virtual void Update(float)` after
// Reset (slot [5]) — proven by CFlashUI::Update (sub_1803E0918, IFlashUI [7])
// calling module->vtbl+0x28 per frame, and CFlashUI::Reload (sub_1818926FC,
// IFlashUI [8]) calling module->vtbl+0x18 (= Reload at its SDK position [3]).
//
// Slot evidence across implementers (CUIEntityDynTexTag @ 0x1826cf4e0,
// C_UIMenuEvents @ 0x1822ed1f8, C_UIInventoryActions @ 0x1822e8978,
// C_UISaveLoad @ 0x1822ed138):
//   [0] deleting dtor       — wh::guimodule::CUIManager dtor body sub_18112906C
//                             destroys its sub-controllers through slot [0]
//   [1] Init                — C_UIMenuEvents sub_18114B0C4 / C_UISaveLoad
//                             sub_18114B380 / C_UIInventoryActions sub_18112D64C
//                             all register the module with game systems
//   [2] Shutdown            — nop default in every observed vtable (decl-mapped)
//   [3] Reload              — called by CFlashUI::Reload (+0x18);
//                             CUIEntityDynTexTag: sub_18111EA38 (conditional
//                             ClearAllTags)
//   [4] Reset               — CUIEntityDynTexTag: sub_18111EC88 (ClearAllTags);
//                             C_UIMenuEvents: sub_181155910 (closes menus)
//   [5] Update(float)       — called by CFlashUI::Update (+0x28); nop default
//                             everywhere observed (Warhorse-inserted slot)
//   [6] EditorAllowReload   — sub_1806F8140 = `return 1` shared default,
//                             matches SDK `{ return true; }`
//   [7] EditorReload        — nop default everywhere observed (decl-mapped)

namespace Offsets {

struct IUIModule {
    virtual void Dtor(char flags) = 0;        // [0] 0x00
    virtual void Init() = 0;                  // [1] 0x08
    virtual void Shutdown() = 0;              // [2] 0x10
    virtual void Reload() = 0;                // [3] 0x18
    virtual void Reset() = 0;                 // [4] 0x20
    virtual void Update(float fDeltaTime) = 0; // [5] 0x28  Warhorse addition (not in SDK header)
    virtual bool EditorAllowReload() = 0;     // [6] 0x30  default sub_1806F8140 returns true
    virtual void EditorReload() = 0;          // [7] 0x38
};

}  // namespace Offsets
