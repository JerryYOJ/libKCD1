#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBind_Sharpening — Lua "Sharpening" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBind_Sharpening@playermodule@wh@@
// vtable: 0x182312c40
// Constructor: sub_181282658
// Registration: sub_1812863F0
// Size: 0x68

namespace wh::playermodule {

class C_ScriptBind_Sharpening : public CScriptableBase {
public:
    void* m_pOwner;  // +0x60

    // Lua methods
    int Start(IFunctionHandler* pH, EntityId user, EntityId grindstoneId, EntityId itemId);  // 0x180B1B17C
    int Stop(IFunctionHandler* pH);                  // 0x180B1AB4C
    int IsActive(IFunctionHandler* pH);              // 0x180B1AC14
    int SetGrindstone(IFunctionHandler* pH, EntityId user);  // 0x180B1AC1C
    int DoStepOnGrindstone(IFunctionHandler* pH);    // 0x180B1AC24
    int SetPressure(IFunctionHandler* pH);           // 0x180B1AC2C
    int SetPosition(IFunctionHandler* pH);           // 0x180B1AD1C
    int SetRotation(IFunctionHandler* pH);           // 0x180B1AC34
    int SetOptimalRotation(IFunctionHandler* pH);    // 0x180B1AC3C
    int MoveToWorstZone(IFunctionHandler* pH);       // 0x180B1AC44
    int GetTotalQuality(IFunctionHandler* pH);       // 0x180B1AC4C
    int GetWheelSpeed(IFunctionHandler* pH);         // 0x180B1AC54
    int SetWheelSpeed(IFunctionHandler* pH);         // 0x180B1AC5C
};
static_assert(sizeof(C_ScriptBind_Sharpening) == 0x68);

} // namespace wh::playermodule
