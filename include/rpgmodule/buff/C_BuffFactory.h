#pragma once
#include <cstdint>
#include "../../framework/C_HashMap.h"
#include "../../framework/S_TypeFactoryEntry.h"

// -----------------------------------------------
// Buff factory — buff-specific constants for the engine type registry
// -----------------------------------------------
// The buff system uses the generic wh::shared type factory (C_HashMap + S_TypeFactoryEntry)
// with keys prefixed "wh.rpgmodule.buff.".
//
// Factory singleton:  qword_1835F0228 (C_HashMap<S_TypeFactoryEntry*>)
// Factory accessor:   sub_180449C0C (lazy-init, thread-safe)
// Key prefix:         "wh.rpgmodule.buff." (prepended by sub_1804499D4)
//
// Creation flow:
//   1. XML implementation="Cpp:Constant" → "Cpp:" stripped → "Constant"
//   2. Prepend prefix → "wh.rpgmodule.buff.Constant"
//   3. FNV-1a lookup in factory → calls entry->m_creator → allocates buff instance
//   4. instance->Init(buffData, implKey, initParams) via vtable[0]
//   5. AttachBuff (sub_180449188): stores soul at +0x88, calls ProcessModifiers/UpdateSoul

namespace wh::rpgmodule {

namespace BuffFactory {
    inline constexpr uintptr_t kFactorySingletonRVA     = 0x35F0228;    // qword_1835F0228
    inline constexpr uintptr_t kGetFactoryRVA           = 0x449C0C;     // sub_180449C0C
    inline constexpr uintptr_t kRegisterTypeRVA         = 0x712B68;     // sub_180712B68
    inline constexpr uintptr_t kIdentityPassthroughRVA  = 0x44B450;     // sub_18044B450
    inline constexpr uintptr_t kFNV1aHashRVA            = 0x449CD4;     // sub_180449CD4
    inline constexpr uintptr_t kCreateBuffRVA           = 0x4490A8;     // sub_1804490A8
    inline constexpr uintptr_t kAttachBuffRVA           = 0x449188;     // sub_180449188
    inline constexpr uintptr_t kSoulBuffCtorRVA         = 0x617B58;     // sub_180617B58
    inline constexpr uintptr_t kRegisterInstanceRVA     = 0x617DC4;     // sub_180617DC4
}

}  // namespace wh::rpgmodule
