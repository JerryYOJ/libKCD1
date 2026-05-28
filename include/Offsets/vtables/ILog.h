#pragma once
#include <cstdarg>

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

#include "../../CryEngine/CryCommon/ILog.h"  // SDK types: ILogCallback, ELogType, etc.

struct ICrySizer;

// -----------------------------------------------
// ILog — Binary vtable order (interfuscated)
// -----------------------------------------------
// CLog vtable at 0x182680258. Singleton at gEnv+0xE0.
//
// ALL 35 slots decompiled and verified. 30 SDK methods + 5 WH additions.
//
// Call chain: variadic → [2] LogV → [0] LogVF(flags) → [34] LogV_WH_Impl
// [1] inserts flags=0 then calls [34], used by standalone CryLogAlways (sub_18040EF74).
//
// Severity→verbosity in [34]: 0=eMessage(v=3), 1=eWarning(v=2), 2=eError(v=1),
//   3=eAlways(v=0), 4=eWarningAlways(v=0), 5=eErrorAlways(v=0), 8=eComment(v=4), 9=WH(v=0).
//   1/4 prefix "$6[Warning]", 2/5 prefix "$4[Error]".

namespace Offsets {

struct ILog {
    virtual void LogVF(int type, int flags, const char* fmt, va_list args) = 0;                                       // [0]  0x00  SDK LogV(flags) — prepends source="log.cpp":0x18C, calls [34]
    virtual void LogV_WH(const char* source, unsigned int line, int severity, const char* fmt, va_list args) = 0;    // [1]  0x08  WH extension — inserts flags=0, calls [34]
    virtual void LogV(int type, const char* fmt, va_list args) = 0;                                                  // [2]  0x10  SDK LogV — calls [0] with flags=0
    virtual void Dtor(char flags) = 0;                                                                                // [3]  0x18  SDK ~IMiniLog destructor
    virtual void Log(const char* fmt, ...) = 0;                                                                       // [4]  0x20  SDK — severity=0 (eMessage), filtered by verbosity
    virtual void LogWarning(const char* fmt, ...) = 0;                                                                // [5]  0x28  SDK — severity=1 (eWarning), "$6[Warning]" prefix
    virtual void LogError(const char* fmt, ...) = 0;                                                                  // [6]  0x30  SDK — severity=2 (eError), "$4[Error]" prefix
    virtual void Release() = 0;                                                                                       // [7]  0x38  SDK — calls Dtor(1)
    virtual bool SetFileName(const char* path) = 0;                                                                   // [8]  0x40  SDK — file ops, fclose+reopen
    virtual const char* GetFileName() = 0;                                                                            // [9]  0x48  SDK — return this+0x14
    virtual const char* GetBackupFileName() = 0;                                                                      // [10] 0x50  SDK — return this+0x120
    virtual void LogAlways(const char* fmt, ...) = 0;                                                                 // [11] 0x58  SDK — severity=3 (eAlways), always shown
    virtual void _vf12(const char* fmt, ...) = 0;                                                                     // [12] 0x60  WH — variadic, severity=9 (always shown, no prefix)
    virtual void LogPlus(const char* fmt, ...) = 0;                                                                   // [13] 0x68  SDK — calls [15] LogToFilePlus + [17] LogToConsolePlus
    virtual void LogToFile(const char* fmt, ...) = 0;                                                                 // [14] 0x70  SDK — file only, sub_18040EFC0(buf,0)
    virtual void LogToFilePlus(const char* fmt, ...) = 0;                                                             // [15] 0x78  SDK — file append, sub_18040EFC0(buf,1)
    virtual void LogToConsole(const char* fmt, ...) = 0;                                                              // [16] 0x80  SDK — console only, sub_180E3C4A0(buf,0)
    virtual void LogToConsolePlus(const char* fmt, ...) = 0;                                                          // [17] 0x88  SDK — console append, sub_180E3C4A0(buf,1)
    virtual void UpdateLoadingScreen(const char* fmt, ...) = 0;                                                       // [18] 0x90  SDK — LogV(eMessage) + renderer pump (0.1s throttle)
    virtual void RegisterConsoleVariables() = 0;                                                                      // [19] 0x98  SDK — registers log_Verbosity, log_Filter, etc.
    virtual void UnregisterConsoleVariables() = 0;                                                                    // [20] 0xA0  SDK — unregisters wh_sys_LogViewer* CVars, zeroes ptrs
    virtual void SetVerbosity(int verbosity) = 0;                                                                     // [21] 0xA8  SDK — passthrough to log_Verbosity CVar SetIVal
    virtual int  GetVerbosityLevel() = 0;                                                                             // [22] 0xB0  SDK — reads log_Verbosity CVar GetIVal
    virtual void AddCallback(ILogCallback* pCallback) = 0;                                                            // [23] 0xB8  SDK — inserts into linked list at +0x2103F0
    virtual void RemoveCallback(ILogCallback* pCallback) = 0;                                                         // [24] 0xC0  SDK — removes from linked list
    virtual void Update() = 0;                                                                                        // [25] 0xC8  SDK — flushes queued msgs, tick logging, periodic file flush
    virtual const char* GetModuleFilter() = 0;                                                                        // [26] 0xD0  SDK — reads log_Module CVar string
    virtual void GetMemoryUsage(ICrySizer* pSizer) const = 0;                                                         // [27] 0xD8  SDK — collects CVar memory via ICrySizer
    virtual void PushAssetScopeName(const char* sAssetType, const char* sName) = 0;                                   // [28] 0xE0  SDK — nop (default empty impl)
    virtual void PopAssetScopeName() = 0;                                                                             // [29] 0xE8  SDK — nop (default empty impl)
    virtual const char* GetAssetScopeString() = 0;                                                                    // [30] 0xF0  SDK — returns "" (default impl)
    virtual void _vf31() = 0;                                                                                         // [31] 0xF8  WH — Update() + fflush (flush without close)
    virtual void FlushAndClose() = 0;                                                                                 // [32] 0x100 SDK — Update() + fclose, zeroes file handle
    virtual void _vf33() = 0;                                                                                         // [33] 0x108 WH — on-screen log viewer (keyboard scroll, renders text)
    virtual void LogV_WH_Impl(const char* source, unsigned int line, int severity, int flags, const char* fmt, va_list args) = 0; // [34] 0x110 WH — main dispatch implementation
};

}  // namespace Offsets
