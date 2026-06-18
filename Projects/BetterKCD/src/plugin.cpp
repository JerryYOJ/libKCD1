// BetterKCD — a KCSE plugin hosting read-only "dump" console commands.
//
// Commands:
//   kcse_dump_npcs     [radius=15]      List nearby NPCs (name / faction / opinion / guard / distance).
//   kcse_dump_crimes   [radius]         List crime informations (type / id / a few witnesses + faction);
//                                       radius>0 filters to crimes whose location is within r m of the player.
//   kcse_dump_factions [onlyVisible=0]  List factions (name / reputation / visible); onlyVisible=1 hides hidden.
//
#include "KCSE/KCSEAPI.h"
#include "crysystem/SSystemGlobalEnvironment.h"    // GetInstance()->pConsole / pLog / pEntitySystem
#include "xgenaimodule/C_InformationManager.h"     // GetInstance / m_records / m_byId
#include "xgenaimodule/S_InformationRecord.h"      // label / informationId / posX..Z
#include "xgenaimodule/C_IntelligentObject.h"      // crime holder ("witness")
#include "xgenaimodule/C_AIPuppet.h"               // holder->m_pHost: GetEntityId / GetEntityName
#include "rpgmodule/C_FactionManager.h"            // GetInstance / m_factions
#include "rpgmodule/C_Faction.h"                   // m_reputation / m_pDef
#include "rpgmodule/S_FactionDef.h"                // name / visible
#include "rpgmodule/C_Soul.h"                       // FromEntityId / m_soulName / m_pFactionData / GetPlayerOpinion / IsGuard
#include "Offsets/Offsets.h"                        // GetCCryAction()
#include "Offsets/vtables/IEntitySystem.h"          // IEntitySystem / IEntity / IEntityIt

#include <unordered_set>
#include <cstring>   // strcmp (IsCrimeLabel)
#include <cstdlib>   // atof (ArgFloat)
#include <cmath>     // sqrt
#include <cstdint>

using wh::xgenaimodule::C_InformationManager;
using wh::xgenaimodule::S_InformationRecord;
using wh::xgenaimodule::C_IntelligentObject;
using wh::rpgmodule::C_FactionManager;
using wh::rpgmodule::C_Faction;
using wh::rpgmodule::C_Soul;

