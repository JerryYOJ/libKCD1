#pragma once

#include <cstdint>
#include "../CryEngine/CryCommon/smartptr.h"

// ---------------------------------------------------------------------------
// I_Action -- ref-counted action base.
//
// RTTI base: _i_multithread_reference_target<int>
// Size: 0x10 (vtable + refcount + pad)
//
// Inherits CryEngine's multithread ref-counted base directly.
// AddRef()  -> CryInterlockedIncrement(this+0x08)   (sub_1806F8410)
// Release() -> CryInterlockedDecrement(this+0x08)   (sub_180370BBC)
// ---------------------------------------------------------------------------

namespace wh::framework {

class I_Action : public _i_multithread_reference_target<int> {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_Action;
    // No additional members -- _i_multithread_reference_target provides:
    //   +0x00: vtable
    //   +0x08: volatile int m_nRefCounter
    //   +0x0C: (pad to 0x10)
};
static_assert(sizeof(I_Action) == 0x10);

}  // namespace wh::framework
