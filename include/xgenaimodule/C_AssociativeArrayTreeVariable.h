#pragma once

#include <cstdint>
#include <cstring>   // strcmp (FindHolder)
#include <map>
#include <vector>
#include "C_Variable.h"
#include "S_VariableValue.h"   // the 0x10 storage element

namespace wh::xgenaimodule {

// -----------------------------------------------
// S_VariableNameHash -- the fast name->index hash embedded in C_AssociativeArrayTreeVariable (+0x48).
// -----------------------------------------------
// A custom Warhorse hash map: member-name (string) -> uint32 index. NOT a std::unordered_map. Keyed by
// string CONTENT, not pointer: lookup sub_1803B40E4 hashes the bytes (rolling h = (h*0x20)^(h>>27)^ch,
// seeded with the string length) then byte-compares within the bucket chain. Separate chaining (one node
// list per bucket; node = links + key-ptr@+0x18 + uint32 index), an embedded chunked node-pool
// (sub_1805B2548), and load-factor grow/shrink (grow 80% / shrink 20%, min 10 buckets). It is the O(1)
// companion to the owner's ordered m_orderedNameToIndex (std::map) -- both map a name to the SAME index
// into m_valueHolders, kept in sync. value uint32 (0xFFFFFFFF = not found). Size 0x60.
// [field-by-field from ctor sub_1805B1B30; exact declared template name UNVERIFIED]
struct S_VariableNameHash {
    std::vector<void*> m_buckets;        // +0x00  bucket array (Node**)
    uint32_t           m_count;          // +0x18  live entry count
    uint32_t           m_shrinkThreshold;// +0x1C
    uint32_t           m_growThreshold;  // +0x20
    uint32_t           m_minBuckets;     // +0x24  = 0x0A
    uint32_t           m_growLoadPct;    // +0x28  = 0x50 (80%)
    uint32_t           m_shrinkLoadPct;  // +0x2C  = 0x14 (20%)
    uint8_t            _pad30[8];        // +0x30  (not initialized by ctor) [UNVERIFIED pad]
    std::vector<void*> m_nodePoolBlocks; // +0x38  block-pool chunk list
    uint32_t           m_blockCount;     // +0x50
    uint32_t           m_chunkMul;       // +0x54  = 1
    void*              m_curBlock;       // +0x58
};
static_assert(sizeof(S_VariableNameHash) == 0x60);

// ===========================================================================
// C_AssociativeArrayTreeVariable -- a string-keyed composite ("struct") brain variable.
// ===========================================================================
// RTTI: .?AVC_AssociativeArrayTreeVariable@xgenaimodule@wh@@ ; vtable 0x1821C7E00 ; ctor sub_1805B1AA8.
// This is the form behind composite brain vars like b_soul. GetValue (vtbl[0x20] = sub_1803B3CB0)
// builds a Lua table by walking the ordered name->index map (+0xA8) and, per member, fetching the
// value holder m_valueHolders[index] (+0xB8) and decoding it (sub_1803B3790). To read ONE member
// natively: find its index in m_orderedNameToIndex by name, then decode *m_valueHolders[index].
// Size 0xE8. (Siblings C_IndexedArrayTreeVariable 0x60 / C_CustomAssociativeTreeVariable 0xC0 derive
// from C_Variable in parallel with DIFFERENT layouts -- not a shared intermediate base.)
class C_AssociativeArrayTreeVariable : public C_Variable {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AssociativeArrayTreeVariable;

    // Each member's value holder is the same value vector C_SingleVariable uses.
    using ValueHolder = std::vector<S_VariableValue>;

    S_VariableNameHash               m_nameToIndex;        // +0x48  (0x60) fast name->index
    std::map<CryStringT<char>, uint32_t> m_orderedNameToIndex; // +0xA8  (0x10) ordered name->index (iteration)
    std::vector<ValueHolder*>        m_valueHolders;       // +0xB8  (0x18) per-index value storage
    std::vector<uint32_t>            m_freeIndices;        // +0xD0  (0x18) recycled-index free list

    // --- accessors ---
    // Find a member's value holder by name (iterates the ordered map + strcmp -- avoids depending on the
    // game-built std::map's comparator). Returns nullptr if the member is absent.
    ValueHolder* FindHolder(const char* name) const {
        for (const auto& kv : m_orderedNameToIndex)
            if (std::strcmp(kv.first.c_str(), name) == 0)
                return kv.second < m_valueHolders.size() ? m_valueHolders[kv.second] : nullptr;
        return nullptr;
    }
    // The member's value cell. Even a scalar variable's holder has 2 cells (its type's member array is
    // 2 entries: (typeDesc+0xA8 - typeDesc+0xA0) == 0x10), and the engine reads the value from cell[1]
    // (= holder.first + 0x10; verified from sub_1803B3790). cell[0] is a separate, non-value cell
    // (role unconfirmed). Returns nullptr if the member is absent or the holder is too small.
    const S_VariableValue* FindCell(const char* name) const {
        ValueHolder* h = FindHolder(name);
        return (h && h->size() >= 2) ? &(*h)[1] : nullptr;
    }
};
static_assert(sizeof(C_AssociativeArrayTreeVariable) == 0xE8);

}  // namespace wh::xgenaimodule
