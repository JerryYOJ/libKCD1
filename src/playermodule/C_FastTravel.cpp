#include "playermodule/C_FastTravel.h"
#include "guimodule/C_UIMap.h"
#include "Offsets/Offsets.h"

namespace wh::playermodule {

bool C_FastTravel::IsFastTravelling() const
{
    using Fn = char(__fastcall*)(const C_FastTravel*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFastTravelIsTravellingOffset);
    return fn(this) != 0;
}

void C_FastTravel::Stop()
{
    using Fn = char(__fastcall*)(C_FastTravel*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFastTravelStopOffset);
    fn(this);
}

void C_FastTravel::SetDestination(const Vec3& worldPos, bool forced)
{
    using Fn = void(__fastcall*)(C_FastTravel*, const Vec3*, char);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFastTravelSetDestinationOffset);
    fn(this, &worldPos, forced ? 1 : 0);
}

E_FastTravelResult C_FastTravel::CanStartTravelling()
{
    using Fn = uint32_t(__fastcall*)(C_FastTravel*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFastTravelCanStartOffset);
    return static_cast<E_FastTravelResult>(fn(this));
}

E_FastTravelResult C_FastTravel::StartTravelling()
{
    using Fn = uint32_t(__fastcall*)(C_FastTravel*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFastTravelStartTravellingOffset);
    return static_cast<E_FastTravelResult>(fn(this));
}

bool C_FastTravel::AnswerRandomEvent(uint32_t eventId, uint32_t optionId)
{
    using Fn = char(__fastcall*)(C_FastTravel*, uint32_t, uint32_t);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFastTravelAnswerRandomEventOffset);
    return fn(this, eventId, optionId) != 0;
}

void C_FastTravel::ScheduleStopAtEvent(float seconds, int eventId)
{
    using Fn = void(__fastcall*)(C_FastTravel*, float, int);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kFastTravelScheduleStopOffset);
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
