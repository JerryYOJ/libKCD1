#pragma once
#include "I_BuffInitParams.h"

// -----------------------------------------------
// C_ItemHealthCheckingBuffInitParams — carries soul reference + health threshold
// -----------------------------------------------
// RTTI: .?AVC_ItemHealthCheckingBuffInitParams@rpgmodule@wh@@
// vtable: 0x1821cf8c0
// Constructor: 0x18062BE80
// Size: 0x18
//
// Only subclass that overrides GetEntityRef with an actual entity reference.

namespace wh::rpgmodule {

class C_ItemHealthCheckingBuffInitParams : public I_BuffInitParams {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ItemHealthCheckingBuffInitParams;
    ~C_ItemHealthCheckingBuffInitParams() override;                                     // 0x1806ED33C
    float GetFloatParam(int nKey) override;                                             // 0x1811C0F58 key=0x103 -> m_healthParam
    int GetIntParam(int nKey) override;                                                 // 0x1803953E0 -> 0
    uint64_t* GetEntityRef(uint64_t* pOutWUID) override;                                // 0x1806FE380 -> m_soulWUID

    uint64_t    m_soulWUID;             // +0x08  soul WUID, returned by GetEntityRef
    float       m_healthParam;          // +0x10  GetFloatParam(0x103), from C_RPGParams+0x720
    uint8_t     _pad14[4];              // +0x14
};
static_assert(sizeof(C_ItemHealthCheckingBuffInitParams) == 0x18);

}  // namespace wh::rpgmodule
