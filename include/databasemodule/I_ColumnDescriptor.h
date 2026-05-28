#pragma once

#include <cstdint>

namespace wh::databasemodule {

// I_ColumnDescriptor — pure interface for column schema descriptors.
// Each column in a database table has one descriptor that stores
// the column's name, type, offset within the row struct, and size.
//
// vtable @ 0x1822bfe78 (all pure virtual except dtor)
class I_ColumnDescriptor {
public:
    virtual ~I_ColumnDescriptor() = 0;                  // [0]
    virtual uint32_t GetTypeId() const = 0;             // [1]  0=int32/enum, 1=int64, 2=float, 3=guid, 4=bool, 5=string
    virtual uint32_t GetOffset() const = 0;             // [2]  byte offset into the row struct
    virtual uint32_t GetSize() const = 0;               // [3]  data size in bytes
    virtual uint32_t GetAlignment() const = 0;          // [4]  data alignment
    virtual bool IsPrimaryKey() const = 0;              // [5]  true for C_PKColumnDescriptor
    virtual const char* GetName() const = 0;            // [6]  column name string (e.g., "buff_id")
    virtual uint8_t GetFlags() const = 0;               // [7]  flags byte at +0x20
    virtual const void* GetDefaultValuePtr() const = 0; // [8]  pointer to default value storage
    virtual void* GetDefaultValueData() = 0;            // [9]  direct pointer to default value bytes
    virtual bool HasDefaultValue() const = 0;           // [10] +0x21
    virtual bool IsInlineData() const = 0;              // [11] true for Col/PK (data in row), false for computed
    virtual bool IsComputed() const = 0;                // [12] true if column is computed/virtual
    virtual uint8_t GetSerializeFlags() const = 0;      // [13] +0x22
    virtual uint8_t GetPatchFlags() const = 0;          // [14] +0x23
    virtual bool IsNullable() const = 0;                // [15] +0x24
};

}  // namespace wh::databasemodule
