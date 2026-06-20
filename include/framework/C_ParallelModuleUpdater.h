#pragma once

#include <cstdint>

// ===========================================================================
// wh::framework::C_ParallelModuleUpdater  (size 0x4C0)
// ===========================================================================
// RTTI: .?AVC_ParallelModuleUpdater@framework@wh@@ (??_R0 0x1829EA0B0).
// Primary vtable 0x1826A2340 (12 slots; slot[12] is the next object's COL). ctor sub_180F061D4.
// A module-update job dispatcher: it embeds a 0x40-slot lock-free job ring at +0x10 (built by
// sub_180F05C04) used to run a module's parallel update graph. Inherited as a SECONDARY base by
// modules that need parallel updates (e.g. C_RPGModule @ +0x88).
//
// Layout from ctor sub_180F061D4 (sets vtable; sub_180F05C04(this+0x10); this+0x4B8 = 0) and the
// ring ctor sub_180F05C04. The ring's exact lock-free field semantics are only partly recovered;
// un-RE'd spans are flagged [UNVERIFIED] rather than collapsed to one blob. Size 0x4C0 confirmed by
// C_RPGModule's layout (this base spans +0x88..+0x548, where C_RPGModule's own members begin).
// ===========================================================================

namespace wh::framework {

class C_ParallelModuleUpdater {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ParallelModuleUpdater;

    virtual ~C_ParallelModuleUpdater() = default;   // [0]  0x180F07080
    virtual void _vf1() = 0;                          // [1]  no-op (0x1802E39B0)
    virtual void _vf2() = 0;                          // [2]  no-op
    virtual void _vf3() = 0;                          // [3]  no-op
    virtual void _vf4() = 0;                          // [4]  no-op
    virtual void _vf5() = 0;                          // [5]  0x1803E8698
    virtual void _vf6() = 0;                          // [6]  no-op
    virtual void _vf7() = 0;                          // [7]  no-op
    virtual void _vf8() = 0;                          // [8]  no-op
    virtual void _vf9() = 0;                          // [9]  0x180A2CA89
    virtual bool _vf10() = 0;                         // [10] returns 1 (0x1806F8140)
    virtual void _vf11() = 0;                         // [11] 0x180A2CA89

    // embedded lock-free job ring at +0x10 (ctor sub_180F05C04). 0x40 fixed slots of 0x10 bytes
    // plus head/capacity/tail atomics. Field names below are best-effort from the ctor inits.
    struct S_JobRing {
        struct S_Slot { uint8_t m_data[0x10]; };   // 0x10 each; first word seeded to 0x40 at init

        uint8_t  m_flag00;        // +0x00  init 0
        uint8_t  _pad01[3];       // +0x01
        uint32_t _unk04;          // +0x04  init 0
        uint32_t _unk08;          // +0x08  init 0
        int32_t  m_head;          // +0x0C  atomic, init 0x40
        uint8_t  _unk10[0x3C];    // +0x10  [UNVERIFIED]
        S_Slot   m_slots[0x40];   // +0x4C  (0x400) ring slots
        int32_t  m_capacity;      // +0x44C atomic, init 0x40
        uint64_t _unk450;         // +0x450 init 0
        uint8_t  _unk458[0x40];   // +0x458 [UNVERIFIED]
        uint64_t _unk498;         // +0x498 init 0
        int32_t  m_tail;          // +0x4A0 atomic, init 0
        uint32_t _pad4A4;         // +0x4A4
    };
    static_assert(sizeof(S_JobRing) == 0x4A8);

    uint64_t  _unk08;             // +0x08  not set by ctor [UNVERIFIED]
    S_JobRing m_jobRing;          // +0x10  (0x4A8)
    uint32_t  m_state;            // +0x4B8 init 0 (set by sub_180F061D4)
    uint32_t  _pad4BC;            // +0x4BC -> 0x4C0
};
static_assert(sizeof(C_ParallelModuleUpdater) == 0x4C0, "C_ParallelModuleUpdater (ctor sub_180F061D4)");

}  // namespace wh::framework
