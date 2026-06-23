#pragma once

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// S_CombatQueryData<TDerived> -- CRTP base for the combat "query" request
// objects passed to the action factories. Data-less; it owns the 2-slot vtable.
//
// Confirmed from the RTTI of S_CombatActionAttackQueryData: a single base at
// offset 0 whose type descriptor is ".?AU?$S_CombatQueryData@U...", i.e.
// S_CombatQueryData<S_CombatActionAttackQueryData>. The two slots are shared
// across query instantiations (slot 0 is a generic type-name hasher):
//   vtable[0] GetTypeNameHash -- hashes the derived RTTI type name into an out StringHash
//   vtable[1] GetCacheKey     -- hashes the query's fields into the candidate-cache key
// [V] workflow wf_05aec32f + RTTI walk (vtable 0x1821A33B8, CHD 0x182474398).
// ---------------------------------------------------------------------------
template <class TDerived>
struct S_CombatQueryData {
    virtual void* GetTypeNameHash(void* outStringHash) = 0;  // vtable[0]
    virtual uint64_t GetCacheKey() = 0;                      // vtable[1]
};

}  // namespace wh::combatmodule
