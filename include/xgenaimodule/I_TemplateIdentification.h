#pragma once

// ===========================================================================
// wh::xgenaimodule::I_TemplateIdentification  -  template-type identity interface (declared `struct`).
// ===========================================================================
// RTTI: .?AUI_TemplateIdentification@xgenaimodule@wh@@ (TD 0x182b1e350; .?AU = struct). The VIRTUAL
// base introduced by C_SmartEntity (vbptr @C_SmartEntity+0x188; vbase @C_SmartArea+0x438). vtable
// 0x1827039c0 (1 slot). PURE interface (sizeof 0x08). NOT interfuscated.
// ===========================================================================

namespace wh::xgenaimodule {

struct I_TemplateIdentification {
    // [0] +0x00  sub_1806F8C40 returns the constant 3 (E_TemplateType; SmartArea == 3). [enum name UNVERIFIED]
    virtual int GetTemplateType() = 0;
};
static_assert(sizeof(I_TemplateIdentification) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::xgenaimodule
