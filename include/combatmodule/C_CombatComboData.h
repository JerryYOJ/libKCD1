#pragma once

#include <cstdint>
#include <vector>

namespace wh::combatmodule {

// Forward declaration
struct C_CombatComboData;

// ==========================================================================
// I_CombatComboData — pure interface for combo data access.
//
// vtable @ 0x1821cc0d8 (all purecall)
// RTTI: .?AVI_CombatComboData@combatmodule@wh@@
// TypeDescriptor: 0x1829fe0f8
// COL: 0x182452248
//
// Used by the combat system to query combo properties. Implemented by
// S_ComboInstance (the runtime combo tracking state) which holds a
// pointer to C_CombatComboData.
//
// S_ComboInstance vtable @ 0x1821cc0a8, layout (0x20 bytes):
//   +0x00: vtable (I_CombatComboData / S_ComboInstance)
//   +0x08: C_CombatComboData* m_comboData
//   +0x10: int32_t m_currentStep
//   +0x14: bool m_active
//   +0x18: int32_t m_damageState
//
// Virtual methods (interfuscator-shuffled):
//   [0] GetComboId()       -> **(uint32_t**)(this+8) = m_comboData->row_id
//   [1] GetComboStrid()    -> *(qword*)(this+8) + 8  = &m_comboData->combat_combo_strid
//   [2] GetCurrentStep()   -> *(uint32_t*)(this+0x10)
//   [3] GetStepCount()     -> indexes into m_comboData->m_steps vector
//   [4] ExecuteCombo()     -> complex combat execution
// ==========================================================================
class I_CombatComboData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatComboData;
    virtual int32_t GetComboId() const = 0;                     // [0]
    virtual const void* GetComboStrid() const = 0;              // [1]
    virtual int32_t GetCurrentStep() const = 0;                 // [2]
    virtual void* GetStepByIndex(int32_t index) const = 0;      // [3]
    virtual float ExecuteCombo(void* combatActor) = 0;          // [4]
};

// ==========================================================================
// I_CombatComboStepData — pure interface for combo step data access.
//
// RTTI: .?AVI_CombatComboStepData@combatmodule@wh@@
// TypeDescriptor: 0x182a11ca8
// COL: 0x18248b970
//
// Interface for querying individual combo step properties. Implemented
// directly by C_CombatComboStepData.
// ==========================================================================
class I_CombatComboStepData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatComboStepData;
    virtual int32_t GetCombatComboId() const = 0;               // [0]
    virtual int32_t GetStep() const = 0;                        // [1]
    virtual int32_t GetAtkCombatZoneId() const = 0;             // [2]
    virtual int32_t GetAttackTypeId() const = 0;                // [3]
    virtual bool HasAttackType() const = 0;                     // [4]
};

// ==========================================================================
// C_CombatComboStepData — data wrapper for a single combo step.
//
// vtable @ 0x1822cb548
// RTTI: .?AVC_CombatComboStepData@combatmodule@wh@@
// TypeDescriptor: 0x182a0cf60
// COL: 0x18248ac00
//
// Created during C_CombatComboStepDatabase::OnPostLoad (sub_180F92DE4).
// Each instance wraps one S_CombatComboStepTableRow with typed accessors.
//
// Virtual methods (at vtable 0x1822cb548):
//   [0] 0x1806f9d00: GetCombatComboId() -> return *(uint32_t*)(this + 0x0C)
//   [1] 0x1806f8b10: GetStep()          -> return *(uint32_t*)(this + 0x10)
//   [2] 0x1806f99e0: GetAtkCombatZoneId()-> return *(uint32_t*)(this + 0x18)
//   [3] 0x1806f91d0: GetAttackTypeId()  -> return *(uint32_t*)(this + 0x14)
//   [4] 0x1804e36e8: HasAttackType()    -> return *(uint32_t*)(this + 0x14) != 0xFFFFFFFF
//
// Inherits from I_CombatComboStepData (secondary vtable at offset 0x00
// since it's the primary base).
//
// Size: 0x20 bytes
// ==========================================================================
class C_CombatComboStepData : public I_CombatComboStepData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatComboStepData;
    // --- Virtual method implementations ---
    int32_t GetCombatComboId() const override { return m_combatComboId; }
    int32_t GetStep() const override { return m_step; }
    int32_t GetAtkCombatZoneId() const override { return m_atkCombatZoneId; }
    int32_t GetAttackTypeId() const override { return m_attackTypeId; }
    bool HasAttackType() const override { return m_attackTypeId != -1; }

    // +0x00: vtable (C_CombatComboStepData / I_CombatComboStepData)
    int32_t     m_rowId;                // +0x08  row base value (from _rowbase)
    int32_t     m_combatComboId;        // +0x0C  FK to combat_combo
    int32_t     m_step;                 // +0x10  step number within the combo
    int32_t     m_attackTypeId;         // +0x14  FK to combat_attack_type (-1 = none)
    int32_t     m_atkCombatZoneId;      // +0x18  FK to combat zone
    int32_t     _pad1C;                 // +0x1C  padding to 0x20
};
static_assert(sizeof(C_CombatComboStepData) == 0x20, "C_CombatComboStepData must be 0x20 bytes");

