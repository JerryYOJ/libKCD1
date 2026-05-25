#pragma once
#include <cstdint>

// -----------------------------------------------
// IEntitySystemSink -- Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine/CryCommon/IEntitySystem.h
// RTTI: .?AUIEntitySystemSink@@
// SDK order (pre-shuffle):
//   ~dtor, OnBeforeSpawn, OnSpawn, OnRemove, OnReused, OnEvent, GetMemoryUsage
//
// Binary vtable for C_CombatScene at 0x1826b1d20 (7 slots):
//   [0] sub_180B1A4D4  ~C_CombatScene() thunk (this -= 0x10)
//   [1] sub_1806F8140  returns 1 (bool) -- OnBeforeSpawn or OnRemove
//   [2] nop            -- empty impl
//   [3] sub_1806F8140  returns 1 (bool) -- OnBeforeSpawn or OnRemove
//   [4] nop            -- empty impl
//   [5] sub_180631FA8  OnEvent: handles entity event types 4 and 0x2E
//   [6] nop            -- GetMemoryUsage (default empty impl)

// Inheritance-compatible base (just a vtable pointer for sizeof correctness).
struct IEntitySystemSink {
    virtual ~IEntitySystemSink() = default;   // [0]
    virtual void _iessSink_1() {}             // [1]
    virtual void _iessSink_2() {}             // [2]
    virtual void _iessSink_3() {}             // [3]
    virtual void _iessSink_4() {}             // [4]
    virtual void _iessSink_5() {}             // [5]
    virtual void _iessSink_6() {}             // [6]
};

namespace Offsets {

struct IEntitySystemSink {
    virtual void Dtor(char flags) = 0;               // [0] 0x00
    virtual void _vf1() = 0;                         // [1] 0x08  returns 1 (bool)
    virtual void _vf2() = 0;                         // [2] 0x10  nop
    virtual void _vf3() = 0;                         // [3] 0x18  returns 1 (bool)
    virtual void _vf4() = 0;                         // [4] 0x20  nop
    virtual void OnEvent(void* pEntity, void* event) = 0;  // [5] 0x28  sub_180631FA8
    virtual void _vf6() = 0;                         // [6] 0x30  nop (GetMemoryUsage)
};

}  // namespace Offsets
