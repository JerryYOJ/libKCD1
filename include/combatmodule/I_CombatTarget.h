#pragma once

#include <cstdint>

namespace Offsets { struct IEntity; }

namespace wh::combatmodule {

class C_CombatActor;

// ---------------------------------------------------------------------------
// I_CombatTarget — interface for a combat target reference.
//
// RTTI: .?AVI_CombatTarget@combatmodule@wh@@
// vtable @ 0x182217AA8 (pure interface: [0] is a scalar-deleting dtor,
//          [1..7] are purecall)
// Size: 0x08 (just a vtable pointer)
//
// A uniform handle to a combat target. The sole concrete implementation,
// C_CombatTarget (see C_CombatTarget.h), wraps a CryEngine IEntity* and
// forwards every query to that entity's IEntity vtable.
//
// Slot semantics were re-verified against C_CombatTarget's implementations
// and the wrapped IEntity vtable (CEntity @ 0x1821A54C8):
//   IEntity::GetId           = vt[1]    (returns *(entity+0x0C))
//   IEntity::GetPos          = vt[0x2B] (Vec3,  sub_18033C610)
//   IEntity::GetWorldRotation= vt[0x2D] (Quat,  sub_18033E548)  <-- a rotation
//
// NOTE: slot [4] was previously mis-RE'd as "GetWeaponPosition". Its
// implementation (C_CombatTarget::GetWorldRotation_180F52458) forwards to the
// entity's vt[0x2D], which builds a quaternion from the world matrix — i.e. it
// returns a rotation (Quat), not a weapon position. Renamed accordingly.
// ---------------------------------------------------------------------------
class I_CombatTarget {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatTarget;

    virtual ~I_CombatTarget() = default;                            // [0]

    // Returns the wrapped target entity (C_CombatTarget::m_pActor).
    virtual Offsets::IEntity* GetActor() const = 0;                 // [1]

    // Entity id of the wrapped entity (IEntity::GetId == *(entity+0x0C)).
    virtual EntityId GetEntityId() const = 0;                       // [2]

    // World position of the wrapped entity (IEntity::GetPos, vt[0x2B]).
    virtual Vec3 GetPosition() const = 0;                           // [3]

    // World rotation of the wrapped entity (IEntity::GetWorldRotation,
    // vt[0x2D]). Was mis-RE'd as "GetWeaponPosition" — it returns a Quat.
    virtual Quat GetWorldRotation() const = 0;                      // [4]

    // Resolves the wrapped entity to its actor object via the actor system
    // (S_GameContext+0x128, vtbl[3], keyed by GetEntityId()). Returns the
    // actor/soul object (its world position lives at +0x1A0). Null if missing.
    virtual void* LookupEntity() const = 0;                         // [5]

    // The wrapped entity's combat actor: *(LookupEntity()+0x1A0), or null.
    // (UpdateOpponent feeds this into S_CombatActorState::m_pOpponent.)
    virtual C_CombatActor* GetCombatActor() const = 0;             // [6]

    // True iff this and other wrap the same entity (GetActor() identity).
    virtual bool IsSameTarget(const I_CombatTarget* other) const = 0; // [7]
};

}  // namespace wh::combatmodule
