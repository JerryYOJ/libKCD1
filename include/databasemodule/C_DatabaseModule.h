#pragma once

#include <vector>
#include "../framework/C_BaseModule.h"   // canonical wh::framework::C_BaseModule (0x88, includes I_ModuleMessageListener @ +0x78)
#include "I_DatabaseModule.h"
#include "I_TableSerializer.h"
#include "C_ObjectDatabaseManager.h"     // C_DynamicEnumManager (0x40)

namespace wh::databasemodule {

struct C_ScriptBindDatabase;

// C_DatabaseModule — concrete database module singleton.
// Owns all databases, serializers, dynamic enums, and the Lua script binding.
//
// RTTI: .?AVC_DatabaseModule@databasemodule@wh@@
// Constructor: 0x180F36658
// Destructor:  0x180F36914
// Global singleton stored at: 0x18378D5E0
//
// Multiple inheritance (3 vtable pointers in the binary):
//   +0x00: C_BaseModule vtable            (@6B@_0 = 0x1826a46a0)
//   +0x78: I_ModuleMessageListener vtable (@6B@   = 0x1826a45a8)  <- C_BaseModule's own 2nd base
//   +0x88: I_DatabaseModule vtable        (@6B@_1 = 0x1826a45c0)
//
// The +0x78 I_ModuleMessageListener sub-object is supplied by C_BaseModule itself
// (C_BaseModule : C_Graph, I_ModuleMessageListener; sizeof 0x88). So C_DatabaseModule
// is just `C_BaseModule, I_DatabaseModule` — two declared bases, three vtables.
//
// ScriptBindDatabase stores (module + 0x88) as its I_DatabaseModule pointer.
// All I_DatabaseModule vtable offsets are relative to +0x88:
//   [0]  ~dtor (adjusts this by -0x88)
//   [1]  Initialize() -> bool
//   [2]  GetDatabaseManager() -> *(this+0x38)
//   [3]  FindDatabase(name) -> linear search, strcmp on GetTableName
//   [4]  GetDatabase(index) -> m_databases[index]
//   [5]  RegisterDatabase(db)
//   [6]  IsLoaded() -> m_isLoaded
//   [10] GetDynamicEnum(name)
//   [11] GetDynamicEnumByIndex(idx)
//   [14] FindDatabaseByName(name) -> iterates m_databases
//   [19] GetEnumValueName(enum, id)
//
// Size: 0x160 bytes. Abstract (inherited pure virtuals are not overridden here);
// this header models layout only, the type is never instantiated.
class C_DatabaseModule : public wh::framework::C_BaseModule,
                         public I_DatabaseModule {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DatabaseModule;
    // bases:
    //   wh::framework::C_BaseModule  @ +0x00  (0x88: primary vtable @+0x00,
    //                                          I_ModuleMessageListener vtable @+0x78, m_state @+0x80)
    //   I_DatabaseModule             @ +0x88  (vtable only)
    // first own member begins at +0x90.

    void* _unk90;                                               // +0x90  (0 in ctor)
    void* _unk98;                                               // +0x98  (0 in ctor)
    void* _unkA0;                                               // +0xA0  (0 in ctor)

    // I_DatabaseModule+0x20 = module+0xA8
    std::vector<I_ObjectDatabase*> m_databases;                 // +0xA8  all registered databases

    void* m_tablePath;                                          // +0xC0  CryString — path for table files

    C_ScriptBindDatabase* m_scriptBind;                         // +0xC8  Lua "Database" global table binding
    void* m_tableDataHolder;                                    // +0xD0  0x50-byte context: {module*, ...}
    void* m_unkD8;                                              // +0xD8  (0 in ctor)
    void* m_unkE0;                                              // +0xE0  (0 in ctor)

    std::vector<I_TableSerializer*> m_serializers;              // +0xE8  XML + TBL serializers

    void* _unk100;                                             // +0x100 (0 in ctor)
    void* _unk108;                                             // +0x108 (0 in ctor)

    // +0x110: embedded, owns all dynamic enum definitions
    C_DynamicEnumManager m_dynamicEnumManager;                  // +0x110 (0x40 bytes)

    int32_t m_unkInt150;                                        // +0x150 (0 in ctor)
    bool m_isLoaded;                                            // +0x154 (true in ctor, returned by IsLoaded)
    uint8_t _pad155[3];                                         // +0x155

    void* m_selfPtr;                                            // +0x158 allocated 8-byte block -> this
    // Total: 0x160 bytes
};
static_assert(sizeof(C_DatabaseModule) == 0x160, "C_DatabaseModule must be 0x160 bytes");

}  // namespace wh::databasemodule
