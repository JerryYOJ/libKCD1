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

    virtual int GetStage(IFunctionHandler* pH);    // 0x181284240
    virtual int IsComplete(IFunctionHandler* pH);  // 0x181284744
    virtual int IsActive(IFunctionHandler* pH);    // 0x181284690
    virtual int Complete(IFunctionHandler* pH);    // 0x1812833F0
    virtual int Restart(IFunctionHandler* pH);     // 0x1812869F0
    virtual int Proceed(IFunctionHandler* pH);     // 0x1812850E8
};
static_assert(sizeof(C_ScriptBindTutorial) == 0x68);

} // namespace wh::playermodule
