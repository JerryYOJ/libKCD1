#pragma once

#include <cstdint>
#include "playermodule/I_RandomEventListener.h"
#include "framework/I_ReadinessDebuggable.h"
#include "guimodule/SUIEventSenderBlock.h"
#include "guimodule/SSpatialBucketContainer.h"

// -----------------------------------------------
// C_FastTravel — fast travel simulation controller
// -----------------------------------------------
// RTTI: .?AVC_FastTravel@playermodule@wh@@
// Constructor: sub_18121BF58
// Init:        sub_18121C03C (registers CVars, hooks signals on parent)
// Inherits:
//   [+0x00] I_RandomEventListener (wh::playermodule)  primary vtable 0x1826dd700
//   [+0x08] I_ReadinessDebuggable (wh)                2 slots (vtable 0x1826dd728)
//
// Accessed from wh_pl_FastTravelTo via:
//   *(S_GameContext+0xE8)+0xB0 → C_FastTravel*   (C_PlayerModule+0xB0 VERIFIED via ctor)
//   NOTE: S_GameContext+0xE8 = C_PlayerModule* is still UNVERIFIED
//     +0x90 → C_UIMap*
//     +0xA8 bit 0 → FT blocked flag

namespace wh::guimodule { class C_UIMap; }
namespace wh::entitymodule { class C_Player; }

namespace wh::playermodule {

class C_FastTravel
    : public I_RandomEventListener      // +0x00
    , public I_ReadinessDebuggable      // +0x08  (2 slots)
{
public:
    guimodule::SUIEventSenderBlock m_signalStarted;  // +0x10  FT started signal
    guimodule::SUIEventSenderBlock m_signalStopped;  // +0x50  FT stopped signal

    void*       m_pOwner;                       // +0x80  parent back-ptr (set by Init)
    int32_t     m_nSlowDownPerceptionCount;     // +0x88  wh_pl_FastTravelSlowDownPerceptionCount
    float       m_fSkipTimeStepModif;           // +0x8C  wh_pl_FastTravelSkipTimeStepModif
    guimodule::C_UIMap* m_pUIMap;               // +0x90  C_UIMap back-pointer
    uint64_t    m_unk98;                        // +0x98
    uint64_t    m_unkA0;                        // +0xA0
    uint8_t     m_nFlags;                       // +0xA8  bit 0 = FT blocked
    char        _padA9[0x7];                    // +0xA9
    entitymodule::C_Player* m_pPlayer;           // +0xB0  player entity (soul at +0x650, flags at +0xA30, trespass at +0xA70)
    uint64_t    m_unkB8;                        // +0xB8
    uint64_t    m_unkC0;                        // +0xC0
    uint32_t    m_unkC8;                        // +0xC8
    char        _padCC[0x1C];                   // +0xCC
    uint64_t    m_unkE8;                        // +0xE8
    uint64_t    m_unkF0;                        // +0xF0
    uint64_t    m_unkF8;                        // +0xF8
    uint64_t    m_unk100;                       // +0x100
    uint64_t    m_unk108;                       // +0x108
    uint64_t    m_unk110;                       // +0x110
    uint64_t    m_unk118;                       // +0x118
    uint32_t    m_nMode;                        // +0x120  init 0x11
    char        _pad124[0x4];                   // +0x124
    uint64_t    m_unk128;                       // +0x128
    uint64_t    m_unk130;                       // +0x130
    uint64_t    m_unk138;                       // +0x138
    uint64_t    m_unk140;                       // +0x140
    guimodule::SSpatialBucketContainer m_buckets; // +0x148

    bool IsFTBlocked() const { return (m_nFlags & 1) != 0; }
};

}  // namespace wh::playermodule
