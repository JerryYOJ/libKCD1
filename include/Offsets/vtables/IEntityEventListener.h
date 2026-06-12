#pragma once
#include <cstdint>

// -----------------------------------------------
// IEntityEventListener -- Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine/CryCommon/IEntitySystem.h
// RTTI: .?AUIEntityEventListener@@
// SDK order (pre-shuffle):
//   ~dtor, OnEntityEvent
//
// Binary vtable for C_CombatActor at 0x182229418 (2 slots):
//   [0] sub_180B1A1B0  ~C_CombatActor() thunk (this -= 0x10)
//   [1] sub_180F4A780  OnEntityEvent: handles entity event type 4

// NOTE (style-review follow-up 2026-06-12): this header defines TWO types —
// the global-namespace stub below (used by combatmodule/C_CombatActor.h) and
// Offsets::IEntityEventListener. The global one collides by name with the
// real SDK struct in CryCommon/IEntitySystem.h:345 (ODR risk if both headers
// ever appear in one TU — currently they don't). Migrating C_CombatActor.h to
// the Offsets:: type and deleting the stub is the clean fix; deferred to a
// combatmodule pass.

// Inheritance-compatible base (just a vtable pointer for sizeof correctness).
struct IEntityEventListener {
    virtual ~IEntityEventListener() = default;                           // [0]
    virtual void OnEntityEvent(void* pEntity, void* event) {}            // [1]
};

namespace Offsets {

struct IEntityEventListener {
    virtual void Dtor(char flags) = 0;                           // [0] 0x00
    virtual void OnEntityEvent(void* pEntity, void* event) = 0;  // [1] 0x08  sub_180F4A780
};

}  // namespace Offsets
