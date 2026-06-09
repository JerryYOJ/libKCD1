#pragma once

#include <cstdint>
#include "C_LinkableObject.h"
#include "../framework/C_HashMap.h"
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::C_MessageCapableObject : C_LinkableObject
// ===========================================================================
// Ctor:    sub_1802784C0(this, &ctorArgs)
// vtable:  0x1821A4478 (17 slots) — overrides 0/1/2, adds slot 16 (pure at
// this level; implemented by C_IntelligentObject). Registers into
// qword_1837999D0. Joins the global C_NPC2NPCInterweb (singleton
// qword_1835013B0) via the node at +0xA0.
// size 0x118.
// ===========================================================================

namespace wh::xgenaimodule {

class C_MessageCapableObject : public C_LinkableObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MessageCapableObject;
    // --- primary-vtable addition (slot 16) ---
    // Introduced here as a pure/abstract slot; C_IntelligentObject provides the body.
    virtual int64_t vf16_MessageHook();   // [16] +0x80  [name UNVERIFIED]

    // --- fields (ctor sub_1802784C0) ---
    void* m_interwebNode[2];                 // +0xA0  C_NPC2NPCInterweb registration node (sub_1802787DC) [size LIKELY 0x10]
    void* m_owner;                           // +0xB0  owner/context (ctor arg)
    uint8_t m_delegate[0x20];                // +0xB8  std::function-style delegate pair (sub_1803A95AC / sub_180273D10) [UNVERIFIED]
    wh::shared::C_HashMap<wh::framework::WUID, void*> m_messageMap;  // +0xD8  (0x40) message/handler map [key/value UNVERIFIED]
};
static_assert(sizeof(C_MessageCapableObject) == 0x118);

}  // namespace wh::xgenaimodule
