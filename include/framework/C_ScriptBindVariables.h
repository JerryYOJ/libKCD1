#pragma once
#include "../crysystem/CScriptableBase.h"

// C_ScriptBindVariables — Lua "Variables" table
// RTTI: .?AVC_ScriptBindVariables@framework@wh@@  vtable: 0x1822c1bf0
// Constructor: sub_180F32D00  Registration: sub_180F34BB8  Size: 0x70

namespace wh::framework {
class C_ScriptBindVariables : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindVariables;
    void* m_pSystem;   // +0x60
    void* m_pContext;   // +0x68
    // int SetGlobal(IFunctionHandler* pH, const char* name, float value);        // 0x1805E3AC4
    // int GetGlobal(IFunctionHandler* pH);                                       // 0x180F33A4C
    // int IncrementGlobal(IFunctionHandler* pH);                                 // 0x180F33C00
    // int DecrementGlobal(IFunctionHandler* pH);                                 // 0x180F33438
    // int CreateContext(IFunctionHandler* pH);                                    // 0x180F3340C
    // int DestroyContext(IFunctionHandler* pH);                                   // 0x180F33668
    // int DiscardContextVariables(IFunctionHandler* pH);                          // 0x180F337A4
    // int SetLocal(IFunctionHandler* pH, const char* name, int contextId, float value); // 0x1802ACA4C
    // int GetLocal(IFunctionHandler* pH);                                        // 0x180F33B34
    // int IncrementLocal(IFunctionHandler* pH);                                  // 0x180F33C4C
    // int DecrementLocal(IFunctionHandler* pH);                                  // 0x180F33484
};
static_assert(sizeof(C_ScriptBindVariables) == 0x70);
} // namespace wh::framework
