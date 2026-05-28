#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindTrace — Lua "Trace" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindTrace@framework@wh@@
// vtable: 0x1822c1c18
// Constructor: sub_180F32C90
// Registration: sub_180F34864
// Size: 0x68
//
// All methods route to the same handler (sub_180F32EF0).
// T-prefixed constants are registered on the IScriptSystem global table.

namespace wh::framework {

class C_ScriptBindTrace : public CScriptableBase {
public:
    void* m_pContext;  // +0x60

    int PlotXY(IFunctionHandler* pH, int level, float x, float y, const char* tag);  // 0x180F32EF0
    int TableXY(IFunctionHandler* pH, int level, float x, float y, const char* msg); // 0x180F32EF0
    int Msg(IFunctionHandler* pH, int level, const char* msg);                        // 0x180F32EF0
    int Fatal(IFunctionHandler* pH);     // 0x180F32EF0
    int Error(IFunctionHandler* pH);     // 0x180F32EF0
    int Warning(IFunctionHandler* pH);   // 0x180F32EF0
    int Info(IFunctionHandler* pH);      // 0x180F32EF0
    int Detail(IFunctionHandler* pH);    // 0x180F32EF0
    int Debug(IFunctionHandler* pH);     // 0x180F32EF0
    int Brutus(IFunctionHandler* pH);    // 0x180F32EF0
    int max_trace_level(IFunctionHandler* pH);  // 0x180F32EF0
};
static_assert(sizeof(C_ScriptBindTrace) == 0x68);

} // namespace wh::framework
