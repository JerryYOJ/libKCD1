#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindHorse — entity script binding for horses
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindHorse@entitymodule@wh@@
// vtable: 0x1826c6050
// Constructor: sub_1810B953C
// Size: 0x78

namespace wh::entitymodule {

class C_ScriptBindHorse : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindHorse;
    Offsets::IScriptTable*  m_pEntityTable;     // +0x60
    void*                   m_pGameFramework;   // +0x68
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x70

    virtual int HasRider(IFunctionHandler* pH);          // 0x1810CD588
    virtual int IsMountable(IFunctionHandler* pH);       // 0x1810D2CE4
    virtual int RearAndThrowDown(IFunctionHandler* pH);  // 0x1810DDA00
};
static_assert(sizeof(C_ScriptBindHorse) == 0x78);

} // namespace wh::entitymodule
