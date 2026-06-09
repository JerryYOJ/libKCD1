#pragma once

// -----------------------------------------------
// I_EquipmentManagerListener — equipment change callback
// -----------------------------------------------
// RTTI: .?AVI_EquipmentManagerListener@entitymodule@wh@@
// C_Player implements at object offset +0x9F8

namespace wh::entitymodule {

struct I_EquipmentManagerListener {
    inline static constexpr auto RTTI = Offsets::RTTI_I_EquipmentManagerListener;
    virtual ~I_EquipmentManagerListener() = default;
    virtual void OnEquipmentChanged() {}
    virtual void OnEquipmentSlotUpdated() {}
};

} // namespace wh::entitymodule
