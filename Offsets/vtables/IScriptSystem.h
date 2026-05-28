#pragma once
#include <cstdint>
#include <cstdarg>
#include "IScriptTable.h"

// -----------------------------------------------
// IScriptSystem — Binary vtable order (interfuscated)
// -----------------------------------------------
// Singleton: gEnv+0x30 = qword_1829D16E8
// CScriptSystem vtable: 0x1827d2488 (67 slots, verified from binary)
//
// ScriptAnyValue type enum (confirmed from wrappers):
//   0 = Nil, 2 = Bool, 3 = ScriptHandle (int64), 4 = Number/float,
//   5 = String, 6 = IScriptTable*, 7 = HSCRIPTFUNCTION, 9 = Vec3
//
// ScriptAnyValue struct layout:
//   +0x00: int type
//   +0x08: union { bool, float, const char*, IScriptTable*, HSCRIPTFUNCTION, int64 }

typedef void* HSCRIPTFUNCTION;
typedef struct lua_State lua_State;

struct ISerialize;

class CScriptableBase;

namespace Offsets {

struct ScriptAnyValue {
    int     type;       // +0x00  (0=Nil, 2=Bool, 3=Handle, 4=Number, 5=String, 6=Table, 7=Function, 9=Vec3)
    int     _pad;       // +0x04
    union {
        bool            bVal;       // type 2
        int64_t         nVal;       // type 3 (ScriptHandle / WUID / EntityId)
        float           fVal;       // type 4
        const char*     sVal;       // type 5
        IScriptTable*   pTable;     // type 6
        void*           pFunction;  // type 7 (HSCRIPTFUNCTION)
    };                  // +0x08
};
static_assert(sizeof(ScriptAnyValue) == 0x10);

// -----------------------------------------------
// IScriptSystem — 67 vfunc slots (INTERFUSCATED binary order)
// -----------------------------------------------
// ALL slots verified by reading vtable at 0x1827d2488 and decompiling each entry.
// CryEngine interfuscator shuffles slot order — indices do NOT match SDK header.
// 6 slots are nop stubs (unimplemented pure virtuals).
struct IScriptSystem {
    virtual ~IScriptSystem() = 0;                                                                   // [0]  +0x000

    // --- Lifecycle ---
    virtual void Update() = 0;                                                                      // [1]  +0x008
    virtual void SetGCFrequency(float fRate) = 0;                                                   // [2]  +0x010

    // --- Environment ---
    virtual void SetEnvironment(IScriptTable* pCaller, IScriptTable* pEnv) = 0;                     // [3]  +0x018
    virtual IScriptTable* GetGlobalValue(const char* pKey) = 0;                                     // [4]  +0x020

    // --- Script execution ---
    virtual bool ExecuteFile(const char* sFileName, bool bRaiseError, void* pSink) = 0;             // [5]  +0x028
    virtual bool ExecuteBuffer(const char* sBuffer, size_t nSize,                                   // [6]  +0x030
                               const char* sDesc, IScriptTable* pEnv) = 0;

    // --- Script management ---
    virtual void UnloadScript(const char* sFileName) = 0;                                           // [7]  +0x038
    virtual void UnloadScripts() = 0;                                                               // [8]  +0x040
    virtual bool ReloadScript(const char* sFileName, bool bRaiseError) = 0;                         // [9]  +0x048
    virtual bool ReloadScripts() = 0;                                                               // [10] +0x050
    virtual void DumpLoadedScripts() = 0;                                                           // [11] +0x058

    // --- Tables ---
    virtual IScriptTable* CreateTable(int nArraySize, int nHashSize) = 0;                           // [12] +0x060
    virtual IScriptTable* CreateTable(bool bEmpty) = 0;                                             // [13] +0x068
    virtual IScriptTable* AllocScriptTable() = 0;                                                   // [14] +0x070

    // --- Global values ---
    virtual bool SetGlobalValue(const char* pKey, ScriptAnyValue* pVal) = 0;                        // [15] +0x078

    // --- Function calls ---
    virtual bool BeginCall(IScriptTable* pTable, const char* sFuncName) = 0;                        // [16] +0x080
    virtual bool BeginCall(const char* sFuncName) = 0;                                              // [17] +0x088
    virtual bool EndCall(ScriptAnyValue* pResult) = 0;                                              // [18] +0x090
    virtual bool EndCall() = 0;                                                                     // [19] +0x098
    virtual bool EndCallN(ScriptAnyValue* pResult) = 0;                                             // [20] +0x0A0
    virtual bool EndCallN(int nResults, ScriptAnyValue* pResults) = 0;                              // [21] +0x0A8

