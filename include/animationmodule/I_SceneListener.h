#pragma once

// -----------------------------------------------
// I_SceneListener -- Warhorse interface for animation scene notifications
// -----------------------------------------------
// RTTI: .?AVI_SceneListener@animationmodule@wh@@
// Pure vtable @ 0x1821c77f0 (2 slots):
//   [0] sub_180F6EDF4  scalar deleting destructor (frees 8 bytes)
//   [1] purecall
//
// C_CombatScene implements at object offset +0x08
//
// C_CombatScene implementation vtable @ 0x1826b1d08 (2 slots):
//   [0] sub_180B1A4C8  dtor thunk (this -= 0x08)
//   [1] nop            OnSceneChanged (empty impl in C_CombatScene)

namespace wh::animationmodule {

class I_SceneListener {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_SceneListener;
    virtual ~I_SceneListener() = default;       // [0]
    virtual void OnSceneChanged() = 0;          // [1] UNVERIFIED name
};

} // namespace wh::animationmodule
