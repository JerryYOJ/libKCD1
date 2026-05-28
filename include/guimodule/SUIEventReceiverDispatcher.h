#pragma once

#include <cstdint>
#include <map>

// -----------------------------------------------
// SUIEventReceiverDispatcher<T> — CryEngine template
// -----------------------------------------------
// Dispatches Flash UI events to the owning IUIGameEventSystem.
// Each instantiation has its own vtable (interfuscator-shuffled).
//
// Known instantiation:
//   SUIEventReceiverDispatcher<C_UIMap>
//   RTTI: .?AU?$SUIEventReceiverDispatcher@VC_UIMap@guimodule@wh@@@@
//   Binary vtable at 0x1826d15d8 (3 slots):
//     [0] sub_18110EB94
//     [1] sub_1806FE6B0
//     [2] sub_181129AF8
//
// Size: 0x18 (vtable ptr + std::map<const char*, void*>)

namespace wh::guimodule {

template<typename T>
struct SUIEventReceiverDispatcher {
    virtual void _vf0() {}   // [0] 0x00
    virtual void _vf1() {}   // [1] 0x08
    virtual void _vf2() {}   // [2] 0x10

    std::map<const char*, void*, CStrLess> m_dispatchMap; // +0x08
};

static_assert(sizeof(SUIEventReceiverDispatcher<void>) == 0x18);

}  // namespace wh::guimodule
