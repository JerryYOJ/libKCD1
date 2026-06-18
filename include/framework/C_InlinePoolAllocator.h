#pragma once

#include <cstddef>

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
    template <class U>
    C_InlinePoolAllocator(const C_InlinePoolAllocator<U, Pool>& o) noexcept : m_pPool(o.m_pPool) {}

    T*   allocate(std::size_t n);                 // game pool allocator
    void deallocate(T* p, std::size_t n) noexcept;

    template <class U> bool operator==(const C_InlinePoolAllocator<U, Pool>&) const noexcept { return true; }
    template <class U> bool operator!=(const C_InlinePoolAllocator<U, Pool>&) const noexcept { return false; }
};

}  // namespace wh::framework
