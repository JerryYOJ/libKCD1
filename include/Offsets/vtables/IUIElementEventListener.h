#pragma once
#include <cstdint>

// -----------------------------------------------
// IUIElementEventListener — Binary vtable order (NOT interfuscated)
// -----------------------------------------------
// SDK: CryCommon/IFlashUI.h:1019 (GLOBAL namespace, untagged header ->
// declaration order). RTTI: .?AUIUIElementEventListener@@
//
// EXACTLY 8 SLOTS. (This file previously claimed 20 slots from the C_UIMap
// vtable @ 0x1826d1738 — that fused THREE adjacent vtables: the following
// 2-slot + 8-slot vtables (COLs at 0x1826d1778 / 0x1826d1790) belong to
// C_UIInventoryElements, a different class. Corrected via COL walk
// 2026-06-12.)
//
// Slot map (SDK declaration order; all SDK impls are empty defaults):
//   [0] OnUIEvent            C_UIMap impl sub_1811368C8 (main Flash->C++
//                            dispatcher); C_UIEBase impl sub_180501E90
//   [1] OnUIEventEx          (decl-mapped; nop in observed implementers)
//   [2] OnInit               (decl-mapped)
//   [3] OnUnload             (decl-mapped)
//   [4] OnSetVisible         (decl-mapped)
//   [5] OnInstanceCreated    (decl-mapped)
//   [6] OnInstanceDestroyed  CUIEntityDynTexTag impl sub_18111E534 (zeroes
//                            the destroyed instance in m_Tags) — VERIFIED
//   [7] Dtor                 deleting dtor (protected ~ in SDK); C_UIEBase
//                            thunk sub_180B1AF7C
//
// Forward declarations of real SDK types (GLOBAL namespace, pointer/ref use only):
struct SUIEventDesc;
struct SUIArguments;

namespace Offsets {

struct IUIElement;
struct IFlashPlayer;

struct IUIElementEventListener {
    virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args) = 0;      // [0] 0x00
    virtual void OnUIEventEx(IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData) = 0; // [1] 0x08  (pUserData is void* in the SDK too)
    virtual void OnInit(IUIElement* pSender, IFlashPlayer* pFlashPlayer) = 0;                                  // [2] 0x10
    virtual void OnUnload(IUIElement* pSender) = 0;                                                            // [3] 0x18
    virtual void OnSetVisible(IUIElement* pSender, bool bVisible) = 0;                                         // [4] 0x20
    virtual void OnInstanceCreated(IUIElement* pSender, IUIElement* pNewInstance) = 0;                         // [5] 0x28
    virtual void OnInstanceDestroyed(IUIElement* pSender, IUIElement* pDeletedInstance) = 0;                   // [6] 0x30
    virtual void Dtor(char flags) = 0;                                                                         // [7] 0x38
};

}  // namespace Offsets
