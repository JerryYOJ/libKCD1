#pragma once

#include <cstdint>
#include <cstddef>

// ===========================================================================
// wh::rpgmodule::S_TimedFactionEvent  -  a delayed (propagation-scheduled)
// reputation/angriness change pending on a faction.
// ===========================================================================
// Element of the vector at C_Faction+0x240 (control: begin@+0x248, end@+0x250,
// cap@+0x258). Element stride 0x40 [CONFIRMED]: the push sub_18118A09C copies a
// full 0x40 bytes and advances the end pointer by 0x40.
//
// Field meanings are from the enqueue writer sub_18119E1C0 (FactionReputation_
// EnqueueDelayed) per analysis/regional_reputation/regional_reputation_re.md S6.5;
// only the 0x40 stride was re-verified this session. fireTime = now + delay, where
// delay (ms) = 1000 * max(0, (rand01*2*Bias + (Time - Bias)) * delayMult), with
// Time=10800s (RPGParams 0x1D6), Bias=1800s (0x1D7).
namespace wh::rpgmodule {

struct S_TimedFactionEvent {
    uint32_t    flags;              // +0x00  [CONFIRMED] bit3 (0x8) => use game clock; deser inits 0x11
    uint8_t     _pad04[4];          // +0x04
    int64_t     fireTime;           // +0x08  [CONFIRMED] game-clock time the event fires (now + delay)
    uint8_t     _gap10[8];          // +0x10  [UNVERIFIED] (copied by push; meaning not decoded)
    int64_t     clockBase;          // +0x18  [CONFIRMED] game-clock base captured at enqueue
    float       amount;             // +0x20  [CONFIRMED] reputation/angriness delta
    uint8_t     targetMask;         // +0x24  [CONFIRMED] E_ReputationChangeTarget byte
    uint8_t     flag;               // +0x25  [CONFIRMED] canChangeHostility / sign byte
    uint8_t     _pad26[2];          // +0x26
    float       delayMult;          // +0x28  [CONFIRMED] delay multiplier (1.0 full; 1-prox in nearby spread)
    uint8_t     _gap2C[0x0C];       // +0x2C  [UNVERIFIED] (copied by push; meaning not decoded)
    uint32_t    changeId;           // +0x38  [CONFIRMED] reputation_change row id
    uint8_t     _pad3C[4];          // +0x3C  padding to 0x40 element stride
};
static_assert(sizeof(S_TimedFactionEvent) == 0x40, "S_TimedFactionEvent size");

}  // namespace wh::rpgmodule
