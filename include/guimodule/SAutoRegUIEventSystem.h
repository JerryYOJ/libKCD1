#pragma once

#include "guimodule/IUIEventSystemFactory.h"

// -----------------------------------------------
// SAutoRegUIEventSystem<T> — auto-registration glue for UI event systems
// -----------------------------------------------
// RTTI: .?AU?$SAutoRegUIEventSystem@V<T>@@@@ — GLOBAL namespace (CryEngine
// GameSDK Game/UI/UIManager.h template copied by Warhorse; NOT wh::guimodule).
//
// One static instance per UI element class links itself into the
// IUIEventSystemFactory list at DLL static-init time; CUIManager's ctor later
// walks the list and Create()s every element (see IUIEventSystemFactory.h).
//
// Verified instantiations (vtables; [0] = shared dtor sub_18110D438,
// [1] = per-class Create):
//   SAutoRegUIEventSystem<wh::guimodule::C_UIMap>           @ 0x1822e8930,
//     Create = sub_18112ACE8 (allocates 0x4C8, ctor sub_181128558)
//   SAutoRegUIEventSystem<wh::guimodule::C_UIHUDElements>   @ 0x1822e7548
//   SAutoRegUIEventSystem<wh::guimodule::CUIEntityDynTexTag>@ 0x1822e7580
//   SAutoRegUIEventSystem<C_UIEventLog>                     @ 0x1822e76d0
//   SAutoRegUIEventSystem<C_UICombatListener>               @ 0x1822e6b38
//   SAutoRegUIEventSystem<C_UIActionHintManager>            @ 0x1822e6b90
//   SAutoRegUIEventSystem<wh::guimodule::C_UIInventoryElements> @ 0x1822e8948
//   SAutoRegUIEventSystem<wh::guimodule::C_UIKeybinds>      @ 0x1822e8960
//   SAutoRegUIEventSystem<wh::guimodule::C_UIInteractiveDialog> @ 0x1822e8a10
//   SAutoRegUIEventSystem<wh::guimodule::CUISettings>       @ 0x1822ecd38
//   SAutoRegUIEventSystem<wh::guimodule::C_UISubtitles>     @ 0x1822ece38
//   SAutoRegUIEventSystem<wh::guimodule::C_UIRPGElements>   @ 0x1822ed120
//   SAutoRegUIEventSystem<wh::guimodule::C_UIQuestLog>      @ 0x1822ed180
//   SAutoRegUIEventSystem<wh::guimodule::C_UIMinigameElements> @ 0x1822ed1e0
//
// The implicit upcast in `return new T()` performs the this-adjustment seen in
// the binary (e.g. C_UIHUDElements factory sub_18111AB18 returns alloc+8, the
// IUIGameEventSystem subobject).

template <class T>
struct SAutoRegUIEventSystem : public IUIEventSystemFactory {
    // Original body: `{ return new T(); }` — kept pure here because the RE
    // models of every registered T are abstract (interface virtuals are
    // documented, not stubbed), so the original body would not compile.
    // The template adds NO data members: layout == IUIEventSystemFactory
    // (0x10; static_assert lives in IUIEventSystemFactory.h).
    Offsets::IUIGameEventSystem* Create() override = 0;  // [1] per-class impl, see vtable list above
};
