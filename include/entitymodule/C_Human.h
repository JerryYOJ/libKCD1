#pragma once

#include <cstdint>
#include "C_Actor.h"
#include "../framework/C_Signal.h"

// -----------------------------------------------
// C_Human — Humanoid actor intermediate class
// -----------------------------------------------
// RTTI: .?AVC_Human@entitymodule@wh@@
// Constructor: 0x180600100  |  Destructor: 0x180600620
//
// vtable (primary):                overrides C_Actor at +0x00
// vtable (IGameObjectView):       overrides at +0x40
// vtable (IGameObjectProfileMgr): overrides at +0x48
//
// The constructor:
//   1. Allocates C_AnimatedHuman (0x180) via sub_1805FFC34
//   2. Calls C_Actor ctor, passing it as m_pAnimatedModel (+0x2F8)
//   3. Overwrites vtables with C_Human's
//   4. Initializes C_Signal<> at +0x930
//   5. Registers ragdoll callback on m_pRagdollManager (+0x178)
//
// Derived: C_NPCActor (0x9F0, vtable-only), C_Player (0xC70)
// Total size: 0x9F0

namespace wh::entitymodule {

class C_HumanHandHelper;

class C_Human : public C_Actor {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Human;
    // No new virtual methods identified — overrides only

    // Signal (void)
    wh::shared::C_Signal<>  m_humanSignal;              // +0x930  (size 0x30)

    uint64_t                m_unk960;                   // +0x960
    uint64_t                m_unk968;                   // +0x968
    uint8_t                 _pad970[5];                 // +0x970
    bool                    m_flag975;                  // +0x975
    uint8_t                 _pad976[2];                 // +0x976
    uint64_t                m_unk978;                   // +0x978
    uint64_t                m_unk980;                   // +0x980
    uint32_t                m_unk988;                   // +0x988

    // Stance params (same layout as C_Actor+0x2C0, size 0x38)
    uint8_t                 m_humanStanceParams[0x38];  // +0x98C

    uint16_t                m_unk9C4;                   // +0x9C4
    uint8_t                 _pad9C6[2];                 // +0x9C6
    uint64_t                m_unk9C8;                   // +0x9C8
    uint32_t                m_unk9D0;                   // +0x9D0
    uint8_t                 _pad9D4[4];                 // +0x9D4
    uint64_t                m_unk9D8;                   // +0x9D8

    void*                   m_pGlobalTableRef;          // +0x9E0  qword_1835A14A0
    C_HumanHandHelper*      m_pHandHelper;              // +0x9E8  (size 0xE0)
};
static_assert(sizeof(C_Human) == 0x9F0);

} // namespace wh::entitymodule
