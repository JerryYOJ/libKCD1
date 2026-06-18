#pragma once

#include <cstdint>
#include <cstring>                          // strcmp (FindCell)
#include <boost/container/vector.hpp>       // the store's two count-based {ptr,size,cap} vectors
#include "S_DynamicInfoCell.h"

namespace wh::xgenaimodule {

// ===========================================================================
// wh::xgenaimodule::C_DynamicInformationStore
// ===========================================================================
// Process-wide store of crime/information DYNAMIC values -- the backing the
// LockDynamicInformationValues / Get/Set/Clear-DynamicInformationValue BT nodes
// operate on. XGenAIModule-owned; the global pointer is qword_183501560 (lazy
// ctor+getter sub_1814CEBBC: alloc 0x30, mutex unk_1837050F0). NAME IS OURS -- the
// store is an anonymous singleton (no RTTI / no vtable); named from its users.
//
// Two boost::container::vector members (count-based {ptr, size_t size, size_t cap};
// the size/capacity are element COUNTS, not end-pointers). Layout VERIFIED: get-or-create
// sub_180447844 (realloc trigger cap@+0x10 == size@+0x08; element stride 4 for A), save
// serializer sub_1815DC76C, removal sub_1815DB658 (0x18 stride for B):
//
//   m_lockedIds @ +0x00  ids with an OPEN LockDynamicInformationValues transaction.
//                        The GET worker only reads a value while its id is present here.
//   m_cells     @ +0x18  the committed (id, tag) -> value cells, sorted by (id, strcmp(tag)).
//
// Lifecycle: Set/Clear buffer their ops in the Lock node's per-agent journal; on child
// success the journal is committed here (sub_1815DDEAC), on failure rolled back, and the
// id is removed from m_lockedIds on unlock. Cells are pruned by id when an information is
// destroyed (sub_1815DB658). Both vectors are saved with the AI module (flag 0x800).
// ===========================================================================
class C_DynamicInformationStore {
public:
    boost::container::vector<uint32_t>          m_lockedIds;  // +0x00  ids inside an open Lock transaction
    boost::container::vector<S_DynamicInfoCell> m_cells;      // +0x18  committed (id,tag) -> value cells

    // *qword_183501560 -- the live store, or NULL if no dynamic-info value exists yet this session.
    // Reads the global pointer DIRECTLY (impl in C_DynamicInformationStore.cpp). We deliberately do
    // NOT call the lazy creator sub_1814CEBBC: that would allocate the store (malloc + mutex) as a
    // side effect of inspection -- same reasoning as querying a map with find() rather than operator[].
    static C_DynamicInformationStore* GetInstance();

    // Read-only scan for the (infoId, tag) value cell (e.g. tag = "expiration" / "expired").
    // The vector is sorted, but a linear scan is simple and side-effect-free. Null if absent.
    S_DynamicInfoCell* FindCell(uint32_t infoId, const char* tag) {
        for (auto& c : m_cells)
            if (c.m_infoId == infoId && std::strcmp(c.m_tag.c_str(), tag) == 0)
                return &c;
        return nullptr;
    }

    // True if the information currently has an open Lock transaction (id present in m_lockedIds).
    bool IsLocked(uint32_t infoId) const {
        for (uint32_t id : m_lockedIds)
            if (id == infoId) return true;
        return false;
    }
};
static_assert(sizeof(C_DynamicInformationStore) == 0x30);

}  // namespace wh::xgenaimodule
