#pragma once

// =====================================================================
// IFlashUI.h — Umbrella header for the KCD UI interface replicas
// =====================================================================
// Mirrors the SDK's CryCommon/IFlashUI.h organization: one include gets
// all FlashUI value types, all Offsets:: interface replicas, and both
// dispatcher templates. Consumer headers should include only this file.
//
// Includes (in dependency order):
//   guimodule/SUITypes.h    — FlashUI value types (SUIParameterDesc, SUIArguments,
//                             SUIEventDesc, TUIData, SUIEvent, ...) — real & usable
//   IUIEventListener.h      — 3 slots
//   IUIEventSystem.h        — 12 slots
//   IUIElementEventListener.h — 8 slots
//   IUIElementIterator.h    — 5 slots
//   IUIElement.h            — 101 slots (KCD-divergent: +RequestUnload [18])
//   IUIModule.h             — 8 slots (KCD-divergent: +Update [5])
//   [this file]             — IFlashUI: 43 slots (KCD-divergent: +slot[6], -CreateLookup* trio)
//   SUIEventReceiverDispatcher.h  — 0x28, global namespace
//   SUIEventSenderDispatcher.h    — 0x18, global namespace

#include "guimodule/SUITypes.h"
#include "IUIEventListener.h"
#include "IUIEventSystem.h"
#include "IUIElementEventListener.h"
#include "IUIElementIterator.h"
#include "IUIElement.h"
#include "IUIModule.h"

// -----------------------------------------------
// IFlashUI — Binary vtable order (NOT interfuscated)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashUI.h (struct IFlashUI : public ICryUnknown).
// IFlashUI.h carries NO <interfuscator:shuffle> tags -> slot order == C++
// declaration order. gEnv+0x130 holds the IFlashUI* (CFlashUI singleton).
//
// Implementation: CFlashUI, primary vtable @ 0x1827345f0 (43 slots).
// RTTI: .?AVCFlashUI@@ : IFlashUI : ICryUnknown (+0), IHardwareMouseEventListener (+0x08),
//       IInputEventListener (+0x10), IGameFrameworkListener (+0x18), ILevelSystemListener (+0x20),
//       ISystemEventListener (+0x28), ILoadtimeCallback (+0x30).
//
// Layout notes (verified against WHGame.dll):
// - Slots [0]-[3] come from ICryUnknown (CRYINTERFACE_DECLARE expands
//   _PROTECTED_DTOR first, so the dtor is slot 0, then GetFactory,
//   QueryInterface, QueryComposite — CryExtension/ICryUnknown.h).
// - Slot [6] is an EXTRA virtual present in the KCD build but absent from our
//   SDK header copy (between PostInit and Update). Impl 0x1806f8c30 returns
//   the CFlashUIActionEvents* member at this+0x38 created by Init [4].
// - The 3 trailing SUIItemLookupSet_Impl Create* methods of the SDK header are
//   guarded by #ifndef _LIB (IFlashUI.h:1586-1590) and are COMPILED OUT of the
//   monolithic WHGame.dll -> vtable ends at RemoveEditorUILogEventCallback.
// - MSVC emits adjacent overloads in REVERSE declaration order: GetUIElement
//   (int) lands at [12], (const char*) at [13]; same for GetUIAction.
// - Anchors verified behaviorally: GetUIElement(const char*) [13] 0x68
//   (name->index map lookup; also called with elem names by
//   LoadElementsFromFile), CreateEventSystem [25] 0xC8 (allocates 0x58-byte
//   CFlashUIEventSystem via ctor sub_181864DBC, checks GetEventSystem [26]
//   0xD0 first; CFlashUIActionEvents ctor sub_181862F3C calls it with
//   ("System",1)/("System",0)), Reload [8] logs "FlashUI reload start/end",
//   LoadElementsFromFile [10] logs "FlashUI parse element XML file %s" and
//   news 0x228-byte CFlashUIElement (ctor sub_1818644BC).

namespace Offsets {

struct IVirtualKeyboardEvents;

struct IFlashUI {
    // --- ICryUnknown base slots ---
    virtual void Dtor(char flags) = 0;                                              // [0]  0x000  sub_18186884C (scalar deleting dtor)
    virtual ICryFactory* GetFactory() const = 0;                                    // [1]  0x008  sub_180708C90  (decl-mapped)
    virtual void* QueryInterface(const void* iid) const = 0;                        // [2]  0x010  sub_1818916F4  (const CryInterfaceID& — GUID typedef, not forward-declarable) (decl-mapped)
    virtual void* QueryComposite(const char* name) const = 0;                       // [3]  0x018  sub_1803953E0  (decl-mapped)

