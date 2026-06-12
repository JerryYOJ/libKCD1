#pragma once

#include <cstdint>

// -----------------------------------------------
// ITimer — CryEngine timer interface (interfuscator-shuffled binary vtable)
// -----------------------------------------------
// SDK: CryEngine/CryCommon/ITimer.h
// Binary vtable for CTimer @ 0x18268b070 (30 slots)
// Accessed via SSystemGlobalEnvironment::GetInstance()->pTimer
//
// Slot assignments verified by decompiling each CTimer vtable entry
// and matching behavior to the SDK method descriptions.

namespace Offsets {

struct ITimer {
    enum ETimer : int32_t {
        ETIMER_GAME = 0,
        ETIMER_UI   = 1,
    };

    virtual void    Dtor(char flags) = 0;                                   // [0]  0x00  scalar deleting dtor
    virtual void    ResetTimer() = 0;                                       // [1]  0x08  sub_180EA9D18 — QueryPerformanceCounter, zeroes timers
    virtual void    UpdateOnFrameStart() = 0;                               // [2]  0x10  sub_1805BAD98 — main frame tick, computes deltas
    virtual float   GetCurrTime(ETimer which = ETIMER_GAME) const = 0;      // [3]  0x18  sub_180374640 — (int)ticks * 1e-5
    virtual double  GetCurrTimeD(ETimer which = ETIMER_GAME) const = 0;     // [4]  0x20  sub_1802A2900 — (int)ticks * 1e-5 (double)
    virtual void*   GetFrameStartTime(ETimer which = ETIMER_GAME) const = 0;// [5]  0x28  sub_180233120 — returns ptr to CTimeValue
    virtual float   GetAsyncCurTime() = 0;                                  // [6]  0x30  sub_1802922A4 — QPC-based, clamped
    virtual void    GetAsyncTime(void* outTimeValue) const = 0;             // [7]  0x38  sub_18029181C — QPC into CTimeValue
    virtual float   GetFrameTime(ETimer which = ETIMER_GAME) const = 0;     // [8]  0x40  sub_18033474C — smoothed/scaled frame dt
    virtual float   GetRealFrameTime() const = 0;                           // [9]  0x48  sub_1803DC5C8 — unscaled frame dt
    virtual float   GetReplicationNetworkFrameTime(uint32_t idx) const = 0; // [10] 0x50  sub_180E9DB50 — scaled by net replication
    virtual float   GetTimeScale() const = 0;                               // [11] 0x58  sub_1805BB010 — timeScale * timeScaleMul
    virtual float   GetFrameRate() = 0;                                     // [12] 0x60  sub_18061E028 — 1.0 / realFrameTime
    virtual void    Serialize(void* ser) = 0;                               // [13] 0x68  sub_18061E004
    virtual void    EnableTimer(bool bEnable) = 0;                          // [14] 0x70  sub_1806F9240 — sets m_enabled byte
    virtual bool    IsTimerEnabled() const = 0;                             // [15] 0x78  sub_1806F9760 — reads m_enabled byte
    virtual float   GetFrameRateSmoothed() = 0;                             // [16] 0x80  sub_18061E028 — same impl as [12]
    virtual void    _vf17() = 0;                                            // [17] 0x88  sub_18061E004
    virtual void    SetTimer(ETimer which, float val) = 0;                  // [18] 0x90  sub_180EAACC0 — bulk timer set
    virtual void    SecondsToDateUTC(void*) = 0;                            // [19] 0x98  sub_1805BABA4
    virtual void    ResetTimeScale() = 0;                                   // [20] 0xA0  sub_180E96A54 — resets all scale channels to 1.0
    virtual void    SetTimeScaleChannel(float scale, uint32_t chan) = 0;    // [21] 0xA8  sub_180EABACC — per-channel time scale
    virtual float   GetProfileFrameBlending() = 0;                         // [22] 0xB0  sub_1806C8120
    virtual void    _vf23() = 0;                                            // [23] 0xB8  sub_180EABB34
    virtual void    _vf24() = 0;                                            // [24] 0xC0  sub_180EAAAC8
    virtual void    _vf25() = 0;                                            // [25] 0xC8  sub_180E9AB28
    virtual void    _vf26() = 0;                                            // [26] 0xD0  sub_1805BAFE0
    virtual void    _vf27() = 0;                                            // [27] 0xD8  sub_1806F9610
    virtual void    _vf28() = 0;                                            // [28] 0xE0  sub_180E97D14
    virtual void    _vf29() = 0;                                            // [29] 0xE8  sub_180E9DB70
};

}  // namespace Offsets
