#include "combatmodule/S_CombatSettings.h"
#include "Offsets/Offsets.h"

wh::combatmodule::S_CombatSettings* wh::combatmodule::S_CombatSettings::GetInstance() {
    return reinterpret_cast<S_CombatSettings*>(Offsets::GetBase() + Offsets::kCombatSettingsOffset);
}
