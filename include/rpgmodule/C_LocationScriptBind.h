#pragma once

#include "../crysystem/CScriptableBase.h"

// C_LocationScriptBind — entity script binding for locations
// RTTI: .?AVC_LocationScriptBind@rpgmodule@wh@@  vtable: 0x1826d93f8
// Registration: sub_1811CC304  Size: 0x60
// Embedded inside C_ScriptBindRPGModule at offset +0xD0.

namespace wh::rpgmodule {
class C_LocationScriptBind : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LocationScriptBind;
    // int __tostring(IFunctionHandler* pH);                           // 0x1811D1AF0
    // int GetId(IFunctionHandler* pH);                                // 0x1811C1274
    // int GetName(IFunctionHandler* pH);                              // 0x1811C25FC
    // int GetCategory(IFunctionHandler* pH);                          // 0x1811C0B38
    // int GetState(IFunctionHandler* pH);                             // 0x1811C3F7C
    // int SetState(IFunctionHandler* pH, int state);                  // 0x1803953E0
    // int IsDiscovered(IFunctionHandler* pH);                         // 0x1811C5910
    // int GetPosition(IFunctionHandler* pH);                          // 0x1811C31D0
    // int GetReputation(IFunctionHandler* pH);                        // 0x1811C3654
    // int GetWantedLevel(IFunctionHandler* pH);                       // 0x1811C4268
    // int SetWantedLevel(IFunctionHandler* pH, int level);            // 0x18027CF60
};
static_assert(sizeof(C_LocationScriptBind) == 0x60);
} // namespace wh::rpgmodule
