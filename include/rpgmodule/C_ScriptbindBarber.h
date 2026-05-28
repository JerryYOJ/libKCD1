#pragma once

#include "../crysystem/CScriptableBase.h"

// C_ScriptbindBarber — Lua "Barber" table
// RTTI: .?AVC_ScriptbindBarber@rpgmodule@wh@@  vtable: 0x1826d8d08
// Constructor: sub_1811BA584  Registration: sub_1811CD77C  Size: 0x60

namespace wh::rpgmodule {
class C_ScriptbindBarber : public CScriptableBase {
public:
    // int Create(IFunctionHandler* pH, ScriptHandle soul);    // 0x1811BE584
    // int Destroy(IFunctionHandler* pH, ScriptHandle barber); // 0x1811BEDD4
    // int TryHair(IFunctionHandler* pH, const char* guid);    // 0x1811CFDE8
    // int TryBeard(IFunctionHandler* pH, const char* guid);   // 0x1811CFC88
    // int Commit(IFunctionHandler* pH);                       // 0x1811BE2BC
    // int Revert(IFunctionHandler* pH);                       // 0x1811CE5A0
};
static_assert(sizeof(C_ScriptbindBarber) == 0x60);
} // namespace wh::rpgmodule