    // --- IFlashUI ---
    virtual void Init() = 0;                                                        // [4]  0x020  sub_181881EFC  VERIFIED: news 0x68 CFlashUIActionEvents (ctor sub_181862F3C) -> this+0x38
    virtual bool PostInit() = 0;                                                    // [5]  0x028  sub_18188A490  VERIFIED: ANDs elem->Init(false)[+0x70], action->Init[+0x20], module->Init[+0x08]
    // KCD-ADDED slot, not in our SDK header copy. Returns the CFlashUIActionEvents*
    // member at this+0x38 (impl 0x1806f8c30 is ICF-folded with
    // CFlashUIElement::GetFlashFile — both `mov rax,[rcx+38h]`).
    // UNVERIFIED name; behavior (returns m_pUIActionEvents) verified.
    virtual CFlashUIActionEvents* GetUIActionEvents() const = 0;                    // [6]  0x030  0x1806f8c30
    virtual void Update(float fDeltatime) = 0;                                      // [7]  0x038  sub_1803E0918  VERIFIED: module->Update[+0x28], elem Update[+0xB0]/Render[+0xB8]/HasFlag[+0xF0]
    virtual void Reload() = 0;                                                      // [8]  0x040  sub_1818926FC  VERIFIED: "FlashUI reload start"/"FlashUI reload end", module->Reload[+0x18]
    virtual void Shutdown() = 0;                                                    // [9]  0x048  sub_1818963A0  (decl-mapped)

    virtual bool LoadElementsFromFile(const char* fileName) = 0;                    // [10] 0x050  sub_1818858B8  VERIFIED: "FlashUI parse element XML file %s", news CFlashUIElement(0x228)
    virtual bool LoadActionFromFile(const char* sFileName, int type) = 0;           // [11] 0x058  sub_1818856D8  IUIAction::EUIActionType (decl-mapped)

    // access for IUIElements. MSVC emits adjacent same-name virtual overloads in
    // REVERSED source order (proven: the 2nd-declared lands at the LOWER slot), so
    // const-char*-FIRST here compiles to the binary order int@+0x60 / const char*@
    // +0x68. Declaring (int) first instead sends GetUIElement("name") to the +0x60
    // (int) slot -> string ptr used as an index -> crash.
    virtual IUIElement* GetUIElement(const char* name) const = 0;                   // [13] 0x068  sub_180372A8C  VERIFIED ANCHOR: map lookup this+0x68; sub_18111B2C8 calls with "hud"; returns null on miss
    virtual IUIElement* GetUIElement(int index) const = 0;                          // [12] 0x060  sub_18187E62C  (indexes array at this+0x60)
    virtual int GetUIElementCount() const = 0;                                      // [14] 0x070  sub_180708EF0  (decl-mapped)
    virtual IUIElement* GetUIElementByInstanceStr(const char* UIInstanceStr) const = 0; // [15] 0x078  sub_18187E648  (decl-mapped)

    // access for IUIActions (const-char*-first, same MSVC overload-reversal reason as above)
    virtual IUIAction* GetUIAction(const char* name) const = 0;                     // [17] 0x088  sub_1806C8D74
    virtual IUIAction* GetUIAction(int index) const = 0;                            // [16] 0x080  sub_18046E0D4
    virtual int GetUIActionCount() const = 0;                                       // [18] 0x090  sub_180708EE0  (decl-mapped)

    virtual IUIActionManager* GetUIActionManager() const = 0;                       // [19] 0x098  0x1806fbe30  VERIFIED shape: returns this+0xE0
    virtual void UpdateFG() = 0;                                                    // [20] 0x0A0  sub_18046DFE4  (decl-mapped)
    virtual void RegisterModule(IUIModule* pModule, const char* name) = 0;          // [21] 0x0A8  sub_1818923D4  (decl-mapped; callers: C_UIMenuEvents/C_UIInventoryActions/C_UISaveLoad/CUISettings/CUIEntityDynTexTag)
    virtual void UnregisterModule(IUIModule* pModule) = 0;                          // [22] 0x0B0  sub_181898404  (decl-mapped; caller: CUIEntityDynTexTag::UnloadEventSystem)
    virtual void SetHudElementsVisible(bool bVisible) = 0;                          // [23] 0x0B8  sub_181895428  (decl-mapped)
    virtual void EnableEventStack(bool bEnable) = 0;                                // [24] 0x0C0  sub_181872FE0  (decl-mapped)

