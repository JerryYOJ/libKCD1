#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindInteractiveObject — entity script binding for interactive objects
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindInteractiveObject@entitymodule@wh@@
// vtable: 0x1826beb88
// Constructor: sub_181056FAC
// Registration: sub_18106B6F4
// Size: 0xA8
//
// Entity binding — stored at C_EntityModule+0xD0.

namespace wh::entitymodule {

class C_ScriptBindInteractiveObject : public CScriptableBase {
public:
    void*       m_pContext;         // +0x60
    void*       m_pManager1;       // +0x68  from sub_180732120()
    void*       m_pUnk70;          // +0x70
    void*       m_pManager2;       // +0x78  from sub_180730B28()
    void*       m_pUnk80;          // +0x80
    int32_t     m_nUnk88;          // +0x88
    int32_t     _pad8C;            // +0x8C
    void*       m_pUnk90;          // +0x90
    void*       m_pUnk98;          // +0x98
    void*       m_pUnkA0;          // +0xA0

    // Lua methods (4)
    int CanUse(IFunctionHandler* pH, EntityId userId);   // 0x18105AAFC
    int Use(IFunctionHandler* pH, EntityId userId);      // 0x181075180
    int StopUse(IFunctionHandler* pH, EntityId userId);  // 0x181073B90
    int AbortUse(IFunctionHandler* pH);                  // 0x1810587B4
};
static_assert(sizeof(C_ScriptBindInteractiveObject) == 0xA8);

} // namespace wh::entitymodule
