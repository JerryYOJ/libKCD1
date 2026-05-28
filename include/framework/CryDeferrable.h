#pragma once

#include <cstdint>

// CryEngine deferrable base class
// Used as a base for deferred-operation entities
// Size: 0x10 (vtable + uint32 state + padding)
// Confirmed from C_Soul constructor: *(soul+0x10) = 0 between CryDeferrable vtable and I_InventoryListener vtable

namespace UnsafeOp {

class CryDeferrable {
public:
    virtual ~CryDeferrable() {}
    uint32_t    m_deferState;           // +0x08  (zeroed in C_Soul ctor)
    uint32_t    _pad0C;                 // +0x0C
};
static_assert(sizeof(CryDeferrable) == 0x10);

}  // namespace UnsafeOp
