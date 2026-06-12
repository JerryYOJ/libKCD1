#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/IUIEventListener.h"
#include "Offsets/vtables/IUIEventSystem.h"

// -----------------------------------------------
// SUIEventReceiverDispatcher<T> — CryEngine template (UI->system dispatch)
// -----------------------------------------------
// SDK: CryCommon/IFlashUI.h:1892 — `template<class C> struct
// SUIEventReceiverDispatcher : public IUIEventListener`. GLOBAL namespace
// (binary RTTI: .?AU?$SUIEventReceiverDispatcher@VC_UIMap@guimodule@wh@@@@).
//
// SDK semantics: Init(pEventSystem, pThis, listenerName) stores
// m_pEventSystem/m_pThis and calls pEventSystem->RegisterListener(this, name);
// RegisterEvent(desc, memberFn) maps the engine id returned by
// IUIEventSystem::RegisterEvent to a heap dispatch functor (binary common
// base RTTI .?AUIUIEventDispatchFct@@) in mFunctionMap; OnEvent ([0]) looks
// the id up and invokes the member function on m_pThis.
//
// Size 0x28 VERIFIED (was previously modeled 0x18 here — fixed 2026-06-12):
// every heap form allocates 0x28 (CUIInput/C_UIMenuEvents/C_UISaveLoad/
// C_UIInventoryActions/CUISettings ctors); embedded forms span 0x28
// (CUIGameEvents +0x18..0x40, C_UIKeybinds +0x08..0x30 — Init writes the
// m_pEventSystem/m_pThis tail). Function-map node = 0x30 (0x20 RB-tree header
// + pair<unsigned int id, IUIEventDispatchFct*>); sentinel allocator
// sub_180732120. See analysis/ui_infra/ui_managers.md.
//
// Known instantiation vtables (3 slots each == IUIEventListener):
//   <C_UIMap>               0x1826d15d8   <C_UIKeybinds>     0x1826d15f8
//   <C_UIInventoryElements> 0x1826d1618   <CUIGameEvents>    0x1822e7560
//   <CUISettings>           0x1826d2860   <C_UIHUDElements>  0x1826cf5f0

struct IUIEventDispatchFct;  // binary RTTI .?AUIUIEventDispatchFct@@ — base of SUIEventDispatchFctImpl<...>

template<typename T>
struct SUIEventReceiverDispatcher : public Offsets::IUIEventListener {
    // The SDK template is concrete (it implements IUIEventListener); stub
    // overrides here so the type can be embedded by value. Real per-T impls
    // are in the binary vtables listed above.
    SUIArguments* OnEvent(SUIArguments* sretArgs, const SUIEvent& event) override { return nullptr; }
    void OnEventSystemDestroyed(Offsets::IUIEventSystem* pEventSystem) override {}
    void Dtor(char flags) override {}

    std::map<unsigned int, IUIEventDispatchFct*> mFunctionMap;   // +0x08  engine event id -> dispatch functor (SDK name)
    Offsets::IUIEventSystem*                     m_pEventSystem; // +0x18  set by Init()
    T*                                           m_pThis;        // +0x20  set by Init(); OnEvent dispatch target
};

static_assert(sizeof(SUIEventReceiverDispatcher<void>) == 0x28);
