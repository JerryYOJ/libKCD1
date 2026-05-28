#pragma once

#include "../crysystem/CScriptableBase.h"

// C_ScriptBindStatistics — Lua "Statistics" table
// RTTI: .?AVC_ScriptBindStatistics@rpgmodule@wh@@  vtable: 0x182306bd0
// Constructor: sub_1811BA508  Registration: sub_1811CD6FC  Size: 0x60

namespace wh::rpgmodule {
class C_ScriptBindStatistics : public CScriptableBase {
public:
    // int Increment(IFunctionHandler* pH, const char* statisticName, float value);  // 0x1811C483C
    // int Set(IFunctionHandler* pH, const char* statisticName, float value);        // 0x1811CEF74
    // int Reset(IFunctionHandler* pH, const char* statisticName);                   // 0x1811CE208
};
static_assert(sizeof(C_ScriptBindStatistics) == 0x60);
} // namespace wh::rpgmodule
