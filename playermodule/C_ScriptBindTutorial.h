#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindTutorial — Lua "Tutorial" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindTutorial@playermodule@wh@@
// vtable: 0x182312a50
// Constructor: sub_1812824D8
// Registration: sub_1812860C8
// Size: 0x68

namespace wh::playermodule {

class C_ScriptBindTutorial : public CScriptableBase {
public:
    void* m_pOwner;  // +0x60

    // Lua methods
    int GetStage(IFunctionHandler* pH);    // 0x180B1B17C
    int IsComplete(IFunctionHandler* pH);  // 0x180B1AB4C
    int IsActive(IFunctionHandler* pH);    // 0x180B1AC14
    int Complete(IFunctionHandler* pH);    // 0x180B1AC1C
    int Restart(IFunctionHandler* pH);     // 0x180B1AC24
    int Proceed(IFunctionHandler* pH);     // 0x180B1AC2C
};
static_assert(sizeof(C_ScriptBindTutorial) == 0x68);

} // namespace wh::playermodule
