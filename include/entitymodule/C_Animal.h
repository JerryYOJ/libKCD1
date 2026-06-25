#pragma once

#include <cstdint>
#include "C_Actor.h"

struct IPhysicalEntity;   // CryEngine SDK (CryPhysics)

// -----------------------------------------------
// C_Animal — base class for animal actors (horse, dog, …)
// -----------------------------------------------
// RTTI: .?AVC_Animal@entitymodule@wh@@   (C_Animal : C_Actor : CGameObjectExtensionHelper<…> : IActor : …)
// Constructor: 0x181016AF0  |  Destructor: 0x18101790C / 0x181017EB4 (scalar-deleting)
// vtables at +0x00 / +0x40 / +0x48 (inherited IActor / IGameObjectView / IGameObjectProfileManager).
// Own fields: +0x930 (= sizeof C_Actor) .. +0x958.  Concrete animals begin at +0x958
// (verified: C_Dog ctor 0x18103DD18 and C_Horse ctor 0x181056468 both write their first
//  own field at +0x958). Abstract — only instantiated through subclasses.
// ============================================================================

namespace wh::entitymodule {

class C_Animal : public C_Actor {
public:
    int32_t   m_animalId;        // +0x930  init 0xFFFFFFFF; fed to the character/skeleton system
    int32_t   m_unk934;          // +0x934
    int32_t   m_unk938;          // +0x938
    int32_t   m_unk93C;          // +0x93C
    uint32_t  m_animalFlags;     // +0x940  init 0x00A00000
    int32_t   m_unk944;          // +0x944
    IPhysicalEntity* m_pNeckPhysics; // +0x948  phys entity the horse attaches procedural neck-mass +
                                     //         collision-capsule geometry to (C_Horse::sub_18105918C).
                                     //         CONFLICT: also driven via vtbl+0x20 (action-descriptor) path.
    int32_t   m_unk950;          // +0x950
    int32_t   m_unk954;          // +0x954
};
static_assert(sizeof(C_Animal) == 0x958);

} // namespace wh::entitymodule
