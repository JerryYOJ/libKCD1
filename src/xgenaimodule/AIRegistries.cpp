#include "xgenaimodule/EntityToAIMap.h"
#include "xgenaimodule/C_IntelligentObjectManager.h"
#include "Offsets/Offsets.h"

// Forwarders for the AI WUID registries (declared in their headers as "address forwarders, see the
// .cpp"). EntityToAIMap is a bare std::unordered_map -- callers index it natively via .find(); only
// its global pointer is resolved here. The C_IntelligentObjectManager map is a custom T_WuidHashMap,
// so its lookup goes through the engine's Find.

namespace wh::xgenaimodule {

// *qword_18378D6E8 -- the entity-GUID -> {C_AIPuppet*, WUID} map (std::unordered_map). Null before
// the AI module's lazy init runs.
C_EntityToAIMap* GetEntityToAIMap()
{
    static REL::Relocation<C_EntityToAIMap**> p{ REL::ID(883) };
    return *p;
}

// sub_18023BDCC: engine find by entity GUID -> &value.m_wuid (or the all-FF invalid-WUID sentinel on
// miss). Equivalent to GetEntityToAIMap()->find(guid) but uses the engine's own hash; kept for callers
// that prefer the engine path.
const wh::framework::WUID* FindWuidByEntity(C_EntityToAIMap* map, EntityGUID guid)
{
    using Fn = const wh::framework::WUID* (__fastcall*)(C_EntityToAIMap*, EntityGUID);
    static REL::Relocation<Fn> fn{ REL::ID(6) };
    return fn(map, guid);
}

// *qword_183799950 -- the WUID -> C_IntelligentObject* registry singleton.
C_IntelligentObjectManager* C_IntelligentObjectManager::GetInstance()
{
    static REL::Relocation<C_IntelligentObjectManager**> p{ REL::ID(884) };
    return *p;
}

// sub_1802B620C: hash the WUID, walk the T_WuidHashMap bucket chain; value@node+0x18, null on miss.
C_IntelligentObject* C_IntelligentObjectManager::Find(wh::framework::WUID w) const
{
    using Fn = C_IntelligentObject* (__fastcall*)(const C_IntelligentObjectManager*, const wh::framework::WUID*);
    static REL::Relocation<Fn> fn{ REL::ID(10) };
    return fn(this, &w);
}

}  // namespace wh::xgenaimodule
