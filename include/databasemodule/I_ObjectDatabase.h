#pragma once

#include <cstdint>

namespace wh::databasemodule {

class I_ColumnDescriptor;

// Column metadata container — holds the descriptor array and row stride.
// Pointed to by C_ObjectDatabaseBase+0x40 and similar.
// Layout recovered from GetTableLine (0x180F3A064) and TBL loader usage.
struct S_ColumnMetadata {
    int32_t m_columnCount;              // +0x00  number of columns
    uint8_t _pad04[4];                  // +0x04
    I_ColumnDescriptor** m_columns;     // +0x08  array of column descriptor pointers
    int32_t m_rowStride;                // +0x10  size of one row in bytes
    uint8_t _pad14[4];                  // +0x14
    int32_t m_columnCountCheck;         // +0x18  column count (verified against TBL header)
    int32_t m_layoutHash;               // +0x1C  layout hash (verified against TBL header)
};

// I_ObjectDatabase — interface for a typed table container.
// Owns the row data array, provides indexed access.
//
// vtable @ 0x1822c1db0
class I_ObjectDatabase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_ObjectDatabase;
    virtual ~I_ObjectDatabase() = 0;                        // [0]
    virtual int GetVersion() const = 0;                     // [1]  returns 1
    virtual bool Load() = 0;                                // [2]  pure — triggers XML/TBL loading
    virtual void OnPostLoad() = 0;                          // [3]
    virtual int GetRowCount() const = 0;                    // [4]
    virtual const void* GetRowByIndex(int index) const = 0; // [5]
    virtual const void* GetRowData(int index) const = 0;    // [6]
    virtual uint32_t GetRowId(int index) const = 0;         // [7]
    virtual const void* GetRowExtra(int index) const = 0;   // [8]
    virtual void Rebuild() = 0;                             // [9]
    virtual I_ObjectDatabase* GetSelf() = 0;                // [10] returns this
    virtual void Validate() = 0;                            // [11]
    virtual I_ObjectDatabase* GetSelf2() = 0;               // [12] returns this
    virtual void Register() = 0;                            // [13] pure
    virtual void Unregister() = 0;                          // [14] pure
    virtual const char* GetTableName() const = 0;           // [15] pure
    virtual S_ColumnMetadata* GetColumnMetadata() const = 0;// [16] pure
    virtual void SetColumnMetadata(S_ColumnMetadata*) = 0;  // [17] pure
    virtual void NotifyListeners() = 0;                     // [18] pure
    virtual void ClearData() = 0;                           // [19] pure
};

}  // namespace wh::databasemodule
