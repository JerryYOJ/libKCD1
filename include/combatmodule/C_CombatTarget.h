#pragma once

#include <cstdint>
#include "I_CombatTarget.h"

namespace Offsets { struct IEntity; }

namespace wh::combatmodule {

class C_CombatActor;

// ---------------------------------------------------------------------------
// C_CombatTarget — concrete I_CombatTarget that wraps a CryEngine IEntity*.
//
// RTTI: .?AVC_CombatTarget@combatmodule@wh@@
// vtable @ 0x1822075A0
// Allocated (0x10) from the combat-target pool by sub_1806DA5C8 / sub_1806DA544.
// Scalar-deleting dtor: sub_1806EA35C.  Size: 0x10.
//
// Every override forwards to the wrapped entity (m_pActor) via its IEntity
// vtable. The implementations and the IEntity slots they call:
//   [1] GetActor          sub_1806F8130 : return m_pActor
//   [2] GetEntityId       sub_1804ACC24 : m_pActor->GetId()          [IEntity vt[1]]
//   [3] GetPosition       sub_180455F00 : m_pActor->GetPos()         [IEntity vt[0x2B]]
//   [4] GetWorldRotation  sub_180F52458 : m_pActor->GetWorldRotation [IEntity vt[0x2D]]
//   [5] LookupEntity      sub_18045760C : ActorSystem(GameCtx+0x128).vt[3](GetEntityId())
//   [6] GetCombatActor    sub_180455F20 : LookupEntity() ? *(+0x1A0) : nullptr (combat actor)
//   [7] IsSameTarget      sub_180F50BF0 : m_pActor == other->GetActor()
// ---------------------------------------------------------------------------
class C_CombatTarget : public I_CombatTarget {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatTarget;

    ~C_CombatTarget() override = default;                                    // [0] sub_1806EA35C
    Offsets::IEntity* GetActor() const override { return m_pActor; }         // [1] sub_1806F8130
    EntityId GetEntityId() const override { return {}; }                     // [2] sub_1804ACC24
    Vec3 GetPosition() const override { return {}; }                        // [3] sub_180455F00
    Quat GetWorldRotation() const override { return {}; }                   // [4] sub_180F52458
    void* LookupEntity() const override { return nullptr; }                 // [5] sub_18045760C
    C_CombatActor* GetCombatActor() const override { return nullptr; }      // [6] sub_180455F20
    bool IsSameTarget(const I_CombatTarget* other) const override           // [7] sub_180F50BF0
    { return false; }

    Offsets::IEntity* m_pActor;     // +0x08  wrapped target entity (CryEngine IEntity)
};
static_assert(sizeof(C_CombatTarget) == 0x10);

}  // namespace wh::combatmodule
