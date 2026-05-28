#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindMap — Lua "UIMap" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindMap@guimodule@wh@@
// vtable: 0x1822e6ba8
// Constructor: sub_18110CD28
// Registration: inline via sub_18110B038 + sub_18110AF94
// Size: 0x70

namespace wh::guimodule {

class C_ScriptBindMap : public CScriptableBase {
public:
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68

    int SetPlaceDiscovered(IFunctionHandler* pH, const char* name, bool visited, bool show); // 0x18110D9D0
    int GoToCheckpointMark(IFunctionHandler* pH);                                            // 0x1806A71FC
};
static_assert(sizeof(C_ScriptBindMap) == 0x70);

} // namespace wh::guimodule
