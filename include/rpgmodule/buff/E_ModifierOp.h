#pragma once
#include <cstdint>

namespace wh::rpgmodule {

// Modifier operation type, determines how a modifier's value is applied to a stat.
// Parsed from buff param string operators at sub_18027C848.
// Modifiers are sorted ascending by this enum during CommitModifiers,
// so additive ops apply first, then multiplicative, then clamps, then overrides.
//
// Application formula (c = current, b = base, v = value, e = effectiveness):
//   AddAbs:      c += e * v
//   SubAbs:      c -= e * v
//   MulBase:     c += (v - 1.0) * b * e
//   MulCurrent:  c += (v - 1.0) * c * e
//   ClampMax:    c = min(v, c)
//   ClampMin:    c = max(v, c)
//   SubFromVal:  c = v - c
//   Override:    c = v
enum class E_ModifierOp : int32_t {
    AddAbs      = 0,  // '+'
    SubAbs      = 1,  // '-'
    MulBase     = 2,  // '*'
    MulCurrent  = 3,  // '%'
    ClampMax    = 4,  // '<'
    ClampMin    = 5,  // '>'
    SubFromVal  = 6,  // '!'
    Override    = 7,  // '='
    Invalid     = 8
};

}  // namespace wh::rpgmodule
