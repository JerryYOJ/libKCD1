// PCH provides: Offsets::*, CryEngine types, rpgmodule headers
#include <Windows.h>
#include "vtable_hook.h"

// Stubs for CryEngine SDK symbols referenced by SDK inline code in the PCH
void CryCreateCriticalSectionInplace(void* p) { InitializeCriticalSection(static_cast<CRITICAL_SECTION*>(p)); }
void CryDeleteCriticalSectionInplace(void* p) { DeleteCriticalSection(static_cast<CRITICAL_SECTION*>(p)); }

// -----------------------------------------------
// KCD Test Plugin — injected DLL
// -----------------------------------------------

using PostUpdateFn = void(__fastcall*)(void* pThis, bool haveFocus, unsigned int updateFlags);

static PostUpdateFn g_origPostUpdate = nullptr;
static SSystemGlobalEnvironment* g_pEnv = nullptr;
static Offsets::IGameFramework* g_pFramework = nullptr;

// -----------------------------------------------
// Player soul lookup via IScriptTable WUID
// -----------------------------------------------

static wh::rpgmodule::C_Soul* FindPlayerSoul() {
    auto rpgModule = Offsets::GetRPGModule();
    if (!rpgModule) return nullptr;
    // C_SoulList is a member of C_RPGModule, accessed via rpgModule->m_pSoulList (+0x548)
    auto soulList = rpgModule->m_pSoulList;
    if (!soulList) return nullptr;
    
    // Get player entity
    auto pEnt = g_pFramework->GetClientEntity();
    if (!pEnt) return nullptr;

    // Entity → script proxy → script table → soul.__ThisWUID
    auto pProxy = reinterpret_cast<Offsets::IEntityScriptProxy*>(pEnt->GetProxy(2));
    if (!pProxy) return nullptr;
    auto pScript = pProxy->GetScriptTable();
    if (!pScript) return nullptr;

    // Get "soul" sub-table
    Offsets::ScriptAnyValue soulVal = {};
    if (!pScript->GetValueAny("soul", &soulVal, false) || soulVal.type != 6)
        return nullptr;
    auto pSoulTable = soulVal.pTable;
    if (!pSoulTable) return nullptr;

    // Get __ThisWUID from soul table
    Offsets::ScriptAnyValue wuidVal = {};
    if (!pSoulTable->GetValueAny("__ThisWUID", &wuidVal, false) || wuidVal.type != 3)
        return nullptr;

    // WUID slot lookup: LOWORD = slot index
    uint16_t slotIdx = static_cast<uint16_t>(wuidVal.nVal);
    if (slotIdx == 0 || slotIdx >= 0x10000) return nullptr;

    return soulList->m_slots[slotIdx].pSoul;
}

// -----------------------------------------------
// Console command: wh_set_main_perk_points <value>
// -----------------------------------------------

static void CmdSetMainPerkPoints(IConsoleCmdArgs* pArgs) {
    if (pArgs->GetArgCount() < 2) {
        g_pEnv->pLog->LogAlways("[Plugin] Usage: wh_set_main_perk_points <value>");
        return;
    }

    int value = atoi(pArgs->GetArg(1));

    auto soul = FindPlayerSoul();
    if (!soul) {
        g_pEnv->pLog->LogAlways("[Plugin] ERROR: could not find player soul");
        return;
    }

    auto perkPts = soul->m_perkMgmt.m_statPerks.m_perkList.m_pPerkPoints;
    if (!perkPts) {
        g_pEnv->pLog->LogAlways("[Plugin] ERROR: perk points not allocated");
        return;
    }

    perkPts->mainLevelPoints = static_cast<uint16_t>(value);
    g_pEnv->pLog->LogAlways("[Plugin] Set main level perk points to %d", value);
}

// -----------------------------------------------
// PostUpdate hook — registers command once on main thread
// -----------------------------------------------

void __fastcall Hooked_PostUpdate(void* pThis, bool haveFocus, unsigned int updateFlags) {
    g_origPostUpdate(pThis, haveFocus, updateFlags);


    g_pEnv->pConsole->AddCommand(
        "wh_set_main_perk_points",
        CmdSetMainPerkPoints,
        0,
        "Set player main level perk points. Usage: wh_set_main_perk_points <value>"
    );
        
    g_pEnv->pLog->LogAlways("[Plugin] Registered: wh_set_main_perk_points");

    VtableHook::Restore<PostUpdateFn>(g_pFramework, 0x60, g_origPostUpdate);
    g_origPostUpdate = nullptr;
}

// -----------------------------------------------
// DLL entry
// -----------------------------------------------

static DWORD WINAPI InitThread(LPVOID hModule) {

    //while (!IsDebuggerPresent());

    g_pEnv = Offsets::GetGEnv();
    while (!g_pEnv->pConsole) {
        Sleep(100);
    }

    g_pFramework = Offsets::GetCCryAction();
    while (!g_pFramework) {
        Sleep(100);
        g_pFramework = Offsets::GetCCryAction();
    }

    g_origPostUpdate = VtableHook::Swap<PostUpdateFn>(
        g_pFramework,
        0x60,
        Hooked_PostUpdate
    );

    return 0;
}

static void Cleanup() {
    if (g_pFramework) {
        g_pEnv->pConsole->RemoveCommand("wh_set_main_perk_points");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, InitThread, hModule, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        Cleanup();
        break;
    }
    return TRUE;
}
