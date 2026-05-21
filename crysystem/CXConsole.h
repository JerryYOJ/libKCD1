#pragma once

#include <cstdint>

// Guard macros for CryEngine SDK headers (interfuscator/printf attributes)
#ifndef UNIQUE_IFACE
#define UNIQUE_IFACE
#endif
#ifndef DEVIRTUALIZE_HEADER_FIX
#define DEVIRTUALIZE_HEADER_FIX(HEADER) <cstdint>
#endif
#ifndef PRINTF_PARAMS
#define PRINTF_PARAMS(...)
#endif

#include "../Offsets/vtables/IConsole.h"        // binary vtable order (includes SDK IConsole.h for types)

// -----------------------------------------------
// CXConsole — CryEngine console implementation
// -----------------------------------------------
// RTTI: .?AVCXConsole@@
// Source: g:\workspace\kcdx_0109\code\cryengine\crysystem\xconsole.cpp
// Constructor/Init: sub_180EC9E58
//
// Three vtables (multiple inheritance):
//   Primary (IConsole): 0x1826968c8   (70 entries, interfuscated order)
//   Secondary _0:       0x182696880
//   Secondary _1:       0x1826968a8
//
// Singleton access:
//   IConsole* g_pConsole = *(IConsole**)0x1829D1768;
//
// Related singletons:
//   ILog*     g_pLog    = *(ILog**)0x1829D1798;
//   ISystem*  g_pSystem = *(ISystem**)0x1829D1780;
//
// NOTE: IConsole uses CryEngine Interfuscator — vtable order in the binary
// does NOT match the SDK IConsole.h declaration order. The offsets below
// are the actual binary vtable byte offsets.
//
// -----------------------------------------------
// Console output architecture
// -----------------------------------------------
// All console text output routes through CLog (ILog), NOT IConsole::PrintLine.
//
// Call chain:
//   System.LogAlways("text")                                    -- Lua
//   -> CLog::LogV (g_pLog vtable[2], offset 0x10)
//       -> CLog::LogToConsoleAndFile (sub_18040EFC0)
//            -> writes to kcd.log file
//            -> iterates ILogCallback list -> populates console line buffer
//       -> IRemoteConsole::AddLogMessage / AddLogWarning / AddLogError
//
// ILog severity levels (passed to LogV):
//   0 = eAlways        -> console + file, remote AddLogMessage
//   1 = eWarningAlways -> "$6[Warning]" prefix, remote AddLogWarning
//   2 = eErrorAlways   -> "$4[Error]" prefix, remote AddLogError
//   3 = eMessage       -> console + file, remote AddLogMessage
//   4 = eWarning       -> "$6[Warning]" prefix, remote AddLogWarning
//   5 = eError         -> "$4[Error]" prefix, remote AddLogError
//   6 = eConsole       -> console only, remote AddLogMessage
//   7 = eConsoleInfo   -> console only, remote AddLogMessage
//   9 = eFileOnly      -> file only
//
// -----------------------------------------------
// How to output to console (practical)
// -----------------------------------------------
// 1. From Lua (remote console):
//      #System.LogAlways('hello')
//
// 2. From native (ILog — preferred):
//      auto pLog = *(ILog**)0x1829D1798;
//      pLog->LogAlways("hello %s", name);    // SDK vtable, interfuscated
//
// 3. From native (IConsole::ExecuteString):
//      auto pConsole = *(IConsole**)0x1829D1768;
//      // binary vtable[35] offset 0x118
//      pConsole->ExecuteString("#System.LogAlways('hello')");
//
// -----------------------------------------------
// IConsole vtable layout (INTERFUSCATED — binary order)
// -----------------------------------------------
// Only verified entries listed. Byte offset = index * 8.
//
// [0]  0x00  ~IConsole()
// [3]  0x18  RegisterString(name, value, flags, help, onChange)
// [7]  0x38  Register(name, const char** src, default, flags, help, onChange, allowModify)
// [8]  0x40  Register(name, int* src, default, flags, help, onChange, allowModify)
// [10] 0x50  UnregisterVariable(name, bDelete)
// [12] 0x60  AddOutputPrintSink(IOutputPrintSink*)
// [13] 0x68  RemoveOutputPrintSink(IOutputPrintSink*)
// [14] 0x70  ShowConsole(show, requestScrollMax)
// [15] 0x78  DumpCVars(callback, flagsFilter)
// [21] 0xA8  GetLineNo(lineNo, outBuffer, bufferSize) -> bool
// [23] 0xB8  GetCVar(name) -> ICVar*
// [29] 0xE8  Clear()
// [32] 0x100 AddCommand(name, scriptFunc, flags, help)      [script variant]
// [33] 0x108 AddCommand(name, func, flags, help)            [native variant]
// [34] 0x110 RemoveCommand(name)
// [35] 0x118 ExecuteString(command, bSilent, bDeferred)
// [36] 0x120 Exit(format, ...)
// [39] 0x138 GetSortedVars(outArray, numItems, prefix) -> count
// [42] 0x150 ProcessCompletion(inputBuffer) -> const char*
// [43] 0x158 RegisterAutoComplete(name, IConsoleArgumentAutoComplete*)
// [46] 0x170 SaveInternalState(writer)
// [49] 0x188 SetInputLine(line)
// [50] 0x190 DumpKeyBinds(callback)
// [59] 0x1D8 AddConsoleVarSink(IConsoleVarSink*)
// [60] 0x1E0 RemoveConsoleVarSink(IConsoleVarSink*)
// [61] 0x1E8 GetHistoryElement(bUpOrDown) -> const char*
// [62] 0x1F0 AddCommandToHistory(command)
// [63] 0x1F8 LoadConfigVar(variable, value)

