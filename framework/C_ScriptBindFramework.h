#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindFramework — Lua "Framework" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindFramework@framework@wh@@
// vtable: 0x1822c0d38
// Constructor: sub_180F17E78
// Registration: sub_180F1A58C
// Size: 0x68

namespace wh::framework {

class C_ScriptBindFramework : public CScriptableBase {
public:
    void* m_pFramework;  // +0x60

    int ScriptHandlerToString(IFunctionHandler* pH);  // 0x180F1A914
    int IsValidWUID(IFunctionHandler* pH);             // 0x180F1A2F8
    int WUIDToString(IFunctionHandler* pH);            // 0x180F1B404
    int WUIDToMsg(IFunctionHandler* pH);               // 0x180F1B37C
    int WUIDToUI(IFunctionHandler* pH);                // 0x180F1B450
    int Expr(IFunctionHandler* pH);                    // 0x180F19DB4
};
static_assert(sizeof(C_ScriptBindFramework) == 0x68);

} // namespace wh::framework
