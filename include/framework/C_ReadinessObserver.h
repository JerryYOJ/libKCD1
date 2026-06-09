#pragma once

#include <cstdint>

namespace wh {

// -----------------------------------------------
// C_ReadinessObserver — named hook into the readiness/system-event system
// -----------------------------------------------
// RTTI/vtable: wh::C_ReadinessObserver::`vftable'
// Constructor: sub_180F0025C  (binds gEnv.pSystem ref, interns a name, primes timeout)
// Size: 0x70
//
// Embedded by value wherever a subsystem wants to observe a named readiness gate
// (e.g. "BeforeGameSave" in C_PlayerProfileWHManager, "AfterGameLoad" in
// C_SaveGameManager). Holds the readiness manager back-ref and the gate name.

class C_ReadinessObserver {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ReadinessObserver;
    virtual ~C_ReadinessObserver() = default;       // [0] 0x00

    void*       m_pReadinessMgr;    // +0x08  system readiness manager (gEnv.pSystem vf @0x2A0)
    void*       m_name;             // +0x10  CryStringT<char> — interned gate name (refcount at [-0xC])
    char        _pad18[0x08];       // +0x18
    int64_t     m_timeoutMs;        // +0x20  primed to (int)-100000.0
    char        _pad28[0x38];       // +0x28
    void*       m_pNext;            // +0x60  intrusive list link (nulled in ctor)
    uint8_t     m_registered;       // +0x68
    char        _pad69[0x07];       // +0x69
};
static_assert(sizeof(C_ReadinessObserver) == 0x70);

}  // namespace wh
