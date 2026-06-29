#include "rpgmodule/C_RPGModule.h"
#include "rpgmodule/buff/C_BuffManager.h"
#include "rpgmodule/S_RpgParams.h"
#include "Offsets/Offsets.h"

wh::rpgmodule::C_RPGModule* wh::rpgmodule::C_RPGModule::GetInstance() {
    static REL::Relocation<C_RPGModule**> p{ REL::ID(877) };
    return *p;
}

wh::rpgmodule::C_BuffManager* wh::rpgmodule::C_BuffManager::GetInstance() {
    static REL::Relocation<C_BuffManager**> p{ REL::ID(872) };
    return *p;
}

wh::rpgmodule::S_RpgParamValues* wh::rpgmodule::S_RpgParamValues::Get() {
    return reinterpret_cast<S_RpgParamValues*>(REL::ID(871).address());
}

wh::rpgmodule::S_RpgParamDefs* wh::rpgmodule::S_RpgParamDefs::Get() {
    return reinterpret_cast<S_RpgParamDefs*>(REL::ID(63).address());
}
