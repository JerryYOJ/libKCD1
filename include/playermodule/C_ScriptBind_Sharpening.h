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

    virtual int Start(IFunctionHandler* pH);              // 0x181287324
    virtual int Stop(IFunctionHandler* pH);               // 0x181287934
    virtual int IsActive(IFunctionHandler* pH);           // 0x1812846E8
    virtual int SetGrindstone(IFunctionHandler* pH);      // 0x18128707C
    virtual int DoStepOnGrindstone(IFunctionHandler* pH); // 0x1812836B4
    virtual int SetPressure(IFunctionHandler* pH);        // 0x181287150
    virtual int SetPosition(IFunctionHandler* pH);        // 0x181287100
    virtual int SetRotation(IFunctionHandler* pH);        // 0x1812871A0
    virtual int SetOptimalRotation(IFunctionHandler* pH); // 0x1812870C4
    virtual int MoveToWorstZone(IFunctionHandler* pH);    // 0x181284B4C
    virtual int GetTotalQuality(IFunctionHandler* pH);    // 0x181284290
    virtual int GetWheelSpeed(IFunctionHandler* pH);      // 0x1812843D4
    virtual int SetWheelSpeed(IFunctionHandler* pH);      // 0x181287260
};
static_assert(sizeof(C_ScriptBind_Sharpening) == 0x68);

} // namespace wh::playermodule
