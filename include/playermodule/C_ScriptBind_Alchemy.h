#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBind_Alchemy — Lua "Alchemy" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBind_Alchemy@playermodule@wh@@
// vtable: 0x182312cd0
// Constructor: sub_181282558
// Registration: sub_1812861C4
// Size: 0x68

namespace wh::playermodule {

class C_ScriptBind_Alchemy : public CScriptableBase {
public:
    void* m_pOwner;  // +0x60

    // -- Direct Lua methods --
    // int StartAlchemy(IFunctionHandler* pH, EntityId userId, EntityId tableId);  // 0x181287418
    // int ResetTable(IFunctionHandler* pH, EntityId tableId);                     // 0x1812869D0
    // int GetUsableFor(IFunctionHandler* pH);            // 0x18128437C
    // int IsUsableEnabledFor(IFunctionHandler* pH);      // 0x18128482C
    // int IsUsableByHold(IFunctionHandler* pH);          // 0x181284798
    // int GetFlagTextFor(IFunctionHandler* pH);          // 0x181283D74
};
static_assert(sizeof(C_ScriptBind_Alchemy) == 0x68);

} // namespace wh::playermodule
