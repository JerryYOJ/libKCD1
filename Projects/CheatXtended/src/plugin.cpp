// CheatXtended — a KCSE plugin for manipulating crime, reputation, stats, skills and perk points.
//
// Commands (all prefixed cheatx_):
//   cheatx_dump_npcs       [radius=15]              List nearby NPCs.
//   cheatx_dump_factions   [onlyVisible=0]           List factions.
//   cheatx_dump_crimes     [radius]                  List crime records.
//   cheatx_dump_stats                                Dump player stats/skills/perk points.
//   cheatx_set_reputation  <faction_name> <value>    Set faction reputation [-1,1].
//   cheatx_set_opinion     <npc_name> <value>        Set NPC opinion-of-player [-1,1].
//   cheatx_clear_crimes    [radius]                  Erase crimes.
//   cheatx_clear_witness   <npc_name|radius>         Wipe NPC crime witness knowledge.
//   cheatx_set_stat        <stat> <level>            Set main stat level.
//   cheatx_set_skill       <skill> <level>           Set skill level.
//   cheatx_set_perk_points <category> <value>        Set perk point counters.
//
#include "KCSE/KCSEAPI.h"
#include "crysystem/SSystemGlobalEnvironment.h"
#include "xgenaimodule/C_InformationManager.h"
#include "xgenaimodule/S_InformationRecord.h"
#include "xgenaimodule/C_IntelligentObject.h"
#include "xgenaimodule/C_AIPuppet.h"
#include "rpgmodule/C_FactionManager.h"
#include "rpgmodule/C_Faction.h"
#include "rpgmodule/S_FactionDef.h"
#include "rpgmodule/C_Soul.h"
#include "rpgmodule/E_RPGStat.h"
#include "rpgmodule/E_RPGSkill.h"
#include "rpgmodule/S_ProgressionSubsystem.h"
#include "rpgmodule/S_SoulProgression.h"
#include "rpgmodule/C_PerkList.h"
#include "rpgmodule/S_PerkPointCounters.h"
#include "Offsets/Offsets.h"
#include "Offsets/vtables/IEntitySystem.h"

#include <unordered_set>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <cctype>
#include <vector>

using wh::xgenaimodule::C_InformationManager;
using wh::xgenaimodule::S_InformationRecord;
using wh::xgenaimodule::C_IntelligentObject;
using wh::rpgmodule::C_FactionManager;
using wh::rpgmodule::C_Faction;
using wh::rpgmodule::C_Soul;
using wh::rpgmodule::S_ProgressionSubsystem;
using wh::rpgmodule::S_PerkPointCounters;
using wh::rpgmodule::E_RPGStat;
using wh::rpgmodule::E_RPGSkill;

