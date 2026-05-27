#pragma once
#include <cstdint>

// -----------------------------------------------
// C_HashMap — Warhorse custom hash map
// -----------------------------------------------
// NOT std::unordered_map (field order differs: load factor is first, not last).
// Same concept: chained bucket hash map with a linked list of all elements.
//
// Used by the engine-wide type registry, C_BuffManager, and likely other modules.
//
// Hash map init: sub_18071265C(map, bucket_count)
// Node create:   sub_180DA8038(map, prev, next, {key, value})
// Find:          sub_180209AE4(map, outRange, hashKey)
// Insert:        sub_180DA821C(map, temp, {key, value})

namespace wh::shared {

template<typename V>
struct S_HashMapNode {
    S_HashMapNode*  pPrev;          // +0x00
    S_HashMapNode*  pNext;          // +0x08
    uint64_t        key;            // +0x10  hash key (FNV-1a or similar)
    V               value;          // +0x18
};
static_assert(sizeof(S_HashMapNode<void*>) == 0x20);

template<typename V>
struct S_HashMapBucket {
    using Node = S_HashMapNode<V>;
    Node*  pFirst;  // +0x00  first node in bucket (sentinel if empty)
    Node*  pEnd;    // +0x08  past-the-end boundary for iteration
};
static_assert(sizeof(S_HashMapBucket<void*>) == 0x10);

template<typename V>
class C_HashMap {
public:
    using Node   = S_HashMapNode<V>;
    using Bucket = S_HashMapBucket<V>;

    float           m_maxLoadFactor;    // +0x00  init 1.0f
    uint32_t        _pad04;             // +0x04
    Node*           m_pListHead;        // +0x08  sentinel node (circular doubly-linked list)
    int64_t         m_nCount;           // +0x10  number of stored elements
    Bucket*         m_pBuckets;         // +0x18  bucket array begin
    Bucket*         m_pBucketsEnd;      // +0x20  bucket array end
    Bucket*         m_pBucketsCap;      // +0x28  bucket array capacity
    uint64_t        m_nMask;            // +0x30  bucket_count - 1 (for power-of-2 modulo)
    uint64_t        m_nBucketCount;     // +0x38  number of buckets
};
static_assert(sizeof(C_HashMap<void*>) == 0x40);

}  // namespace wh::shared
