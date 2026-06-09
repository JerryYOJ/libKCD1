#pragma once
#include "../crysystem/CScriptableBase.h"

// C_ScriptBindEnvironment — Lua "EnvironmentModule" table
// RTTI: .?AVC_ScriptBindEnvironment@environmentmodule@wh@@  vtable: 0x1822e54a8
// Constructor: sub_1810FCAC4  Registration: sub_1810FE508  Size: 0x70

namespace wh::environmentmodule {
class C_ScriptBindEnvironment : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindEnvironment;
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68
    // int MakeHole(IFunctionHandler* pH, bool make, EntityId entityId);                       // 0x1810FDF7C
    // int CoverHole(IFunctionHandler* pH, bool cover, EntityId entityId);                     // 0x1810FD554
    // int BlendTimeOfDay(IFunctionHandler* pH, const char* ProfileName, float BlendDuration, bool Force); // 0x1810FD440
    // int RebuildClouds(IFunctionHandler* pH);                                                // 0x1810FE4D4
    // int ForceWindDirection(IFunctionHandler* pH, float fAngleDeg);                          // 0x1810FDDC8
    // int ForceImmediateWeatherUpdate(IFunctionHandler* pH);                                  // 0x180F32EF0 (noop)
};
static_assert(sizeof(C_ScriptBindEnvironment) == 0x70);
} // namespace wh::environmentmodule
