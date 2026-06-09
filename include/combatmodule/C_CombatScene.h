#pragma once

#include <cstdint>
#include <vector>
#include "../animationmodule/I_SceneListener.h"
#include "../Offsets/vtables/IEntitySystemSink.h"

namespace wh::combatmodule {

// Forward declarations
class I_CombatActor;
class C_CombatActor;

// ---------------------------------------------------------------------------
// I_CombatScene -- pure interface for the combat scene.
//
// RTTI: .?AVI_CombatScene@combatmodule@wh@@
// vtable @ 0x1822d0668
// Scalar deleting dtor: sub_180FAA0FC (frees 8 bytes -- interface-only)
// Size: 0x08 (just a vtable pointer)
//
// vtable layout:
//   [0] scalar deleting destructor
//   [1] purecall
// ---------------------------------------------------------------------------
class I_CombatScene {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatScene;
    virtual ~I_CombatScene() = default;                                     // [0]
    // VERIFIED from sub_180FAA9F8: iterates m_actors vector, for each actor
    // calls vtable+0x40 (GetEntityId, returns uint32_t), compares with a2.
    // Matching actors are pushed into the output vector (a3).
    // a3 is a std::vector<C_CombatActor*> (pre-reserved to capacity 3).
    virtual void GetActorsByEntityId(uint32_t entityId,
                                     std::vector<C_CombatActor*>& outVec) = 0;  // [1]
};

// ---------------------------------------------------------------------------
// S_CombatSceneSubObject -- small helper object owned by C_CombatScene at +0x30.
//
// Allocated 0x10 bytes in sub_180FA962C.
// Registers a callback (sub_180FAB61C) with the animation system.
// ---------------------------------------------------------------------------
struct S_CombatSceneSubObject {
    bool        m_initialized;      // +0x00  (init 0)
    uint8_t     _pad01[7];          // +0x01
    uint64_t    m_callbackData;     // +0x08  (init 0, set via animation system registration)
};
static_assert(sizeof(S_CombatSceneSubObject) == 0x10);

// ---------------------------------------------------------------------------
// C_CombatScene -- manages active combat actors and their interactions.
//
// RTTI: .?AVC_CombatScene@combatmodule@wh@@
// Primary vtable   @ 0x1826b1cf0
// Secondary vtable @ 0x1826b1d08 (I_SceneListener, at this+0x08)
// Tertiary vtable  @ 0x1826b1d20 (IEntitySystemSink, at this+0x10)
// Constructor: sub_180FA9680
// Destructor (scalar deleting): sub_180FA9FA0 (frees 0x40)
// Size: 0x40 bytes
//
// Inheritance chain (from RTTI BaseClassArray):
//   C_CombatScene
//     I_CombatScene              (wh::combatmodule, at +0x00)
//     I_SceneListener            (wh::animationmodule, at +0x08)
//     IEntitySystemSink          (CryEngine, at +0x10)
//
// === Primary vtable layout (interfuscator-shuffled) ===
//   [0] sub_180FA9FA0  -- scalar deleting destructor (frees 0x40)
//   [1] sub_180FAA9F8  -- GetActorsByEntityId: iterates m_actors,
//                         matches by actor->GetEntityId(), collects into output vector
//
// === Secondary vtable (I_SceneListener, at +0x08) ===
//   [0] sub_180B1A4C8  -- destructor thunk (adjusts this by -0x08)
//
// === Tertiary vtable (IEntitySystemSink, at +0x10) ===
//   [0] sub_180B1A4D4  -- destructor thunk (adjusts this by -0x10)
//   ...
//   sub_180631FA8      -- OnEntityEvent: handles event types 4 and 0x2E
//                         for entity audio/combat state updates
//
// The constructor allocates 0x10 bytes for S_CombatSceneSubObject (sub_180FA962C)
// and reserves the actor vector to capacity 100 (0x64).
// ---------------------------------------------------------------------------
class C_CombatScene : public I_CombatScene,
                      public wh::animationmodule::I_SceneListener,
                      public IEntitySystemSink
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatScene;
    // ---- Virtual method overrides (I_CombatScene) ----
    ~C_CombatScene() override = default;                                    // [0]
    void GetActorsByEntityId(uint32_t entityId,
                             std::vector<C_CombatActor*>& outVec) override {}   // [1] sub_180FAA9F8

    // ---- I_SceneListener override ----
    void OnSceneChanged() override {}                                       // nop in C_CombatScene

    // ---- Data members ----
    // +0x00: vtable (I_CombatScene / C_CombatScene primary)
    // +0x08: vtable (I_SceneListener)
    // +0x10: vtable (IEntitySystemSink)
    std::vector<C_CombatActor*>     m_actors;           // +0x18  (begin/end/capacity, reserved to 100)
    S_CombatSceneSubObject*         m_pSubObject;       // +0x30  (0x10 bytes, sub_180FA962C)
    uint64_t                        m_unknown38;        // +0x38  (init 0)

    static C_CombatScene* GetInstance();              // Offsets.cpp
};
static_assert(sizeof(C_CombatScene) == 0x40, "C_CombatScene must be 0x40 bytes");

}  // namespace wh::combatmodule
