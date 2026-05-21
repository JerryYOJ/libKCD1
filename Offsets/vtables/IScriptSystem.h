#pragma once
#include <cstdint>
#include <cstdarg>
#include "IScriptTable.h"

// -----------------------------------------------
// IScriptSystem — Binary vtable order (interfuscated)
// -----------------------------------------------
// Singleton: gEnv+0x30 = qword_1829D16E8
// 14 slots cracked from callers in soul binding, Lua global setting, and script execution code.
//
// ScriptAnyValue type enum (confirmed from wrappers):
//   0 = Nil, 2 = Bool, 3 = ScriptHandle (int64), 4 = Number/float,
//   5 = String, 6 = IScriptTable*, 7 = HSCRIPTFUNCTION, 9 = Vec3
//
// ScriptAnyValue struct layout:
//   +0x00: int type
//   +0x08: union { bool, float, const char*, IScriptTable*, HSCRIPTFUNCTION, int64 }

typedef void* HSCRIPTFUNCTION;

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
        // Vec3 (type 9) uses extended stack allocation, not this union
    };                  // +0x08
};
static_assert(sizeof(ScriptAnyValue) == 0x10);

struct IScriptSystem {
    virtual void _vf0() = 0;                                                        // [0]  0x00
    virtual void _vf1() = 0;                                                        // [1]  0x08
    virtual void _vf2() = 0;                                                        // [2]  0x10
    virtual void _vf3() = 0;                                                        // [3]  0x18
    virtual void _vf4() = 0;                                                        // [4]  0x20
    virtual bool ExecuteFile(const char* filename, bool forceReload = false) = 0;    // [5]  0x28  "scripts/physics.lua" xref
    virtual void _vf6() = 0;                                                        // [6]  0x30
    virtual void _vf7() = 0;                                                        // [7]  0x38
    virtual bool GetGlobalValue(const char* key, ScriptAnyValue& out) = 0;           // [8]  0x40  type-7 biased retrieval
    virtual void _vf9() = 0;                                                        // [9]  0x48
    virtual void _vf10() = 0;                                                       // [10] 0x50
    virtual void _vf11() = 0;                                                       // [11] 0x58
    virtual void _vf12() = 0;                                                       // [12] 0x60
    virtual IScriptTable* CreateTable(bool bEmpty = false) = 0;                      // [13] 0x68  returns new table, caller AddRef's
    virtual void _vf14() = 0;                                                       // [14] 0x70
    virtual void _vf15() = 0;                                                       // [15] 0x78
    virtual void _vf16() = 0;                                                       // [16] 0x80
    virtual void _vf17() = 0;                                                       // [17] 0x88
    virtual bool BeginCall(IScriptTable* tbl) = 0;                                   // [18] 0x90  starts Lua function call
    virtual bool EndCall() = 0;                                                      // [19] 0x98  ends call, no return value
    virtual bool EndCallAny(ScriptAnyValue& out) = 0;                                // [20] 0xA0  ends call, retrieves return (type 2=bool)
    virtual void _vf21() = 0;                                                       // [21] 0xA8
    virtual void _vf22() = 0;                                                       // [22] 0xB0
    virtual void _vf23() = 0;                                                       // [23] 0xB8
    virtual HSCRIPTFUNCTION GetFuncHandle(IScriptTable* tbl, const char* funcName) = 0; // [24] 0xC0
    virtual void _vf25() = 0;                                                       // [25] 0xC8
    virtual void ReleaseFunc(HSCRIPTFUNCTION f) = 0;                                 // [26] 0xD0  cleanup for handles/tables
    virtual void _vf27() = 0;                                                       // [27] 0xD8
    virtual void _vf28() = 0;                                                       // [28] 0xE0
    virtual void PushFuncParam(const ScriptAnyValue& val) = 0;                       // [29] 0xE8  push param for BeginCall
    virtual void SetGlobalValue(const char* key, const ScriptAnyValue& val) = 0;     // [30] 0xF0  sub_180F161A4 / sub_180F16104
    virtual bool GetGlobalValueTable(const char* key, ScriptAnyValue& out) = 0;      // [31] 0xF8  variant for table retrieval
    virtual void SetGlobalToNull(const char* key) = 0;                               // [32] 0x100 clears "g_localActorId" etc.
    virtual void _vf33() = 0;                                                       // [33] 0x108
    virtual void _vf34() = 0;                                                       // [34] 0x110
    virtual void _vf35() = 0;                                                       // [35] 0x118
    virtual void _vf36() = 0;                                                       // [36] 0x120
    virtual void _vf37() = 0;                                                       // [37] 0x128
    virtual void _vf38() = 0;                                                       // [38] 0x130
    virtual void _vf39() = 0;                                                       // [39] 0x138
    virtual void _vf40() = 0;                                                       // [40] 0x140
    virtual void _vf41() = 0;                                                       // [41] 0x148
    virtual void _vf42() = 0;                                                       // [42] 0x150
    virtual void _vf43() = 0;                                                       // [43] 0x158
    virtual void _vf44() = 0;                                                       // [44] 0x160
    virtual void _vf45() = 0;                                                       // [45] 0x168
    virtual void _vf46() = 0;                                                       // [46] 0x170
    virtual void _vf47() = 0;                                                       // [47] 0x178
    virtual void _vf48() = 0;                                                       // [48] 0x180
    virtual void _vf49() = 0;                                                       // [49] 0x188
    virtual void _vf50() = 0;                                                       // [50] 0x190
    virtual void _vf51() = 0;                                                       // [51] 0x198
    virtual void _vf52() = 0;                                                       // [52] 0x1A0
    virtual void _vf53() = 0;                                                       // [53] 0x1A8
    virtual void ForceGarbageCollection() = 0;                                       // [54] 0x1B0
    virtual void _vf55() = 0;                                                       // [55] 0x1B8
    virtual void _vf56() = 0;                                                       // [56] 0x1C0
    virtual IScriptTable* CompileBuffer(const char* buf, int len, const char* debugName) = 0; // [57] 0x1C8
};

}  // namespace Offsets
