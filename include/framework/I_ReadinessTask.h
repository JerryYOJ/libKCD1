#pragma once

#include <cstdint>
#include "framework/I_ReadinessDebuggable.h"

namespace wh {

// -----------------------------------------------
// I_ReadinessTask — Warhorse async-readiness participant
// -----------------------------------------------
// RTTI: .?AVI_ReadinessTask@wh@@  (derives from I_ReadinessDebuggable)
//
// Subsystems that must report when they are "ready" before a save/load or level
// transition proceeds (e.g. C_PlayerProfileWHManager). The readiness manager
// polls IsReady() and gates progress on the result.
//
// Adds 2 slots on top of I_ReadinessDebuggable's 2, giving the 4-slot primary
// vtable seen on C_PlayerProfileWHManager (0x1826a2318). Slot order is
// interfuscator-shuffled in retail, so the indices below are logical:
//   IsReady     sub_1806F0F3C  returns true once all pending-state fields are clear
//   GetTypeMask sub_1806F9D60  returns a constant requirement mask (0x4008)

class I_ReadinessTask : public I_ReadinessDebuggable {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_ReadinessTask;
    virtual bool     IsReady(uint8_t flags) = 0;   // pending work drained?
    virtual uint32_t GetTypeMask() = 0;            // readiness requirement bitmask
};

}  // namespace wh
