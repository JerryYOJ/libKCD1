#include "framework/S_GameTimer.h"
#include "Offsets/Offsets.h"

namespace wh::framework {

bool S_GameTimer::IsExpired() const
{
    using Fn = bool(__fastcall*)(const S_GameTimer*);
    static REL::Relocation<Fn> fn{ REL::ID(29) };  // sub_180652DB4
    return fn(this);
}

void S_GameTimer::Arm(int64_t durationMs)
{
    using Fn = void(__fastcall*)(S_GameTimer*, int64_t);
    static REL::Relocation<Fn> fn{ REL::ID(30) };  // sub_180652DEC
    fn(this, durationMs);
}

}  // namespace wh::framework
