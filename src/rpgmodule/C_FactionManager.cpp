#include "rpgmodule/C_FactionManager.h"
#include "Offsets/Offsets.h"

// C_FactionManager engine-function forwarders.
// The manager is a Meyers-singleton OBJECT embedded at qword_1836E39F0; the accessor
// sub_18022877C returns &it and runs the lazy-init guard on first call.

namespace wh { namespace rpgmodule {

C_FactionManager* C_FactionManager::GetInstance()
{
    using Fn = C_FactionManager* (__fastcall*)();
    return reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFactionManagerAccessorOffset)();
}

}}  // namespace wh::rpgmodule
