#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include "../databasemodule/C_ObjectTableDatabase.h"

namespace wh::animationmodule {

// ==========================================================================
// C_AnimationDatabaseBase<TData, TRow, TBase>
//
// Template base for animation databases. Extends C_ObjectTableDatabase
// (or a wrapped variant) with animation-specific data management:
//   - Maintains a vector of TData entries (loaded from table rows)
//   - Stores table name and module name strings for animation system lookup
//   - Tracks animation data loading state
//
// TData = the C_*Data wrapper class (e.g. C_CombatComboData)
// TRow  = the S_*TableRow POD struct
// TBase = the database base type (typically C_ObjectTableDatabase<TData, TRow>
//         or a wrapped variant like C_ObjectDatabaseGenerated<...>)
//
// RTTI pattern:
//   .?AV?$C_AnimationDatabaseBase@V<TData>@<module>@wh@@U<TRow>@23@
//       V?$C_ObjectTableDatabase@...@databasemodule@3@@animationmodule@wh@@
//
// Constructor pattern (from 0x180F87668 for Combo variant):
//   1. Calls TBase constructor (C_ObjectDatabaseBase ctor at sub_180F3684C)
//   2. Zero-initializes m_dataEntries vector at +0x90
//   3. Initializes two MSVC SSO strings at +0xB0 and +0xD0 (empty)
//   4. Clears m_animVersion and m_animDataReady flags
//
// Vtable slot differences from C_ObjectDatabaseBase (interfuscator-shuffled):
//   [1] GetVersion: returns version constant (5 for Indexed, 2 for others)
//   [3] OnPostLoad: loads animation data from the animation system
//   [5] GetRowByIndex: returns m_animDataReady flag at +0xF4
//   [7] GetRowId/Load: creates TData entries from rows
//   [16] SetColumnMetadata: stores version at +0xF0
//
// Size (this layer only): 0xF8 bytes
// ==========================================================================
template<typename TData, typename TRow, typename TBase = databasemodule::C_ObjectTableDatabase<TData, TRow>>
class C_AnimationDatabaseBase : public TBase {
public:
    // --- Fields added by C_AnimationDatabaseBase ---

    // +0x90: Data entries created during OnPostLoad/Load.
    //        Each element is a TData instance wrapping row data with
    //        typed accessors and FK resolution.
    //        Element size depends on TData (e.g. 0x48 for C_CombatComboData,
    //        0x20 for C_CombatComboStepData).
    std::vector<TData>  m_dataEntries;          // +0x90  (0x18 bytes: begin/end/cap)

    uint8_t             _padA8[8];              // +0xA8  (alignment padding)

    // +0xB0: Table name string, e.g. "combat_combo".
    //        Used for animation system lookup and database identification.
    //        Initialized empty, then filled by C_CombatDatabase constructor
    //        from its constructor parameters.
    //        MSVC SSO layout: buf[16] + size(8) + capacity(8) = 0x20 bytes
    std::string         m_tableName;            // +0xB0  (0x20 bytes)

    // +0xD0: Module name string, e.g. "combat".
    //        Identifies which game module owns this database for the
    //        animation system's module-based lookup.
    std::string         m_moduleName;           // +0xD0  (0x20 bytes)

    // +0xF0: Version/flags for the animation data loader.
    //        Set via vtable[16] (SetColumnMetadata equivalent), read by
    //        vtable[5] (GetRowByIndex) to check load state.
    int32_t             m_animVersion;          // +0xF0

    // +0xF4: Set to 1 after animation data has been successfully loaded.
    //        Checked by vtable[10] (GetSelf) as: return m_animDataReady == a2
    bool                m_animDataReady;        // +0xF4