    // event systems
    virtual IUIEventSystem* CreateEventSystem(const char* name, IUIEventSystem::EEventSystemType eType) = 0; // [25] 0x0C8  sub_181870284  VERIFIED ANCHOR: news 0x58 CFlashUIEventSystem; callers sub_18110DE2C ("ActionHints", C_UIActionHintManager), sub_18111C520 ("HUDElements", C_UIHUDElements)
    virtual IUIEventSystem* GetEventSystem(const char* name, IUIEventSystem::EEventSystemType eType) = 0;    // [26] 0x0D0  sub_18187BF14  VERIFIED: called first by CreateEventSystem [25]
    virtual void* CreateEventSystemIterator(void* sret, IUIEventSystem::EEventSystemType eType) = 0;         // [27] 0x0D8  sub_1818703E0  SDK: IUIEventSystemIteratorPtr by value -> hidden sret param (decl-mapped)

    // input events
    virtual void DispatchControllerEvent(int event, int state) = 0;                 // [28] 0x0E0  sub_1804FF850  IUIElement::EControllerInputEvent/State (decl-mapped)
    virtual void SendFlashMouseEvent(int evt, int iX, int iY, int iButton, float fWheel, bool bFromController) = 0; // [29] 0x0E8  sub_180500238  SFlashCursorEvent::ECursorState (decl-mapped)
    virtual bool DisplayVirtualKeyboard(unsigned int flags, const wchar_t* title, const wchar_t* initialInput, int maxInputLength, IVirtualKeyboardEvents* pInCallback) = 0; // [30] 0x0F0  sub_181872730  (decl-mapped)
    virtual bool IsVirtualKeyboardRunning() = 0;                                    // [31] 0x0F8  sub_1805007AC  (decl-mapped)
    virtual bool CancelVirtualKeyboard() = 0;                                       // [32] 0x100  sub_18186B238  (decl-mapped)

    virtual void CheckPreloadedTexture(ITexture* pTexture) const = 0;               // [33] 0x108  sub_18186B584  (decl-mapped)
    virtual bool UseSharedRT(const char* instanceStr, bool defVal) const = 0;       // [34] 0x110  sub_181899D4C  (decl-mapped)
    virtual void GetMemoryStatistics(ICrySizer* s) const = 0;                       // [35] 0x118  sub_18187C480  (decl-mapped)
    virtual void GetScreenSize(int& width, int& height) = 0;                        // [36] 0x120  sub_18187E1F8  (decl-mapped)

    // UI Emulator (Sandbox) callbacks
    virtual void SetEditorScreenSizeCallback(void* cb) = 0;                         // [37] 0x128  sub_180709010  TEditorScreenSizeCallback& (decl-mapped)
    virtual void RemoveEditorScreenSizeCallback() = 0;                              // [38] 0x130  sub_180708F70  (decl-mapped)
    virtual void SetEditorPlatformCallback(void* cb) = 0;                           // [39] 0x138  sub_180708FF0  TEditorPlatformCallback& (decl-mapped)
    virtual void RemoveEditorPlatformCallback() = 0;                                // [40] 0x140  sub_180708F40  (decl-mapped)
    virtual void SetEditorUILogEventCallback(void* cb) = 0;                         // [41] 0x148  sub_180709030  TEditorUILogEventCallback& (decl-mapped)
    virtual void RemoveEditorUILogEventCallback() = 0;                              // [42] 0x150  sub_180708FA0  (decl-mapped; LAST slot — CreateLookup* trio is #ifndef _LIB and absent)
};

}  // namespace Offsets

// Dispatcher templates (GLOBAL namespace, matching binary RTTI).
// These depend on Offsets::IUIEventSystem and Offsets::IUIEventListener
// defined above.
#include "guimodule/SUIEventReceiverDispatcher.h"
#include "guimodule/SUIEventSenderDispatcher.h"
