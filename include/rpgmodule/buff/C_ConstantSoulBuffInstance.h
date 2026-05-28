#pragma once
#include "C_SoulBuffInstance.h"

// -----------------------------------------------
// C_ConstantSoulBuffInstance — permanent buff (never expires)
// -----------------------------------------------
// RTTI: .?AVC_ConstantSoulBuffInstance@rpgmodule@wh@@
// vtable: 0x1821cdf68
// Factory key: "wh.rpgmodule.buff.Constant"  (XML: implementation="Cpp:Constant")
// Constructor: sub_1806179F8
// Size: 0xD0 (same as C_SoulBuffInstance — no additional fields)
//
// The simplest concrete buff: Update() returns true unconditionally,
// GetProgress() reports no timer bar. Used for most perk buffs and
// permanent stat modifiers.
//
// Example buff params: "str+2,agi-1", "spc*1.8", "rdq>1"

namespace wh::rpgmodule {

class C_ConstantSoulBuffInstance : public C_SoulBuffInstance {
public:
    // Buff never expires.
    bool Update() override { return true; }                                            // [1] 0x1806F82B0

    // No progress info (constant buffs have no timer bar).
    // Writes {progress=0.0, valid=true} to outResult.
    // UNVERIFIED: exact return struct layout
    void* GetProgress(void* pOutResult);                                               // [9] 0x1806FE980

    // Returns "constant" type name string.
    void* GetTypeName(void* pOutStr) override;                                         // [13] 0x1806FEA30

    // Checks "constant" then chains to C_SoulBuffInstance::CastTo.
    C_BuffInstanceBase* CastTo(const void* pTypeName) override;                        // [14] 0x18115E5C4
    C_BuffInstanceBase* CastToConst(const void* pTypeName) override;                   // [15] 0x18115E5C4
};
static_assert(sizeof(C_ConstantSoulBuffInstance) == 0xD0);

}  // namespace wh::rpgmodule
