#pragma once

#include <cstdint>

// -----------------------------------------------
// C_SoulPropertyNotifier
// -----------------------------------------------
// RTTI: .?AVC_SoulPropertyNotifier@rpgmodule@wh@@
// vtable: 0x182208cf8
// Embedded in C_Soul at +0x48, size = 0x20
// Connects soul property changes to the UI notification system.
// Registered as a listener via sub_1804A2938(notifier, 0x54, callback).

namespace wh::rpgmodule {

class C_SoulPropertyNotifier {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SoulPropertyNotifier;
    virtual ~C_SoulPropertyNotifier();      // vfunc[0]

    uint64_t    m_pConnectionList;          // +0x08  (init 0 — linked list of connections)
    uint64_t    m_pCallbackData;            // +0x10  (init 0)
    uint64_t    m_unk18;                    // +0x18  (init 0)
};
static_assert(sizeof(C_SoulPropertyNotifier) == 0x20);

}  // namespace wh::rpgmodule
