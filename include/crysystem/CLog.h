#pragma once

#include <cstdint>
#include <cstdio>

#ifndef UNIQUE_IFACE
#define UNIQUE_IFACE
#endif
#ifndef DEVIRTUALIZE_HEADER_FIX
#define DEVIRTUALIZE_HEADER_FIX(HEADER) <cstdint>
#endif
#ifndef PRINTF_PARAMS
#define PRINTF_PARAMS(...)
#endif

#include "../Offsets/vtables/ILog.h"         // binary vtable order (includes SDK ILog.h for types)

// -----------------------------------------------
// CLog — CryEngine log implementation
// -----------------------------------------------
// RTTI: .?AVCLog@@
// Source: g:\workspace\kcdx_0109\code\cryengine\crysystem\log.cpp
// Implements: ILog : IMiniLog
// Constructor: sub_180E329C4
// Destructor: sub_180E33BC0  (frees 0x2104C8 bytes)
//
// vtable: 0x182680258
// Size: 0x2104C8
//
// Singleton access:
//   ILog* g_pLog = *(ILog**)0x1829D1798;
//
// -----------------------------------------------
// CLog vtable (interfuscated — binary order)
// -----------------------------------------------
// [0]  0x00  LogV_Inner  — dispatches to vtable[34] (offset 0x110)
// [2]  0x10  LogV_Wrapper — calls vtable[0]
// [5]  0x28  LogAlways (formats + calls LogV)
// [34] 0x110 LogV_18040F874 — central dispatch
//
// -----------------------------------------------
// Logging pipeline (LogV_18040F874)
// -----------------------------------------------
// 1. EnterCriticalSection(this+0x280)
// 2. Verbosity gate: m_pVerbosityGate (+0x2103C8) and m_pFileVerbosity (+0x2103B0)
// 3. Verbosity filter: sub_18040FB78 checks m_pFileVerbosity (+0x2103B0) and
//    m_pConsoleVerbosity (+0x2103C0) against severity
// 4. Format message (vsnprintf into 4KB stack buffer)
// 5. Prepend "$6[Warning] " or "$4[Error] " for warning/error severities
// 6. Duplicate suppression via ring buffer (16 entries at +0x2A8)
// 7. Console+file output: LogToConsoleAndFile (sub_18040EFC0)
//      -> fputs to m_pLogFile (+0x220)
//      -> iterates ILogCallback list (+0x2103F0)
// 8. Remote console: ISystem->GetIRemoteConsole->AddLogMessage/Warning/Error
// 9. LeaveCriticalSection
//
// -----------------------------------------------
// Severity levels
// -----------------------------------------------
//   0 = eAlways        console + file
//   1 = eWarningAlways "$6[Warning]" prefix, remote AddLogWarning
//   2 = eErrorAlways   "$4[Error]" prefix, remote AddLogError
//   3 = eMessage       console + file (verbosity gated)
//   4 = eWarning       "$6[Warning]" prefix
//   5 = eError         "$4[Error]" prefix
//   6 = eConsole       console only
//   7 = eConsoleInfo   console only
//   9 = eFileOnly      file only

struct ISystem;
struct ICVar;

// Ring buffer entry for duplicate message suppression
struct S_LogRingEntry {
    char        text[0x1000];       // +0x00  formatted message copy
    void*       pOrigFormat;        // +0x1000  original format string pointer
    uint32_t    severity;           // +0x1008  log severity level
    float       timestamp;          // +0x100C  time of message
};
static_assert(sizeof(S_LogRingEntry) == 0x1010);

class CLog : public Offsets::ILog
{
public:
    // === VERIFIED from constructor sub_180E329C4 ===

    ISystem*        m_pSystem;              // +0x08
    uint32_t        m_initFloat;            // +0x10  (0xBF800000 = -1.0f as bits)
    char            m_logFileName[0x100];   // +0x14  (memset 0)
    char            _pad114[4];             // +0x114
    CryStringT<char> m_backupLogPath;       // +0x118  (init from "permanent.log")
    char            m_logFilePath[0x100];   // +0x120  (memset 0)

