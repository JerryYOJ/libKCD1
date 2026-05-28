#pragma once

// -----------------------------------------------
// I_ItemAttachmentListener -- Warhorse interface for item attachment events
// -----------------------------------------------
// RTTI: .?AVI_ItemAttachmentListener@entitymodule@wh@@
// Pure vtable @ 0x1821bda68 (3 slots):
//   [0] sub_180F460FC  scalar deleting destructor (frees 8 bytes)
//   [1] purecall
//   [2] purecall
//
// C_Player implements at object offset +0xA00
// C_CombatActor implements at object offset +0x08
//
// C_CombatActor implementation vtable @ 0x1822293f8 (3 slots):
//   [0] sub_180B1A1A4  dtor thunk (this -= 0x08)
//   [1] sub_18054A9F4  OnItemAttached: resolves item entity, updates
//                      combat scene weapon/model state via sub_18054B2C0,
//                      sub_18054B250, sub_18054B230, sub_18054B07C
//   [2] sub_18054A904  OnItemDetached: clears weapon/model state,
//                      fires an animation event via gEnv subsystem

namespace wh::entitymodule {

class I_ItemAttachmentListener {
public:
    virtual ~I_ItemAttachmentListener() = default;                                      // [0]
    virtual void OnItemAttached(uint64_t entityId, unsigned int handSlot) = 0;          // [1] sub_18054A9F4
    virtual void OnItemDetached(uint64_t entityId, unsigned int handSlot) = 0;          // [2] sub_18054A904
};

} // namespace wh::entitymodule
