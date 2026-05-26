#pragma once

#include "C_Action.h"

namespace wh::framework {

// ---------------------------------------------------------------------------
// C_ParamAction<TParams, TBase> — extends TBase with an embedded params struct.
//
// RTTI pattern: .?AV?$C_ParamAction@U<TParams>@...@@V<TBase>@...@@@framework@wh@@
// Adds sizeof(TParams) bytes at offset 0xD0 (immediately after C_Action base).
// The params struct may have its own vtable (polymorphic params) or be POD.
// ---------------------------------------------------------------------------
template<typename TParams, typename TBase>
class C_ParamAction : public TBase {
public:
    TParams m_params;   // +0xD0
};

}  // namespace wh::framework
