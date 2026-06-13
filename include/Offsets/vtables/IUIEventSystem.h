#pragma once
#include "guimodule/SUITypes.h"
#include "IUIEventListener.h"

// -----------------------------------------------
// IUIEventSystem — Binary vtable order (NOT interfuscated)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashUI.h:1406 (UNIQUE_IFACE struct IUIEventSystem).
// No <interfuscator:shuffle> tags -> slot order == C++ declaration order.
//
// Implementation: CFlashUIEventSystem (size 0x58, ctor sub_181864DBC, newed by
// CFlashUI::CreateEventSystem). Single vtable @ 0x1827347e0 (12 slots,
// this_off 0). RTTI: .?AVCFlashUIEventSystem@@ : IUIEventSystem.
// 12 binary slots == 12 SDK declarations: this interface matches our SDK
// header copy EXACTLY (no inserted slot).
//
// Members recovered: +0x18 std::vector-style array of SUIEventDesc* (events;
// SUIEventDesc allocation size 0x68), +0x30 vector of IUIEventListener*.
//
// Anchors verified: sub_18110DE2C (C_UIActionHintManager::InitEventSystem) /
// sub_18111C520 (C_UIHUDElements::InitEventSystem) call [3] RegisterEvent
// (+0x18) with SUIEventDesc and [4] RegisterListener (+0x20) with
// (listener, "C_UIActionHintManager") / (listener, "C_UIHUDElements")
// respectively. CFlashUIActionEvents ctor sub_181862F3C does the
// same for the "System" event systems ("OnSystemStarted", "OnLoadingStart"...).
// MSVC overload REVERSAL applies to the GetEventDesc pair: (const char*) at
// [7], (int) at [8].

namespace Offsets {

struct IUIEventSystem {
    enum EEventSystemType {
        eEST_UI_TO_SYSTEM = 0,
        eEST_SYSTEM_TO_UI = 1,
    };

    virtual void Dtor(char flags) = 0;                                  // [0]  0x00  sub_181869060 (scalar deleting dtor)
    virtual const char* GetName() const = 0;                            // [1]  0x08  0x1806f8130  (decl-mapped; ICF-shared member getter)
    virtual EEventSystemType GetType() const = 0;                       // [2]  0x10  sub_1806F8B10  (decl-mapped)

    virtual unsigned int RegisterEvent(const SUIEventDesc& eventDesc) = 0;   // [3]  0x18  sub_181891D40  VERIFIED: clones 0x68-byte desc, appends to this+0x18 array, returns size-1 as event id
    virtual void RegisterListener(IUIEventListener* pListener, const char* name) = 0; // [4]  0x20  sub_180E483A0  VERIFIED: push-unique into vector at this+0x30
    virtual void UnregisterListener(IUIEventListener* pListener) = 0;   // [5]  0x28  sub_180E59BE8  (decl-mapped)

    virtual SUIArguments* SendEvent(SUIArguments* sret, const SUIEvent& event) = 0; // [6]  0x30  sub_1805012B4  SDK: SUIArgumentsRet SendEvent(const SUIEvent&) — by-value return modeled as explicit hidden-sret param (decl-mapped)

    // overload pair REVERSED vs declaration
    virtual const SUIEventDesc* GetEventDesc(const char* eventName) const = 0;  // [7]  0x38  sub_18187BEAC  (decl-mapped)
    virtual const SUIEventDesc* GetEventDesc(int index) const = 0;      // [8]  0x40  sub_1805015B0  VERIFIED: bounds-checked index into the same this+0x18 array RegisterEvent fills
    virtual int GetEventCount() const = 0;                              // [9]  0x48  sub_180708C80  (decl-mapped)

    virtual unsigned int GetEventId(const char* sEventName) = 0;        // [10] 0x50  sub_18187BEB8  (decl-mapped)

    virtual void GetMemoryUsage(ICrySizer* s) const = 0;                // [11] 0x58  sub_18187D470  (decl-mapped)
};

}  // namespace Offsets
