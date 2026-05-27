#pragma once
#include "I_BuffInitParams.h"

// -----------------------------------------------
// C_InjuredBuffInitParams — carries injury severity data
// -----------------------------------------------
// RTTI: .?AVC_InjuredBuffInitParams@rpgmodule@wh@@
// vtable: 0x1821a6d68
// Constructor: 0x18030DDA4
// Size: 0x18

namespace wh::rpgmodule {

class C_InjuredBuffInitParams : public I_BuffInitParams {
public:
    ~C_InjuredBuffInitParams() override;                                                // 0x1806ED33C
    float GetFloatParam(int nKey) override;                                             // 0x1806CD564 key=0 -> m_injuryAmount
    int GetIntParam(int nKey) override;                                                 // 0x1806CD54C key=1 -> m_injuryIntParam, key=2 -> m_injuryFlag
    uint64_t* GetEntityRef(uint64_t* pOutWUID) override;                                // 0x1806FE160 -> invalid

    float       m_injuryAmount;         // +0x08  GetFloatParam(0)
    int32_t     m_injuryIntParam;       // +0x0C  GetIntParam(1)
    uint8_t     m_injuryFlag;           // +0x10  GetIntParam(2)
    uint8_t     _pad11[7];              // +0x11
};
static_assert(sizeof(C_InjuredBuffInitParams) == 0x18);

}  // namespace wh::rpgmodule
