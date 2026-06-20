#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
// CryStringT<char> comes from the PCH prelude.

// ===========================================================================
// wh::xgenaimodule::S_AIUpdateScheduler  (size 0x2D0)   [SYNTHETIC NAME -- no RTTI]
// ===========================================================================
// A non-polymorphic per-area AI update scheduler embedded by value in C_SmartAreaManager (+0x190) and,
// with a different config, in C_SmartObjectsManager (+0x248) -- it is a GENERIC shared type, so the
// "SmartArea" name is only by convention; it carries no vtable and no RTTI (the name here is synthetic).
// Identified at runtime by its config's CryStringT name ("SmartAreaUpdate" vs "SmartObjectUpdate").
// ctor sub_1815E4668(this, cfg) (cfg = the magic-static singleton from sub_1815E98AC, unk_18372BF20);
// member-dtor sub_1815E5248. Drives per-frame updates via C_SmartAreaManager::Update (slot[0]); paused
// /resumed via slot[10].
//
// Layout VERIFIED byte-exact from ctor sub_1815E4668, dtor sub_1815E5248, the budget sub-object ctor
// sub_1815E45E0/sub_1815E4074 + CVar registrar sub_1815EB214 + unregistrar sub_1815EC728, and the
// generic block-pool ctor sub_1807128D4 (cross-checked against the standalone pool unk_18359EA70).
// ===========================================================================

namespace wh::xgenaimodule {

class S_AIUpdateScheduler {
public:
    // --- nested layout sub-objects (this scheduler's private structure) ---

    // one of the three update buckets (+0x00). Each owns a direct-count array of 0x10-byte records
    // (allocated from m_recordPool) plus a secondary intrusive list. Per-entry ctor sub_1806E1078,
    // dtor sub_1810255EC. (Records are pointers to 0x10-byte objects; pointee not reconstructed.)
    struct S_UpdateBucket {
        void*    m_sentinelNode;    // +0x00  intrusive-list sentinel node (0x10, self-linked at init)
        void**   m_records;         // +0x08  begin of a direct-count array of record pointers
        uint64_t m_recordCount;     // +0x10  element COUNT (read directly; size == capacity)
        void*    m_secondaryHead;   // +0x18  secondary intrusive list head
        uint64_t m_secondaryCount;  // +0x20  secondary list count
    };
    static_assert(sizeof(S_UpdateBucket) == 0x28);

    // generic CryEngine fixed-size block/pool allocator (+0x90, element size 0x10). Used in 40+ places
    // (e.g. global unk_18359EA70); deserves its own shared header -- modeled here as the scheduler's
    // record allocator. ctor sub_1807128D4; free-list drained on teardown.
    struct S_BlockPool {
        uint64_t m_pageSize;        // +0x00  page alloc size (rounded up to 0x1000, min 0x1000)
        void*    m_heapDesc;        // +0x08  CRT heap descriptor (global allocator fn-table)
        void*    m_freeListMarker;  // +0x10
        void*    m_freeListHead;    // +0x18  singly-linked free node list
        uint64_t _unk20;            // +0x20  zero-init
        uint64_t m_chunkAccount;    // +0x28  per-chunk allocation accounting counter
        uint64_t m_blockSize;       // +0x30  element/block size (= 0x10 here)
        uint64_t m_alignment;       // +0x38  element alignment (= 8)
        uint64_t _scratch40;        // +0x40
        uint64_t _scratch48;        // +0x48
        void*    m_owner;           // +0x50  self-ref (= &this pool)
        void*    m_chunkListHead;   // +0x58  singly-linked allocated-page list
    };
    static_assert(sizeof(S_BlockPool) == 0x60);

    // one per-layer AI job-budget entry (3 of them inside S_BudgetConfig). Registers 4 CVars
    // (wh_ai_<prefix>{BudgetRatio,JobBudget,Count,MinimalBudget}Layer<n>). Per-entry ctor
    // sub_1815E49C8, dtor sub_1815E5478.
    struct S_BudgetLayer {
        int32_t          m_flags;             // +0x00  copied from cfg [meaning unverified]
        int32_t          m_jobBudget;         // +0x04  CVar JobBudgetLayer<n>
        float            m_budgetRatio;       // +0x08  = m_jobBudget / 1000.0f (derived; CVar BudgetRatioLayer<n>)
        int32_t          m_count;             // +0x0C  CVar CountLayer<n>
        int32_t          m_minimalBudget;     // +0x10  CVar MinimalBudgetLayer<n>
        int32_t          _pad14;              // +0x14
        CryStringT<char> m_cvarBudgetRatio;   // +0x18
        CryStringT<char> m_cvarJobBudget;     // +0x20
        CryStringT<char> m_cvarCount;         // +0x28
        CryStringT<char> m_cvarMinimalBudget; // +0x30
    };
    static_assert(sizeof(S_BudgetLayer) == 0x38);

