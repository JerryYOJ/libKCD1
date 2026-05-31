#pragma once

// Guard macros for CryEngine SDK headers
#ifndef UNIQUE_IFACE
#define UNIQUE_IFACE
#endif
#ifndef DEVIRTUALIZE_HEADER_FIX
#define DEVIRTUALIZE_HEADER_FIX(HEADER) <cstdint>
#endif
#ifndef PRINTF_PARAMS
#define PRINTF_PARAMS(...)
#endif

#include "../../CryEngine/CryCommon/IConsole.h"  // SDK types: IOutputPrintSink, etc.

// CVar callback: called when a variable's value changes
// SDK defines: typedef void (*ConsoleVarFunc)(ICVar*);
// EVarFlags enum (VF_NULL, VF_CHEAT, etc.) is in the SDK header included above.

// -----------------------------------------------
// IConsole — Binary vtable order (interfuscated)
// -----------------------------------------------
// Cracked from CXConsole vtable at 0x1826968c8 (70 entries)
// Verified against: CXConsole::ExecuteString_180EC6920, GetCVar (sub_180328910 with debug string),
//                   CXConsole::Clear_180EC2E00, CXConsole::GetLineNo_180EC8324
//
// Replaces SDK IConsole for inheritance — SDK IConsole has wrong vtable order.
// SDK types (ICVar, IOutputPrintSink, etc.) are still used for params.

