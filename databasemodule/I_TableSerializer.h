#pragma once

namespace wh::databasemodule {

struct C_ObjectDatabaseBase;

// I_TableSerializer — interface for XML/TBL file loaders.
//
// vtable @ 0x1822c1f70
// Two concrete implementations: C_XMLTableSerializer and C_TBLTableSerializer.
//
// vtable methods:
//   [0] ~dtor
//   [1] GetFormatName() -> const char* ("TBL" or "XML")
//   [2] GetFileExtension() -> const char* (pure)
//   [3] SetModified(bool)
//   [4] IsModified() -> bool (returns false by default)
//   [5] Deserialize(C_ObjectDatabaseBase* db) -> bool (pure — loads file into db)
//   [6] CanSerialize() -> bool (returns false by default)
//   [7] Serialize(db) -> bool (returns false by default)
struct I_TableSerializer {
    virtual ~I_TableSerializer() = 0;
    virtual const char* GetFormatName() const = 0;
    virtual const char* GetFileExtension() const = 0;
    virtual void SetModified(bool modified) = 0;
    virtual bool IsModified() const = 0;
    virtual bool Deserialize(C_ObjectDatabaseBase* db) = 0;
    virtual bool CanSerialize() const = 0;
    virtual bool Serialize(const C_ObjectDatabaseBase* db) const = 0;
};

// C_XMLTableSerializer — loads rows from XML files in Tables.pak.
//
// vtable @ 0x1826a4ae8
// Deserialize: 0x180F3B914
// Size: 0x28 (40 bytes)
//
// Parses XML structure: <database name="hammerheart"><table name="X" version="N"><header/><rows><row .../>
// For each <row>, iterates column descriptors and reads XML attributes by name.
// Type-specific parsing: %d (int), %f (float), %lld (int64), True/False (bool),
//   GUID string (guid), direct string (string).
// After all rows parsed, calls sub_180F3C390 to finalize (patch string pointers).
//
// Created in C_DatabaseModule init (sub_180F37930):
//   allocate(0x28) -> init -> store in module's serializer vector
//
// Layout (from init code in sub_180F37930):
//   +0x00: vtable*
//   +0x08: bool m_modified          (set to 0)
//   +0x10: void* m_unk10            (set to 0, patched later)
//   +0x18: void* m_columnState      (= module->m_tableDataHolder, the 0x50-byte context object)
//   +0x20: bool m_validateLayout    (set to 0)
struct C_XMLTableSerializer : I_TableSerializer {
    // +0x00: vtable*
    bool m_modified;                // +0x08
    uint8_t _pad09[7];             // +0x09
    void* m_unk10;                 // +0x10
    void* m_columnState;           // +0x18  points to table data context (module+0xD0 object)
    bool m_validateLayout;         // +0x20
    uint8_t _pad21[7];             // +0x21
};
static_assert(sizeof(C_XMLTableSerializer) == 0x28, "C_XMLTableSerializer must be 0x28");

// C_TBLTableSerializer — loads rows from precompiled TBL binary files.
//
// vtable @ 0x1826a48b0
// Deserialize: 0x180F3A36C
// Size: 0x20 (32 bytes)
//
// TBL format header (0x1C bytes):
//   magic=3, column_count, layout_hash, row_count, row_data_size, string_data_size, extra
// Validates column_count and layout_hash against column metadata.
// Bulk-reads row data and string data, then calls sub_180F3C390 to finalize.
//
// Created in C_DatabaseModule init (sub_180F37930):
//   allocate(0x20) -> init
//
// Layout (from init code):
//   +0x00: vtable*
//   +0x08: bool m_modified
//   +0x10: void* m_unk10
//   +0x18: bool m_validateLayout   (= module+0x154 byte, skips stale file check if false)
struct C_TBLTableSerializer : I_TableSerializer {
    // +0x00: vtable*
    bool m_modified;                // +0x08
    uint8_t _pad09[7];             // +0x09
    void* m_unk10;                 // +0x10
    bool m_validateLayout;         // +0x18
    uint8_t _pad19[7];             // +0x19
};
static_assert(sizeof(C_TBLTableSerializer) == 0x20, "C_TBLTableSerializer must be 0x20");

}  // namespace wh::databasemodule
