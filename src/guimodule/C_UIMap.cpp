#include "guimodule/C_UIMap.h"
#include "Offsets/Offsets.h"

namespace wh::guimodule {

void C_UIMap::ForceStartFastTravel(const Vec3& worldPos, int iconType)
{
    using Fn = void(__fastcall*)(C_UIMap*, const Vec3*, int);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kUIMapForceStartFastTravelOffset);
    fn(this, &worldPos, iconType);
}

}  // namespace wh::guimodule
