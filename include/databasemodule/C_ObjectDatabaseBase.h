#pragma once

#include "I_ObjectDatabase.h"
#include "../framework/C_Signal.h"

namespace wh::databasemodule {

// C_ObjectDatabaseBase — base class for all database table containers.
//
// vtable @ 0x1822c1ca8
// RTTI: .?AVC_ObjectDatabaseBase@databasemodule@wh@@
// Constructor: 0x180F3684C(this, int type)
// Size (base only): 0x90 bytes. Concrete instances extend to ~0x100+.
//
// IMPORTANT: After loading, sub_180F3C390 OVERWRITES +0x00 (the vtable pointer)
// with the row data buffer pointer. The vtable only functions during init/registration.
// After data loading, the object is accessed as a flat data container via raw offsets
// (see GetTableLine @ 0x180F3A064). Virtual dispatch is NOT used post-load.
//
// Layout has two phases:
//
// === INIT PHASE (constructor through registration) ===
//   +0x00: vtable* (C_ObjectDatabaseBase or derived)
//   +0x08: int32_t m_type (constructor param, typically 1)
//   +0x0A: uint16_t m_rowStride (returned by vtable[18])
//
// === DATA PHASE (after sub_180F3C390 fills the table) ===
//   +0x00: void* m_rowData       — row buffer (row_count * row_stride bytes, memset to 0 then filled)
//   +0x08: int32_t m_rowCount    — number of rows loaded
//   +0x0C: (unused/pad)
//   +0x10: void* m_stringData    — string data block (string offsets patched to absolute ptrs into here)
//   +0x18: int32_t m_stringDataSize
//   +0x1C: int32_t m_patchedStringCount — number of string pointers patched
//   +0x20: int32_t m_stringExtraInfo
//   +0x24: (pad)
//   +0x28: (reserved)
//
// === SHARED (same meaning in both phases) ===
//   +0x30: C_Signal<> m_onChanged (0x30 bytes, to +0x5F)
//          INIT PHASE: signal fires when table data changes
//          DATA PHASE: signal is dead, internals repurposed:
//            +0x40 = S_ColumnMetadata* (set during registration, NOT overwritten by loader)
//            +0x50 = flags (bit 3 cleared by loader: *(DWORD*)(this+0x50) &= ~8)
//            +0x54 = m_isLoaded (byte, set to 1 after data fill)
//            +0x58 = m_totalRowCount (dword)
//            +0x5C = sentinel = -1 (from signal init)
//
//   +0x60: C_Signal<bool> m_onLoaded (0x30 bytes, to +0x8F)
//          INIT PHASE: signal fires when table loading completes
//          DATA PHASE: signal is dead
//            +0x88 = sentinel = -1
//            +0x8C = sentinel = -1
//
// Registration:
//   Constructor calls sub_180F3780C() to get the global C_ObjectDatabaseManager,
//   then pushes `this` into the manager's database vector (manager+0x20..+0x28).
//   After registration, FindDatabase (I_DatabaseModule vtable[3]) can locate
//   this database by name via linear search + vtable[2] GetTableName call.
//
// Row access (GetTableLine @ 0x180F3A064):
//   row_ptr = *(void**)(db+0x00) + index * columnMeta->m_rowStride
//   field   = *(FieldType*)((char*)row_ptr + descriptor->GetOffset())

class C_ObjectDatabaseBase : public I_ObjectDatabase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ObjectDatabaseBase;
    // --- Init phase fields (overwritten after loading) ---
    // +0x00: vtable* OR void* m_rowData (post-load)
    // +0x08: int32_t m_type OR int32_t m_rowCount (post-load)
    // +0x0A: uint16_t m_rowStride (init only, overlaps m_type high word)

    // --- Post-load data fields ---
    // +0x10:
    void* m_stringData;             // +0x10  string data block base pointer
    int32_t m_stringDataSize;       // +0x18  size of string data in bytes
    int32_t m_patchedStringCount;   // +0x1C  count of patched string columns
    int32_t m_stringExtraInfo;      // +0x20  extra string/offset info
    int32_t _pad24;                 // +0x24

    // +0x28:
    uint64_t _reserved28;           // +0x28  (0 in ctor)

    // --- Dual-phase region: +0x30 to +0x8F ---
    // INIT PHASE: two C_Signal objects (each 0x30 bytes)
    //   C_Signal<>     at +0x30 (fires on data change)
    //   C_Signal<bool> at +0x60 (fires on load complete)
    // DATA PHASE: signals are dead, same bytes repurposed:
    //   +0x40 = S_ColumnMetadata* (column descriptors, row stride)
    //   +0x48 = 0
    //   +0x50 = flags (bit 3 = needs refresh)
    //   +0x54 = m_isLoaded (byte, set to 1 after fill)
    //   +0x58 = m_totalRowCount
    //
    // Modeled as raw bytes to avoid sizeof issues with the C_Signal change.
    // Access data-phase fields via reinterpret_cast or S_LoadedTableView.
    //
    // INIT PHASE: two C_Signal objects occupy +0x30..+0x8F
    //   C_Signal<>     m_onChanged at +0x30 (0x30 bytes)
    //   C_Signal<bool> m_onLoaded  at +0x60 (0x30 bytes)
    //
    // DATA PHASE: signals are dead, same memory repurposed as below.
    // Both phases represented as a single POD struct to avoid union-with-
    // non-trivial-destructor issues in the C++ type system.
    struct {  // DATA PHASE view (fields overlap signal internals)
        uint64_t _sig1_vtable;              // +0x30  (dead signal vtable)
        uint64_t _sig1_bypass;              // +0x38
        S_ColumnMetadata* m_columnMeta;     // +0x40  column descriptors
        uint64_t _sig1_connData;            // +0x48
        uint32_t m_flags;                   // +0x50  bit flags (bit 3 = needs refresh)
        bool     m_isLoaded;                // +0x54  set to 1 after data fill
        uint8_t  _pad55[3];                 // +0x55
        int32_t  m_totalRowCount;           // +0x58
        int32_t  _sentinel5C;              // +0x5C  = -1 (signal sentinel, still valid)
        uint64_t _sig2_vtable;              // +0x60  (dead signal vtable)
        uint64_t _sig2_bypass;              // +0x68
        uint64_t _sig2_connList;            // +0x70
        uint64_t _sig2_connData;            // +0x78
        uint64_t _sig2_emitData;            // +0x80
        int32_t  _sentinel88;              // +0x88  = -1
        int32_t  _sentinel8C;              // +0x8C  = -1
    };
    // Total base: 0x90 bytes
};

// Post-load data access view (what GetTableLine uses).
// After loading, sub_180F3C390 overwrites +0x00 (vtable) with row data.
// Reinterpret db base as this to access loaded data:
struct S_LoadedTableView {
    void* m_rowData;                // +0x00  row buffer (was vtable)
    int32_t m_rowCount;             // +0x08  number of rows (was m_type)
    int32_t _pad0C;                 // +0x0C
    void* m_stringData;             // +0x10  string data block
    int32_t m_stringDataSize;       // +0x18
    int32_t m_patchedStringCount;   // +0x1C
    int32_t m_stringExtraInfo;      // +0x20
    int32_t _pad24;                 // +0x24
    uint64_t _reserved28;           // +0x28
    uint64_t _deadSignalVtable;     // +0x30  (dead C_Signal<> vtable, not overwritten by loader)
    uint64_t _deadSignalBypass;     // +0x38
    S_ColumnMetadata* m_columnMeta; // +0x40  column descriptors (lives inside dead signal memory)
};

}  // namespace wh::databasemodule
