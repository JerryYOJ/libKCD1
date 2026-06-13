#pragma once

#include <cstdint>

// -----------------------------------------------
// S_FTSlowdownTracker — fast-travel time-scale helper (name is ours, no RTTI)
// -----------------------------------------------
// Size: 0x90, heap-allocated raw (no vtable).
// Constructor: sub_18121C03C(this, C_FastTravel* owner)
//   - registers CVars binding +0x88/+0x8C:
//       wh_pl_FastTravelSlowDownPerceptionCount → +0x88
//       wh_pl_FastTravelSkipTimeStepModif       → +0x8C
//     (these were previously misattributed to C_FastTravel+0x88/+0x8C!)
//   - subscribes OnFTStarted (sub_181223AD4) / OnFTStopped (sub_181223A08) to
//     the owner's m_signalStarted (+0x10) / m_signalStopped (+0x50): while
//     travelling it watches entities appearing near the player (callback
//     sub_181223C20 — keeps souls [type 5] and 0xD-type objects that pass a
//     relevance check) and collects their ids in the watcher blocks below.
// Created and stored at C_FastTravel+0x140 by C_FastTravel registration
// (sub_181220D6C), which also registers callback sub_180B1B03C with the
// perception manager (sub_1806308B0 / sub_180245EC0).
//
// ComputeSlowdownModifier (sub_18121F17C, called from C_FastTravel::Update
// while PerceptionSuspended):
//   if (m_fSkipTimeStepModif != 0) return it;            // fixed override
//   return 1 - clamp((countA + countB) / m_nSlowDownPerceptionCount, 0, 1);
// The result scales the engine fixed timestep (t_FixedStep CVar via the
// magic-static at sub_181286FE8) — i.e. world-time acceleration slows down
// as more perception-relevant entities are near the travel path.

namespace wh::playermodule {

class C_FastTravel;

struct S_FTSlowdownTracker {
    char     _watcherStarted[0x10];      // +0x00  watcher block A (sub_18030D1A8-initialized)
    int32_t  m_nWatchedCountA;           // +0x10  tracked-entity count A
    char     _watcherStartedTail[0x2C];  // +0x14
    char     _watcherStopped[0x10];      // +0x40  watcher block B (entity-id list, sub_180450F78)
    int64_t  m_nWatchedCountB;           // +0x50  tracked-entity count B (read as qword)
    char     _watcherStoppedTail[0x28];  // +0x58
    C_FastTravel* m_pFastTravel;         // +0x80  owner back-pointer
    int32_t  m_nSlowDownPerceptionCount; // +0x88  wh_pl_FastTravelSlowDownPerceptionCount
    float    m_fSkipTimeStepModif;       // +0x8C  wh_pl_FastTravelSkipTimeStepModif (0 = auto)
};
static_assert(sizeof(S_FTSlowdownTracker) == 0x90);

}  // namespace wh::playermodule
