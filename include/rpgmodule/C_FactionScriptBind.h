#pragma once

#include "../crysystem/CScriptableBase.h"

// C_FactionScriptBind — entity script binding for factions
// RTTI: .?AVC_FactionScriptBind@rpgmodule@wh@@  vtable: 0x1826d93a0
// Registration: sub_1811CC058  Size: 0x60
// Embedded inside C_ScriptBindRPGModule at offset +0x70.

namespace wh::rpgmodule {
class C_FactionScriptBind : public CScriptableBase {
public:
    // int __tostring(IFunctionHandler* pH);                                    // 0x1811D1A58
    // int GetId(IFunctionHandler* pH);                                         // 0x1811C124C
    // int GetName(IFunctionHandler* pH);                                       // 0x1811C2520
    // int GetLocationId(IFunctionHandler* pH);                                 // 0x1811C1A9C
    // int GetReputation(IFunctionHandler* pH);                                 // 0x1811C35F8
    // int GetBaseReputation(IFunctionHandler* pH);                             // 0x1811C07C0
    // int AddReputation(IFunctionHandler* pH, const char* sEnumName);          // 0x1811BBCB4
    // int GetAngriness(IFunctionHandler* pH);                                  // 0x1811C0620
    // int SetAngriness(IFunctionHandler* pH, float fValue);                    // 0x1811CF0FC
    // int AddAngriness(IFunctionHandler* pH, float fValue);                    // 0x1811BB624
};
static_assert(sizeof(C_FactionScriptBind) == 0x60);
} // namespace wh::rpgmodule
