#include "framework/S_GameTimer.h"
#include "Offsets/Offsets.h"

namespace wh::framework {

bool S_GameTimer::IsExpired() const
{
    using Fn = bool(__fastcall*)(const S_GameTimer*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kGameTimerIsExpiredOffset);
    return fn(this);
}

void S_GameTimer::Arm(int64_t durationMs)
{
    using Fn = void(__fastcall*)(S_GameTimer*, int64_t);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kGameTimerArmOffset);
    fn(this, durationMs);
}

}  // namespace wh::framework