    uint8_t             _padF5[3];              // +0xF5
};

// ==========================================================================
// C_AnimationDatabaseStatic<TData, TRow>
//
// Static variant of animation database. Used for databases that load
// their animation data once at startup and don't support hot-reload
// of individual entries (no per-item hash index).
//
// Does NOT add any fields beyond C_AnimationDatabaseBase.
// Overrides OnPostLoad (vtable[3]) to perform one-time animation data
// binding using the animation system's static registration API.
//
// RTTI pattern:
//   .?AV?$C_AnimationDatabaseStatic@V<TData>@<module>@wh@@U<TRow>@23@
//       @animationmodule@wh@@
//
// Used in: C_CombatComboStepDatabase, C_PerkComboStepDatabase
// Size: 0xF8 bytes (same as AnimationDatabaseBase)
// ==========================================================================
template<typename TData, typename TRow>
class C_AnimationDatabaseStatic
    : public C_AnimationDatabaseBase<TData, TRow, databasemodule::C_ObjectTableDatabase<TData, TRow>> {
public:
    // No additional fields.
};

// ==========================================================================
// C_AnimationDatabaseStaticIndexed<TData, TRow>
//
// Indexed variant of the static animation database. Adds a hash map
// for O(1) lookup of data entries by key, plus callback vectors for
// notifying listeners when data changes or individual items are updated.
//
// RTTI pattern:
//   .?AV?$C_AnimationDatabaseStaticIndexed@V<TData>@<module>@wh@@
//       U<TRow>@23@@animationmodule@wh@@
//
// Constructor (from 0x180F87668 for Combo variant):
//   1. Calls C_AnimationDatabaseBase constructor (sets up through +0xF7)
//   2. Sets AnimationDatabaseStaticIndexed vtable
//   3. Allocates hash map (sub_180E1CEE8 -> 0x68 bytes, CryHashMap head)
//   4. Registers lambda callbacks into m_onReloadCallbacks and
//      m_onItemCallbacks vectors
//
// Vtable slot differences from C_AnimationDatabaseStatic:
//   [1] GetVersion: returns 5 (vs 2 for non-indexed)
//   [12] GetSelf2: performs indexed rebuild (maps data by key, fires callbacks)
//
// Size: 0x148 bytes
// ==========================================================================
template<typename TData, typename TRow>
class C_AnimationDatabaseStaticIndexed
    : public C_AnimationDatabaseBase<TData, TRow, databasemodule::C_ObjectTableDatabase<TData, TRow>> {
public:

    // +0xF8: Hash map for key-based lookup of TData entries.
    //        Allocated via sub_180E1CEE8 (0x68-byte CryHashMap head node).
    //        Allows O(1) lookup by primary key (e.g. combat_combo_id).
    void*               m_hashMap;              // +0xF8

    // +0x100: Secondary hash map or extra index state.
    //         Initialized to 0 in constructor.
    void*               m_hashMapExtra;         // +0x100

    // +0x108: Vector of callbacks invoked when an individual TData item
    //         is updated. Each element is a std::function<void(const TData&)>
    //         (0x40 bytes in MSVC).
    //         Registered by the constructor with a lambda that captures
    //         a reference to this database.
    std::vector<std::function<void(const TData&)>> m_onItemCallbacks; // +0x108 (0x18)

    // +0x120: Vector of callbacks invoked on full database reload.
    //         Each element is a std::function<void()> (0x40 bytes in MSVC).
    //         Registered by the constructor with a lambda that triggers
    //         rebuild of the hash index.
    std::vector<std::function<void()>> m_onReloadCallbacks;   // +0x120 (0x18)

    // +0x138: Listener set for external subscribers (tree/map node).
    //         Allocated via sub_180732120 (0x30-byte node).
    //         Used by the Validate method (vtable[12]) to dispatch
    //         item change notifications to registered listeners.
    void*               m_listenerSet;          // +0x138

    // +0x140: Reserved/extra state for listener management.
    //         Initialized to 0.
    void*               m_listenerExtra;        // +0x140
};

}  // namespace wh::animationmodule
