#pragma once

#include <cstdint>
#include <cstddef>
#include <new>
#include <utility>

namespace wh {

// ---------------------------------------------------------------------------
// wh::DynArray<T> — binary-compatible reimplementation of CryEngine's
// DynArray<T, int, SmallDynStorage> as the game actually compiled it.
//
// The whole object is one element pointer (8 bytes). The element count is an
// int32 stored immediately before the first element:
//     count = ((int32*)m_aElems)[-1] & 0x7FFFFFFF
// the top bit (0x80000000) marks "extra capacity after the elements"; we never
// set it. An empty array uses a null pointer (size 0). The game's empty arrays
// point at a static zero header — reading those still yields count 0.
//
// We reimplement rather than use CryEngine's CryArray.h DynArray because our
// SDK build instantiates SmallDynStorage at 16 bytes (extra allocator/MEMSTAT
// state) whereas the shipped game compiled it to 8; matching the binary needs
// the single-pointer form.
//
// Layout/header verified in WHGame.dll: SUIArguments ctor sub_18020DF40,
// grow sub_18020D434 (count = *(elems-4)&0x7FFFFFFF, top bit = slack),
// element insert sub_18020D168 (SUIData stride 0x20).
//
// Ownership: an array we build owns its block (alloc + free here). Passing one
// to a read-only game API (e.g. IUIElement::CallFunction, const SUIArguments&)
// is safe — the game reads, never frees ours. Reading a game-provided array
// works directly via the shared header layout.
// ---------------------------------------------------------------------------

template <class T>
class DynArray
{
public:
    typedef T        value_type;
    typedef T*       iterator;
    typedef const T* const_iterator;

    DynArray() : m_aElems(nullptr) {}
    ~DynArray() { destroy(); }

    DynArray(const DynArray& o) : m_aElems(nullptr) { assign(o.begin(), o.size()); }
    DynArray& operator=(const DynArray& o)
    {
        if (this != &o) { destroy(); assign(o.begin(), o.size()); }
        return *this;
    }
    DynArray(DynArray&& o) noexcept : m_aElems(o.m_aElems) { o.m_aElems = nullptr; }
    DynArray& operator=(DynArray&& o) noexcept
    {
        if (this != &o) { destroy(); m_aElems = o.m_aElems; o.m_aElems = nullptr; }
        return *this;
    }

    int  size() const  { return m_aElems ? (countHeader(m_aElems) & kSizeMask) : 0; }
    bool empty() const { return size() == 0; }

    iterator       begin()       { return m_aElems; }
    iterator       end()         { return m_aElems + size(); }
    const_iterator begin() const { return m_aElems; }
    const_iterator end()   const { return m_aElems + size(); }

    T&       operator[](int i)       { return m_aElems[i]; }
    const T& operator[](int i) const { return m_aElems[i]; }
    T&       back()       { return m_aElems[size() - 1]; }
    const T& back() const { return m_aElems[size() - 1]; }

    void clear() { destroy(); m_aElems = nullptr; }

    T& push_back(const T& v) { T* slot = grow_one(); new (slot) T(v); return *slot; }
    T& push_back()           { T* slot = grow_one(); new (slot) T(); return *slot; }

private:
    static const int32_t kSizeMask = 0x7FFFFFFF;
    static const size_t  kPrefix   = 8;   // 4-byte count header inside an 8-aligned reservation

    static int32_t countHeader(const T* e)          { return reinterpret_cast<const int32_t*>(e)[-1]; }
    static void    setHeader(T* e, int32_t n)        { reinterpret_cast<int32_t*>(e)[-1] = n; }
    static T*      allocBlock(int n)                 { char* b = static_cast<char*>(::operator new(kPrefix + (size_t)n * sizeof(T))); return reinterpret_cast<T*>(b + kPrefix); }
    static void    freeBlock(T* e)                   { if (e) ::operator delete(reinterpret_cast<char*>(e) - kPrefix); }

    void destroy()
    {
        if (!m_aElems) return;
        int n = size();
        for (int i = 0; i < n; ++i) m_aElems[i].~T();
        freeBlock(m_aElems);
        m_aElems = nullptr;
    }

    T* grow_one()
    {
        int n = size();
        T* old = m_aElems;
        T* fresh = allocBlock(n + 1);
        setHeader(fresh, (n + 1) & kSizeMask);
        for (int i = 0; i < n; ++i) { new (&fresh[i]) T(std::move(old[i])); old[i].~T(); }
        freeBlock(old);
        m_aElems = fresh;
        return &fresh[n];
    }

    void assign(const T* src, int n)
    {
        if (n <= 0) { m_aElems = nullptr; return; }
        m_aElems = allocBlock(n);
        setHeader(m_aElems, n & kSizeMask);
        for (int i = 0; i < n; ++i) new (&m_aElems[i]) T(src[i]);
    }

    T* m_aElems;
};

}  // namespace wh

static_assert(sizeof(wh::DynArray<int>) == 0x8, "wh::DynArray must be a single element pointer");
