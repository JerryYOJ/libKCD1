#include "rpgmodule/C_FactionManager.h"
#include "Offsets/Offsets.h"

// C_FactionManager engine-function forwarders.
// The manager is a Meyers-singleton OBJECT embedded at qword_1836E39F0; the accessor
// sub_18022877C returns &it and runs the lazy-init guard on first call.

namespace wh { namespace rpgmodule {

C_FactionManager* C_FactionManager::GetInstance()
{
    using Fn = C_FactionManager* (__fastcall*)();
    static REL::Relocation<Fn> fn{ REL::ID(3) };  // sub_18022877C -> &C_FactionManager
    return fn();
}

}}  // namespace wh::rpgmodule
