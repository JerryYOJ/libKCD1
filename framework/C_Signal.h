#pragma once

#include <cstdint>
#include <vector>

namespace wh::shared {

template<typename... Args>
struct S_SignalTraits {};

template<typename... Args>
struct S_Delegate {
    using FnType = void(*)(void*, Args...);

    FnType  m_pInvoke;      // +0x00
    void*   m_pInstance;    // +0x08

    void operator()(Args... args) const {
        m_pInvoke(m_pInstance, args...);
    }

    bool operator==(const S_Delegate& o) const {
        return m_pInvoke == o.m_pInvoke && m_pInstance == o.m_pInstance;
    }
    bool operator!=(const S_Delegate& o) const { return !(*this == o); }
};
static_assert(sizeof(S_Delegate<>) == 0x10);

template<typename... Args>
struct S_SortedConnectionEntry {
    int32_t             m_nSlot;        // +0x00
    int32_t             _pad04;         // +0x04
    S_Delegate<Args...> m_callback;     // +0x08
};
static_assert(sizeof(S_SortedConnectionEntry<>) == 0x18);


// Layout matches CryEngine FastDynArray<T, int64_t>: {T* m_aElems, I m_nCount, I m_nCapacity}
template<typename Traits>
class C_BypassedConnections;

template<typename... Args>
class C_BypassedConnections<S_SignalTraits<Args...>> {
public:
    using Entry = S_SortedConnectionEntry<Args...>;

    Entry*      m_aElems;       // +0x00
    int64_t     m_nCount;       // +0x08
    int64_t     m_nCapacity;    // +0x10

    Entry* begin()              { return m_aElems; }
    Entry* end()                { return m_aElems + m_nCount; }
    int64_t size() const        { return m_nCount; }
    int64_t capacity() const    { return m_nCapacity; }
    bool empty() const          { return m_nCount == 0; }
};
static_assert(sizeof(C_BypassedConnections<S_SignalTraits<>>) == 0x18);

template<typename Traits, typename BypassedConnPolicy, typename... Args>
class C_SignalBase {
public:
    using Delegate = S_Delegate<Args...>;

    void*                   m_pField08;         // +0x08  dead; never read/written/freed in binary
    std::vector<Delegate>   m_connections;      // +0x10  {begin, end, cap_end} — freed in dtor
    int32_t                 m_nEmitSlot;        // +0x28  -1 = idle
    int32_t                 m_nReentrancyDepth; // +0x2C  -1 = not firing
};

template<typename Traits, typename BypassedConnPolicy, typename... Args>
class C_EmitingSignal : public C_SignalBase<Traits, BypassedConnPolicy, Args...> {
public:
    using Delegate = S_Delegate<Args...>;

    void Emit(Args... args) {
        for (auto& conn : this->m_connections) {
            conn(args...);
        }
    }
};

// vtable: 1 entry [0] dtor — verified via RTTI COL at 0x182208ce8
template<typename... Args>
class C_Signal : public C_EmitingSignal<
    S_SignalTraits<Args...>,
    C_BypassedConnections<S_SignalTraits<Args...>>,
    Args...>
{
public:
    using Delegate = S_Delegate<Args...>;

    virtual ~C_Signal() = default;  // [0]
};
static_assert(sizeof(C_Signal<>) == 0x30);

}  // namespace wh::shared