// ==========================================================================
// C_CombatComboData — data wrapper for a combat combo definition.
//
// NON-POLYMORPHIC (no vtable). Created during
// C_CombatComboDatabase::OnPostLoad (sub_180F92CE4) via sub_180F8C2B8.
//
// Each instance wraps one S_CombatComboTableRow and owns a vector of
// pointers to C_CombatComboStepData steps belonging to this combo.
//
// Constructor (sub_180F8C2B8) copies:
//   +0x00: int32 from row[0x00] (_rowbase / row_id)
//   +0x08: CryString from row[0x08] (combat_combo_strid) via CryString ctor
//   +0x10: CryString from row[0x10] (combat_combo_name) via CryString ctor
//   +0x18: int32 from row[0x18] (atk_r_weapon_class_id)
//   +0x1C: int32 from row[0x1C] (atk_l_weapon_class_id)
//   +0x20: int32 from row[0x20] (atk_r_weapon_group_id)
//   +0x24: int32 from row[0x24] (atk_l_weapon_group_id)
//   +0x28: int32 step count = (end - begin) / sizeof(ptr)
//   +0x30: vector<C_CombatComboStepData*> steps
//
// Destructor (sub_1807471D4) destroys:
//   - m_steps vector at +0x30
//   - CryString at +0x10 (m_comboName)
//   - CryString at +0x08 (m_comboStrid)
//
// Size: 0x48 bytes
// ==========================================================================
struct C_CombatComboData {
    int32_t         m_rowId;                // +0x00  row base value / combo ID
    int32_t         _pad04;                 // +0x04  alignment padding
    const char*     m_comboStrid;           // +0x08  CryStringT<char> (string ID)
    const char*     m_comboName;            // +0x10  CryStringT<char> (display name)
    int32_t         m_atkRWeaponClassId;    // +0x18  right-hand weapon class FK
    int32_t         m_atkLWeaponClassId;    // +0x1C  left-hand weapon class FK
    int32_t         m_atkRWeaponGroupId;    // +0x20  right-hand weapon group FK
    int32_t         m_atkLWeaponGroupId;    // +0x24  left-hand weapon group FK
    int32_t         m_stepCount;            // +0x28  cached count of steps
    int32_t         _pad2C;                 // +0x2C  alignment padding

    // +0x30: Vector of pointers to C_CombatComboStepData instances.
    //        Built during OnPostLoad by looking up steps that match
    //        this combo's ID. Ownership depends on the database.
    //        Accessed by S_ComboInstance::GetStepByIndex (sub_1804E36C0).
    std::vector<C_CombatComboStepData*> m_steps; // +0x30 (0x18 bytes)
};
static_assert(sizeof(C_CombatComboData) == 0x48, "C_CombatComboData must be 0x48 bytes");

// ==========================================================================
// S_ComboInstance — runtime combo tracking state.
//
// vtable @ 0x1821cc0a8
// RTTI: .?AUS_ComboInstance@combatmodule@wh@@
// TypeDescriptor: 0x1829fbd18
// COL: 0x182450588
//
// Inherits from I_CombatComboData. Created by the combat system to track
// an active combo execution for a combat actor.
//
// Size: 0x20 bytes
// ==========================================================================
class S_ComboInstance : public I_CombatComboData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_S_ComboInstance;
    int32_t GetComboId() const override { return m_comboData ? m_comboData->m_rowId : -1; }
    const void* GetComboStrid() const override { return m_comboData ? &m_comboData->m_comboStrid : nullptr; }
    int32_t GetCurrentStep() const override { return m_currentStep; }
    void* GetStepByIndex(int32_t index) const override;                 // sub_1804E36C0
    float ExecuteCombo(void* combatActor) override { return 0.0f; }     // vtable[4], stub return

    C_CombatComboData*  m_comboData;        // +0x08
    int32_t             m_currentStep;      // +0x10
    bool                m_active;           // +0x14
    uint8_t             _pad15[3];          // +0x15
    int32_t             m_comboState;       // +0x18
    int32_t             _pad1C;             // +0x1C
};
static_assert(sizeof(S_ComboInstance) == 0x20, "S_ComboInstance must be 0x20 bytes");

}  // namespace wh::combatmodule
