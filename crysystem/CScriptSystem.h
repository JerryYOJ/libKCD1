#pragma once

#include <cstdint>

// -----------------------------------------------
// CScriptSystem — CryEngine Lua scripting implementation
// -----------------------------------------------
// RTTI: .?AVCScriptSystem@@
// Source: g:\workspace\kcdx_0109\code\cryengine\cryscriptsystem\scriptsystem.cpp
// Implements: IScriptSystem (CryEngine/CryCommon/IScriptSystem.h)
//
// Lua version: 5.1 (confirmed: LUA_GLOBALSINDEX = 0xFFFFD8EE = -10002)
//
// vtables:
//   Primary (IScriptSystem): 0x1827d2488
//   Secondary _0:            0x1827d2468
//
// Size: 0x43D8 (from destructor free size)
// Constructor/Init: sub_18213C2DC
//
// -----------------------------------------------
// Global accessors
// -----------------------------------------------
//   lua_State*      g_pLuaState     = *(lua_State**)0x183787948;
//   lua_State*      g_pLuaState2    = *(lua_State**)0x1837879F0;  (secondary copy)
//   CScriptSystem*  g_pScriptSystem = *(CScriptSystem**)0x183787950;
//   CScriptSystem*  g_pScriptSystem2= *(CScriptSystem**)0x183787940;
//
// Init sequence (sub_18213C2DC):
//   a1[2] = lua_newstate();        // +0x10 = lua_State*
//   qword_1837879F0 = a1[2];
//   qword_183787948 = a1[2];
//   qword_183787950 = a1;
//
// -----------------------------------------------
// How to eval Lua commands
// -----------------------------------------------
// Method 1 — CScriptSystem::ExecuteBuffer (vtable[6], offset 0x30):
//   auto pSS = *(void**)0x183787950;
//   auto vtable = *(uintptr_t**)pSS;
//   using FnExecBuf = bool(__fastcall*)(void*, const char*, size_t, const char*, void*);
//   auto ExecuteBuffer = (FnExecBuf)vtable[6];
//   ExecuteBuffer(pSS, code, strlen(code), "eval", nullptr);
//
// Method 2 — Direct Lua C API:
//   auto L = *(lua_State**)0x183787948;
//   luaL_loadbuffer(L, code, len, "eval");  // via lua_load at 0x1806E088C
//   lua_pcall(L, 0, LUA_MULTRET, 0);       // 0x1803B8254
//
// -----------------------------------------------
// How to register new Lua functions
// -----------------------------------------------
//   auto L = *(lua_State**)0x183787948;
//   lua_pushcclosure(L, my_func, 0);                  // 0x1802B8734
//   lua_setfield(L, LUA_GLOBALSINDEX, "MyFunc");      // 0x1803B801C
//
//   // Then callable from Lua as: MyFunc(args)
//   // lua_CFunction signature: int (*)(lua_State*)
//
// -----------------------------------------------
// Lua C API addresses (statically linked Lua 5.1)
// -----------------------------------------------
//   lua_newstate            0x18211D1D4
//   lua_load                0x1806E088C   (L, reader, data, chunkname)
//   lua_pcall               0x1803B8254   (L, nargs, nresults, errfunc)
//   lua_pushcclosure        0x1802B8734   (L, fn, nupvalues)
//   lua_pushstring          0x1802B815C   (L, s)
//   lua_pushvalue           0x180553AA4   (L, idx)
//   lua_setfield            0x1803B801C   (L, idx, key)
//   lua_getfield            0x1821137B8   (L, idx, key)
//   lua_settop              0x1803B9484   (L, idx)
//   lua_type                0x1803B9150   (L, idx)
//   lua_gc                  0x1803B9234   (L, what, data)
//   lua_rawget              0x1802B7D04   (L, idx)
//   lua_tolstring           0x1802B7EE4   (L, idx, len*)
//   luaL_ref                0x1803B477C   (L, t)
//
// LUA_GLOBALSINDEX = -10002 (0xFFFFD8EE)
// LUA_MULTRET      = -1

// -----------------------------------------------
// IScriptSystem vtable (INTERFUSCATED — binary order)
// -----------------------------------------------
// [0]  0x00   ~dtor
// [1]  0x08   Update()
// [2]  0x10   SetGCFrequency(float)
// [3]  0x18   SetEnvironmentToGlobal?
// [4]  0x20   GetGlobalTable?
// [5]  0x28   ExecuteFile(filename, raise, forceReload)
// [6]  0x30   ExecuteBuffer(buffer, size, desc, pEnv)
// [7]  0x38   UnloadScript(filename)
// [8]  0x40   UnloadScripts()
// [9]  0x48   ReloadScript(filename, raise)
// [10] 0x50   ReloadScripts()
// [11] 0x58   DumpLoadedScripts()
// [12] 0x60   CreateTable(nArray, nHash)
// [13] 0x68   CreateTable(bEmpty) / AllocTable
// [14] 0x70   AllocScriptTable
// [16] 0x80   BeginCall(tableName, funcName)
// [17] 0x88   BeginCall(funcName)
// [18] 0x90   EndCall / ExecuteFunction
// [22] 0xB0   GetMethodReference(tableName, funcName)
// [23] 0xB8   GetGlobalFuncRef(funcName)
// [40] 0x140  DumpCallStack / TraceScriptError

typedef struct lua_State lua_State;

struct CScriptSystem {
    // +0x00: IScriptSystem vtable (primary, interfuscated)
    // +0x08: secondary vtable _0
    char            _vtables[0x10];         // +0x00  (two vtable pointers)

    lua_State*      m_pLS;                  // +0x10  THE lua_State*

    uint64_t        m_luaDebugState[3];     // +0x18  debug/error state
    uint64_t        m_scriptTables[6];      // +0x30  various script tables
    uint64_t        m_loadedScripts[2];     // +0x60  loaded file map
    uint64_t        m_scriptBindings[5];    // +0x70
    void*           m_pSystem;              // +0x98  ISystem*
    uint64_t        m_frameData[2];         // +0xA0  timing/frame

    char            _padB0[0x4328];         // +0xB0  (large internal state, uncharted)
};
static_assert(sizeof(CScriptSystem) == 0x43D8);

// -----------------------------------------------
// Convenience types for hooking
// -----------------------------------------------
using lua_CFunction = int (*)(lua_State*);

// Typed function pointers for direct calls:
using fn_lua_pcall        = int  (*)(lua_State*, int, int, int);
using fn_lua_load         = int  (*)(lua_State*, void*, void*, const char*);
using fn_lua_pushcclosure = void (*)(lua_State*, lua_CFunction, int);
using fn_lua_pushstring   = void (*)(lua_State*, const char*);
using fn_lua_setfield     = void (*)(lua_State*, int, const char*);
using fn_lua_getfield     = void (*)(lua_State*, int, const char*);
using fn_lua_settop       = void (*)(lua_State*, int);
using fn_lua_tolstring    = const char* (*)(lua_State*, int, size_t*);
