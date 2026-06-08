#pragma once
#include <cstdint>
#include <cstring>

// ===========================================================================
// C_HashMap<K, V, Hash> — Warhorse custom chained hash map.
//
// Reverse-engineered from WHGame.dll (KCD1 retail, imagebase 0x180000000).
// Namespace wh::shared (inferred from usage — no RTTI on the map itself).
//
// STRUCTURE (0x40 bytes, verified from ctors sub_180F39820 / sub_180F993F0):
//   Chained hash map with a circular doubly-linked sentinel node.
//   Buckets are pairs of node pointers {pFirst, pBound} stored in a
//   power-of-2-sized array. The sentinel serves as both end-of-list
//   and empty-bucket marker.
//
// DEFAULT HASH: FNV-1a 64-bit (basis 0xCBF29CE484222325, prime 0x100000001B3),
//   byte-by-byte over sizeof(K) raw bytes of the key.
// COMPOSITE KEYS use boost::hash_combine to fold multiple field hashes
//   (override via the Hash template param).
// BUCKET SELECTION: Hash{}(key) & m_mask.
// COLLISION RESOLUTION: chained via prev/next on each node; walk within the
//   bucket until pBound, compare keys by operator==.
//
// VERIFIED FUNCTIONS:
//   ctor (0x40 init):   sub_180F39820 / sub_180F993F0
//   bucket array alloc: sub_18071265C(map, bucketCount)
//   sentinel alloc:     sub_1807125EC (sizeof(Node)==0x20) /
//                       sub_180731290 (sizeof(Node)==0x18)
//   hash FNV-1a 64:     sub_1804BF50C(_, &key, sizeof(K))
//   hash FNV-1  32:     sub_1802540B4(const char*)  (null-terminated string)
//   hash_combine:       boost pattern: seed ^= value + 0x9E3779B9 + (seed<<6) + (seed>>2)
//   find:               sub_180209AE4(map, outRange, &key)
//   insert:             sub_180DA821C(map, outResult, &{key,value})
//   node create:        sub_180DA8038(map, prev, next, &{key,value})
//   bucket resolve:     sub_180207188(map, out, bucketIdx)
//   insert+rebalance:   sub_180DA8094(map, out, &key, &node)
//   rehash:             sub_180DA8840(map)
// ===========================================================================

namespace wh::shared {

// ---------------------------------------------------------------------------
// Hash primitives (verified from binary)
// ---------------------------------------------------------------------------

// FNV-1a 64-bit — the engine's default hash for typed keys.
// Hashes sizeof(K) raw bytes. (sub_1804BF50C)
inline uint64_t fnv1a(const void* data, size_t len) {
    uint64_t h = 0xCBF29CE484222325ULL;
    auto p = static_cast<const uint8_t*>(data);
    for (size_t i = 0; i < len; ++i)
        h = (h ^ p[i]) * 0x100000001B3ULL;
    return h;
}

// FNV-1 32-bit — the engine's hash for null-terminated strings.
// (sub_1802540B4)
inline uint32_t fnv1_32(const char* str) {
    uint32_t h = 0x811C9DC5u;
    while (*str)
        h = (h * 0x01000193u) ^ static_cast<uint8_t>(*str++);
    return h;
}

// boost::hash_combine — used by the engine to fold multiple hashes into one.
// Verified from disasm at 0x1815d4042-0x1815d406d.
inline uint64_t hash_combine(uint64_t seed, uint64_t value) {
    seed ^= value + 0x9E3779B9ULL + (seed << 6) + (seed >> 2);
    return seed;
}

// ---------------------------------------------------------------------------
// Default hash functor: FNV-1a over sizeof(K) raw bytes.
// Specialize for composite key types that need hash_combine.
// ---------------------------------------------------------------------------
template<typename K>
struct S_DefaultHash {
    uint64_t operator()(const K& key) const {
        return fnv1a(&key, sizeof(K));
    }
};

// ---------------------------------------------------------------------------
// S_HashNode<K, V>
// ---------------------------------------------------------------------------
template<typename K, typename V>
struct S_HashNode {
    S_HashNode* pPrev;     // +0x00
    S_HashNode* pNext;     // +0x08
    K           key;       // +0x10
    V           value;     // +0x10 + sizeof(K) (aligned)
};

template<typename K>
struct S_HashNode<K, void> {
    S_HashNode* pPrev;     // +0x00
    S_HashNode* pNext;     // +0x08
    K           key;       // +0x10
};

// ---------------------------------------------------------------------------
// S_HashBucket<K, V>
// ---------------------------------------------------------------------------
template<typename K, typename V>
struct S_HashBucket {
    using Node = S_HashNode<K, V>;
    Node* pFirst;          // +0x00
    Node* pBound;          // +0x08
};

// ---------------------------------------------------------------------------
// C_HashMap<K, V, Hash>
// ---------------------------------------------------------------------------
template<typename K, typename V = void, typename Hash = S_DefaultHash<K>>
class C_HashMap {
public:
    using Node   = S_HashNode<K, V>;
    using Bucket = S_HashBucket<K, V>;

