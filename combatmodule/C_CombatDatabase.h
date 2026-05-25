#pragma once

#include <cstdint>

#include "../animationmodule/C_AnimationDatabase.h"
#include "../databasemodule/tables/S_CombatComboTableRow.h"
#include "../databasemodule/tables/S_CombatComboStepTableRow.h"
#include "C_CombatComboData.h"

namespace wh::combatmodule {

// ==========================================================================
// C_CombatDatabase<TAnimDB> — combat-specific database template.
//
// Extends an animation database (TAnimDB) with combat system integration.
// Adds a listener set for combat system callbacks and copies the table
// name and module name from constructor parameters into the inherited
// string fields.
//
// Template parameter TAnimDB is one of:
//   - C_AnimationDatabaseStaticIndexed<TData, TRow> (for indexed databases)
//   - C_AnimationDatabaseStatic<TData, TRow> (for non-indexed databases)
//
// RTTI pattern (Combo variant):
//   .?AV?$C_CombatDatabase@V?$C_AnimationDatabaseStaticIndexed@
//       VC_CombatComboData@combatmodule@wh@@US_CombatComboTableRow@23@
//       @animationmodule@wh@@@combatmodule@wh@@
//
// Constructor pattern (from sub_18071DE84 for CombatComboDatabase):
//   1. Calls TAnimDB constructor (AnimationDatabaseStaticIndexed ctor)
//   2. Sets C_CombatDatabase vtable
//   3. Copies table name and module name from params into m_tableName/m_moduleName
//   4. Allocates listener set (sub_180732120, 0x30-byte node) at +0x148
//   5. Sets C_CombatComboDatabase vtable (leaf class)
//   6. Registers listeners for rebuild notifications
//
// Vtable (Combo variant) @ 0x1822cb6a8 (18 entries):
//   [0] 0x180f8d598 dtor (scalar deleting)
//   [1] 0x1806f82c0 GetVersion() -> returns 2
//   [2] 0x180f74110 Load()
//   [3] 0x180f906fc OnPostLoad() (creates TData entries from rows)
//   [4] 0x1802e39b0 nop (GetRowCount placeholder)
//   [5] 0x1806fbeb0 GetRowByIndex() -> return *(uint8_t*)(this + 0xF4)
//   [6] 0x180f7bd10 GetRowData() (animation data loader)
//   [7] 0x180f92ce4 GetRowId() (Combo: creates C_CombatComboData entries)
//   [8] 0x180434c90 GetRowExtra() -> return 0
//   [9] 0x1802e39b0 Rebuild() -> nop (overridden by leaf classes)
//  [10] 0x180f7b924 GetSelf() -> return m_animDataReady == arg
//  [11] 0x180f7f170 Validate() (animation system validation)
//  [12] 0x180f9118c GetSelf2() (indexed: rebuild map + fire callbacks)
//  [13] 0x1802e39b0 Register() -> nop
//  [14] 0x180f3722c GetTableName() -> signal at +0x30
//  [15] 0x180f37220 GetColumnMetadata() -> signal at +0x60
//  [16] 0x1806fbea0 SetColumnMetadata() -> *(int*)(this+0xF0) = arg
//  [17] 0x1806f8140 NotifyListeners() -> return 1
//
// NOTE: vtable slots are interfuscator-shuffled. The slot indices do NOT
// match I_ObjectDatabase's logical ordering. The labels above reflect
// inherited base class slot names for positional reference only.
// ==========================================================================
template<typename TAnimDB>
class C_CombatDatabase : public TAnimDB {
public:
    // --- Fields added by C_CombatDatabase ---
    // Offset depends on TAnimDB:
    //   If TAnimDB = AnimDBStaticIndexed<TData,TRow>: fields start at +0x148
    //   If TAnimDB = AnimDBStatic<TData,TRow>: fields start at +0xF8
    //
    // For the Combo variant (AnimDBStaticIndexed, base size 0x148):
    //   +0x148: void* m_combatListenerSet
    //   +0x150: void* m_combatListenerExtra
    //
    // For the ComboStep variant (AnimDBStatic, base size 0xF8):
    //   No additional fields from C_CombatDatabase itself
    //   (the concrete leaf class C_CombatComboStepDatabase adds its own)
};

// ==========================================================================
// C_CombatComboDatabase — concrete database for combat combos.
//
// Singleton instance at: 0x18359B960
// vtable @ 0x1822cb740
// RTTI: .?AVC_CombatComboDatabase@combatmodule@wh@@
// TypeDescriptor: 0x182a0d000
// COL: 0x18248abd8
//
// Constructor: sub_18071DE84
// Table: "combat_combo" (S_CombatComboTableRow, row_size=40)
//
// Inheritance chain:
//   C_CombatComboDatabase
//     : C_CombatDatabase<C_AnimationDatabaseStaticIndexed<C_CombatComboData, S_CombatComboTableRow>>
//       : C_AnimationDatabaseStaticIndexed<C_CombatComboData, S_CombatComboTableRow>
//         : C_AnimationDatabaseBase<C_CombatComboData, S_CombatComboTableRow, C_ObjectTableDatabase<...>>
//           : C_ObjectTableDatabase<C_CombatComboData, S_CombatComboTableRow>
//             : C_ObjectDatabaseBase
//               : I_ObjectDatabase
//
// Vtable differences from C_CombatDatabase:
//   [0] 0x180f8de84 dtor (C_CombatComboDatabase-specific cleanup)
//   [9] 0x180f8e514 Rebuild: pushes this pointer into a listener vector
//       (registers the database as a rebuild subscriber)
//
// OnPostLoad (vtable[7], sub_180F92CE4):
//   For each table row (stride 0x28 = sizeof(S_CombatComboTableRow)):
//     1. Creates C_CombatComboData (0x48 bytes) via sub_180F8C2B8
//        - Copies row fields (id, strid, name, weapon class/group IDs)
//        - Resolves step references into m_steps vector
//     2. Pushes the TData into m_dataEntries vector
//   Then rebuilds the hash index and fires item callbacks
//
// Size: 0x158 bytes
//   C_ObjectDatabaseBase: 0x90
//   + C_AnimationDatabaseBase: 0x68 -> 0xF8
//   + C_AnimationDatabaseStaticIndexed: 0x50 -> 0x148
//   + C_CombatDatabase: 0x10 -> 0x158
//   + C_CombatComboDatabase: 0x00 (no extra fields)
// ==========================================================================
class C_CombatComboDatabase
    : public C_CombatDatabase<
        animationmodule::C_AnimationDatabaseStaticIndexed<
            C_CombatComboData,
            databasemodule::S_CombatComboTableRow>> {
public:

    // +0x148: Listener set for combat system rebuild notifications.
    //         Allocated via sub_180732120 (0x30-byte tree node).
    //         Used by Rebuild (vtable[9]) to register this database
    //         as a subscriber for combat system events.
    void*           m_combatListenerSet;        // +0x148

    // +0x150: Extra listener state, initialized to 0.
    void*           m_combatListenerExtra;      // +0x150
};
// VERIFIED: size 0x158 confirmed from constructor sub_18071DE84.
// Singleton at 0x18359B960. Last field written is +0x150 (qword), total = 0x158.

// ==========================================================================
// C_CombatComboStepDatabase — concrete database for combat combo steps.
//
// Singleton instance at: 0x18359BAC0
// vtable @ 0x1822cb578
// RTTI: .?AVC_CombatComboStepDatabase@combatmodule@wh@@
// TypeDescriptor: 0x182a0cc40
// COL: 0x18248ac50
//
// Constructor: sub_18071DFC8
// Table: "combat_combo_step" (S_CombatComboStepTableRow, row_size=20)
//
// Inheritance chain:
//   C_CombatComboStepDatabase
//     : C_CombatDatabase<C_AnimationDatabaseStatic<C_CombatComboStepData, S_CombatComboStepTableRow>>
//       : C_AnimationDatabaseStatic<C_CombatComboStepData, S_CombatComboStepTableRow>
//         : C_AnimationDatabaseBase<C_CombatComboStepData, S_CombatComboStepTableRow, ...>
//           : C_ObjectTableDatabase<C_CombatComboStepData, S_CombatComboStepTableRow>
//             : C_ObjectDatabaseBase
//               : I_ObjectDatabase
//
// Vtable @ 0x1822cb578 (18 entries):
//   [0] 0x180f8def0 dtor
//   [1] 0x1806f82c0 GetVersion() -> returns 2
//   [3] 0x180f907f0 OnPostLoad() (ComboStep variant)
//   [7] 0x180f92de4 Load/GetRowId() (creates C_CombatComboStepData entries inline)
//   [12] 0x180f91ab4 GetSelf2() (rebuilds step-to-combo mapping)
//
// OnPostLoad (vtable[7], sub_180F92DE4):
//   For each table row (stride 0x14 = sizeof(S_CombatComboStepTableRow)):
//     Creates C_CombatComboStepData (0x20 bytes) inline:
//       +0x00: vtable = C_CombatComboStepData::vftable
//       +0x08: row[0] (_rowbase)
//       +0x0C: row[1] (combat_combo_id)
//       +0x10: row[2] (step)
//       +0x14: row[4] (attack_type_id) -- NOTE: field order differs from row
//       +0x18: row[3] (atk_combat_zone_id)
//     Pushes into m_dataEntries vector
//
// C_CombatComboStepDatabase adds its own fields beyond C_CombatDatabase:
//   +0xF8: float m_comboScale = 1.0f (0x3F800000)
//   +0x100: void* m_stepGroupMap (allocated via sub_18072B504)
//   +0x108-0x110: secondary map/extra state
//   +0x110-0x120: additional vector/state
//   +0x120: extra qword
//
// Size: 0x128 bytes
//   C_ObjectDatabaseBase: 0x90
//   + C_AnimationDatabaseBase: 0x68 -> 0xF8
//   + C_CombatDatabase (AnimStatic variant): 0x00 -> 0xF8
//   + C_CombatComboStepDatabase: 0x30 -> 0x128
// ==========================================================================
class C_CombatComboStepDatabase
    : public C_CombatDatabase<
        animationmodule::C_AnimationDatabaseStatic<
            C_CombatComboStepData,
            databasemodule::S_CombatComboStepTableRow>> {
public:

    // +0xF8: Combo damage/speed scale factor.
    //        Initialized to 1.0f (0x3F800000) in constructor.
    //        Registered as a tunable parameter via sub_18071265C.
    float           m_comboScale;               // +0xF8
    uint8_t         _padFC[4];                  // +0xFC  alignment

    // +0x100: Step group map. Groups steps by combat_combo_id for fast
    //         lookup. Allocated via sub_18072B504 (0x30-byte node).
    //         Maps combo_id -> vector<C_CombatComboStepData*>.
    void*           m_stepGroupMap;             // +0x100

    // +0x108: Extra state for step group map.
    void*           m_stepGroupMapExtra;        // +0x108

    // +0x110: Additional state. VERIFIED from constructor sub_18071DFC8:
    //         xmmword at +0x110 is zeroed (two qwords).
    uint64_t        m_extraState[2];            // +0x110 (16 bytes)

    // +0x120: Reserved extra state. VERIFIED: qword at +0x120 = 0.
    uint64_t        m_reserved120;              // +0x120
};
// VERIFIED: size 0x128 confirmed from constructor sub_18071DFC8.
// Singleton at 0x18359BAC0. Last written field is +0x120 (qword), total = 0x128.

}  // namespace wh::combatmodule
