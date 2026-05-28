#pragma once

// ==========================================================================
// database_types.h
//
// Shared type definitions for KCD database module table structs.
//
// Auto-generated from Warhorse C_ColumnDescriptor extraction.
// Source: table_schemas.json (375 table registrations,
//         287 unique (table_name, row_size) combinations)
//
// Each struct represents the in-memory row layout for a database table
// as registered by wh::databasemodule column descriptor functions.
//
// Column types:
//   int32  -> int32_t       int16  -> int16_t
//   int64  -> int64_t       uint32 -> uint32_t
//   float  -> float         bool   -> bool
//   string -> const char*   guid   -> CryGUID (16B) or uint64_t (8B)
//   data   -> uint8_t[N]
//
// Fields with offset -1 are virtual/computed (not in struct memory).
// Padding bytes fill gaps between columns to match the original layout.
//
// Row headers (_rowbase[4/8/16]):
//   The first N bytes of each row (before the first column) are zero-
//   initialized struct padding inherited from the C++ source struct's
//   base class. The XML/TBL loaders memset the entire row buffer to 0
//   and only write to offsets described by column descriptors.
//   These bytes are always zero in the loaded data.
// ==========================================================================

#include <cstdint>
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"
