#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_FastTravelScriptBind — Lua "FastTravel" table
// -----------------------------------------------
// RTTI: .?AVC_FastTravelScriptBind@playermodule@wh@@
// vtable: 0x182312358
// Constructor: sub_181281668
// Registration: sub_181285D54
// Size: 0x60 (no extra members)

namespace wh::playermodule {

class C_FastTravelScriptBind : public CScriptableBase {
public:
    // Lua methods
    int Stop(IFunctionHandler* pH);                                     // 0x181287904
    int DespawnLastRandomEvent(IFunctionHandler* pH);                   // 0x181283454
    int DespawnRandomEvent(IFunctionHandler* pH, int id);               // 0x1812834E4
    int StopToEvent(IFunctionHandler* pH, float time, int id);          // 0x1812879AC
};
static_assert(sizeof(C_FastTravelScriptBind) == 0x60);

} // namespace wh::playermodule
