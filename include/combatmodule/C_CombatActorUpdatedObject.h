#pragma once

#include <cstdint>
#include "C_CombatActorObject.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActorUpdatedObject — adds frame update tick to C_CombatActorObject.
//
// RTTI: .?AVC_CombatActorUpdatedObject@combatmodule@wh@@
// Constructor: sub_180431218(this, owner, updateFlag)
// Destructor: sub_180431108
// Size: 0x18 bytes (base 0x10 + update flag + pad)
//
// If updateFlag != 0, registers with owner for per-frame Update calls.
// ---------------------------------------------------------------------------
class C_CombatActorUpdatedObject : public C_CombatActorObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorUpdatedObject;
    ~C_CombatActorUpdatedObject() override = default;
    virtual void Update(float dt) {}                        // [7]

    int32_t     m_updateFlag;       // +0x10  (nonzero = registered for updates)
    uint32_t    _pad14;             // +0x14
};
static_assert(sizeof(C_CombatActorUpdatedObject) == 0x18);

}  // namespace wh::combatmodule
