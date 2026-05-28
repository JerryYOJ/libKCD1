#pragma once

#include <cstdint>
#include "playermodule/C_FastTravel.h"

// -----------------------------------------------
// C_PlayerModule — player module singleton
// -----------------------------------------------
// RTTI: .?AVC_PlayerModule@playermodule@wh@@
// Constructor: sub_1812816E4
// Alloc size:  0x110  (verified from mov r14d, 110h in sub_18215EB90)
// Inherits:
//   [+0x00] C_BaseModule → C_Graph → S_Graph → S_Job (wh::framework)
//   [+0x78] I_ModuleMessageListener (wh::framework)
//   [+0x88] ISystemEventListener
//
// Stored at S_GameContext+0xE8 (VERIFIED via sub_18215EB90 decompilation).
//
// Sub-objects created in constructor (verified via sub_1812816E4):
//   +0x90:  (0x2 bytes) flags
//   +0x98:  (0x78 bytes, sub_18126EAFC)
//   +0xA0:  (0x30 bytes) map/container
//   +0xA8:  (0x50 bytes, sub_18128288C)
//   +0xB0:  C_FastTravel* (0x188 bytes, sub_18121BF58) VERIFIED
//   +0xB8:  (0xA8 bytes, sub_18121C2A4)
//   +0xC0:  (0xA0 bytes, sub_18121BED4)
//   +0xC8:  (0x1E8 bytes, sub_18122DA04)
//   +0xD0:  (0x68 bytes, sub_18122D8C4)
//   +0xD8:  C_Signal<> (0x70 bytes)
//   +0xE0:  (0x170 bytes, sub_18122D118)
//   +0xE8:  (0x58 bytes, sub_18122D374)
//   +0xF0:  (0x40 bytes, sub_18122D9C8)
//   +0xF8:  (0x10 bytes, map container)
//   +0x100: C_BlockSourcesManager (0x10 bytes)
//   +0x108: bool

namespace wh::playermodule {

class C_PlayerModule {
public:
    char            _pad00[0x90];           // +0x00  base classes + early members
    void*           m_pFlags;               // +0x90  (0x2 bytes)
    void*           m_pUnk98;               // +0x98  (0x78 bytes, sub_18126EAFC)
    void*           m_pUnkA0;               // +0xA0  (0x30 bytes)
    void*           m_pUnkA8;               // +0xA8  (0x50 bytes, sub_18128288C)
    C_FastTravel*   m_pFastTravel;          // +0xB0  (0x188 bytes) VERIFIED
    void*           m_pUnkB8;               // +0xB8  (0xA8 bytes, sub_18121C2A4)
    void*           m_pUnkC0;               // +0xC0  (0xA0 bytes, sub_18121BED4)
    void*           m_pUnkC8;               // +0xC8  (0x1E8 bytes, sub_18122DA04)
    void*           m_pUnkD0;               // +0xD0  (0x68 bytes, sub_18122D8C4)
    void*           m_pSignal;              // +0xD8  wh::shared::C_Signal<> (0x70 bytes)
    void*           m_pUnkE0;               // +0xE0  (0x170 bytes, sub_18122D118)
    void*           m_pUnkE8;               // +0xE8  (0x58 bytes, sub_18122D374)
    void*           m_pUnkF0;               // +0xF0  (0x40 bytes, sub_18122D9C8)
    void*           m_pUnkF8;               // +0xF8  (0x10 bytes, map)
    void*           m_pBlockSourcesMgr;     // +0x100 C_BlockSourcesManager (0x10 bytes)
    bool            m_bUnk108;              // +0x108
    char            _pad109[0x7];           // +0x109
};
static_assert(sizeof(C_PlayerModule) == 0x110);

}  // namespace wh::playermodule
