#pragma once

#include <cstdint>
#include "Offsets/vtables/IScriptTable.h"

// -----------------------------------------------
// C_ScriptBindMap — Lua "UIMap" table provider
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindMap@guimodule@wh@@  (inferred from vtable symbol)
// Constructor: sub_18110CD28
// Binary vtable at 0x1822e6ba8 (10 slots)
// Size: 0x70
//
// Lua methods:
//   UIMap.SetPlaceDiscovered(name, visited, show)  — sub_18110FB9C
//   UIMap.GoToCheckpointMark()                     — sub_18110DC88

namespace wh::guimodule {

class C_ScriptBindMap {
public:
    virtual void _vf0() {};   // [0] 0x00
    virtual void _vf1() {};   // [1] 0x08
    virtual void _vf2() {};   // [2] 0x10
    virtual void _vf3() {};   // [3] 0x18
    virtual void _vf4() {};   // [4] 0x20
    virtual void _vf5() {};   // [5] 0x28
    virtual void _vf6() {};   // [6] 0x30
    virtual void _vf7() {};   // [7] 0x38
    virtual void _vf8() {};   // [8] 0x40
    virtual void _vf9() {};   // [9] 0x48

    uint8_t     m_bInitialized;     // +0x08
    char        _pad09[0x7];        // +0x09
    char        _data10[0x40];      // +0x10  script system internals
    Offsets::IScriptTable* m_pScriptTable; // +0x50
    uint64_t    m_unk58;            // +0x58
    void*       m_pMapSystem;       // +0x60  back-ptr to POI/map subsystem
    void*       m_pEventDispatcher; // +0x68
};
static_assert(sizeof(C_ScriptBindMap) == 0x70);

}  // namespace wh::guimodule