    FILE*           m_pLogFile;             // +0x220  (kcd.log file handle)

    // String object at +0x228 (inline buffer pattern: ptr=self+0x240, cap=0x1F)
    uint64_t        m_strData1;             // +0x228  (init 0)
    uint64_t        m_strCapacity;          // +0x230  (init 0x1F)
    uint64_t        m_strDataPtr;           // +0x238  (init self+0x240)
    uint8_t         m_strInlineBuf;         // +0x240  (init 0)
    char            _pad241[0x2F];          // +0x241

    // === VERIFIED from LogV / LogToConsoleAndFile ===

    ICVar*          m_pIncludeTimeCVar;     // +0x270  (log_IncludeTime)
    char            _pad278[8];             // +0x278

    // Thread lock (CRITICAL_SECTION, 0x28 bytes on x64)
    char            m_lock[0x28];           // +0x280  (InitializeCriticalSection)

    // Duplicate message suppression ring buffer (16 entries)
    S_LogRingEntry  m_ringBuffer[16];       // +0x2A8  (memset 0, 16 × 0x1010 = 0x10100)
    uint32_t        m_ringBufIndex;         // +0x103A8  (init 0, wraps at 16)
    uint8_t         m_bLogToFileEnabled;    // +0x103AC  (init 1)

    // === UNVERIFIED GAP ===
    // ~1MB gap. Likely contains: loaded script file state, additional
    // formatting buffers, module filter strings, asset scope state.
    // NOT filler padding — this region exists in the binary but I haven't
    // identified what's in it yet.
    char            _gap103AD[0x200003];    // +0x103AD  (0x2103B0 - 0x103AD)

    // === VERIFIED from constructor + LogV + sub_18040FB78 ===

    ICVar*          m_pFileVerbosity;       // +0x2103B0  (log_WriteToFileVerbosity)
    ICVar*          m_pUnkCVar2103B8;       // +0x2103B8  (unknown CVar, init 0)
    ICVar*          m_pConsoleVerbosity;    // +0x2103C0  (log_Verbosity)
    ICVar*          m_pVerbosityGate;       // +0x2103C8  (first gate check in LogV)
    ICVar*          m_pDupSuppression;      // +0x2103D0  (init 0)
    ICVar*          m_pUnkCVar2103D8;       // +0x2103D8  (init 0)
    ICVar*          m_pUnkCVar2103E0;       // +0x2103E0  (init 0)
    ICVar*          m_pConsoleFilter;       // +0x2103E8  (console filter CVar)

    // ILogCallback linked list
    uint64_t        m_callbackListHead;     // +0x2103F0  (init via sub_180731290)
    uint64_t        m_callbackListCount;    // +0x2103F8  (init 0)

    // Thread safety
    uint32_t        m_mainThreadId;         // +0x210400  (init GetCurrentThreadId)
    char            _pad210404[4];          // +0x210404

    // Cross-thread log message queue
    uint64_t        m_threadQueueHead;      // +0x210408  (init 0)
    uint64_t        m_threadQueueTail;      // +0x210410  (init 0)
    uint64_t        m_threadQueueData;      // +0x210418  (init 0)
    char            m_threadLock[0x28];     // +0x210420  (second CRITICAL_SECTION)

    // Sub-object initialized by sub_180E32F10
    char            m_remoteLogData[0x80];  // +0x210448  (tail sub-object, size estimated)
};
static_assert(sizeof(CLog) == 0x2104C8);

// -----------------------------------------------
// Key function addresses
// -----------------------------------------------
// CLog constructor:                sub_180E329C4
// CLog destructor:                 sub_180E33BC0
// CLog vtable:                     0x182680258
// CLog::LogV (central dispatch):   sub_18040F874
// CLog::LogV wrapper (vtable[2]):  sub_18040F820
// CLog::LogV inner (vtable[0]):    sub_18040F83C
// CLog::LogToConsoleAndFile:       sub_18040EFC0
// CLog::LogAlways (vtable[5]):     sub_180E3CA60
// CLog verbosity filter:           sub_18040FB78
