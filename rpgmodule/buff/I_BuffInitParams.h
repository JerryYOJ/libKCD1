#pragma once
#include <cstdint>

// -----------------------------------------------
// I_BuffInitParams — polymorphic buff initialization parameters
// -----------------------------------------------
// RTTI: .?AVI_BuffInitParams@rpgmodule@wh@@
// vtable: 0x1821be970 (4 slots)
//
// Passed to C_BuffInstanceBase::Init() by the buff factory.
// The factory creates C_BuffInitParamsDefault if no custom params are provided.
// Specialized buffs receive their own subclasses carrying extra data.
//
// Interface is minimal: 3 keyed accessors (float, int, entity ref).
// Each subclass responds to its own specific keys and returns defaults for all others.

namespace wh::rpgmodule {

class I_BuffInitParams {
public:
    virtual ~I_BuffInitParams() = default;                                             // [0]
    virtual float GetFloatParam(int nKey) = 0;                                         // [1]
    virtual int GetIntParam(int nKey) = 0;                                             // [2]
    virtual uint64_t* GetEntityRef(uint64_t* pOutWUID) = 0;                            // [3] returns WUID
};
static_assert(sizeof(I_BuffInitParams) == 0x08);

}  // namespace wh::rpgmodule
