#pragma once

#include "C_EquippableItemRuntimeData.h"

// ===========================================================================
// wh::entitymodule::C_ConsumableRuntimeData  -  per-instance consumable runtime
//                                                state (concrete equippable leaf).
//   vtable 0x1821cf790. [own fields past +0xA8 UNVERIFIED — RE on demand.]
// ===========================================================================

namespace wh { namespace entitymodule {

class C_ConsumableRuntimeData : public C_EquippableItemRuntimeData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ConsumableRuntimeData;
    I_ItemRuntimeData* Clone() override;    // slot0 (per-class deep-copy)
    // own per-instance fields (consumable state, ...) start at +0xA8 [UNVERIFIED]
};

}} // namespace wh::entitymodule
