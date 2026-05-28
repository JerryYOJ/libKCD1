#pragma once

#include <cstdint>
#include <vector>
#include <set>
#include "../CryEngine/CryCommon/CryString.h"
#include "../CryEngine/CryCommon/CryFixedString.h"
#include "../Offsets/vtables/IScriptSystem.h"
#include "../Offsets/vtables/ISystemEventListener.h"
#include "../Offsets/vtables/IConsole.h"
#include "CScriptableBase.h"

// -----------------------------------------------
// CScriptSystem — CryEngine Lua scripting implementation
// -----------------------------------------------
// RTTI: .?AVCScriptSystem@@
// Source: g:\workspace\kcdx_0109\code\cryengine\cryscriptsystem\scriptsystem.cpp
// Implements: IScriptSystem, ISystemEventListener [MI]
//
// Lua version: 5.1 (confirmed: LUA_GLOBALSINDEX = 0xFFFFD8EE = -10002)
//
// vtables:
//   Primary (IScriptSystem): 0x1827d2488  (67 slots, INTERFUSCATED)
//   ISystemEventListener:    0x1827d2468  (3 slots)
//
// Size: 0x43D8 (from destructor free size)
// Constructor/Init: sub_18213C2DC
//
// -----------------------------------------------
// Global accessors
// -----------------------------------------------
//   lua_State*      g_pLuaState     = *(lua_State**)0x183787948;
//   CScriptSystem*  g_pScriptSystem = *(CScriptSystem**)0x183787950;
//
// -----------------------------------------------
// How to eval Lua commands
// -----------------------------------------------
// Method 1 — CScriptSystem::ExecuteBuffer (vtable[6], offset 0x30):
//   auto pSS = *(CScriptSystem**)0x183787950;
//   pSS->ExecuteBuffer(code, strlen(code), "eval", nullptr);
//
// Method 2 — Direct Lua C API:
//   auto L = *(lua_State**)0x183787948;
//   luaL_loadbuffer(L, code, len, "eval");
//   lua_pcall(L, 0, LUA_MULTRET, 0);
//
// -----------------------------------------------
// Lua C API addresses (statically linked Lua 5.1)
// -----------------------------------------------
//   lua_newstate            0x18211D1D4
//   lua_load                0x1806E088C
//   lua_pcall               0x1803B8254
//   lua_pushcclosure        0x1802B8734
//   lua_pushstring          0x1802B815C
//   lua_pushvalue           0x180553AA4
//   lua_setfield            0x1803B801C
//   lua_getfield            0x1821137B8
//   lua_settop              0x1803B9484
//   lua_type                0x1803B9150
//   lua_gc                  0x1803B9234
//   lua_rawget              0x1802B7D04
//   lua_tolstring           0x1802B7EE4
//   luaL_ref                0x1803B477C
//
// LUA_GLOBALSINDEX = -10002
// LUA_MULTRET      = -1

typedef struct lua_State lua_State;

struct ISystem;
class CScriptTimerMgr;
class CLUADbg;

// CScriptBindings — embedded sub-object managing script bind registrations
// Has its own vtable. Constructed by sub_18213BB28.
class CScriptBindings {
public:
    virtual ~CScriptBindings();                                                 // [0]

    std::vector<CScriptableBase*>   m_scriptBinds;          // +0x08  7 built-in bindings
    void*                           m_pCommandBuf;          // +0x20  0x30-byte heap obj (2 vectors)
};
static_assert(sizeof(CScriptBindings) == 0x28);

class CScriptSystem : public Offsets::IScriptSystem,        // vtable at +0x00 (67 slots)
                      public Offsets::ISystemEventListener   // vtable at +0x08 (3 slots)
{
public:
    lua_State*              m_pLS;                          // +0x10  from lua_newstate()

    Offsets::ICVar*         m_pCVarDebugger;                // +0x18  "lua_debugger" (0/1/2)
    Offsets::ICVar*         m_pCVarCodeCoverage;            // +0x20  "lua_CodeCoverage"
    int32_t                 m_nParamCount;                  // +0x28  nArgs for BeginCall/EndCall
    int32_t                 _pad2C;                         // +0x2C

    Offsets::IScriptTable*  m_pTempTable1;                  // +0x30  working table
    Offsets::IScriptTable*  m_pTempTable2;                  // +0x38  working table

    std::vector<CryStringLocal> m_vecPreCached;              // +0x40  pre-cached script paths (UNVERIFIED name)

    int32_t                 m_nErrorHandlerRef;             // +0x58  luaL_ref for error handler
    int32_t                 _pad5C;                         // +0x5C

    // Loaded script filenames, case-insensitive. DumpLoadedScripts iterates this.
    // ExecuteFile inserts, UnloadScript removes.
    std::set<CryStringLocal> m_setLoadedFiles;               // +0x60  case-insensitive loaded script filenames

    CScriptBindings         m_bindings;                     // +0x70  embedded (0x28 bytes, to +0x98)

    ISystem*                m_pSystem;                      // +0x98
    float                   m_gcFrequency;                  // +0xA0  from SetGCFrequency, init 10.0f
    float                   m_lastTime;                     // +0xA4  cached _time from Update
    int32_t                 m_lastGCCount;                  // +0xA8  cached GetGCCount from Update
    int32_t                 m_nNestedForceReload;           // +0xAC  incr/decr in ExecuteFile

    CScriptTimerMgr*        m_pScriptTimerMgr;              // +0xB0  0x40-byte timer manager
    int32_t                 m_nTempArg;                     // +0xB8  index into m_sTemp[], reset each frame
    int32_t                 _padBC;                         // +0xBC

    CryFixedStringT<512>    m_sTemp[32];                    // +0xC0  32 temp string buffers (0x4300 bytes)

    CryStringLocal          m_sBuffer;                      // +0x43C0  vestigial empty string (8 bytes = char*)
    uint64_t                _pad43C8;                       // +0x43C8  never accessed

    CLUADbg*                m_pDebugger;                    // +0x43D0  created lazily when lua_debugger CVar > 0
};
static_assert(sizeof(CScriptSystem) == 0x43D8);

// -----------------------------------------------
// Convenience types for hooking
// -----------------------------------------------
using lua_CFunction = int (*)(lua_State*);

using fn_lua_pcall        = int  (*)(lua_State*, int, int, int);
using fn_lua_load         = int  (*)(lua_State*, void*, void*, const char*);
using fn_lua_pushcclosure = void (*)(lua_State*, lua_CFunction, int);
using fn_lua_pushstring   = void (*)(lua_State*, const char*);
using fn_lua_setfield     = void (*)(lua_State*, int, const char*);
using fn_lua_getfield     = void (*)(lua_State*, int, const char*);
using fn_lua_settop       = void (*)(lua_State*, int);
using fn_lua_tolstring    = const char* (*)(lua_State*, int, size_t*);
