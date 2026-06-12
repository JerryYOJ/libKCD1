#pragma once

// -----------------------------------------------
// IUIEventListener — Binary vtable order (NOT interfuscated)
// -----------------------------------------------
// SDK: CryCommon/IFlashUI.h:1398 (GLOBAL namespace, untagged header ->
// declaration order). RTTI: .?AUIUIEventListener@@ — base of every
// SUIEventReceiverDispatcher<T> instantiation.
//
// Slot evidence (SUIEventReceiverDispatcher<C_UIMap> vtable 0x1826d15d8,
// 3 slots — COL-bounded, matches the 3 SDK declarations exactly):
//   [0] sub_18110EB94  OnEvent — looks up event.event id in mFunctionMap and
//                      dispatches to m_pThis
//   [1] sub_1806FE6B0  OnEventSystemDestroyed (clears m_pEventSystem)
//   [2] sub_181129AF8  deleting dtor (protected ~IUIEventListener in SDK)
//
// SDK signature of [0] is `SUIArgumentsRet OnEvent(const SUIEvent& event)` —
// SUIArguments returned by value => hidden sret first parameter in the binary.

// Forward declarations of real SDK types (GLOBAL namespace, pointer/ref use only):
struct SUIArguments;
struct SUIEvent;

namespace Offsets {

struct IUIEventSystem;

struct IUIEventListener {
    virtual SUIArguments* OnEvent(SUIArguments* sretArgs, const SUIEvent& event) = 0; // [0] 0x00  SDK: SUIArgumentsRet OnEvent(const SUIEvent&) — by-value return modeled as explicit hidden-sret param
    virtual void OnEventSystemDestroyed(IUIEventSystem* pEventSystem) = 0;            // [1] 0x08
    virtual void Dtor(char flags) = 0;                                                // [2] 0x10  protected ~ in SDK; deleting dtor in binary
};

}  // namespace Offsets
