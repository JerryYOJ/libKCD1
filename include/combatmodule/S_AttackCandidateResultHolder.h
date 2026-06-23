#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include "../framework/C_InlinePoolAllocator.h"   // C_InlinePoolAllocator + C_InlineArena (+ its functional allocator)

namespace wh::combatmodule {

class C_CombatActionAttackData;
struct S_CombatActionAttackQueryData;

// ---------------------------------------------------------------------------
// S_AttackCandidateRecord -- one 0x10-byte entry the candidate enumerator appends
// (sub_180A54E40). The selection loop iterates these (stride 0x10). The two flag
// bytes are zero on append and filled for the selected record by sub_180455844
// (rec[8] -> action+0xE3, rec[9] -> action+0xE2). [V] workflow wf_05aec32f.
// ---------------------------------------------------------------------------
struct S_AttackCandidateRecord {
    C_CombatActionAttackData* m_pAttackData; // +0x00  the candidate (also baked into action+0xD8)
    uint8_t  m_feasibilityFlag;              // +0x08  sub_180455844 result -> action+0xE3
    uint8_t  m_zoneReachableFlag;            // +0x09  sub_180455844 marker-reachable -> action+0xE2
    uint8_t  _pad0A[6];                      // +0x0A  unused on this path (stride is 0x10)
};
static_assert(sizeof(S_AttackCandidateRecord) == 0x10, "S_AttackCandidateRecord must be 0x10");

// ---------------------------------------------------------------------------
// S_AttackCandidateResultHolder -- the result container the candidate enumerator fills:
// a genuine std::vector with the short_alloc/arena idiom (an inline C_InlineArena<rec,15>
// + a std::vector whose C_InlinePoolAllocator serves from it). The arena's allocate/
// deallocate live in C_InlinePoolAllocator.h (the generic C_InlineArena specialization).
// [V] container fns sub_18045FB70/FC70/FE70 + grow sub_180666D74 (std::_Xlength_error,
// 1.5x growth) + RTTI; layout matches the engine CreateAndDispatch stack composite.
//
// Usage (RAII):
//   S_AttackCandidateResultHolder holder;   // ctor reserve(15)s the arena
//   holder.Enumerate(&query);
//   for (auto* r = holder.begin(); r != holder.end(); ++r) { ... r->m_pAttackData ... }
//   // dtor frees through the pool allocator
// ---------------------------------------------------------------------------
struct S_AttackCandidateResultHolder {
    using Arena = wh::framework::C_InlineArena<S_AttackCandidateRecord, 15>;
    using RecordVector = std::vector<S_AttackCandidateRecord,
        wh::framework::C_InlinePoolAllocator<S_AttackCandidateRecord, Arena>>;
    static_assert(sizeof(RecordVector) == 0x20, "pool-backed std::vector must be 0x20 {alloc, first, last, end}");

    Arena        m_arena;        // +0x000 (0x100) the inline arena<15> the allocator serves from
    RecordVector m_records;      // +0x100 (0x20)  the real std::vector (allocator -> m_arena)
    uint8_t      m_enumerating;  // +0x120  guard flag set during fill (sub_18045FD18)
    uint8_t      _pad121[7];     // +0x121

    S_AttackCandidateResultHolder();             // reserve(15) into the arena
    ~S_AttackCandidateResultHolder() = default;  // RAII: m_records frees through the pool allocator

    // Fill from a built query (engine global-moveset walk sub_18045FD18; arg1 ignored).
    void Enumerate(S_CombatActionAttackQueryData* query);

    S_AttackCandidateRecord* begin() { return m_records.data(); }
    S_AttackCandidateRecord* end()   { return m_records.data() + m_records.size(); }
    bool empty() const { return m_records.empty(); }
};
static_assert(sizeof(S_AttackCandidateResultHolder) == 0x128, "S_AttackCandidateResultHolder must be 0x128");

}  // namespace wh::combatmodule