    // the per-area AI job-budget config block (+0xF8, 0x150). ctor sub_1815E45E0 (copies tuning from
    // cfg+0x88); registers 16 CVars (3 layers x 4 + 4 globals), unregistered by sub_1815EC728.
    struct S_BudgetConfig {
        S_BudgetLayer    m_layers[3];               // +0x00 (0xA8)
        uint8_t          m_flagA8;                  // +0xA8
        uint8_t          _padA9[7];                 // +0xA9
        uint64_t         m_handleB0;                // +0xB0  init -1 (sentinel)
        uint8_t          _gapB8[0x18];              // +0xB8  caller-zeroed gap
        uint64_t         m_handleD0;                // +0xD0  init -1
        uint64_t         _gapD8;                    // +0xD8  [UNVERIFIED]
        uint64_t         m_unkE0;                   // +0xE0  init 0
        uint64_t         m_handleE8;                // +0xE8  init -1
        uint8_t          m_flagF0;                  // +0xF0  init (dword_183785BA8 != 0)
        uint8_t          m_flagF1;                  // +0xF1  init 0
        uint8_t          _padF2[6];                 // +0xF2
        uint64_t         m_unkF8;                   // +0xF8  init 0
        uint16_t         m_word100;                 // +0x100 init 1
        uint8_t          _pad102[6];                // +0x102
        CryStringT<char> m_prefix;                  // +0x108  the "%s" name prefix (from cfg+0x88)
        int32_t          m_budgetLowerBound;        // +0x110  CVar value
        int32_t          _pad114;                   // +0x114
        CryStringT<char> m_cvarBudgetLowerBound;    // +0x118
        int32_t          m_fixedBudget;             // +0x120  CVar value (bool)
        int32_t          _pad124;                   // +0x124
        CryStringT<char> m_cvarFixedBudget;         // +0x128
        int32_t          m_postLoadBudget;          // +0x130  CVar value
        int32_t          _pad134;                   // +0x134
        CryStringT<char> m_cvarPostLoadBudget;      // +0x138
        int32_t          m_postLoadJobBudget;       // +0x140  CVar value
        int32_t          _pad144;                   // +0x144
        CryStringT<char> m_cvarPostLoadJobBudget;   // +0x148
    };
    static_assert(sizeof(S_BudgetConfig) == 0x150);

    // --- scheduler fields (+0x00 .. +0x2D0) ---
    S_UpdateBucket m_buckets[3];     // +0x00  (0x78)  3 update/priority buckets of owned 0x10 records
    uint64_t       m_unk78[3];       // +0x78  (0x18)  zeroed at ctor, not freed [UNVERIFIED -- pool-backed handles?]
    S_BlockPool    m_recordPool;     // +0x90  (0x60)  0x10-block allocator backing the bucket records
    uint64_t       _unkF0;           // +0xF0           untouched by ctor/dtor [UNVERIFIED]
    S_BudgetConfig m_budget;         // +0xF8  (0x150)  per-layer AI job-budget config + CVars
    std::unordered_map<uint64_t, void*> m_jobMap;  // +0x248 (0x40)  scheduled-job map; node 0x20, key+value
                                                   //        trivial 8+8 (no CryStringT) [exact key/value UNVERIFIED]
    std::function<void()> m_callback;// +0x288 (0x40)  copied from cfg (empty by default); signature UNVERIFIED
    uint8_t        m_flag2C8;        // +0x2C8          byte flag from cfg+0x40
    uint8_t        _pad2C9[7];       // +0x2C9  -> 0x2D0
};
static_assert(sizeof(S_AIUpdateScheduler) == 0x2D0, "S_AIUpdateScheduler (ctor sub_1815E4668)");

}  // namespace wh::xgenaimodule
