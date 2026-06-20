#pragma once

#include <cstddef>                  // size_t (GetBoundaryPoints count)
#include "../framework/WUID.h"      // wh::framework::WUID (GetKey)
// Vec3 / AABB come from the PCH prelude (Cry_Math.h).

// ===========================================================================
// wh::xgenaimodule::I_Area  -  the spatial "area" identity interface of a C_SmartArea.
// ===========================================================================
// RTTI: .?AVI_Area@... (TD 0x182b1e438). This is the C_SmartArea identity sub-object living at
// C_SmartArea+0x218 (COL 0x1825958c8, offset field 0x218); vtable 0x182703a08, 9 slots. PURE interface
// (sizeof 0x08, vtable pointer only) -- the data lives in C_SmartArea (see C_SmartArea.h). Member methods
// reach C_SmartArea fields via `this` = I_Area* = C_SmartArea+0x218 (e.g. GetKey returns this-0x210 =
// C_SmartArea+0x08). NOT interfuscated (wh:: type -> canonical slot order). All slots VERIFIED by decompile.
//
// A SmartArea is the world-region primitive the location system resolves against: the SmartArea manager's
// grid point query hands back C_SmartArea*, GetKey() yields its WUID, and C_RPGLocationManager maps that
// key to a C_RPGLocation. A SmartArea owns its geometry here (AABB + boundary polygon), unlike a location.
// ===========================================================================

namespace wh::xgenaimodule {

class I_Area {
public:
    // [0] 0x00  scalar-deleting dtor (adjustor thunk -> C_SmartArea deleting dtor, this-0x218) (0x180B1C644)
    virtual ~I_Area() = 0;
    // [1] 0x08  is `pt` inside this area: AABB reject then polygon test (sub_180375AB8 -> sub_180375B20)
    virtual bool ContainsPoint(const Vec3& pt) = 0;
    // [2] 0x10  this area's key/WUID: returns *(C_SmartArea+0x08) (sub_180208AC0)
    virtual wh::framework::WUID GetKey() = 0;
    // [3] 0x18  script/lua table (C_SmartArea+0x58; default qword_18372ED20) (sub_1815D3AE4 -> sub_1802CB25C)
    virtual void* GetScriptTable() = 0;
    // [4] 0x20  copy this area's AABB (Vec3 min @C_SmartArea+0x264, Vec3 max @+0x270) into `outAABB` (sub_1815D3A18)
    virtual void GetAABB(void* outAABB) = 0;   // outAABB -> AABB { Vec3 min; Vec3 max }
    // [5] 0x28  boundary polygon: *out = points (C_SmartArea+0x248), *count = (end-begin)/sizeof(Vec3) (sub_180655C14)
    virtual void GetBoundaryPoints(const Vec3** out, size_t* count) = 0;
    // [6] 0x30  &boundary-points DynArray (returns C_SmartArea+0x248) (sub_1806F9160)
    virtual void* GetBoundaryPointsArray() = 0;
    // [7] 0x38  scalar at C_SmartArea+0x260 (init -1.0f) -- likely height / Z-extent (sub_1806F99C0)
    virtual float GetHeight() = 0;
    // [8] 0x40  case-insensitive tag test: binary-search the two sorted tag vectors @C_SmartArea+0x3D0/+0x3E8 (sub_180428068)
    virtual bool HasTag(const char* tag) = 0;
};
static_assert(sizeof(I_Area) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::xgenaimodule
