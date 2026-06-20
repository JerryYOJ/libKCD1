#pragma once

#include <cstdint>

// ===========================================================================
// wh::xgenaimodule::I_SmartEntitySubbrainListener  -  subbrain-change listener interface.
// ===========================================================================
// RTTI: .?AVI_SmartEntitySubbrainListener@xgenaimodule@wh@@ (TD 0x182aa6130). An MI base of
// C_SmartEntity at +0x178; vtable 0x182703a78 (3 slots). PURE interface (sizeof 0x08). NOT
// interfuscated. Slot bodies VERIFIED by decompile; the per-listener gameplay names are inferred.
// ===========================================================================

namespace wh::xgenaimodule {

class I_SmartEntitySubbrainListener {
public:
    virtual void OnSubbrainNotify(uint64_t key, int id) = 0;  // [0] +0x00  sub_180545FA4  hash-keyed notify dispatch
    virtual bool _vf1() = 0;                                   // [1] +0x08  sub_18167B088  subbrain query -> sub_1806638EC
    virtual void _vf2() = 0;                                   // [2] +0x10  sub_1806638A8  subbrain query -> sub_1806638EC
};
static_assert(sizeof(I_SmartEntitySubbrainListener) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::xgenaimodule
