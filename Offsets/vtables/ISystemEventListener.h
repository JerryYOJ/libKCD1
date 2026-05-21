#pragma once
#include <cstdint>

// -----------------------------------------------
// ISystemEventListener — Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine/CryCommon/ISystem.h
// SDK order (pre-shuffle): ~dtor, OnSystemEventAnyThread, OnSystemEvent
//
// Binary vtable for CUIManager at 0x1822e8b90 (4 slots):
//   [0] sub_181129B60  ~CUIManager()
//   [1] nop            OnSystemEventAnyThread (empty impl)
//   [2] sub_1806A2A24  OnSystemEvent
//   [3] nop            (CUIManager's own virtual — extends primary vtable)

namespace Offsets {

struct ISystemEventListener {
    virtual void Dtor(char flags) = 0;                                              // [0] 0x00
    virtual void OnSystemEventAnyThread(unsigned int event, uintptr_t wp, uintptr_t lp) = 0; // [1] 0x08
    virtual void OnSystemEvent(unsigned int event, uintptr_t wp, uintptr_t lp) = 0;          // [2] 0x10
};

}  // namespace Offsets
