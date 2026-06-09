#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionBlockParams.h"
#include "I_CombatActorActionBlock.h"
#include "I_CombatActionHelperOwner.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionBlock
    : public C_CombatActorAnimatedAction<S_CombatActorActionBlockParams, 2, I_CombatActorActionBlock>,
      public I_CombatActionHelperBlockOwner
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionBlock;
    // Primary vtable: 0x1821B49C0 | Ctor: 0x1804E1268 | Size: 0x128
    // UNIQUE: only action using I_CombatActorActionBlock (not I_CombatActorActionPrivate)
    float                       m_blockTimer;       // (init -100000.0f)
    uint32_t                    _pad;
    C_CombatActionHelperBlock*  m_pBlockHelper;     // alloc 0x28
    bool                        m_blockFlag;        // (init 0)
    uint8_t                     _pad2[7];
};
static_assert(sizeof(C_CombatActorActionBlock) == 0x128);

}  // namespace wh::combatmodule
