#pragma once

#include <cstdint>
#include <vector>
#include "C_Variable.h"
#include "S_VariableValue.h"   // the 0x10 storage element

namespace wh::xgenaimodule {

// ===========================================================================
// C_SingleVariable -- a flat "single value" AI/brain variable.
// ===========================================================================
// RTTI: .?AVC_SingleVariable@xgenaimodule@wh@@ ; vtable 0x1821A3C40 ; ctor sub_180253B30.
// The entire payload is one value vector at +0x48 (base C_Variable is 0x48). GetValue (vtbl[0x20] =
// sub_1802B61F0) decodes m_value into a ScriptAnyValue; SetValue (vtbl[0x28] = sub_1803BA3B0) writes
// it and fires change callbacks. The vector is sized to the type's field count (usually 1). Size 0x60.
// (C_SingleVariableLuaReadOnly shares this exact layout; only its vtable differs -- read-only writes.)
class C_SingleVariable : public C_Variable {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SingleVariable;
    // m_value: one S_VariableValue per type field (decode via the engine converter, not raw).
    // MSVC std::vector {first,last,end}; usually 1 element (resized to the type's field count).
    std::vector<S_VariableValue> m_value;   // +0x48  (0x18)
};
static_assert(sizeof(C_SingleVariable) == 0x60);

}  // namespace wh::xgenaimodule
