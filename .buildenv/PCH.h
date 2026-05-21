// Precompiled header for KCD RE project
// Includes all RE'd class headers and Offsets vtable interfaces.
// Does NOT include the 300+ database table row headers (include those individually).

#pragma once

// ---- CryEngine SDK (types, enums, structs — NOT interfuscated interfaces) ----
#include "CryEngine/CryCommon/BaseTypes.h"
#include "CryEngine/CryCommon/CryExtension/CryGUID.h"

// ---- Offsets: interfuscated CryEngine vtables (binary order) ----
#include "crysystem/SSystemGlobalEnvironment.h"  // gEnv struct (binary layout)
#include "Offsets/Offsets.h"                     // singleton offsets + getters
#include "Offsets/vtables/VCall.h"
#include "Offsets/vtables/IEntity.h"
#include "Offsets/vtables/IScriptTable.h"

// ---- CryEngine implementation classes ----
#include "crysystem/CXConsole.h"
#include "crysystem/CLog.h"
#include "crysystem/CScriptSystem.h"

// ---- Common RE utilities ----
namespace wh::guimodule {
struct CStrLess {
    bool operator()(const char* a, const char* b) const { return std::strcmp(a, b) < 0; }
};
}  // namespace wh::guimodule

// ---- Warhorse guimodule ----
#include "guimodule/CUIManager.h"
#include "guimodule/C_UIMap.h"

// ---- Warhorse rpgmodule ----
#include "rpgmodule/C_Soul.h"
#include "rpgmodule/C_SoulList.h"
#include "rpgmodule/C_RPGModule.h"
#include "rpgmodule/C_PerkList.h"
#include "rpgmodule/S_PerkPointCounters.h"
#include "rpgmodule/S_PerkSubsystem.h"
#include "rpgmodule/S_PerkManagement.h"
#include "rpgmodule/S_PerkDefinition.h"
#include "rpgmodule/C_Effect.h"
#include "rpgmodule/S_RpgParams.h"
#include "rpgmodule/C_FactionManager.h"

// ---- Warhorse databasemodule ----
// NOT included here — has redefinition conflicts between I_DatabaseListener.h
// and I_DatabaseModule.h. Include individually as needed.