namespace Offsets {

// -----------------------------------------------
// ICVar — Binary vtable order (interfuscated)
// -----------------------------------------------
// Cracked from CXConsoleVariableInt vtable at 0x1822bd8d0 (28 entries)
// SDK: CryEngine/CryCommon/IConsole.h
//
// Member layout (CXConsoleVariableBase):
//   +0x08: const char* m_szName
//   +0x18: int m_nFlags
//   +0x40: void* m_pConsole (back-ptr to CXConsole)
//   +0x48: value storage (int/float/string depending on type)

struct ICVar {
    virtual void Dtor(char flags) = 0;                      // [0]  0x00
    virtual void Release() = 0;                              // [1]  0x08
    virtual int GetIVal() const = 0;                         // [2]  0x10   returns *(int*)(this+0x48)
    virtual int GetRealIVal() const = 0;                     // [3]  0x18
    virtual float GetFVal() const = 0;                       // [4]  0x20   wraps GetIVal → float
    virtual const char* GetString() const = 0;               // [5]  0x28   wraps GetIVal → sprintf "%d"
    virtual void ForceSet(const char* s) = 0;                // [6]  0x30   calls vtable[27]
    virtual void Set(int val) = 0;                           // [7]  0x38   sets *(this+0x48), fires callbacks
    virtual void _vf8() = 0;                                 // [8]  0x40
    virtual void _vf9() = 0;                                 // [9]  0x48   Set variant (called by [10])
    virtual void SetForceInternal() = 0;                     // [10] 0x50   clears flags, calls [9], restores
    virtual void _vf11() = 0;                                // [11] 0x58
    virtual void _vf12() = 0;                                // [12] 0x60
    virtual void _vf13() = 0;                                // [13] 0x68
    virtual int GetType() const = 0;                         // [14] 0x70   returns 1=INT, 2=FLOAT, 3=STRING
    virtual const char* GetName() const = 0;                 // [15] 0x78   returns *(char**)(this+0x08)
    virtual void _vf16() = 0;                                // [16] 0x80
    virtual void _vf17() = 0;                                // [17] 0x88
    virtual void _vf18() = 0;                                // [18] 0x90
    virtual void _vf19() = 0;                                // [19] 0x98
    virtual void _vf20() = 0;                                // [20] 0xA0
    virtual void _vf21() = 0;                                // [21] 0xA8
    virtual void _vf22() = 0;                                // [22] 0xB0
    virtual void _vf23() = 0;                                // [23] 0xB8
    virtual void _vf24() = 0;                                // [24] 0xC0
    virtual void _vf25() = 0;                                // [25] 0xC8
    virtual void _vf26() = 0;                                // [26] 0xD0
    virtual void _vf27() = 0;                                // [27] 0xD8   internal set (called by ForceSet)
};

struct IConsole {
    virtual void Dtor() = 0;                                                                           // [0]  0x00
    virtual void _vf1() = 0;                                                                           // [1]  0x08
    virtual ICVar* RegisterString(const char* name, const char* sValue, int nFlags, const char* help = "", ConsoleVarFunc pChangeFunc = nullptr) = 0; // [2]  0x10  CXConsoleVariableString
    virtual ICVar* RegisterInt(const char* name, int iValue, int nFlags, const char* help = "", ConsoleVarFunc pChangeFunc = nullptr) = 0;         // [3]  0x18  CXConsoleVariableInt
    virtual void _vf4() = 0;                                                                           // [4]  0x20
    virtual void _vf5() = 0;                                                                           // [5]  0x28
    virtual void _vf6() = 0;                                                                           // [6]  0x30
    virtual ICVar* RegisterCVarStr(const char* name, const char** src, const char* defaultValue, int nFlags = 0, const char* help = "", ConsoleVarFunc pChangeFunc = nullptr, bool allowModify = true) = 0; // [7]  0x38
    virtual ICVar* RegisterCVarInt(const char* name, int* src, int defaultValue, int nFlags = 0, const char* help = "", ConsoleVarFunc pChangeFunc = nullptr, bool allowModify = true) = 0;                // [8]  0x40
    virtual ICVar* RegisterCVarFloat(const char* name, float* src, float defaultValue, int nFlags = 0, const char* help = "", ConsoleVarFunc pChangeFunc = nullptr, bool allowModify = true) = 0; // [9]  0x48  sub_180ED364C, creates CXConsoleVariableFloatRef
    virtual void UnregisterVariable(const char* name, bool bDelete = false) = 0;                        // [10] 0x50
    virtual void _vf11() = 0;                                                                          // [11] 0x58
    virtual void AddOutputPrintSink(IOutputPrintSink* sink) = 0;                                        // [12] 0x60
    virtual void RemoveOutputPrintSink(IOutputPrintSink* sink) = 0;                                     // [13] 0x68
    virtual void ShowConsole(bool show, int requestScrollMax = -1) = 0;                                 // [14] 0x70
    virtual void DumpCVars(ICVarDumpSink* callback, unsigned int flagsFilter = 0) = 0;                  // [15] 0x78
    virtual void _vf16() = 0;                                                                          // [16] 0x80
    virtual void _vf17() = 0;                                                                          // [17] 0x88
    virtual void _vf18() = 0;                                                                          // [18] 0x90
    virtual void _vf19() = 0;                                                                          // [19] 0x98
    virtual void _vf20() = 0;                                                                          // [20] 0xA0
    virtual bool GetLineNo(int lineNo, char* outBuffer, int bufferSize) = 0;                            // [21] 0xA8
    virtual void _vf22() = 0;                                                                          // [22] 0xB0
    virtual ICVar* GetCVar(const char* name) = 0;                                                       // [23] 0xB8
    virtual void _vf24() = 0;                                                                          // [24] 0xC0
    virtual void _vf25() = 0;                                                                          // [25] 0xC8
    virtual void _vf26() = 0;                                                                          // [26] 0xD0
    virtual void _vf27() = 0;                                                                          // [27] 0xD8
    virtual void _vf28() = 0;                                                                          // [28] 0xE0
    virtual void Clear() = 0;                                                                           // [29] 0xE8
    virtual void _vf30() = 0;                                                                          // [30] 0xF0
    virtual void _vf31() = 0;                                                                          // [31] 0xF8
    virtual void AddCommandScript(const char* name, const char* scriptFunc, int nFlags = 0, const char* help = "") = 0; // [32] 0x100
    virtual void AddCommand(const char* name, void (*func)(IConsoleCmdArgs*), int nFlags = 0, const char* help = "") = 0; // [33] 0x108
    virtual void RemoveCommand(const char* name) = 0;                                                   // [34] 0x110
    virtual void ExecuteString(const char* command, bool bSilent = false, bool bDeferred = false) = 0;  // [35] 0x118
    virtual void Exit(const char* format, ...) = 0;                                                     // [36] 0x120
    virtual void _vf37() = 0;                                                                          // [37] 0x128
    virtual void _vf38() = 0;                                                                          // [38] 0x130
    virtual int  GetSortedVars(const char** outArray, int numItems, const char* prefix = nullptr) = 0;  // [39] 0x138
    virtual void _vf40() = 0;                                                                          // [40] 0x140
    virtual void _vf41() = 0;                                                                          // [41] 0x148
    virtual const char* ProcessCompletion(const char* inputBuffer) = 0;                                 // [42] 0x150
    virtual void RegisterAutoComplete(const char* name, IConsoleArgumentAutoComplete* pAC) = 0;         // [43] 0x158
    virtual void _vf44() = 0;                                                                          // [44] 0x160
    virtual void _vf45() = 0;                                                                          // [45] 0x168
    virtual void SaveInternalState(void* writer) = 0;                                                   // [46] 0x170
    virtual void _vf47() = 0;                                                                          // [47] 0x178
    virtual void _vf48() = 0;                                                                          // [48] 0x180
    virtual void SetInputLine(const char* line) = 0;                                                    // [49] 0x188
    virtual void DumpKeyBinds(IKeyBindDumpSink* callback) = 0;                                          // [50] 0x190
    virtual void _vf51() = 0;                                                                          // [51] 0x198
    virtual void _vf52() = 0;                                                                          // [52] 0x1A0
    virtual void _vf53() = 0;                                                                          // [53] 0x1A8
    virtual void _vf54() = 0;                                                                          // [54] 0x1B0
    virtual void _vf55() = 0;                                                                          // [55] 0x1B8
    virtual void _vf56() = 0;                                                                          // [56] 0x1C0
    virtual void _vf57() = 0;                                                                          // [57] 0x1C8
    virtual void _vf58() = 0;                                                                          // [58] 0x1D0
    virtual void AddConsoleVarSink(IConsoleVarSink* sink) = 0;                                          // [59] 0x1D8
    virtual void RemoveConsoleVarSink(IConsoleVarSink* sink) = 0;                                       // [60] 0x1E0
    virtual const char* GetHistoryElement(bool bUpOrDown) = 0;                                          // [61] 0x1E8
    virtual void AddCommandToHistory(const char* command) = 0;                                          // [62] 0x1F0
    virtual void LoadConfigVar(const char* variable, const char* value) = 0;                            // [63] 0x1F8
};

}  // namespace Offsets
