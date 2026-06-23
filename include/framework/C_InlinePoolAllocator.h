#pragma once

#include <cstddef>
#include <cstdint>
#include "Offsets/Offsets.h"   // CryMemAlloc / CryMemFree (the uniform bucket heap)

// ===========================================================================
// wh::framework::C_InlinePoolAllocator<T, Pool>
// ===========================================================================
// A stateful std-allocator that draws allocations from an inline Pool arena embedded
// in the owning object (falling back to the heap when the arena is full). Its single
// Pool* member is non-empty, so any std::vector<T, C_InlinePoolAllocator<T, Pool>> is
// 0x20 -- {Pool* alloc, T* begin, T* end, T* cap} -- exactly the shape the game uses for
// the C_Faction angriness/timed-event vectors (the arena pointer sits at the vector's
// +0x00, ahead of begin/end/cap).
//
// This is a layout/type mirror: allocate/deallocate are only declared (the real bodies
// live in the binary's pool allocator, e.g. sub_1811A7174 / sub_1811A724C). They are
// never instantiated by a sizeof-only use.
namespace wh::framework {

template <class T, class Pool>
struct C_InlinePoolAllocator {
    using value_type = T;
    template <class U> struct rebind { using other = C_InlinePoolAllocator<U, Pool>; };

    Pool* m_pPool;   // +0x00  the inline arena this allocator serves from

    C_InlinePoolAllocator() noexcept = default;
    explicit C_InlinePoolAllocator(Pool* pool) noexcept : m_pPool(pool) {}  // serve from this inline arena
    template <class U>
    C_InlinePoolAllocator(const C_InlinePoolAllocator<U, Pool>& o) noexcept : m_pPool(o.m_pPool) {}

    T*   allocate(std::size_t n);                 // game pool allocator
    void deallocate(T* p, std::size_t n) noexcept;

    template <class U> bool operator==(const C_InlinePoolAllocator<U, Pool>&) const noexcept { return true; }
    template <class U> bool operator!=(const C_InlinePoolAllocator<U, Pool>&) const noexcept { return false; }
};

// ===========================================================================
// wh::framework::C_InlineArena<T, N>
// ===========================================================================
// A single-block inline arena -- Howard Hinnant's arena<N>: an inline buffer of N
// T's, an in-use flag, and the arena's self/bump pointer. Used as the Pool for
// C_InlinePoolAllocator<T, C_InlineArena<T, N>> to make a std::vector serve its (one)
// storage block from the inline buffer, falling back to the heap. This is the
// single-flag arena shape the engine uses (combat candidate vector; faction
// timed-event vector at N=1). The per-pool heap fallback lives in the allocator's
// allocate/deallocate (which can't be generic -- each engine pool has its own heap
// allocator), so those stay per-instantiation.
template <class T, std::size_t N>
struct C_InlineArena {
    static constexpr std::size_t capacity = N;
    T       m_buf[N];   // +0x00        inline storage for up to N elements
    uint8_t m_inUse;    // +N*sizeof(T) set while the buffer is handed out
    void*   m_ptr;      // (8-aligned)  arena<N>::ptr_ (the engine stores &m_buf)
};

// Functional allocator for C_InlineArena-backed std::vectors. Unlike the primary
// template (declaration-only, sizeof-only -- the faction vectors are game-constructed),
// this serves the vector's single storage block from the inline arena, falling back to
// the CryEngine bucket heap. VERIFIED: every engine pool allocator (combat sub_18045FC70,
// faction timed-event sub_1811A724C, angriness sub_1811A7174) uses the SAME heap fallback
// sub_18028C040 / CryEngine::MemFree -- so one body serves all single-flag arenas.
template <class T, std::size_t N>
struct C_InlinePoolAllocator<T, C_InlineArena<T, N>> {
    using value_type = T;
    template <class U> struct rebind { using other = C_InlinePoolAllocator<U, C_InlineArena<T, N>>; };

    C_InlineArena<T, N>* m_pPool;   // +0x00  the inline arena this allocator serves from

    C_InlinePoolAllocator() noexcept = default;
    explicit C_InlinePoolAllocator(C_InlineArena<T, N>* pool) noexcept : m_pPool(pool) {}
    template <class U>
    C_InlinePoolAllocator(const C_InlinePoolAllocator<U, C_InlineArena<T, N>>& o) noexcept : m_pPool(o.m_pPool) {}

    T* allocate(std::size_t n) {
        if (m_pPool && !m_pPool->m_inUse && n <= N) { m_pPool->m_inUse = 1; return m_pPool->m_buf; }
        return reinterpret_cast<T*>(Offsets::CryMemAlloc(sizeof(T) * n));
    }
    void deallocate(T* p, std::size_t n) noexcept {
        if (m_pPool && p == m_pPool->m_buf) { m_pPool->m_inUse = 0; return; }
        Offsets::CryMemFree(p, sizeof(T) * n);
    }

    template <class U> bool operator==(const C_InlinePoolAllocator<U, C_InlineArena<T, N>>&) const noexcept { return true; }
    template <class U> bool operator!=(const C_InlinePoolAllocator<U, C_InlineArena<T, N>>&) const noexcept { return false; }
};

}  // namespace wh::framework
