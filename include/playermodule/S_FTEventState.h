#pragma once

#include <cstdint>

// -----------------------------------------------
// S_FTEventState — per-random-event-id travel mark
// -----------------------------------------------
// Value type of C_FastTravel::m_eventStates (+0x148,
// std::unordered_map<int /*randomEventId*/, S_FTEventState>; node layout
// {next, prev, int key @+0x10, value @+0x14} = 0x18 bytes, verified stock
// MSVC _Hash). ScheduleStopAtEvent find-or-inserts (sub_181219F88) and sets
// stopHere; Stop purges all nodes (sub_1802C9A1C).

namespace wh::playermodule {

struct S_FTEventState {
    uint8_t firedModeMask;  // +0x00  bitmask of (1 << pathPointMode): roles this event already fired in (dedup, sub_18121E494)
    bool    stopHere;       // +0x01  stop travel when this event arrives (ScheduleStopAtEvent)
};
static_assert(sizeof(S_FTEventState) == 0x2);

}  // namespace wh::playermodule
