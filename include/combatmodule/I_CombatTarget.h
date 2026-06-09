#pragma once

#include <cstdint>

namespace wh::combatmodule {

class I_CombatActor;

// ---------------------------------------------------------------------------
// I_CombatTarget — interface for a combat target reference.
//
// RTTI: .?AVI_CombatTarget@combatmodule@wh@@
// vtable @ 0x182217AA8 (pure interface, all purecall except [0])
// Size: 0x08 (just a vtable pointer)
//
// Provides a uniform interface to query a target's position, entity,
// and identity without knowing whether the target is a player, NPC, or
// dummy object.
//
// vtable layout (interfuscator-shuffled, 8 slots):
//   [0] sub_180F505A0  scalar deleting destructor
//   [1] purecall       GetActor / GetWrappedPtr
//   [2] purecall       GetEntityId
//   [3] purecall       GetPosition (via actor vtable[0x2B])
//   [4] purecall       GetWeaponPosition (via actor vtable[0x2D])
//   [5] purecall       LookupEntity (GetEntityId → actor system lookup)
//   [6] purecall       GetWorldPosition (LookupEntity → result+0x1A0)
//   [7] purecall       IsSameTarget (compares wrapped ptrs)
// ---------------------------------------------------------------------------
class I_CombatTarget {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatTarget;
    virtual ~I_CombatTarget() = default;                // [0]
    virtual void* GetActor() const = 0;                 // [1] returns *(this+0x08)
    virtual uint32_t GetEntityId() const = 0;           // [2] calls wrapped->vtable[1]
    virtual void GetPosition(void* outVec) const = 0;   // [3] calls wrapped->vtable[0x2B]
    virtual void GetWeaponPosition(void* outVec) const = 0; // [4] calls wrapped->vtable[0x2D]
    virtual void* LookupEntity() const = 0;             // [5] entity system lookup by ID
    virtual void* GetWorldPosition() const = 0;         // [6] LookupEntity()->+0x1A0
    virtual bool IsSameTarget(const I_CombatTarget* other) const = 0; // [7] compares actors
};

// ---------------------------------------------------------------------------
// C_CombatTarget — concrete target wrapper around a combat actor pointer.
//
// RTTI: .?AVC_CombatTarget@combatmodule@wh@@
// vtable @ 0x1822075A0
// Destructor: sub_1806EA35C (frees 0x10)
// Size: 0x10 bytes
//
// All vtable methods delegate to the wrapped pointer at +0x08.
// ---------------------------------------------------------------------------
class C_CombatTarget : public I_CombatTarget {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatTarget;
    ~C_CombatTarget() override = default;
    void* GetActor() const override { return m_pActor; }
    uint32_t GetEntityId() const override { return 0; }
    void GetPosition(void* outVec) const override {}
    void GetWeaponPosition(void* outVec) const override {}
    void* LookupEntity() const override { return nullptr; }
    void* GetWorldPosition() const override { return nullptr; }
    bool IsSameTarget(const I_CombatTarget* other) const override { return false; }

    void* m_pActor;     // +0x08  wrapped actor / entity pointer
};
static_assert(sizeof(C_CombatTarget) == 0x10);

}  // namespace wh::combatmodule
