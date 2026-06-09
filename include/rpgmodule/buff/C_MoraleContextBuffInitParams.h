#pragma once
#include "I_BuffInitParams.h"

// -----------------------------------------------
// C_MoraleContextBuffInitParams — carries morale context data
// -----------------------------------------------
// RTTI: .?AVC_MoraleContextBuffInitParams@rpgmodule@wh@@
// vtable: 0x1821be948
// Constructor: 0x1805685F4
// Size: 0x10
//
// Uses hashed param keys: 0xD8864 (float), 0xD8865/0xD8866 (int).

namespace wh::rpgmodule {

class C_MoraleContextBuffInitParams : public I_BuffInitParams {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MoraleContextBuffInitParams;
    ~C_MoraleContextBuffInitParams() override;                                          // 0x180568690
    float GetFloatParam(int nKey) override;                                             // 0x1802AD99C key=0xD8864 -> m_moraleValue
    int GetIntParam(int nKey) override;                                                 // 0x1802AD97C key=0xD8865 -> m_moraleFlag1, key=0xD8866 -> m_moraleFlag2
    uint64_t* GetEntityRef(uint64_t* pOutWUID) override;                                // 0x1806FE160 -> invalid

    float       m_moraleValue;          // +0x08  GetFloatParam(0xD8864)
    uint8_t     m_moraleFlag1;          // +0x0C  GetIntParam(0xD8865)
    uint8_t     m_moraleFlag2;          // +0x0D  GetIntParam(0xD8866)
    uint8_t     _pad0E[2];             // +0x0E
};
static_assert(sizeof(C_MoraleContextBuffInitParams) == 0x10);

}  // namespace wh::rpgmodule
