#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// CScriptBindBoids — Lua "Boids" table
// -----------------------------------------------
// RTTI: .?AVCScriptBindBoids@boids@entitymodule@wh@@
// vtable: 0x1822e4550
// Constructor: sub_1810B6C7C (methods registered inline)
// Size: 0x68

namespace wh::entitymodule::boids {

class CScriptBindBoids : public CScriptableBase {
public:
    void* m_pContext;  // +0x60

    enum EFlockType {
        FLOCK_BIRDS    = 0,
        FLOCK_FISH     = 1,
        FLOCK_BUGS     = 2,
        FLOCK_CHICKENS = 3,
        FLOCK_FROGS    = 4,
        FLOCK_TURTLES  = 5,
    };

    // -- Direct Lua methods --
    // int CreateFlock(IFunctionHandler* pH, ScriptHandle entity, int nType, SmartScriptTable tParamsTable);  // 0x1810C12F4
    // int SetFlockParams(IFunctionHandler* pH, ScriptHandle entity, SmartScriptTable tParamsTable);          // 0x1810E5E14
    // int EnableFlock(IFunctionHandler* pH, ScriptHandle entity, bool bEnable);                              // 0x1810C4C70
    // int SetFlockPercentEnabled(IFunctionHandler* pH, ScriptHandle entity, float fPercentage);              // 0x1810E6020
    // int OnBoidHit(IFunctionHandler* pH, ScriptHandle boidEntity, SmartScriptTable hit);                    // 0x1810D6964
    // int SetAttractionPoint(IFunctionHandler* pH, ScriptHandle entity, Vec3 point);                         // 0x1810E59F8
};
static_assert(sizeof(CScriptBindBoids) == 0x68);

} // namespace wh::entitymodule::boids
