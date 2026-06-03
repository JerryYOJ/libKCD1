#include "xgenaimodule/C_LinkablesManager.h"
#include "Offsets/Offsets.h"

// C_LinkablesManager engine-function forwarders. The manager is the global *qword_1837999D8;
// Find passes `this` to the engine map-find (sub_18024D6E4). See Offsets.h for the offsets.

namespace wh { namespace xgenaimodule {

C_LinkablesManager* C_LinkablesManager::GetInstance()
{
    return *reinterpret_cast<C_LinkablesManager**>(Offsets::GetBase() + Offsets::kLinkablesManagerOffset);
}

C_LinkableObject* C_LinkablesManager::Find(wh::framework::WUID w) const
{
    using Fn = C_LinkableObject* (__fastcall*)(const C_LinkablesManager*, const wh::framework::WUID*);
    return reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFindLinkableObjectOffset)(this, &w);
}

}} // namespace wh::xgenaimodule
