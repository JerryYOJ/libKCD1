#pragma once

#include "../framework/C_ParamAction.h"
#include "C_CombatActorObject.h"
#include "I_CombatActorAction.h"
#include "I_CombatActionHelperOwner.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActorParamAction<TParams, TPrivate> — convenience alias.
// RTTI pattern: .?AV?$C_CombatActorParamAction@U<TParams>@@V<TPrivate>@@@combatmodule@wh@@
// ---------------------------------------------------------------------------
template<typename TParams, typename TPrivate>
using C_CombatActorParamAction_Base =
    wh::framework::C_ParamAction<TParams, wh::framework::C_Action<TPrivate>>;

// ---------------------------------------------------------------------------
// C_CombatActorAction<TPrivate, TParamAction> — adds C_CombatActorObject as MI.
//
// RTTI pattern: .?AV?$C_CombatActorAction@V<TPrivate>@@V<TParamAction>@@@combatmodule@wh@@
// In MSVC MI layout, C_CombatActorObject is placed AFTER TParamAction's data.
// Offset of C_CombatActorObject = 0xD0 + sizeof(TParams).
// No additional data members in this template.
// ---------------------------------------------------------------------------
template<typename TPrivate, typename TParamAction>
class C_CombatActorAction : public TParamAction, public C_CombatActorObject {
};

// ---------------------------------------------------------------------------
// C_CombatActorAnimatedAction<TParams, N, TPrivate> — adds anim scope data.
//
// RTTI pattern: .?AV?$C_CombatActorAnimatedAction@U<TParams>@@$0<N>@@V<TPrivate>@@@combatmodule@wh@@
// Adds 8 bytes of state + N * 8 bytes of anim callback slots.
// Total added: 8 + 8*N bytes after C_CombatActorObject.
// ---------------------------------------------------------------------------
template<typename TParams, int N, typename TPrivate>
class C_CombatActorAnimatedAction
    : public C_CombatActorAction<TPrivate, C_CombatActorParamAction_Base<TParams, TPrivate>>
{
public:
    uint8_t     m_animState[8];         // state/flags from animated action base
    uint64_t    m_animCallbacks[N];     // anim scope callback slots
};

// ---------------------------------------------------------------------------
// C_CombatActorActionPerfectBlockBase<TParams, N> — adds helper owner MI.
//
// RTTI pattern: .?AV?$C_CombatActorActionPerfectBlockBase@U<TParams>@@$0<N>@@@combatmodule@wh@@
// Adds I_CombatActionHelperBlockOwner and I_CombatActionHelperAttackOwner as MI,
// plus own data for helper pointers and PB state.
// ---------------------------------------------------------------------------
class C_CombatActionHelperBlock;
class C_CombatActionHelperAttack;

template<typename TParams, int N>
class C_CombatActorActionPerfectBlockBase
    : public C_CombatActorAnimatedAction<TParams, N, I_CombatActorActionPrivate>,
      public I_CombatActionHelperBlockOwner,
      public I_CombatActionHelperAttackOwner
{
public:
    uint16_t    m_pbBaseFlags;          // (init 0)
    bool        m_pbBaseFlag2;          // (init 0)
    uint8_t     _pbPad[5];
    C_CombatActionHelperBlock*  m_pBlockHelper;     // alloc 0x28
    C_CombatActionHelperAttack* m_pAttackHelper;    // alloc 0x38
    C_CombatActionHelperBlock*  m_pBlockHelperCopy; // copy of m_pBlockHelper
    uint32_t    m_pbUnknown;            // (init 0)
    uint32_t    _pbPad2;
};

}  // namespace wh::combatmodule
