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
