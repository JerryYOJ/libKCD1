#include <Windows.h>
#include "Offsets.h"
#include "crysystem/SSystemGlobalEnvironment.h"
#include "rpgmodule/C_RPGModule.h"
#include "guimodule/CUIManager.h"
#include "game/S_GameContext.h"

static uintptr_t GetBase() {
    static uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA("WHGame.DLL"));
    return base;
}

SSystemGlobalEnvironment* Offsets::GetGEnv() {
    return reinterpret_cast<SSystemGlobalEnvironment*>(GetBase() + kGEnvOffset);
}

Offsets::IGameFramework* Offsets::GetCCryAction() {
    return *reinterpret_cast<IGameFramework**>(GetBase() + kCCryActionOffset);
}

wh::rpgmodule::C_RPGModule* Offsets::GetRPGModule() {
    return *reinterpret_cast<wh::rpgmodule::C_RPGModule**>(GetBase() + kRPGModuleOffset);
}

wh::guimodule::CUIManager* Offsets::GetCUIManager() {
    return *reinterpret_cast<wh::guimodule::CUIManager**>(GetBase() + kCUIManagerOffset);
}

wh::game::S_GameContext* Offsets::GetGameContext() {
    return *reinterpret_cast<wh::game::S_GameContext**>(GetBase() + kGameContextOffset);
}
