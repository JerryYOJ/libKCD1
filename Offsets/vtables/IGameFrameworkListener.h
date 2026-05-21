#pragma once
#include <cstdint>

// -----------------------------------------------
// IGameFrameworkListener — Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine/CryCommon/IGameFramework.h
// SDK order (pre-shuffle):
//   ~dtor, OnPostUpdate, OnSaveGame, OnLoadGame, OnLevelEnd,
//   OnActionEvent, OnPreRender, OnSavegameFileLoadedInMemory,
//   OnForceLoadingWithFlash
//
// Binary vtable for CUIManager at 0x1822e8b40 (9 slots):
//   [0] sub_180B1AEEC  ~CUIManager() thunk (this -= 8)
//   [1] sub_1805F3848  OnPostUpdate — iterates IUIGameEventSystem map, calls Update()
//   [2] nop
//   [3] nop
//   [4] nop
//   [5] nop
//   [6] nop
//   [7] nop
//   [8] nop

namespace Offsets {

struct IGameFrameworkListener {
    virtual void Dtor(char flags) = 0;                     // [0] 0x00
    virtual void OnPostUpdate(float fDeltaTime) = 0;       // [1] 0x08
    virtual void _vf2() = 0;                               // [2] 0x10
    virtual void _vf3() = 0;                               // [3] 0x18
    virtual void _vf4() = 0;                               // [4] 0x20
    virtual void _vf5() = 0;                               // [5] 0x28
    virtual void _vf6() = 0;                               // [6] 0x30
    virtual void _vf7() = 0;                               // [7] 0x38
    virtual void _vf8() = 0;                               // [8] 0x40
};

}  // namespace Offsets