    float       m_maxLoadFactor;  // +0x00  init 1.0f
    uint32_t    _pad04;           // +0x04
    Node*       m_pSentinel;      // +0x08  circular list sentinel
    int64_t     m_count;          // +0x10  number of stored entries
    Bucket*     m_pBuckets;       // +0x18  bucket array begin
    Bucket*     m_pBucketsEnd;    // +0x20
    Bucket*     m_pBucketsCap;    // +0x28
    uint64_t    m_mask;           // +0x30  bucketCount - 1
    uint64_t    m_bucketCount;    // +0x38

    uint64_t bucket_for(const K& key) const {
        return Hash{}(key) & m_mask;
    }

    Node* find(const K& key) const {
        uint64_t b = bucket_for(key);
        Node* bound = m_pBuckets[b].pBound;
        for (Node* n = m_pBuckets[b].pFirst; n != bound; n = n->pNext) {
            if (n->key == key)
                return n;
        }
        return m_pSentinel;
    }

    Node* begin() const { return m_pSentinel->pNext; }
    Node* end()   const { return m_pSentinel; }
    bool  empty() const { return m_count == 0; }
};
static_assert(sizeof(C_HashMap<uint64_t, void*>) == 0x40);
static_assert(sizeof(C_HashMap<uint32_t>)        == 0x40);

// ---------------------------------------------------------------------------
// C_Set<K, Hash> — the std::unordered_set sibling of C_HashMap.
//
// Identical 0x40 header, but its nodes are S_HashNode<K, void> (0x18: prev,
// next, key — NO value slot). The set's sentinel/node allocator is the 0x18
// variant (sub_180731290) vs the map's 0x20 (sub_1807125EC); both share the
// bucket pool sub_18071265C and the 1.0f load factor.
//
// Intended for a "set of pointers" with a TRANSPARENT hash that reads through
// the stored pointer (e.g. C_Set<S_InformationRecord*> hashed by the pointee's
// {wuid, label}); provide such a Hash functor as the second template arg.
// ---------------------------------------------------------------------------
template<typename K, typename Hash = S_DefaultHash<K>>
class C_Set {
public:
    using Node = S_HashNode<K, void>;   // 0x18

    float       m_maxLoadFactor;  // +0x00  init 1.0f
    uint32_t    _pad04;           // +0x04
    Node*       m_pSentinel;      // +0x08  circular list sentinel (alloc sub_180731290, 0x18)
    int64_t     m_count;          // +0x10
    void*       m_pBuckets;       // +0x18  bucket array begin ({pFirst,pBound} pairs)
    void*       m_pBucketsEnd;    // +0x20
    void*       m_pBucketsCap;    // +0x28
    uint64_t    m_mask;           // +0x30  bucketCount - 1
    uint64_t    m_bucketCount;    // +0x38

    bool empty() const { return m_count == 0; }
};
static_assert(sizeof(C_Set<void*>)               == 0x40);
static_assert(sizeof(S_HashNode<void*, void>)    == 0x18);

}  // namespace wh::shared
