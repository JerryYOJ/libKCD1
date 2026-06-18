#pragma once

#include <cstdint>

namespace wh::xgenaimodule::BehaviorTree::Expressions {

// -----------------------------------------------
// C_ExpressionRef -- 16-byte embedded reference to a bound BT expression (I_Expression).
// -----------------------------------------------
// Embedded by value in C_Variable at +0x38 (an optional condition/binding expression).
// Layout from the C_Variable ctor sub_180253B98 (writes &C_ExpressionRef::vftable @+0x00,
// 0 @+0x08) and dtor sub_1805B3E24 (releases the held expression via sub_18061FF98).
struct C_ExpressionRef {
    virtual ~C_ExpressionRef() = default;   // I_Expression vptr @ +0x00
    void* m_pExpression;                     // +0x08  held expression (owned); null by default
};
static_assert(sizeof(C_ExpressionRef) == 0x10);

}  // namespace wh::xgenaimodule::BehaviorTree::Expressions
