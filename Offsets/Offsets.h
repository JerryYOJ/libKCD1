#pragma once
#include <cstdint>
#include "vtables/IGameFramework.h"

// -----------------------------------------------
// Global singleton offsets and getters
// -----------------------------------------------
// Implementations in Offsets.cpp — resolves WHGame.DLL base internally.

struct SSystemGlobalEnvironment;
namespace wh::rpgmodule { class C_RPGModule; }
namespace wh::guimodule { struct CUIManager; }
namespace wh::game { struct S_GameContext; }

namespace Offsets {

inline static constexpr uintptr_t kGEnvOffset          = 0x29D16B8;
inline static constexpr uintptr_t kCCryActionOffset     = 0x3785D88;  // standalone global, NOT in gEnv
inline static constexpr uintptr_t kRPGModuleOffset      = 0x35AC728;
inline static constexpr uintptr_t kCUIManagerOffset     = 0x2F77888;  // lazy-init singleton (sub_18112D540)
inline static constexpr uintptr_t kGameContextOffset    = 0x4FFD10;   // lazy-init singleton (sub_180430AA4)

SSystemGlobalEnvironment*          GetGEnv();
IGameFramework*                    GetCCryAction();
wh::rpgmodule::C_RPGModule*       GetRPGModule();
wh::guimodule::CUIManager*        GetCUIManager();
wh::game::S_GameContext*           GetGameContext();

}  // namespace Offsets
