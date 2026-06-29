#include "combatmodule/S_CombatActionAttackQueryData.h"
#include "Offsets/Offsets.h"

namespace wh::combatmodule {

// engine ctor sub_1804600BC: installs the engine vtable, defaults id fields to -1,
// allocates the +0xA8 list node.
S_CombatActionAttackQueryData::S_CombatActionAttackQueryData()
{
    using Fn = void(__fastcall*)(S_CombatActionAttackQueryData*, int);
    static REL::Relocation<Fn> fn{ REL::ID(20) };
    fn(this, 1);
}

// manual teardown: destroy the +0xA8 sub-list, then free its 0x30 node with the game allocator.
S_CombatActionAttackQueryData::~S_CombatActionAttackQueryData()
{
    if (!m_pTreeHead) return;
    using Fn = void(__fastcall*)(void*);
    static REL::Relocation<Fn> dtorFn{ REL::ID(1) };  // sub_1802185C4
    dtorFn(&m_pTreeHead);
    Offsets::CryMemFree(m_pTreeHead, 0x30);  // free the 0x30 list node (matches the ctor alloc)
    m_pTreeHead = nullptr;
}

void* S_CombatActionAttackQueryData::GetTypeNameHash(void* outStringHash)
{
    using Fn = void*(__fastcall*)(S_CombatActionAttackQueryData*, void*);
    static REL::Relocation<Fn> fn{ REL::ID(37) };  // vtable[0] GetTypeNameHash
    return fn(this, outStringHash);
}

uint64_t S_CombatActionAttackQueryData::GetCacheKey()
{
    using Fn = uint64_t(__fastcall*)(S_CombatActionAttackQueryData*);
    static REL::Relocation<Fn> fn{ REL::ID(2) };  // vtable[1] GetCacheKey
    return fn(this);
}

}  // namespace wh::combatmodule