namespace {

// ---------------------------------------------------------------------------
// Arg parsing
// ---------------------------------------------------------------------------

float ArgFloat(IConsoleCmdArgs* args, int index, float def)
{
    if (args && args->GetArgCount() > index) {
        const char* a = args->GetArg(index);
        if (a && *a) return static_cast<float>(atof(a));
    }
    return def;
}

int ArgInt(IConsoleCmdArgs* args, int index, int def)
{
    return static_cast<int>(ArgFloat(args, index, static_cast<float>(def)));
}

const char* ArgString(IConsoleCmdArgs* args, int index)
{
    if (args && args->GetArgCount() > index)
        return args->GetArg(index);
    return nullptr;
}

bool IsNumericArg(const char* s)
{
    if (!s || !*s) return false;
    if (*s == '-' || *s == '+') ++s;
    bool hasDot = false;
    for (; *s; ++s) {
        if (*s == '.' && !hasDot) { hasDot = true; continue; }
        if (!isdigit(static_cast<unsigned char>(*s))) return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// Name matching — case-insensitive substring
// ---------------------------------------------------------------------------

bool MatchesName(const char* haystack, const char* needle)
{
    if (!haystack || !needle || !*needle) return false;
    for (const char* h = haystack; *h; ++h) {
        const char* a = h;
        const char* b = needle;
        while (*a && *b && tolower(static_cast<unsigned char>(*a)) == tolower(static_cast<unsigned char>(*b))) {
            ++a; ++b;
        }
        if (!*b) return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Crime labels
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// Player / entity helpers
// ---------------------------------------------------------------------------

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

C_Soul* GetPlayerSoul()
{
    auto* fw = Offsets::GetCCryAction();
    if (!fw) return nullptr;
    return C_Soul::FromEntityId(fw->GetClientActorId());
}

// radius <= 0 means no distance filter (iterate ALL loaded NPCs).
template <class F>
int ForEachNpc(float radius, F&& fn)
{
    auto* env = SSystemGlobalEnvironment::GetInstance();
    auto* fw  = Offsets::GetCCryAction();
    if (!env || !fw || !env->pEntitySystem) return 0;
    Offsets::IEntitySystem* es = env->pEntitySystem;

    const EntityId playerId = fw->GetClientActorId();
    const bool bounded = radius > 0.0f;
    Vec3 ppos;
    if (bounded && !GetPlayerPos(ppos)) return 0;
    const float r2 = radius * radius;

    Offsets::IEntityIt* it = es->GetEntityIterator();
    if (!it) return 0;
    it->MoveFirst();
    int found = 0;
    for (Offsets::IEntity* ent; (ent = it->Next()) != nullptr; ) {
        const EntityId id = ent->GetId();
        if (id == playerId) continue;
        C_Soul* s = C_Soul::FromEntityId(id);
        if (!s) continue;
        Vec3 pos; ent->GetWorldPos(pos);
        if (bounded) {
            float d = pos.GetSquaredDistance(ppos);
            if (d > r2) continue;
            fn(s, std::sqrt(d));
        } else {
            fn(s, -1.0f);
        }
        ++found;
    }
    it->Release();
    return found;
}

// ---------------------------------------------------------------------------
// Stat / Skill lookup tables
// ---------------------------------------------------------------------------

struct NamedEntry { const char* shortName; const char* longName; int id; };

static const NamedEntry kStats[] = {
    {"str", "Strength",  0},
    {"agi", "Agility",   1},
    {"vit", "Vitality",  2},
    {"spc", "Speech",    3},
};
static constexpr int kStatCount = 4;

static const NamedEntry kSkills[] = {
    {"stealth",       "Stealth",         0},
    {"horseriding",   "HorseRiding",     1},
    {"fencing",       "Fencing",         2},
    {"bard",          "Bard",            3},
    {"lockpicking",   "Lockpicking",     4},
    {"pickpocketing", "Pickpocketing",   5},
    {"alchemy",       "Alchemy",         6},
    {"cooking",       "Cooking",         7},
    {"repairing",     "Repairing",       8},
    {"smithing",      "Smithing",        9},
    {"fishing",       "Fishing",        10},
    {"mining",        "Mining",         11},
    {"firstaid",      "FirstAid",       12},
    {"drinking",      "Drinking",       13},
    {"hunter",        "Hunter",         14},
    {"defense",       "Defense",        15},
    {"sword",         "WeaponSword",    16},
    {"axe",           "WeaponAxe",      17},
    {"bow",           "WeaponBow",      18},
    {"crossbow",      "WeaponCrossbow", 19},
    {"shield",        "WeaponShield",   20},
    {"mace",          "WeaponMace",     21},
    {"dagger",        "WeaponDagger",   22},
    {"large",         "WeaponLarge",    23},
    {"unarmed",       "WeaponUnarmed",  24},
    {"herbalism",     "Herbalism",      25},
    {"reading",       "Reading",        26},
    {"tailoring",     "Tailoring",      27},
    {"armourer",      "Armourer",       28},
    {"weaponsmithing","Weaponsmithing", 29},
    {"shoemaking",    "Shoemaking",     30},
    {"gambling",      "Gambling",       31},
    {"houndmaster",   "Houndmaster",    32},
};
static constexpr int kSkillCount = 33;

// Find by substring match. Returns match count; fills outId on single match.
int FindStat(const char* query, int& outId)
{
    int count = 0;
    for (int i = 0; i < kStatCount; ++i) {
        if (MatchesName(kStats[i].shortName, query) || MatchesName(kStats[i].longName, query)) {
            outId = kStats[i].id;
            ++count;
        }
    }
    return count;
}

int FindSkill(const char* query, int& outId)
{
    int count = 0;
    for (int i = 0; i < kSkillCount; ++i) {
        if (MatchesName(kSkills[i].shortName, query) || MatchesName(kSkills[i].longName, query)) {
            outId = kSkills[i].id;
            ++count;
        }
    }
    return count;
}

void ListStatMatches(Offsets::ILog* log, const char* query)
{
    for (int i = 0; i < kStatCount; ++i) {
        if (MatchesName(kStats[i].shortName, query) || MatchesName(kStats[i].longName, query))
            log->LogAlways("[CheatX]   '%s' (%s)", kStats[i].shortName, kStats[i].longName);
    }
}

void ListSkillMatches(Offsets::ILog* log, const char* query)
{
    for (int i = 0; i < kSkillCount; ++i) {
        if (MatchesName(kSkills[i].shortName, query) || MatchesName(kSkills[i].longName, query))
            log->LogAlways("[CheatX]   '%s' (%s)", kSkills[i].shortName, kSkills[i].longName);
    }
}

// ---------------------------------------------------------------------------
// DUMP commands
// ---------------------------------------------------------------------------

void Cmd_DumpNpcs(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const float radius = ArgFloat(args, 1, 15.0f);
    int n = ForEachNpc(radius, [log](C_Soul* s, float dist) {
        C_Faction* f = s->m_pFactionData;
        log->LogAlways("[CheatX]   '%s'  faction=%s(%.2f)  opinion=%.2f  guard=%s  dist=%.1fm",
                       s->m_soulName.c_str(),
                       (f && f->m_pDef) ? f->m_pDef->name.c_str() : "", f ? f->m_reputation : 0.0f,
                       s->GetPlayerOpinion(), s->IsGuard() ? "Y" : "N", dist);
    });
    log->LogAlways("[CheatX] cheatx_dump_npcs: %d NPC(s) within %.0fm", n, radius);
}

void Cmd_DumpFactions(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    auto* mgr = C_FactionManager::GetInstance();
    if (!mgr) { log->LogAlways("[CheatX] cheatx_dump_factions: no faction manager"); return; }
    const bool onlyVisible = ArgFloat(args, 1, 0.0f) > 0.0f;
    int n = 0;
    for (const auto& kv : mgr->m_factions) {
        C_Faction* f = kv.second.get();
        if (!f || !f->m_pDef) continue;
        const bool vis = f->m_pDef->visible;
        if (onlyVisible && !vis) continue;
        log->LogAlways("[CheatX]   '%s'  rep=%.2f  visible=%s",
                       f->m_pDef->name.c_str(), f->m_reputation, vis ? "Y" : "N");
        ++n;
    }
    log->LogAlways("[CheatX] cheatx_dump_factions: %d faction(s)%s", n, onlyVisible ? " (visible only)" : "");
}

void Cmd_DumpCrimes(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    auto* mgr = C_InformationManager::GetInstance();
    if (!mgr) { log->LogAlways("[CheatX] cheatx_dump_crimes: no information manager"); return; }

    const float radius = ArgFloat(args, 1, 0.0f);
    Vec3 ppos;
    const bool spatial = radius > 0.0f && GetPlayerPos(ppos);
    const float r2 = radius * radius;

    std::unordered_set<uint32_t> seen;
    int n = 0;
    for (S_InformationRecord* rec : mgr->m_records) {
        if (!rec || !IsCrimeLabel(rec->label.c_str())) continue;
        if (spatial && Vec3(rec->posX, rec->posY, rec->posZ).GetSquaredDistance(ppos) > r2) continue;
        if (!seen.emplace(rec->informationId).second) continue;

        log->LogAlways("[CheatX]   %s  id=%u  @(%.0f,%.0f,%.0f)",
                       rec->label.c_str(), rec->informationId, rec->posX, rec->posY, rec->posZ);

        auto h = mgr->m_byId.find(rec->informationId);
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
                log->LogAlways("[CheatX]       witness '%s' (%s)", wn, wf);
                ++shown;
            }
            if (holders.size() > 3)
                log->LogAlways("[CheatX]       +%d more witness(es)", static_cast<int>(holders.size()) - 3);
        }
        ++n;
    }
    log->LogAlways("[CheatX] cheatx_dump_crimes: %d crime(s)%s", n, spatial ? " near player" : "");
}

void Cmd_DumpStats(IConsoleCmdArgs*)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    C_Soul* soul = GetPlayerSoul();
    if (!soul) { log->LogAlways("[CheatX] cheatx_dump_stats: no player soul"); return; }

    auto& sub = soul->m_perkMgmt.m_activeStats;

    log->LogAlways("[CheatX] --- Main Stats ---");
    for (int i = 0; i < kStatCount; ++i) {
        auto& e = sub.m_statLevels[kStats[i].id];
        log->LogAlways("[CheatX]   %s (%s): level=%u  xp=%u", kStats[i].shortName, kStats[i].longName, e.level, e.xp);
    }

    log->LogAlways("[CheatX] --- Skills ---");
    for (int i = 0; i < kSkillCount; ++i) {
        auto& e = sub.m_skillLevels[kSkills[i].id];
        if (e.level == 0 && e.xp == 0) continue;
        log->LogAlways("[CheatX]   %s (%s): level=%u  xp=%u", kSkills[i].shortName, kSkills[i].longName, e.level, e.xp);
    }

    log->LogAlways("[CheatX] --- Perk Points ---");
    S_PerkPointCounters* pp = sub.m_perkList.m_pPerkPoints;
    if (pp) {
        log->LogAlways("[CheatX]   main: %u", pp->mainLevelPoints);
        for (int i = 0; i < kStatCount; ++i)
            log->LogAlways("[CheatX]   %s: %u", kStats[i].shortName, pp->statPoints[kStats[i].id]);
        for (int i = 0; i < kSkillCount; ++i) {
            if (pp->skillPoints[kSkills[i].id] > 0)
                log->LogAlways("[CheatX]   %s: %u", kSkills[i].shortName, pp->skillPoints[kSkills[i].id]);
        }
    } else {
        log->LogAlways("[CheatX]   (no perk point counters)");
    }

    C_Faction* f = soul->m_pFactionData;
    if (f && f->m_pDef)
        log->LogAlways("[CheatX] Player faction: '%s'  rep=%.2f", f->m_pDef->name.c_str(), f->m_reputation);
}

// ---------------------------------------------------------------------------
// SET commands
// ---------------------------------------------------------------------------

void Cmd_SetReputation(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const char* name = ArgString(args, 1);
    if (!name) { log->LogAlways("[CheatX] usage: cheatx_set_reputation <faction_name> <value>"); return; }
    float value = ArgFloat(args, 2, 0.0f);
    if (value < -1.0f) value = -1.0f; else if (value > 1.0f) value = 1.0f;

    auto* mgr = C_FactionManager::GetInstance();
    if (!mgr) { log->LogAlways("[CheatX] no faction manager"); return; }

    std::vector<C_Faction*> matches;
    for (const auto& kv : mgr->m_factions) {
        C_Faction* f = kv.second.get();
        if (!f || !f->m_pDef) continue;
        if (MatchesName(f->m_pDef->name.c_str(), name))
            matches.push_back(f);
    }

    if (matches.empty()) {
        log->LogAlways("[CheatX] no faction matching '%s'", name);
        return;
    }
    if (matches.size() > 1) {
        log->LogAlways("[CheatX] ambiguous -- %d factions match '%s':", static_cast<int>(matches.size()), name);
        for (C_Faction* f : matches)
            log->LogAlways("[CheatX]   '%s' (rep=%.2f)", f->m_pDef->name.c_str(), f->m_reputation);
        return;
    }

    C_Faction* f = matches[0];
    float old = f->m_reputation;
    f->m_reputation = value;
    log->LogAlways("[CheatX] set reputation of '%s': %.2f -> %.2f", f->m_pDef->name.c_str(), old, value);
}

void Cmd_SetOpinion(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const char* name = ArgString(args, 1);
    if (!name) { log->LogAlways("[CheatX] usage: cheatx_set_opinion <npc_name> <value>"); return; }
    float value = ArgFloat(args, 2, 0.0f);
    if (value < -1.0f) value = -1.0f; else if (value > 1.0f) value = 1.0f;

    struct Match { C_Soul* soul; float dist; };
    std::vector<Match> matches;
    ForEachNpc(0.0f, [&](C_Soul* s, float dist) {
        if (MatchesName(s->m_soulName.c_str(), name))
            matches.push_back({s, dist});
    });

    if (matches.empty()) {
        log->LogAlways("[CheatX] no loaded NPC matching '%s'", name);
        return;
    }
    if (matches.size() > 1) {
        log->LogAlways("[CheatX] ambiguous -- %d NPCs match '%s':", static_cast<int>(matches.size()), name);
        for (auto& m : matches)
            log->LogAlways("[CheatX]   '%s' (opinion=%.2f, dist=%.1fm)", m.soul->m_soulName.c_str(), m.soul->GetPlayerOpinion(), m.dist);
        return;
    }

    C_Soul* s = matches[0].soul;
    float old = s->GetPlayerOpinion();
    s->SetPlayerOpinion(value);
    log->LogAlways("[CheatX] set opinion of '%s': %.2f -> %.2f", s->m_soulName.c_str(), old, value);
}

void Cmd_SetStat(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const char* name = ArgString(args, 1);
    if (!name) { log->LogAlways("[CheatX] usage: cheatx_set_stat <str|agi|vit|spc> <level>"); return; }
    int level = ArgInt(args, 2, -1);
    if (level < 1 || level > 30) { log->LogAlways("[CheatX] level must be 1-30"); return; }

    int statId = -1;
    int count = FindStat(name, statId);
    if (count == 0) { log->LogAlways("[CheatX] no stat matching '%s' (valid: str, agi, vit, spc)", name); return; }
    if (count > 1) {
        log->LogAlways("[CheatX] ambiguous -- multiple stats match '%s':", name);
        ListStatMatches(log, name);
        return;
    }

    C_Soul* soul = GetPlayerSoul();
    if (!soul) { log->LogAlways("[CheatX] no player soul"); return; }

    auto& entry = soul->m_perkMgmt.m_activeStats.m_statLevels[statId];
    uint32_t oldLevel = entry.level;
    entry.level = static_cast<uint32_t>(level);
    entry.xp = 0;
    log->LogAlways("[CheatX] set %s: level %u -> %u (xp reset to 0)", kStats[statId].shortName, oldLevel, level);
}

void Cmd_SetSkill(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const char* name = ArgString(args, 1);
    if (!name) { log->LogAlways("[CheatX] usage: cheatx_set_skill <skill_name> <level>"); return; }
    int level = ArgInt(args, 2, -1);
    if (level < 1 || level > 30) { log->LogAlways("[CheatX] level must be 1-30"); return; }

    int skillId = -1;
    int count = FindSkill(name, skillId);
    if (count == 0) {
        log->LogAlways("[CheatX] no skill matching '%s'. Valid skills:", name);
        for (int i = 0; i < kSkillCount; ++i)
            log->LogAlways("[CheatX]   %s (%s)", kSkills[i].shortName, kSkills[i].longName);
        return;
    }
    if (count > 1) {
        log->LogAlways("[CheatX] ambiguous -- multiple skills match '%s':", name);
        ListSkillMatches(log, name);
        return;
    }

    C_Soul* soul = GetPlayerSoul();
    if (!soul) { log->LogAlways("[CheatX] no player soul"); return; }

    auto& entry = soul->m_perkMgmt.m_activeStats.m_skillLevels[skillId];
    uint32_t oldLevel = entry.level;
    entry.level = static_cast<uint32_t>(level);
    entry.xp = 0;

    const char* sn = "?";
    for (int i = 0; i < kSkillCount; ++i) {
        if (kSkills[i].id == skillId) { sn = kSkills[i].shortName; break; }
    }
    log->LogAlways("[CheatX] set %s: level %u -> %u (xp reset to 0)", sn, oldLevel, level);
}

void Cmd_SetPerkPoints(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const char* cat = ArgString(args, 1);
    if (!cat) { log->LogAlways("[CheatX] usage: cheatx_set_perk_points <main|str|agi|vit|spc|skill_name|all> <value>"); return; }
    int value = ArgInt(args, 2, -1);
    if (value < 0 || value > 65535) { log->LogAlways("[CheatX] value must be 0-65535"); return; }

    C_Soul* soul = GetPlayerSoul();
    if (!soul) { log->LogAlways("[CheatX] no player soul"); return; }

    S_PerkPointCounters* pp = soul->m_perkMgmt.m_activeStats.m_perkList.m_pPerkPoints;
    if (!pp) { log->LogAlways("[CheatX] no perk point counters allocated"); return; }

    auto v16 = static_cast<uint16_t>(value);

    if (_stricmp(cat, "main") == 0) {
        uint16_t old = pp->mainLevelPoints;
        pp->mainLevelPoints = v16;
        log->LogAlways("[CheatX] set main perk points: %u -> %u", old, v16);
        return;
    }

    if (_stricmp(cat, "all") == 0) {
        pp->mainLevelPoints = v16;
        for (int i = 0; i < 10; ++i) pp->statPoints[i] = v16;
        for (int i = 0; i < 33; ++i) pp->skillPoints[i] = v16;
        log->LogAlways("[CheatX] set ALL perk points to %u", v16);
        return;
    }

    int statId = -1;
    if (FindStat(cat, statId) == 1) {
        uint16_t old = pp->statPoints[statId];
        pp->statPoints[statId] = v16;
        log->LogAlways("[CheatX] set %s perk points: %u -> %u", kStats[statId].shortName, old, v16);
        return;
    }

    int skillId = -1;
    int skillCount = FindSkill(cat, skillId);
    if (skillCount == 1) {
        uint16_t old = pp->skillPoints[skillId];
        pp->skillPoints[skillId] = v16;
        const char* sn = "?";
        for (int i = 0; i < kSkillCount; ++i) {
            if (kSkills[i].id == skillId) { sn = kSkills[i].shortName; break; }
        }
        log->LogAlways("[CheatX] set %s perk points: %u -> %u", sn, old, v16);
        return;
    }
    if (skillCount > 1) {
        log->LogAlways("[CheatX] ambiguous -- multiple skills match '%s':", cat);
        ListSkillMatches(log, cat);
        return;
    }

    log->LogAlways("[CheatX] unknown category '%s' (valid: main, str, agi, vit, spc, <skill_name>, all)", cat);
}

// ---------------------------------------------------------------------------
// CRIME commands
// ---------------------------------------------------------------------------

void Cmd_ClearCrimes(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    auto* mgr = C_InformationManager::GetInstance();
    if (!mgr) { log->LogAlways("[CheatX] cheatx_clear_crimes: no information manager"); return; }

    const float radius = ArgFloat(args, 1, 0.0f);
    Vec3 ppos;
    const bool spatial = radius > 0.0f && GetPlayerPos(ppos);
    const float r2 = radius * radius;

    std::unordered_set<uint32_t> ids;
    for (S_InformationRecord* rec : mgr->m_records) {
        if (!rec || !IsCrimeLabel(rec->label.c_str())) continue;
        if (spatial && Vec3(rec->posX, rec->posY, rec->posZ).GetSquaredDistance(ppos) > r2) continue;
        ids.emplace(rec->informationId);
    }
    for (uint32_t id : ids)
        mgr->DestroyInformationById(id);

    log->LogAlways("[CheatX] cheatx_clear_crimes: erased %d crime(s)%s",
                   static_cast<int>(ids.size()), spatial ? " near player" : "");
}

void Cmd_ClearWitness(IConsoleCmdArgs* args)
{
    auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
    if (!log) return;
    const char* arg = ArgString(args, 1);
    if (!arg) { log->LogAlways("[CheatX] usage: cheatx_clear_witness <npc_name|radius>"); return; }

    auto* infoMgr = C_InformationManager::GetInstance();
    if (!infoMgr) { log->LogAlways("[CheatX] no information manager"); return; }

    if (IsNumericArg(arg)) {
        float radius = static_cast<float>(atof(arg));
        if (radius <= 0.0f) { log->LogAlways("[CheatX] radius must be > 0"); return; }
        int cleared = 0;
        ForEachNpc(radius, [&](C_Soul* s, float) {
            C_IntelligentObject* io = s->GetIntelligentObject();
            if (!io) return;
            infoMgr->RemoveHolder(io);
            log->LogAlways("[CheatX]   cleared witness '%s'", s->m_soulName.c_str());
            ++cleared;
        });
        log->LogAlways("[CheatX] cheatx_clear_witness: wiped %d NPC(s) within %.0fm", cleared, radius);
        return;
    }

    struct Match { C_Soul* soul; float dist; };
    std::vector<Match> matches;
    ForEachNpc(0.0f, [&](C_Soul* s, float dist) {
        if (MatchesName(s->m_soulName.c_str(), arg))
            matches.push_back({s, dist});
    });

    if (matches.empty()) {
        log->LogAlways("[CheatX] no loaded NPC matching '%s'", arg);
        return;
    }
    if (matches.size() > 1) {
        log->LogAlways("[CheatX] ambiguous -- %d NPCs match '%s':", static_cast<int>(matches.size()), arg);
        for (auto& m : matches)
            log->LogAlways("[CheatX]   '%s' (dist=%.1fm)", m.soul->m_soulName.c_str(), m.dist);
        return;
    }

    C_Soul* s = matches[0].soul;
    C_IntelligentObject* io = s->GetIntelligentObject();
    if (!io) { log->LogAlways("[CheatX] '%s' has no AI object (not a witness)", s->m_soulName.c_str()); return; }
    infoMgr->RemoveHolder(io);
    log->LogAlways("[CheatX] cleared all witness knowledge from '%s'", s->m_soulName.c_str());
}

}  // namespace

// ---------------------------------------------------------------------------
// Plugin entry
// ---------------------------------------------------------------------------

KCSE_PLUGIN_INFO("CheatXtended", "RE", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    kcse->GetMessagingInterface()->RegisterListener([](KCSE::Message* msg) {
        if (msg->type != KCSE::IMessagingInterface::kMessage_DataLoaded) return;
        auto* env = SSystemGlobalEnvironment::GetInstance();

        env->pConsole->AddCommand("cheatx_dump_npcs", &Cmd_DumpNpcs, 0,
            "CheatX: cheatx_dump_npcs [radius=15] -- list nearby NPCs (name/faction/opinion/guard/dist)");

        env->pConsole->AddCommand("cheatx_dump_factions", &Cmd_DumpFactions, 0,
            "CheatX: cheatx_dump_factions [onlyVisible=0] -- list factions (name/rep/visible)");

        env->pConsole->AddCommand("cheatx_dump_crimes", &Cmd_DumpCrimes, 0,
            "CheatX: cheatx_dump_crimes [radius] -- list crimes (type/id/witnesses); radius>0 filters near player");

        env->pConsole->AddCommand("cheatx_dump_stats", &Cmd_DumpStats, 0,
            "CheatX: cheatx_dump_stats -- dump player stats, skills, and perk points");

        env->pConsole->AddCommand("cheatx_set_reputation", &Cmd_SetReputation, 0,
            "CheatX: cheatx_set_reputation <faction_name> <value> -- set faction reputation [-1,1]. Substring match on name.");

        env->pConsole->AddCommand("cheatx_set_opinion", &Cmd_SetOpinion, 0,
            "CheatX: cheatx_set_opinion <npc_name> <value> -- set NPC opinion-of-player [-1,1]. Substring match on name.");

        env->pConsole->AddCommand("cheatx_clear_crimes", &Cmd_ClearCrimes, 0,
            "CheatX: cheatx_clear_crimes [radius] -- erase crimes globally; radius>0 limits to near player");

        env->pConsole->AddCommand("cheatx_clear_witness", &Cmd_ClearWitness, 0,
            "CheatX: cheatx_clear_witness <npc_name|radius> -- wipe NPC crime witness knowledge.\n"
            "  Numeric arg = radius (all NPCs in range); text = NPC name (substring match).");

        env->pConsole->AddCommand("cheatx_set_stat", &Cmd_SetStat, 0,
            "CheatX: cheatx_set_stat <stat> <level> -- set main stat level [1-30], xp reset to 0.\n"
            "  Stats: str (Strength), agi (Agility), vit (Vitality), spc (Speech).");

        env->pConsole->AddCommand("cheatx_set_skill", &Cmd_SetSkill, 0,
            "CheatX: cheatx_set_skill <skill> <level> -- set skill level [1-30], xp reset to 0.\n"
            "  Skills: stealth, horseriding, fencing, lockpicking, pickpocketing, alchemy,\n"
            "          repairing, drinking, hunter, defense, sword, axe, bow, mace, unarmed,\n"
            "          herbalism, reading, houndmaster, bard, cooking, smithing, fishing,\n"
            "          mining, firstaid, crossbow, shield, dagger, large, tailoring,\n"
            "          armourer, weaponsmithing, shoemaking, gambling.");

        env->pConsole->AddCommand("cheatx_set_perk_points", &Cmd_SetPerkPoints, 0,
            "CheatX: cheatx_set_perk_points <category> <value> -- set perk points [0-65535].\n"
            "  Categories: main, str, agi, vit, spc, <any_skill_name>, all.");

        env->pLog->LogAlways("[CheatX] loaded -- 11 commands registered");
    });
    return true;
}
