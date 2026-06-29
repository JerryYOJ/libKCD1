#include "playermodule/C_FastTravel.h"
#include "guimodule/C_UIMap.h"
#include "Offsets/Offsets.h"

namespace wh::playermodule {

bool C_FastTravel::IsFastTravelling() const
{
    using Fn = char(__fastcall*)(const C_FastTravel*);
    static REL::Relocation<Fn> fn{ REL::ID(14) };  // sub_1803DBE28
    return fn(this) != 0;
}

void C_FastTravel::Stop()
{
    using Fn = char(__fastcall*)(C_FastTravel*);
    static REL::Relocation<Fn> fn{ REL::ID(43) };  // sub_181226EA8
    fn(this);
}

void C_FastTravel::SetDestination(const Vec3& worldPos, bool forced)
{
    using Fn = void(__fastcall*)(C_FastTravel*, const Vec3*, char);
    static REL::Relocation<Fn> fn{ REL::ID(41) };  // sub_181226B24
    fn(this, &worldPos, forced ? 1 : 0);
}

E_FastTravelResult C_FastTravel::CanStartTravelling()
{
    using Fn = uint32_t(__fastcall*)(C_FastTravel*);
    static REL::Relocation<Fn> fn{ REL::ID(39) };  // sub_18121E530
    return static_cast<E_FastTravelResult>(fn(this));
}

E_FastTravelResult C_FastTravel::StartTravelling()
{
    using Fn = uint32_t(__fastcall*)(C_FastTravel*);
    static REL::Relocation<Fn> fn{ REL::ID(42) };  // sub_181226C54
    return static_cast<E_FastTravelResult>(fn(this));
}

bool C_FastTravel::AnswerRandomEvent(uint32_t eventId, uint32_t optionId)
{
    using Fn = char(__fastcall*)(C_FastTravel*, uint32_t, uint32_t);
    static REL::Relocation<Fn> fn{ REL::ID(40) };  // sub_181226864
    return fn(this, eventId, optionId) != 0;
}

void C_FastTravel::ScheduleStopAtEvent(float seconds, int eventId)
{
    using Fn = void(__fastcall*)(C_FastTravel*, float, int);
    static REL::Relocation<Fn> fn{ REL::ID(44) };  // sub_1812271B0
    fn(this, seconds, eventId);
}

bool C_FastTravel::DebugTravelTo(const Vec3& worldPos)
{
    // Mirrors wh_pl_FastTravelTo (sub_1812831A8): only when idle, route the
    // destination through the map UI. Visual-only — see header note.
    if (IsFastTravelling() || !m_pUIMap)
        return false;
    m_pUIMap->ForceStartFastTravel(worldPos, 0);
    return true;
}

}  // namespace wh::playermodule
