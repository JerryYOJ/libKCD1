#pragma once

#include <cstdint>
#include "Offsets/vtables/IUIGameEventSystem.h"

// -----------------------------------------------
// IUIEventSystemFactory — self-registering factory for IUIGameEventSystem
// -----------------------------------------------
// RTTI: .?AUIUIEventSystemFactory@@ — GLOBAL namespace (CryEngine GameSDK
// Game/UI/UIManager.h header copied by Warhorse; NOT wh::guimodule).
// Vtable: 0x1822e6be8 (2 slots):
//   [0] sub_18110D438  scalar deleting dtor (resets vtbl, frees) — the
//                      Warhorse version HAS a virtual dtor (GameSDK original
//                      declares only Create); shared/COMDAT-folded across all
//                      SAutoRegUIEventSystem<T> instantiations
//   [1] _purecall      Create() — pure here, overridden per template instance
//
// Registration ctor (inlined into every SAutoRegUIEventSystem<T> static
// initializer; canonical shape sub_180713894):
//   m_pNext = nullptr;
//   if (s_pLast) s_pLast->m_pNext = this; else s_pFirst = this;
//   s_pLast = this;
// Statics in WHGame.dll .data:
//   s_pFirst = qword_182F77880   (list head — walked by
//              CUIManager::InitEventSystems sub_18113192C)
//   s_pLast  = qword_182F77878   (list tail)
//
// Consumption (CUIManager::InitEventSystems sub_18113192C):
//   for (f = s_pFirst; f; f = f->m_pNext) {
//     elem = f->Create();                      // vtbl[1]
//     key  = elem->GetName();                  // IUIGameEventSystem vtbl[1]
//     if (!m_eventSystemMap.count(key)) m_eventSystemMap[key] = elem;
//     else elem->Dtor(1);                      // duplicate -> deleted
//   }
//   then InitEventSystem() (IUIGameEventSystem vtbl[2]) on every map entry.

struct IUIEventSystemFactory {
    virtual ~IUIEventSystemFactory() {}                 // [0] 0x00  sub_18110D438
    virtual Offsets::IUIGameEventSystem* Create() = 0;  // [1] 0x08  _purecall in base

    IUIEventSystemFactory* m_pNext;                     // +0x08  next factory in list

    static IUIEventSystemFactory* s_pFirst;             // qword_182F77880 (declared only — the
    static IUIEventSystemFactory* s_pLast;              // qword_182F77878  real lists live in WHGame.dll)

    // Registration ctor intentionally NOT replicated (it would ODR-use the
    // undefined statics and could only build a list separate from the game's).
    // Original shape (inlined at every static instance, sub_180713894):
    //   m_pNext = nullptr;
    //   if (s_pLast) s_pLast->m_pNext = this; else s_pFirst = this;
    //   s_pLast = this;
};
static_assert(sizeof(IUIEventSystemFactory) == 0x10);
