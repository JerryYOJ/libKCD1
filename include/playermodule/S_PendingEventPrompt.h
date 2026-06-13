#pragma once

#include <memory>

// -----------------------------------------------
// S_PendingEventPrompt — displayed random-encounter prompt (heap, 0x18 bytes)
// -----------------------------------------------
// Built by sub_18121AC14 (timeout from the event row), swapped into
// C_FastTravel+0x108 by sub_18121D9F4 (installer sub_1812266DC). Update tail
// sub_18021144C ticks m_autoAnswerTimeLeft -= frame time, pushes the
// remap(timeLeft, 0..rowTotal) fraction to Flash, and auto-answers the default
// option (sub_18121F068) at <= 0. Freed (0x18) by sub_180834C6C from
// sub_181222EF4 / sub_181222FAC / Stop teardown sub_181223770.
//
// The event class name is descriptive — the weak-locked object (lock helper
// sub_180416B08) carries eventId at +0x18 and the table row shared_ptr at
// +0x20; its RTTI was not pulled.

namespace wh::playermodule {

class C_RandomEvent;

struct S_PendingEventPrompt {
    std::weak_ptr<C_RandomEvent> m_event;   // +0x00  ptr + control block
    float m_autoAnswerTimeLeft;             // +0x10  seconds until auto-answer
};
static_assert(sizeof(S_PendingEventPrompt) == 0x18);

}  // namespace wh::playermodule
