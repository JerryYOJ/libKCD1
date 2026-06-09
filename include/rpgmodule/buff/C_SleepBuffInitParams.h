#pragma once
#include "I_BuffInitParams.h"

// -----------------------------------------------
// C_SleepBuffInitParams — carries sleep quality/duration data
// -----------------------------------------------
// RTTI: .?AVC_SleepBuffInitParams@rpgmodule@wh@@
// vtable: 0x1821b2f50
// Size: 0x10

namespace wh::rpgmodule {

class C_SleepBuffInitParams : public I_BuffInitParams {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SleepBuffInitParams;
    ~C_SleepBuffInitParams() override;                                                  // 0x180568690
    float GetFloatParam(int nKey) override;                                             // 0x1802AD5F0 key=0 -> m_sleepParam0, key=1 -> m_sleepParam1
    int GetIntParam(int nKey) override;                                                 // 0x1803953E0 -> 0
    uint64_t* GetEntityRef(uint64_t* pOutWUID) override;                                // 0x1806FE160 -> invalid

    float       m_sleepParam0;          // +0x08  GetFloatParam(0)
    float       m_sleepParam1;          // +0x0C  GetFloatParam(1)
};
static_assert(sizeof(C_SleepBuffInitParams) == 0x10);

}  // namespace wh::rpgmodule
