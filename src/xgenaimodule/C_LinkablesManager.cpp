#include "xgenaimodule/C_LinkablesManager.h"
#include "Offsets/Offsets.h"

// C_LinkablesManager engine-function forwarders. The manager is the global *qword_1837999D8;
// Find passes `this` to the engine map-find (sub_18024D6E4).

namespace wh { namespace xgenaimodule {

C_LinkablesManager* C_LinkablesManager::GetInstance()
{
    static REL::Relocation<C_LinkablesManager**> p{ REL::ID(885) };
    return *p;
}

C_LinkableObject* C_LinkablesManager::Find(wh::framework::WUID w) const
{
    using Fn = C_LinkableObject* (__fastcall*)(const C_LinkablesManager*, const wh::framework::WUID*);
    static REL::Relocation<Fn> fn{ REL::ID(7) };  // sub_18024D6E4
    return fn(this, &w);
}

}} // namespace wh::xgenaimodule
