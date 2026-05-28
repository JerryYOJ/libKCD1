#pragma once
#include "../crysystem/CScriptableBase.h"

// C_ScriptBindTrace — Lua "Trace" table
// RTTI: .?AVC_ScriptBindTrace@framework@wh@@  vtable: 0x1822c1c18
// Constructor: sub_180F32C90  Registration: sub_180F34864  Size: 0x68
// NOTE: All methods route to 0x180F32EF0 (noop — just calls EndFunction)

namespace wh::framework {
class C_ScriptBindTrace : public CScriptableBase {
public:
    void* m_pContext;  // +0x60
    // int PlotXY(IFunctionHandler* pH);       // 0x180F32EF0 (noop)
    // int TableXY(IFunctionHandler* pH);      // 0x180F32EF0 (noop)
    // int Msg(IFunctionHandler* pH);          // 0x180F32EF0 (noop)
    // int Fatal(IFunctionHandler* pH);        // 0x180F32EF0 (noop)
    // int Error(IFunctionHandler* pH);        // 0x180F32EF0 (noop)
    // int Warning(IFunctionHandler* pH);      // 0x180F32EF0 (noop)
    // int Info(IFunctionHandler* pH);         // 0x180F32EF0 (noop)
    // int Detail(IFunctionHandler* pH);       // 0x180F32EF0 (noop)
    // int Debug(IFunctionHandler* pH);        // 0x180F32EF0 (noop)
    // int Brutus(IFunctionHandler* pH);       // 0x180F32EF0 (noop)
    // int max_trace_level(IFunctionHandler* pH); // 0x180F32EF0 (noop)
};
static_assert(sizeof(C_ScriptBindTrace) == 0x68);
} // namespace wh::framework
