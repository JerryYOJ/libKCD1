#include "KCSE/KCSEAPI.h"
#include "Offsets/Offsets.h"
#include "crysystem/SSystemGlobalEnvironment.h"
#include "game/S_GameContext.h"
#include "playermodule/C_PlayerModule.h"
#include "entitymodule/C_Actor.h"
#include "combatmodule/C_CombatActor.h"

int   g_intervalMinutes = 15;
int   g_enabled = 1;
int   g_skipInCombat = 1;
float g_lastSaveTime = 0.f;

static float GameTime()
{
    return SSystemGlobalEnvironment::GetInstance()->pTimer->GetCurrTime();
}

static bool IsPlayerInCombat()
{
    auto* actor = reinterpret_cast<wh::entitymodule::C_Actor*>(Offsets::GetCCryAction()->GetClientActor());
    if (!actor) return false;
    auto* combat = actor->m_pCombatActor;
    if (!combat || !combat->m_pState) return false;
    return combat->m_pState->m_isInCombat;
}

static void RequestAutoSave()
{
    auto* ctx = wh::game::S_GameContext::GetInstance();
    if (!ctx || !ctx->m_pPlayerModule) return;
    ctx->m_pPlayerModule->m_autoSaveRequested = true;
}

static void Tick()
{
    if (g_enabled && g_intervalMinutes > 0) {
        float now = GameTime();
        float thresholdSec = static_cast<float>(g_intervalMinutes) * 60.f;

        if (now - g_lastSaveTime >= thresholdSec) {
            if (!g_skipInCombat || !IsPlayerInCombat()) {
                RequestAutoSave();
                g_lastSaveTime = now;
            }
        }
    }

    KCSE::GetTaskInterface()->AddTask(Tick);
}

KCSE_PLUGIN_INFO("AutoSave", "JerryYOJ", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    kcse->GetMessagingInterface()->RegisterListener([](KCSE::Message* msg) {
        if (msg->type == KCSE::IMessagingInterface::kMessage_DataLoaded) {
            auto* con = SSystemGlobalEnvironment::GetInstance()->pConsole;

            con->RegisterCVarInt("kcse_as_enabled",       &g_enabled,         1, VF_NULL, "1 = autosave enabled");
            con->RegisterCVarInt("kcse_as_interval",      &g_intervalMinutes, 15, VF_NULL, "Autosave interval in minutes");
            con->RegisterCVarInt("kcse_as_skipInCombat",  &g_skipInCombat,     1, VF_NULL, "1 = skip autosave while in combat");

            g_lastSaveTime = GameTime();
        }
    });

    KCSE::GetTaskInterface()->AddTask(Tick);
    return true;
}
