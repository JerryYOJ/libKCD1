#include "rpgmodule/C_RPGModule.h"
#include "rpgmodule/buff/C_BuffManager.h"
#include "Offsets/Offsets.h"

wh::rpgmodule::C_RPGModule* wh::rpgmodule::C_RPGModule::GetInstance() {
    return *reinterpret_cast<C_RPGModule**>(Offsets::GetBase() + Offsets::kRPGModuleOffset);
}

wh::rpgmodule::C_BuffManager* wh::rpgmodule::C_BuffManager::GetInstance() {
    return *reinterpret_cast<C_BuffManager**>(Offsets::GetBase() + Offsets::kBuffManagerOffset);
}
