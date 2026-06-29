#include "combatmodule/S_AttackCandidateResultHolder.h"
#include "combatmodule/S_CombatActionAttackQueryData.h"
#include "Offsets/Offsets.h"

namespace wh::combatmodule {

S_AttackCandidateResultHolder::S_AttackCandidateResultHolder()
    : m_arena{},
      m_records(RecordVector::allocator_type{&m_arena}),  // allocator serves from m_arena
      m_enumerating(0)
{
    m_arena.m_ptr = m_arena.m_buf;   // mirror the engine arena's self/bump pointer (= &m_buf)
    m_records.reserve(15);           // short_alloc: claim the 15-slot inline arena up front
}

void S_AttackCandidateResultHolder::Enumerate(S_CombatActionAttackQueryData* query)
{
    // sub_18045FD18(ignored, &holder, &query): clears the vector, walks the global moveset,
    // std::vector-appends each matching candidate (growing via the pool allocator), introsorts.
    using Fn = void(__fastcall*)(void*, S_AttackCandidateResultHolder*, S_CombatActionAttackQueryData*);
    static REL::Relocation<Fn> fn{ REL::ID(18) };  // sub_18045FD18 enumerate candidates
    fn(nullptr, this, query);
}

}  // namespace wh::combatmodule
