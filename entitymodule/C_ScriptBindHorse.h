#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindHorse — entity script binding for horses
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindHorse@entitymodule@wh@@
// vtable: 0x1826c6050
// Constructor: sub_1810B953C
// Size: 0x78
//
// Entity binding — stored at C_EntityModule+0x98.

namespace wh::entitymodule {

class C_ScriptBindHorse : public CScriptableBase {
public:
    Offsets::IScriptTable*  m_pEntityTable;     // +0x60
    void*                   m_pGameFramework;   // +0x68  IGameFramework*
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x70

    // -- Lua methods (3) --
    int HasRider(IFunctionHandler* pH);          // 0x180B1AB4C
    int IsMountable(IFunctionHandler* pH);       // 0x180B1AC14
    int RearAndThrowDown(IFunctionHandler* pH);  // 0x180B1AC1C
};
static_assert(sizeof(C_ScriptBindHorse) == 0x78);

} // namespace wh::entitymodule
