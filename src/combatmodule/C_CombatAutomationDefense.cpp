#include "combatmodule/C_CombatAutomationDefense.h"
#include "Offsets/Offsets.h"

namespace wh::combatmodule {

void C_CombatAutomationDefense::SetReactionWeights(const S_ReactionWeights& weights)
{
    using Fn = void(__fastcall*)(C_CombatAutomationDefense*, const S_ReactionWeights*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kSetReactionWeightsOffset);
    fn(this, &weights);
}

void C_CombatAutomationDefense::ClearReactionWeights()
{
    using Fn = void(__fastcall*)(C_CombatAutomationDefense*, const S_ReactionWeights*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kSetReactionWeightsOffset);
    fn(this, nullptr);
}

}  // namespace wh::combatmodule
