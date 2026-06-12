#pragma once
#include <cstdint>

// -----------------------------------------------
// IUIGameEventSystem — Binary vtable order
// -----------------------------------------------
// GameSDK-derived game interface, GLOBAL namespace (copied + extended by
// Warhorse from GameSDK Game/UI/IUIGameEventSystem.h). RTTI:
// .?AUIUIGameEventSystem@@ (: IUIPseudoRTTI). Game-side type — NOT
// interfuscated; slots follow declaration order.
//
// GameSDK original declares: ~dtor, GetTypeName, InitEventSystem,
// UnloadEventSystem, OnUpdate(float), UpdateView. The Warhorse variant has
// 8 slots (verified across C_UIMap @ 0x1826d16f0, C_UIHUDElements @
// 0x1826cf610, C_UIKeybinds @ 0x1826d1638, ... — all COL-bounded at 8):
//   [0] Dtor              CUIManager::InitEventSystems (sub_18113192C)
//                         destroys duplicate elements via vtbl[0](1)
//   [1] GetName           registry key (sub_1806FE780 "UIHelpBar",
//                         sub_1806FE810 "UIMap", ...); GameSDK: GetTypeName
//   [2] InitEventSystem   creates the element's IUIEventSystems
//                         (C_UIHUDElements sub_18111C520, C_UIMap
//                         sub_18112FC58, ...); called on every registry entry
//                         by CUIManager::InitEventSystems
//   [3] UnloadEventSystem VERIFIED non-nop: C_UIEventLog sub_181120604
//                         (unregisters from the event-log mgr) and
//                         CUIEntityDynTexTag sub_1811205CC (ClearAllTags +
//                         UnregisterModule); nop default in C_UIMap
//   [4] _vf4              nop in every observed implementation (GameSDK
//                         declares no slot here; purpose UNVERIFIED)
//   [5] Update(float)     per-frame from CUIManager::OnPostUpdate
//                         (sub_1805F3848 calls vtbl+0x28 with dt);
//                         CUIEntityDynTexTag impl sub_1805F38B4(this, float).
//                         GameSDK: OnUpdate(float fDelta)
//   [6] LoadFromProfile   KCD-extended profile hook — CUISettings impl
//                         sub_181150D40; CUISettings's IPlayerProfileListener
//                         vtable thunks LoadFromProfile here
//   [7] SaveToProfile     KCD-extended — CUISettings impl sub_1811559C0
//                         ([6]/[7] assignment follows the
//                         IPlayerProfileListener thunk pairing; bodies not
//                         diffed — direction UNVERIFIED beyond that. Params
//                         not recovered; declared parameterless here.)

namespace Offsets {

struct IUIGameEventSystem {
    virtual void Dtor(char flags) = 0;             // [0] 0x00
    virtual const char* GetName() = 0;             // [1] 0x08  (GameSDK: GetTypeName)
    virtual void InitEventSystem() = 0;            // [2] 0x10
    virtual void UnloadEventSystem() = 0;          // [3] 0x18
    virtual void _vf4() = 0;                       // [4] 0x20  nop everywhere observed
    virtual void Update(float fDeltaTime) = 0;     // [5] 0x28  (GameSDK: OnUpdate)
    virtual void LoadFromProfile() = 0;            // [6] 0x30  KCD-extended (CUISettings)
    virtual void SaveToProfile() = 0;              // [7] 0x38  KCD-extended (CUISettings)
};

}  // namespace Offsets
