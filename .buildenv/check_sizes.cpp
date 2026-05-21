// Compile this file to verify all static_assert(sizeof(...)) in the RE headers.
// Open RE/.build/ in Visual Studio via CMake and build — any size mismatch
// will be a compile error.

#include "CryEngine/CryCommon/BaseTypes.h"   // uint64 etc. needed by CryGUID.h

#include "rpgmodule/C_Soul.h"                // pulls in most rpgmodule headers
#include "rpgmodule/C_RPGModule.h"
#include "rpgmodule/C_Effect.h"
#include "rpgmodule/S_RpgParams.h"
#include "rpgmodule/S_PerkPointCounters.h"
#include "crysystem/CXConsole.h"
#include "crysystem/CLog.h"
#include "crysystem/CScriptSystem.h"
