#pragma once

#include "I_ColumnDescriptor.h"

namespace wh::databasemodule {

// C_ColumnDescriptorBase — base implementation of I_ColumnDescriptor.
// Stores column metadata as flat members. Size = 0x38 (56 bytes).
//
// Created by table registration functions at startup.
// Each table has an array of these describing its columns.
//
// Layout derived from vtable getters at 0x1822bff00
class C_ColumnDescriptorBase : public I_ColumnDescriptor {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ColumnDescriptorBase;
    // +0x00: vtable*
    uint32_t m_typeId;          // +0x08  column type enum
    uint32_t m_offset;          // +0x0C  byte offset in row struct
    uint32_t m_size;            // +0x10  field size in bytes
    uint32_t m_alignment;       // +0x14  field alignment
    const char* m_name;         // +0x18  column name string literal
    uint8_t m_flags;            // +0x20  general flags
    uint8_t m_hasDefault;       // +0x21  1 if default value is set
    uint8_t m_serializeFlags;   // +0x22  serialization flags
    uint8_t m_patchFlags;       // +0x23  patching flags (string relocation etc.)
    uint8_t m_nullable;         // +0x24  1 if column can be null
    uint8_t _pad[3];            // +0x25
    uint64_t m_defaultValue[2]; // +0x28  inline default value storage (16 bytes)
};
static_assert(sizeof(C_ColumnDescriptorBase) == 0x38, "C_ColumnDescriptorBase must be 0x38 bytes");

// C_ColumnDescriptor — non-PK column. IsPrimaryKey() returns false.
// vtable @ 0x1822bfdd8
class C_ColumnDescriptor : public C_ColumnDescriptorBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ColumnDescriptor;
};

// C_PKColumnDescriptor — primary key column. IsPrimaryKey() returns true.
// vtable @ 0x1822bfd50
class C_PKColumnDescriptor : public C_ColumnDescriptorBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PKColumnDescriptor;
};

// C_NotPatchedColumnDescriptor — column that skips string pointer patching.
// vtable @ 0x1822c6a68
class C_NotPatchedColumnDescriptor : public C_ColumnDescriptorBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_NotPatchedColumnDescriptor;
};

// C_RenamedColumnDescriptor — column with a different name mapping.
// vtable @ 0x1826a4a60
class C_RenamedColumnDescriptor : public C_ColumnDescriptorBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RenamedColumnDescriptor;
};

// Helper function that creates a C_ColumnDescriptor with int32 type and default value.
// sub_180713848(descriptor_ptr, row_offset, "column_name", &default_value)
// Sets: type=0(int32), size=4, align=4, flags=0x101(has_default)
// Address: 0x180713848

}  // namespace wh::databasemodule