struct ISystem;
struct IScriptSystem;
struct IRenderer;
struct IInput;
struct ITimer;
struct IFFont;

struct CXConsole : public Offsets::IConsole
{
    // +0x00: IConsole vtable (primary, interfuscated)
    // +0x08: secondary vtable _0 (unknown base)
    // +0x10: secondary vtable _1 (unknown base)
    char            _bases0810[0x10];           // +0x08  secondary vtables

    // Console line ring buffer (cleared by sub_180747EB8)
    uint64_t        m_lineBuffer[5];            // +0x18  (~0x28 bytes, accessed by GetLineNo)

    // Command history (max 50 entries, iterated by GetHistoryElement)
    uint64_t        m_historyBuffer[5];         // +0x40

    uint32_t        m_loadScreenTextureId;      // +0x68
    uint32_t        m_backgroundTextureId;      // +0x6C  (init -1, White.dds)
    uint32_t        m_whiteTextureId;           // +0x70  (init -1, White.dds)
    char            _pad74[0xC];                // +0x74

    // Current input line (CryStringT)
    void*           m_inputLine;                // +0x80
    char            _pad88[8];                  // +0x88

    // Auto-complete state
    void*           m_autoCompletePrefix;        // +0x90  (CryStringT)
    uint32_t        m_autoCompleteIndex;         // +0x98
    char            _pad9C[4];                   // +0x9C

    // Registered commands (std::map, MSVC release = 0x10: head_node + size)
    uint64_t        m_commands[2];               // +0xA0

    // Key bindings (std::map)
    uint64_t        m_keyBindings[2];            // +0xB0

    // CVars (std::map<CryString, ICVar*>)
    uint64_t        m_cvarTree[2];               // +0xC0

    // Cheat CVar tracking
    uint64_t        m_cheatCVarData[6];          // +0xD0

    // Output print sinks (std::vector<IOutputPrintSink*>)
    IOutputPrintSink** m_outputSinks_begin;      // +0x100
    IOutputPrintSink** m_outputSinks_end;        // +0x108
    IOutputPrintSink** m_outputSinks_cap;        // +0x110

    // Deferred command execution queue (std::list)
    uint64_t        m_deferredCmds[2];           // +0x118
    uint8_t         m_bDeferredExecution;         // +0x128
    char            _pad129[0x17];               // +0x129

    // Auto-complete argument registry (std::map)
    uint64_t        m_autoCompleteRegistry[2];   // +0x140

    // Console variable change sinks (std::list head + size = 0x10)
    uint64_t        m_cvarSinkList[2];           // +0x150

    // Config var registry (std::map)
    uint64_t        m_configVarRegistry[2];      // +0x160

    // Unknown gap
    char            _pad170[0x10];               // +0x170

    // History navigation state
    int32_t         m_historyIndex;              // +0x180  (-1 = not navigating)
    char            _pad184[4];                  // +0x184
    int32_t         m_inputLineLength;           // +0x188
    char            _pad18C[4];                  // +0x18C

    // Background image
    ITexture*       m_pBackgroundImage;           // +0x190
    float           m_scrollTimer;                // +0x198
    char            _pad19C[4];                   // +0x19C

    // Deferred command timing
    uint64_t        m_deferredTimingData[4];     // +0x1A0
    char            _pad1C0[0x1C];               // +0x1C0

    uint8_t         m_bRestrictedMode;           // +0x1DC  (0=normal, 1=restricted)
    char            _pad1DD[3];                  // +0x1DD

    // Cheat var hash range
    uint64_t        m_hashRangeStart;            // +0x1E0
    uint64_t        m_hashRangeEnd;              // +0x1E8
    uint8_t         m_bHashDirty;                // +0x1F0
    char            _pad1F1[7];                  // +0x1F1
    uint64_t        m_cheatVarHash;              // +0x1F8

    // Back-pointers to engine systems (set in Init)
    ISystem*        m_pSystem;                   // +0x200
    IScriptSystem*  m_pScriptSystem;             // +0x208
    IRenderer*      m_pRenderer;                 // +0x210
    IInput*         m_pInput;                    // +0x218
    ITimer*         m_pTimer;                    // +0x220
    IFFont*         m_pFont;                     // +0x228
    ICVar*          m_pSysDeactivateConsole;     // +0x230  (sys_DeactivateConsole cvar)
};
static_assert(sizeof(CXConsole) == 0x238);

// -----------------------------------------------
// Key global addresses
// -----------------------------------------------
// IConsole* g_pConsole  @ 0x1829D1768  (CXConsole singleton)
// ILog*     g_pLog      @ 0x1829D1798  (CLog singleton)
// ISystem*  g_pSystem   @ 0x1829D1780  (CSystem singleton)
//
// -----------------------------------------------
// Key function addresses
// -----------------------------------------------
// CXConsole::Init_180EC9E58             — post-construction setup
// CXConsole::ExecuteCommand_180EC626C   — internal command dispatch (called by ExecuteString)
// CXConsole::ExecuteString_180EC6920    — IConsole::ExecuteString implementation
// CXConsole::ExecuteInternal_180EC6A7C  — direct execute (no deferred queue)
// CXConsole::LogCVarChange_180ECD60C    — logs CVar modification
// CLog::LogV_18040F874                  — central log dispatch
// CLog::LogToConsoleAndFile_18040EFC0   — file + callback output
// CXConsole vtable (IConsole):            0x1826968c8
