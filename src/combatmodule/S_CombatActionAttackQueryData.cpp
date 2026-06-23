#include "combatmodule/S_CombatActionAttackQueryData.h"
#include "Offsets/Offsets.h"

namespace wh::combatmodule {

// engine ctor sub_1804600BC: installs the engine vtable, defaults id fields to -1,
// allocates the +0xA8 list node. (Runs after the implicit C++ base/field init, so it
// overwrites the vptr with the engine vtable -- which has the same 2 slots in order.)
S_CombatActionAttackQueryData::S_CombatActionAttackQueryData()
{
    using Fn = void(__fastcall*)(S_CombatActionAttackQueryData*, int);
    reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kQueryCtorOffset)(this, 1);
}

// manual teardown (the engine destroys the query this way, not via a vtable dtor):
// destroy the +0xA8 sub-list, then free its 0x30 node with the game allocator.
S_CombatActionAttackQueryData::~S_CombatActionAttackQueryData()
{
    if (!m_pTreeHead) return;
    reinterpret_cast<void(__fastcall*)(void*)>(
        Offsets::GetBase() + Offsets::kQuerySubListDtorOffset)(&m_pTreeHead);
    Offsets::CryMemFree(m_pTreeHead, 0x30);  // free the 0x30 list node (matches the ctor alloc)
    m_pTreeHead = nullptr;
}

void* S_CombatActionAttackQueryData::GetTypeNameHash(void* outStringHash)
{
    using Fn = void*(__fastcall*)(S_CombatActionAttackQueryData*, void*);
    return reinterpret_cast<Fn>(
        Offsets::GetBase() + Offsets::kQueryGetTypeNameHashOffset)(this, outStringHash);
}

uint64_t S_CombatActionAttackQueryData::GetCacheKey()
{
    using Fn = uint64_t(__fastcall*)(S_CombatActionAttackQueryData*);
    return reinterpret_cast<Fn>(
        Offsets::GetBase() + Offsets::kQueryGetCacheKeyOffset)(this);
}

}  // namespace wh::combatmodule
