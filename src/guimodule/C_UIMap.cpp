#include "guimodule/C_UIMap.h"
#include "Offsets/Offsets.h"

namespace wh::guimodule {

void C_UIMap::ForceStartFastTravel(const Vec3& worldPos, int iconType)
{
    using Fn = void(__fastcall*)(C_UIMap*, const Vec3*, int);
    static REL::Relocation<Fn> fn{ REL::ID(38) };  // C_UIMap::ForceStartFastTravel
    fn(this, &worldPos, iconType);
}

}  // namespace wh::guimodule