namespace {

const float kNpcRadius = 15.0f;

// Parse arg[index] as a float (arg[0] is the command name), else return `def`.
// GetArgCount @ IConsoleCmdArgs vtbl+0x08, GetArg @ vtbl+0x10 (VERIFIED sub_180F29C7C; SDK order).
float ArgFloat(IConsoleCmdArgs* args, int index, float def)
{
    if (args && args->GetArgCount() > index) {
        const char* a = args->GetArg(index);
        if (a && *a) return static_cast<float>(atof(a));
    }
    return def;
}

// The 9 attributed-crime labels (isCrime == true) from Crime.lua / CrimeUtils.InitInformationData.
const char* const kCrimeLabels[] = {
    "assault", "carriedCorpse", "lockpick", "murder",
    "refuseFrisk", "sneak", "theft", "trespass", "weapon",
};

bool IsCrimeLabel(const char* label)
{
    for (const char* c : kCrimeLabels)
        if (std::strcmp(c, label) == 0) return true;
    return false;
}

// Player's world position via the entity system. False if unavailable.
bool GetPlayerPos(Vec3& out)
{
    auto* env = SSystemGlobalEnvironment::GetInstance();
    auto* fw  = Offsets::GetCCryAction();
    if (!env || !fw || !env->pEntitySystem) return false;
    Offsets::IEntity* p = env->pEntitySystem->GetEntity(fw->GetClientActorId());
    if (!p) return false;
    p->GetWorldPos(out);
    return true;
}

// Enumerate NPCs near the player via the ENTITY SYSTEM (the stable public registry; avoids C_SoulList's
// internal handle-table garbage). Each entity is bridged to its soul by C_Soul::FromEntityId (null for
// non-actors, so it doubles as the "is an NPC" filter). Calls fn(soul, distance); returns the count.
template <class F>
int ForEachNearbyNpc(float radius, F&& fn)
{
    auto* env = SSystemGlobalEnvironment::GetInstance();
    auto* fw  = Offsets::GetCCryAction();
    if (!env || !fw || !env->pEntitySystem) return 0;
    Offsets::IEntitySystem* es = env->pEntitySystem;

    const EntityId playerId = fw->GetClientActorId();
    Vec3 ppos;
    if (!GetPlayerPos(ppos)) return 0;

    const float r = radius * radius;
    Offsets::IEntityIt* it = es->GetEntityIterator();
    if (!it) return 0;
    it->MoveFirst();
    int found = 0;
    for (Offsets::IEntity* ent; (ent = it->Next()) != nullptr; ) {
        const EntityId id = ent->GetId();
        if (id == playerId) continue;
        C_Soul* s = C_Soul::FromEntityId(id);      // null unless the entity is an actor/NPC
        if (!s) continue;
        Vec3 pos; ent->GetWorldPos(pos);
        float d = pos.GetSquaredDistance(ppos);
        if (d > r) continue;
        fn(s, std::sqrt(d));
        ++found;
    }
    it->Release();
    return found;
}

void Cmd_DumpNpcs(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const float radius = ArgFloat(args, 1, kNpcRadius);
    int n = ForEachNearbyNpc(radius, [log](C_Soul* s, float dist) {
        C_Faction* f = s->m_pFactionData;
        log->LogAlways("[BetterKCD]   '%s'  faction=%s(%.2f)  opinion=%.2f  guard=%s  dist=%.1fm",
                       s->m_soulName.c_str(),
                       (f && f->m_pDef) ? f->m_pDef->name.c_str() : "", f ? f->m_reputation : 0.0f,
                       s->GetPlayerOpinion(), s->IsGuard() ? "Y" : "N", dist);
    });
    log->LogAlways("[BetterKCD] kcse_dump_npcs: %d NPC(s) within %.0fm", n, radius);
}

void Cmd_DumpCrimes(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    auto* mgr = C_InformationManager::GetInstance();
    if (!mgr) { log->LogAlways("[BetterKCD] kcse_dump_crimes: no information manager"); return; }

    const float radius = ArgFloat(args, 1, 0.0f);     // optional; >0 => only crimes within r m of the player
    Vec3 ppos;
    const bool spatial = radius > 0.0f && GetPlayerPos(ppos);
    const float r2 = radius * radius;

    std::unordered_set<uint32_t> seen;   // one crime == many versioned records sharing an id; dump once
    int n = 0;
    for (S_InformationRecord* rec : mgr->m_records) {
        if (!rec || !IsCrimeLabel(rec->label.c_str())) continue;
        if (spatial && Vec3(rec->posX, rec->posY, rec->posZ).GetSquaredDistance(ppos) > r2) continue;
        if (!seen.emplace(rec->informationId).second) continue;

        log->LogAlways("[BetterKCD]   %s  id=%u  @(%.0f,%.0f,%.0f)",
                       rec->label.c_str(), rec->informationId, rec->posX, rec->posY, rec->posZ);

        auto h = mgr->m_byId.find(rec->informationId);   // witnesses = the holders that know this crime
        if (h != mgr->m_byId.end() && h->second) {
            const auto& holders = *h->second;
            int shown = 0;
            for (C_IntelligentObject* io : holders) {
                if (shown >= 3) break;
                if (!io || !io->m_pHost) continue;
                C_Soul* w = C_Soul::FromEntityId(io->m_pHost->GetEntityId());
                const char* wn = w ? w->m_soulName.c_str() : io->m_pHost->GetEntityName();
                const char* wf = (w && w->m_pFactionData && w->m_pFactionData->m_pDef)
                                 ? w->m_pFactionData->m_pDef->name.c_str() : "?";
                log->LogAlways("[BetterKCD]       witness '%s' (%s)", wn, wf);
                ++shown;
            }
            if (holders.size() > 3)
                log->LogAlways("[BetterKCD]       +%d more witness(es)", static_cast<int>(holders.size()) - 3);
        }
        ++n;
    }
    log->LogAlways("[BetterKCD] kcse_dump_crimes: %d crime(s)%s", n, spatial ? " near player" : "");
}

void Cmd_DumpFactions(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    auto* mgr = C_FactionManager::GetInstance();
    if (!mgr) { log->LogAlways("[BetterKCD] kcse_dump_factions: no faction manager"); return; }

    const bool onlyVisible = ArgFloat(args, 1, 0.0f) > 0.0f;   // optional; 1 => hide non-visible factions
    int n = 0;
    for (const auto& kv : mgr->m_factions) {
        C_Faction* f = kv.second.get();
        if (!f || !f->m_pDef) continue;
        const bool vis = f->m_pDef->visible;
        if (onlyVisible && !vis) continue;
        log->LogAlways("[BetterKCD]   '%s'  rep=%.2f  visible=%s",
                       f->m_pDef->name.c_str(), f->m_reputation, vis ? "Y" : "N");
        ++n;
    }
    log->LogAlways("[BetterKCD] kcse_dump_factions: %d faction(s)%s", n, onlyVisible ? " (visible only)" : "");
}

}  // namespace

KCSE_PLUGIN_INFO("BetterKCD", "RE", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    kcse->GetMessagingInterface()->RegisterListener([](KCSE::Message* msg) {
        if (msg->type != KCSE::IMessagingInterface::kMessage_DataLoaded) return;
        auto* env = SSystemGlobalEnvironment::GetInstance();
        env->pConsole->AddCommand("kcse_dump_npcs", &Cmd_DumpNpcs, 0,
            "BetterKCD: kcse_dump_npcs [radius=15] -- list nearby NPCs (name/faction/opinion/guard/dist)");
        env->pConsole->AddCommand("kcse_dump_crimes", &Cmd_DumpCrimes, 0,
            "BetterKCD: kcse_dump_crimes [radius] -- list crimes (type/id/witnesses); radius>0 filters by crime location");
        env->pConsole->AddCommand("kcse_dump_factions", &Cmd_DumpFactions, 0,
            "BetterKCD: kcse_dump_factions [onlyVisible=0] -- list factions (name/reputation/visible)");
        env->pLog->LogAlways("[BetterKCD] loaded");
    });
    return true;
}
