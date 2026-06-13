#pragma once

#include <cstdint>

// -----------------------------------------------
// S_GameTimer — game-time one-shot countdown (shared utility POD)
// -----------------------------------------------
// No RTTI (plain struct); namespace is a GUESS (helpers live in the generic
// utility region, used by wh::playermodule classes).
//
// Helpers (free functions taking S_GameTimer*):
//   IsExpired: sub_180652DB4 — !(flags&Disabled) && !(flags&Infinite)
//                              && now >= deadline
//   Arm(ms):   sub_180652DEC — NO-OP while Disabled is set (callers clear it
//              first, see C_FastTravel::ScheduleStopAtEvent). ms==INT64_MAX
//              → flags |= (Armed|Infinite), deadline=INT64_MAX; otherwise
//              clears Infinite, deadline = now + ms. Both stamp armTime=now.
//   "now" = qword at sub_180259430()+0x10 (global game-time source, ms).
//
// Known embeddings:
//   C_FastTravel+0x120         (stop-at-event timer; ctor init flags=0x11)
//   C_RandomEventManager+0x88  (10s cooldown ticker;  ctor init flags=0x12,
//                               re-armed by sub_180652D64 check-and-rearm)
//
// The Armed bit is tested by the OWNER (e.g. C_FastTravel::Update tests
// `flags & Armed` before calling IsExpired), not by the helpers themselves.
// Bit 0x10 appears only in the ctor init constants (0x11/0x12) and is read
// nowhere — meaning UNVERIFIED (exhaustive RMW/test byte-pattern sweep over
// the whole binary found no consumer).

namespace wh::framework {

struct S_GameTimer {
    enum E_Flags : uint32_t {
        Disabled = 0x01,  // suppresses Arm() and IsExpired()
        Armed    = 0x02,  // set/cleared by owner code, not by the helpers
        Infinite = 0x04,  // set by Arm(INT64_MAX); IsExpired() never true
        // 0x10 — in ctor init constants only; no reader found
    };

    uint32_t flags;       // +0x00  E_Flags
    uint32_t _pad04;      // +0x04
    int64_t  deadline;    // +0x08  absolute game time (ms); INT64_MAX = infinite
    int64_t  _unk10;      // +0x10  never touched by the helpers
    int64_t  armTime;     // +0x18  game time at Arm()

    bool IsExpired() const;        // sub_180652DB4
    void Arm(int64_t durationMs);  // sub_180652DEC

    bool IsDisabled() const { return (flags & Disabled) != 0; }
    bool IsArmed()    const { return (flags & Armed) != 0; }
};
static_assert(sizeof(S_GameTimer) == 0x20);

}  // namespace wh::framework