    // --- Function references ---
    virtual int GetMethodReference(IScriptTable* pTable, const char* sFuncName) = 0;                // [22] +0x0B0
    virtual int GetGlobalFuncRef(const char* sFuncName) = 0;                                        // [23] +0x0B8
    virtual int GetFuncRef() = 0;                                                                   // [24] +0x0C0
    virtual bool IsEqualFuncRef(int nRef1, int nRef2) = 0;                                          // [25] +0x0C8
    virtual void ReleaseFunc(int nFuncRef) = 0;                                                     // [26] +0x0D0
    virtual ScriptAnyValue* CloneAny(ScriptAnyValue* pDst, ScriptAnyValue* pSrc) = 0;               // [27] +0x0D8

    // --- Parameters ---
    virtual void PushFuncParamRef(ScriptAnyValue* pRef) = 0;                                        // [28] +0x0E0
    virtual void PushFuncParam(ScriptAnyValue* pVal) = 0;                                           // [29] +0x0E8
    virtual void PushFuncParamTable(const char* pKey, ScriptAnyValue* pVal) = 0;                     // [30] +0x0F0

    // --- Global value (dotted path) ---
    virtual bool SetGlobalValueDotted(const char* sDottedPath, ScriptAnyValue* pVal) = 0;           // [31] +0x0F8
    virtual void SetGlobalToNull(const char* pKey) = 0;                                             // [32] +0x100

    // --- User data ---
    virtual IScriptTable* AllocUserData(const void* pData, size_t nSize) = 0;                       // [33] +0x108

    // --- GC ---
    virtual void ForceGarbageCollection() = 0;                                                      // [34] +0x110
    virtual int GetGCCount() = 0;                                                                   // [35] +0x118

    virtual void unk_36() {}                                                                        // [36] +0x120  nop
    virtual void Release(void* pPtr) = 0;                                                           // [37] +0x128

    // --- Debugging ---
    virtual bool DebugCont(const char* sFile, uint32_t nLine, const char* sReason) = 0;             // [38] +0x130
    virtual void SetBreakpoints(int nFile, int nLine) = 0;                                          // [39] +0x138

    // --- Diagnostics ---
    virtual IScriptTable* DumpCallStack(int nStartLevel, bool bDumpLocals) = 0;                     // [40] +0x140
    virtual IScriptTable* GetCallStack() = 0;                                                       // [41] +0x148
    virtual void DumpCallStackLog() = 0;                                                            // [42] +0x150

    virtual void unk_43() {}                                                                        // [43] +0x158  nop
    virtual void unk_44() {}                                                                        // [44] +0x160  nop
    virtual void unk_45() {}                                                                        // [45] +0x168  nop
    virtual void unk_46() {}                                                                        // [46] +0x170  nop

    virtual int GetStackSize() = 0;                                                                 // [47] +0x178

    // --- Serialization ---
    virtual void Serialize(ISerialize* pSerializer) = 0;                                            // [48] +0x180

    virtual void unk_49() {}                                                                        // [49] +0x188  nop

    // --- Error handling ---
    virtual void RaiseError(const char* sFmt, ...) = 0;                                             // [50] +0x190

    // --- Console / AI ---
    virtual void RegisterConsoleVars() = 0;                                                         // [51] +0x198
    virtual void SetGlobalAITable() = 0;                                                            // [52] +0x1A0

    // --- Script bindings ---
    virtual void RegisterScriptBind(::CScriptableBase* pBind) = 0;                                   // [53] +0x1A8
    virtual void FlushBindings() = 0;                                                               // [54] +0x1B0

    // --- Stack info ---
    virtual int GetStackDepth() = 0;                                                                // [55] +0x1B8
    virtual int GetRecursionCount() = 0;                                                            // [56] +0x1C0

    // --- Compilation ---
    virtual int CompileBuffer(const char* sCode, size_t nLen, const char* sDesc) = 0;               // [57] +0x1C8
    virtual int RegisterScriptCommand(void* pSink, const char* sName) = 0;                          // [58] +0x1D0
    virtual bool ExecutePreCached(int nRef) = 0;                                                    // [59] +0x1D8

    // --- Reset ---
    virtual void Reset() = 0;                                                                       // [60] +0x1E0

    // --- Allocator ---
    virtual void* LuaAlloc(size_t nSize) = 0;                                                       // [61] +0x1E8
    virtual void LuaFree(void* pPtr) = 0;                                                           // [62] +0x1F0

    // --- Misc ---
    virtual IScriptTable* GetScriptBind(const char* sName) = 0;                                     // [63] +0x1F8
    virtual void* ValueToString(ScriptAnyValue* pVal, int nDepth) = 0;                               // [64] +0x200
    virtual void DumpStack(const char* sOutputFile) = 0;                                             // [65] +0x208
    virtual void* GetFuncName(ScriptAnyValue* pFuncRef) = 0;                                         // [66] +0x210
};

}  // namespace Offsets
