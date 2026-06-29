#include "combatmodule/C_CombatAutomationDefense.h"
#include "Offsets/Offsets.h"

namespace wh::combatmodule {

void C_CombatAutomationDefense::SetReactionWeights(const S_ReactionWeights& weights)
{
    using Fn = void(__fastcall*)(C_CombatAutomationDefense*, const S_ReactionWeights*);
    static REL::Relocation<Fn> fn{ REL::ID(22) };  // sub_1804F83C8
    fn(this, &weights);
}

void C_CombatAutomationDefense::ClearReactionWeights()
{
    using Fn = void(__fastcall*)(C_CombatAutomationDefense*, const S_ReactionWeights*);
    static REL::Relocation<Fn> fn{ REL::ID(22) };  // sub_1804F83C8 (nullptr clears)
    fn(this, nullptr);
}

}  // namespace wh::combatmodule
