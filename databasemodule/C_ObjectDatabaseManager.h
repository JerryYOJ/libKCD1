#pragma once

#include <vector>
#include "I_ObjectDatabase.h"

namespace wh::databasemodule {

// C_ObjectDatabaseManager — global registry of all I_ObjectDatabase instances.
//
// vtable @ 0x1822c1c98
// RTTI: .?AVC_ObjectDatabaseManager@databasemodule@wh@@
// Inherits: I_ObjectDatabase (adds pure virtuals on top)
// Global instance accessed via sub_180F3780C()
//
// Stores a vector of I_ObjectDatabase* at +0x20..+0x28.
// C_ObjectDatabaseBase constructors register themselves here.
// FindDatabase iterates this vector calling GetTableName on each entry.
//
// Layout (from usage in FindDatabase / GetDatabase):
//   +0x00: vtable*
//   +0x08: (base data)
//   +0x20: I_ObjectDatabase** m_databases_begin
//   +0x28: I_ObjectDatabase** m_databases_end
//   +0x30: I_ObjectDatabase** m_databases_capacity
class C_ObjectDatabaseManager : public I_ObjectDatabase {
public:
    // Inherited from I_ObjectDatabase:
    // +0x00: vtable*

    uint64_t _unk08;                        // +0x08
    uint64_t _unk10;                        // +0x10
    uint64_t _unk18;                        // +0x18

    std::vector<I_ObjectDatabase*> m_databases; // +0x20
};

// C_DynamicEnumManager — manages runtime enum definitions backed by tables.
//
// vtable @ 0x1826a4598
// RTTI: .?AVC_DynamicEnumManager@databasemodule@wh@@
// Destructor: 0x180F36B20
// Inherits: I_DatabaseListener (vtable restored in dtor)
//
// Embedded inside C_DatabaseModule at offset +0x110.
// Owns a flat associative array of enum entries stored as (key, C_DatabaseDynamicEnum*) pairs.
// Entries are 16-byte pairs — destructor cleanup iterates with stride 2 qwords.
//
// Layout (from destructor sub_180F36B20 and cleanup sub_180F35C24):
struct S_EnumEntry {
    uint64_t key;                           // hash or ID key
    C_DatabaseDynamicEnum* enumDef;         // value
};

class C_DynamicEnumManager : public I_DatabaseListener {
public:
    // +0x00: vtable (inherited from I_DatabaseListener)
    S_EnumEntry* m_entries;                 // +0x08  flat array of (key, enum) pairs
    int64_t m_entryCount;                   // +0x10  number of entries
    int64_t m_entryCapacity;                // +0x18  allocated capacity
    void* m_hashBuckets;                    // +0x20  hash bucket array (freed if m_ownsHash is true)
    uint64_t m_hashSize;                    // +0x28  bucket count
    bool m_ownsHash;                        // +0x30  if true, m_hashBuckets is heap-allocated
    uint8_t _pad31[7];                      // +0x31
    uint64_t _unk38;                        // +0x38
};
static_assert(sizeof(C_DynamicEnumManager) == 0x40, "C_DynamicEnumManager must be 0x40");

// C_DatabaseDynamicEnum — single dynamic enum backed by a table.
//
// vtable @ 0x1822c1dd0
// RTTI: .?AVC_DatabaseDynamicEnum@databasemodule@wh@@
// Constructor: 0x180F36510 / 0x180F36B90
// Destructor: 0x180F35C24
// Size: 0x18 bytes
//
// vtable[0]  GetRowCount() -> *(int*)(*(m_sourceTable) + 8)
// vtable[1]  GetRowByIndex(idx) -> row ptr from source table
// vtable[2]  GetRowData(idx) -> row data ptr
// vtable[3]  GetRowId(idx) -> row ID
// vtable[4]  GetRowExtra(idx) -> extra data
// vtable[5]  unk_05()
// vtable[6]  GetSelf() -> returns this
// vtable[7]  unk_07()
// vtable[8]  GetSelf2() -> returns this
// vtable[9..14] = 0 (pure virtual — not implemented, enum is read-only)
class C_DatabaseDynamicEnum {
public:
    virtual int GetRowCount() const = 0;                    // [0]
    virtual const void* GetRowByIndex(int idx) const = 0;   // [1]
    virtual const void* GetRowData(int idx) const = 0;      // [2]
    virtual uint32_t GetRowId(int idx) const = 0;           // [3]
    virtual const void* GetRowExtra(int idx) const = 0;     // [4]
    virtual void unk_05() = 0;                              // [5]
    virtual C_DatabaseDynamicEnum* GetSelf() = 0;           // [6]  returns this
    virtual void unk_07() = 0;                              // [7]
    virtual C_DatabaseDynamicEnum* GetSelf2() = 0;          // [8]  returns this
    virtual void unk_09() = 0;                              // [9]  pure
    virtual void unk_10() = 0;                              // [10] pure
    virtual void unk_11() = 0;                              // [11] pure
    virtual void unk_12() = 0;                              // [12] pure
    virtual void unk_13() = 0;                              // [13] pure
    virtual void unk_14() = 0;                              // [14] pure

    I_ObjectDatabase* m_sourceTable;        // +0x08  backing database table
    const char* m_enumName;                 // +0x10  enum name (CryString, freed with -0xC header)
};
static_assert(sizeof(C_DatabaseDynamicEnum) == 0x18, "C_DatabaseDynamicEnum must be 0x18");

}  // namespace wh::databasemodule
