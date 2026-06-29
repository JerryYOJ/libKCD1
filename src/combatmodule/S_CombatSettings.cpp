#include "combatmodule/S_CombatSettings.h"
#include "Offsets/Offsets.h"

wh::combatmodule::S_CombatSettings* wh::combatmodule::S_CombatSettings::GetInstance() {
    return reinterpret_cast<S_CombatSettings*>(REL::ID(878).address());
}
