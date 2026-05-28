#pragma once

#include "C_ObjectDatabaseBase.h"

namespace wh::databasemodule {

// C_ObjectTableDatabase<TData, TRow> — templated database container.
//
// TRow = the S_*TableRow POD struct (flat row data from XML/TBL)
// TData = the C_*Data wrapper class (provides typed accessors, FK resolution)
//
// RTTI pattern:
//   .?AV?$C_ObjectTableDatabase@VC_CombatActionAttackData@combatmodule@wh@@
//       US_CombatActionAttackTableRow@23@@databasemodule@wh@@
//
// The database owns a contiguous array of TRow structs, loaded by
// C_XMLTableSerializer or C_TBLTableSerializer. TData instances
// wrap individual rows and are created on demand or cached.
//
// Template inheritance chain (typical):
//   C_ObjectTableDatabase<TData, TRow>
//     : C_ObjectDatabaseBase
//
// Then wrapped by indexing templates:
//   C_ObjectDatabaseGenerated<C_ObjectTableDatabase<TData, TRow>>
//     — auto-generated, registers column descriptors
//   C_ObjectDatabaseSortedIdIndexed<...>
//     — adds binary search by PK
//   C_ObjectDatabaseIdIndexed<...>
//     — adds hash-based lookup by int32 ID
//   C_ObjectDatabaseKeyIndexed<...>
//     — adds key-based lookup
//
// Row access pattern (from GetTableLine @ 0x180F3A064):
//   TRow* row = (TRow*)((char*)m_rowData + index * columnMeta->m_rowStride);
//   value = *(FieldType*)((char*)row + descriptor->GetOffset());
//
// Usage in game code:
//   C_CombatModule holds C_CombatActionAttackDatabase* (a typedef for the
//   fully-wrapped template chain). Game code calls methods on TData wrappers,
//   never touches TRow directly.
template<typename TData, typename TRow>
class C_ObjectTableDatabase : public C_ObjectDatabaseBase {
public:
    // No additional members beyond C_ObjectDatabaseBase.
    // Template provides typed access:

    // TRow* GetRow(int index) const {
    //     return (TRow*)((char*)m_rowData + index * m_columnMeta->m_rowStride);
    // }

    // int GetRowCount() const { return m_rowCount; }
};

// C_ObjectDatabaseGenerated<TBase> — auto-generated wrapper that creates
// and registers column descriptors at startup.
// Each table's registration function (the ones we extracted) is the
// static initializer for this template instantiation's descriptor array.
template<typename TBase>
class C_ObjectDatabaseGenerated : public TBase {};

// C_ObjectDatabaseSortedIdIndexed<TBase, TKey> — adds sorted array index
// for fast binary-search lookup by primary key.
template<typename TBase, typename TKey = int32_t>
class C_ObjectDatabaseSortedIdIndexed : public TBase {};

// C_ObjectDatabaseIdIndexed<TBase> — adds hash-based lookup by int32 ID.
template<typename TBase>
class C_ObjectDatabaseIdIndexed : public TBase {};

// C_ObjectDatabaseKeyIndexed<TBase> — adds key-based lookup (string or compound key).
template<typename TBase>
class C_ObjectDatabaseKeyIndexed : public TBase {};

}  // namespace wh::databasemodule
