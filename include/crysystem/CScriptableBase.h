#pragma once
#include <cstdint>
#include "../Offsets/vtables/IScriptTable.h"
#include "../Offsets/vtables/IScriptSystem.h"

// CryEngine script-callback handler (SDK: IScriptSystem.h). ScriptBind headers only
// take IFunctionHandler* parameters, so a global forward declaration suffices and lets
// every C_ScriptBind* header compile standalone (e.g. via the kcd.h umbrella / PCH).
struct IFunctionHandler;

// -----------------------------------------------
// CScriptableBase — CryEngine script binding base class
// -----------------------------------------------
// RTTI: .?AVCScriptableBase@@
// SDK: CryEngine/CryCommon/ScriptHelpers.h
// vtable: e.g., 0x1823f2668 (CScriptBind_Script), 5 slots (INTERFUSCATED)
// Size: 0x60
//
// Base class for all script bindings (CScriptBind_Script, CScriptBind_Action,
// CScriptBindGame, etc.). Registers a global Lua table with methods.
//
// Binary vtable order (interfuscated — NOT SDK order):
//   [0] ~dtor
//   [1] Init(pSS, pSystem, nParamIdOffset)
//   [2] Done()
//   [3] GetMemoryStatistics(pSizer)  — nop in most subclasses
//   [4] GetMemoryUsage(pSizer)       — reports object size to ICrySizer

class CScriptableBase {
public:
    virtual ~CScriptableBase();                                                                     // [0]
    virtual void Init(Offsets::IScriptSystem* pSS, void* pSystem, int nParamIdOffset = 0);          // [1]
    virtual void Done();                                                                            // [2]
    virtual void GetMemoryStatistics(void* pSizer) {}                                               // [3]  nop
    virtual void GetMemoryUsage(void* pSizer);                                                      // [4]

    char                    m_sGlobalName[64];      // +0x08  registered global name (e.g., "Script", "System")
    Offsets::IScriptTable*  m_pMethodsTable;        // +0x48  the Lua table holding registered methods
    Offsets::IScriptSystem* m_pSS;                  // +0x50  back-pointer to IScriptSystem
    int32_t                 m_nParamIdOffset;        // +0x58
    int32_t                 _pad5C;                 // +0x5C
};
static_assert(sizeof(CScriptableBase) == 0x60);
