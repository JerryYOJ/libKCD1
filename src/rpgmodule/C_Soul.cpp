#include "rpgmodule/C_Soul.h"
#include "rpgmodule/C_SoulList.h"
#include "rpgmodule/S_SocialClass.h"
#include "xgenaimodule/C_AIBrain.h"                    // soul -> brain -> variable container
#include "xgenaimodule/C_AssociativeArrayTreeVariable.h" // b_soul composite var
#include "xgenaimodule/EntityToAIMap.h"                // entity GUID -> WUID (std::unordered_map)
#include "xgenaimodule/C_IntelligentObjectManager.h"   // WUID -> C_IntelligentObject (+ m_pBrain)
#include "Offsets/vtables/IEntity.h"                   // m_boundEntities[0]->GetGuid()
#include "xgenaimodule/S_VariableValue.h"             // the 0x10 value cell + accessors
#include "framework/WUID.h"
#include "Offsets/Offsets.h"
#include "Offsets/RTTI.h"                             // kcd_cast<>

// C_Soul / C_SoulList engine-function forwarders. Thin wrappers around the verified RVAs in
// Offsets.h -- the durable way to expose them as typed methods (mirrors C_FactionManager.cpp).

namespace wh { namespace rpgmodule {

C_Soul* C_Soul::FromEntityId(uint32_t entityId)
{
    // sub_18033B518: gEnv.pGame->GetIGameFramework()[0x78] ->GetIActorSystem()[0xC8]
    //   ->GetActor(entityId)[0x18]; then C_Actor+0x650 = the actor's C_Soul* (0 if not an actor).
    // The engine fn ignores its first (rcx/"this") arg -- the id arrives in the 2nd integer
    // register -- so the signature keeps a leading dummy that we pass as null.
    using Fn = C_Soul* (__fastcall*)(void* /*ignored*/, uint32_t);
    static REL::Relocation<Fn> fn{ REL::ID(12) };  // sub_18033B518
    return fn(nullptr, entityId);
}

float C_Soul::GetPlayerOpinion() const
{
    using Fn = float (__fastcall*)(const C_Soul*);
    static REL::Relocation<Fn> fn{ REL::ID(4) };  // sub_1802287D0
    return fn(this);
}

void C_Soul::SetPlayerOpinion(float v)
{
    // The engine has no value-setter (only the delta-apply sub_1811F3224). Write the field directly
    // on the ROOT soul (master chain +0x480), clamped to [-1,+1] -- mirrors sub_1802287D0's resolution.
    if (v < -1.0f) v = -1.0f; else if (v > 1.0f) v = 1.0f;
    C_Soul* root = this;
    for (;;) {
        C_Soul* master = *reinterpret_cast<C_Soul* const*>(reinterpret_cast<const char*>(root) + 0x480);
        if (!master) break;
        root = master;
    }
    *reinterpret_cast<float*>(reinterpret_cast<char*>(root) + 0x6F8) = v;  // m_activeStats.m_playerOpinion
}

int32_t C_Soul::GetFactionId() const
{
    using Fn = int32_t (__fastcall*)(const C_Soul*);
    static REL::Relocation<Fn> fn{ REL::ID(28) };  // sub_18064D750
    return fn(this);
}

E_CrimeSystemRole C_Soul::GetCrimeRole() const
{
    // The brain's live b_soul.crimeSystemRole can diverge from this only via a
    // crimeSystemRoleOverride message (see IsGuard).
    const S_SocialClass* sc = m_pSocialClass;
    return sc ? sc->m_crimeRoleId : E_CrimeSystemRole::None;
}

wh::xgenaimodule::C_IntelligentObject* C_Soul::GetIntelligentObject() const
{
    using namespace wh::xgenaimodule;

    // soul -> entity -> WUID. C_EntityToAIMap is a real std::unordered_map, so index it natively
    // with .find (NEVER operator[] -- that would insert into the game's map). Stateless std::hash<u64>
    // (FNV-1a) matches the engine's, so this walks the game's buckets correctly.
    Offsets::IEntity* ent = m_boundEntities[0];            // C_Soul+0xBE8
    if (!ent) return nullptr;
    C_EntityToAIMap* entMap = GetEntityToAIMap();
    if (!entMap) return nullptr;
    auto it = entMap->find(ent->GetGuid());                // CEntity::GetGuid (IEntity vtbl[0x10])
    if (it == entMap->end()) return nullptr;

    // WUID -> C_IntelligentObject. This registry is a custom T_WuidHashMap (not std), so use its Find.
    C_IntelligentObjectManager* iom = C_IntelligentObjectManager::GetInstance();
    if (!iom) return nullptr;
    return iom->Find(it->second.m_wuid);                   // null on miss
}

E_CrimeSystemRole C_Soul::GetEffectiveCrimeRole() const
{
    using namespace wh::xgenaimodule;
    const E_CrimeSystemRole def = GetCrimeRole();          // default + safe fallback on any miss

    C_IntelligentObject* io = GetIntelligentObject();
    if (!io) return def;
    C_AIBrain* brain = io->m_pBrain;                        // typed (C_IntelligentObject+0x118)
    if (!brain) return def;
    C_VariableIndex* cont = &brain->m_varIndex;

    // look up the composite var "b_soul". GetVariableByName content-compares the name (sub_180253FE8),
    // so a CryStringT view over the literal works -- no CryStringT constructed, store not mutated.
    const char* kBSoul = "b_soul";
    C_Variable* v = cont->GetVariableByName(*reinterpret_cast<const CryStringT<char>*>(&kBSoul), true);
    auto* assoc = kcd_cast<C_AssociativeArrayTreeVariable*>(v);   // safe downcast (null if a different form)
    if (!assoc) return def;

    // Read crimeSystemRole's value cell directly -- no engine decoder, no ScriptAnyValue. FindCell returns
    // element[1] of the member's holder (the exact cell the engine reads; verified from sub_1803B3790).
    // An enum is a number cell; GetInt yields the int (Int as-is, Float truncated), else the default.
    const S_VariableValue* cell = assoc->FindCell("crimeSystemRole");
    if (!cell || !cell->IsNumber()) return def;
    return static_cast<E_CrimeSystemRole>(cell->GetInt(static_cast<int>(def)));
}

bool C_Soul::IsGuard() const
{
    // A "guard" = a crime authority: Soldier (town/world guard) or Circator (monastery enforcer) --
    // the two roles sa_crimeDistrict's LuaGate accepts as authorities. Uses the live, override-aware role.
    const E_CrimeSystemRole r = GetEffectiveCrimeRole();
    return r == E_CrimeSystemRole::Soldier || r == E_CrimeSystemRole::Circator;
}

bool C_Soul::HasSoulAbility(E_SoulAbility ability) const
{
    // sub_18023B6BC (I_Soul vtable +0x1A8): binary-search the sorted m_soulAbilities (+0x180)
    // for the id; a few ids (SteakTartare/TwoHanded) are computed instead. Returns the bool.
    using Fn = char (__fastcall*)(const C_Soul*, uint32_t);
    static REL::Relocation<Fn> fn{ REL::ID(5) };  // sub_18023B6BC (I_Soul vtable +0x1A8)
    return fn(this, static_cast<uint32_t>(ability)) != 0;
}

void C_Soul::ResetInventory(bool resetEquipment)
{
    // sub_18030E278(soul, force=1, resetEquip, presetMultiplier=0)
    // force=1 bypasses the "already initialized" check at +0xBF8.
    using Fn = void (__fastcall*)(C_Soul*, char, char, uint8_t);
    static REL::Relocation<Fn> fn{ REL::ID(11) };  // sub_18030E278
    fn(this, 1, resetEquipment ? 1 : 0, 0);
}

C_SoulList* C_SoulList::GetInstance()
{
    uintptr_t rpgSys = *reinterpret_cast<uintptr_t*>(REL::ID(877).address());
    return rpgSys ? *reinterpret_cast<C_SoulList**>(rpgSys + 0x548) : nullptr;
}

C_Soul* C_SoulList::LookupByWUID(const wh::framework::WUID& wuid)
{
    // Engine lookup takes the embedded slot-map header (this+0x48) + the WUID.
    using Fn = C_Soul* (__fastcall*)(void*, const wh::framework::WUID*);
    static REL::Relocation<Fn> fn{ REL::ID(8) };  // C_SoulList::LookupByWUID (sub_180284B04)
    return fn(&m_slotMapHeader, &wuid);
}

}}  // namespace wh::rpgmodule
