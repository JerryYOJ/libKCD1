#pragma once
#include "I_BuffInitParams.h"

// -----------------------------------------------
// C_BuffInitParamsDefault — no-op defaults for all params
// -----------------------------------------------
// RTTI: .?AVC_BuffInitParamsDefault@rpgmodule@wh@@
// vtable: 0x1821ad0e8
// Size: 0x08

namespace wh::rpgmodule {

class C_BuffInitParamsDefault : public I_BuffInitParams {
public:
    ~C_BuffInitParamsDefault() override;                                                // 0x181099090
    float GetFloatParam(int nKey) override;                                             // 0x1806F8E90 -> 0.0f
    int GetIntParam(int nKey) override;                                                 // 0x1803953E0 -> 0
    uint64_t* GetEntityRef(uint64_t* pOutWUID) override;                                // 0x1806FE160 -> 0xFFFFFFFFFFFFFFFF
};
static_assert(sizeof(C_BuffInitParamsDefault) == 0x08);

}  // namespace wh::rpgmodule
