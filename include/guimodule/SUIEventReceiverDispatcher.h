#pragma once

#include <cstdint>
#include <map>
#include "guimodule/SUITypes.h"
#include "Offsets/vtables/IUIEventListener.h"
#include "Offsets/vtables/IUIEventSystem.h"

// ---------------------------------------------------------------------------
// SUEventReceiverDispatcher<T> + the dispatch functor hierarchy.
//
// Maps engine event ids to typed member-function callbacks. A class embeds one,
// calls Init() once, then RegisterEvent(desc, &Class::Handler) per event. When
// the event system delivers an event, OnEvent looks the id up and unpacks the
// SUIArguments into the handler's typed parameters.
//
// GLOBAL namespace, matching binary RTTI (e.g. SUIEventReceiverDispatcher<C_UIMap>
// vtable 0x1826d15d8; 3 slots == IUIEventListener). Size 0x28:
//   { vtbl, std::map<uint, IUIEventDispatchFct*>, IUIEventSystem*, T* }.
// ---------------------------------------------------------------------------

// deref_t<P> — storage + accessor for a handler parameter type P.
// Value/ref params store the value directly; const char*/wchar_t* params store
// a CryStringT and hand back c_str() (so the arg's lifetime covers the call).
template <class T> struct deref_t            { typedef T type;               type v; T  g()        { return v; } };
template <class T> struct deref_t<T&>        { typedef T type;               type v; T& g()        { return v; } };
template <class T> struct deref_t<const T&>  { typedef T type;               type v; const T& g()  { return v; } };
template <class T> struct deref_t<const T*>  { typedef CryStringT<T> type;   type v; const T* g()  { return v.c_str(); } };

// =====================================================================
// IUIEventDispatchFct — abstract dispatch functor (RTTI .?AUIUIEventDispatchFct@@)
// =====================================================================
struct IUIEventDispatchFct {
    virtual ~IUIEventDispatchFct() {}
    virtual SUIArgumentsRet Dispatch(void* pThis, const SUIEvent& event) = 0;
};

// Return adapter: void handlers yield an empty SUIArguments.
template <class R, class C>
struct SUIEventDispatchFctReturn {
    static SUIArgumentsRet Dispatch(C& impl, void* pThis, const SUIEvent& event) { return impl.Dispatch(pThis, event); }
};
template <class C>
struct SUIEventDispatchFctReturn<void, C> {
    static SUIArgumentsRet Dispatch(C& impl, void* pThis, const SUIEvent& event) { impl.Dispatch(pThis, event); return SUIArgumentsRet(); }
};

template <class R, class C>
struct SUIEventDispatchFctImpl : public IUIEventDispatchFct {
    typedef typename C::TFct TFct;
    SUIEventDispatchFctImpl(TFct fct) : Impl(fct) {}
    virtual SUIArgumentsRet Dispatch(void* pThis, const SUIEvent& event) override { return SUIEventDispatchFctReturn<R, C>::Dispatch(Impl, pThis, event); }
    C Impl;
};

// =====================================================================
// SUIEventDispatchFctN — member-fn + arg unpack for 0..9 params
// =====================================================================
template <class C, class R>
struct SUIEventDispatchFct0 {
    typedef R (C::*TFct)(void);
    SUIEventDispatchFct0(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent&) { return (((C*)pThis)->*m_fct)(); }
    TFct m_fct;
};

template <class C, class R, class T0>
struct SUIEventDispatchFct1 {
    typedef R (C::*TFct)(T0);
    SUIEventDispatchFct1(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v);
        return (((C*)pThis)->*m_fct)(a0.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1>
struct SUIEventDispatchFct2 {
    typedef R (C::*TFct)(T0, T1);
    SUIEventDispatchFct2(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v);
        deref_t<T1> a1; e.args.GetArg(1, a1.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1, class T2>
struct SUIEventDispatchFct3 {
    typedef R (C::*TFct)(T0, T1, T2);
    SUIEventDispatchFct3(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v);
        deref_t<T1> a1; e.args.GetArg(1, a1.v);
        deref_t<T2> a2; e.args.GetArg(2, a2.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g(), a2.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1, class T2, class T3>
struct SUIEventDispatchFct4 {
    typedef R (C::*TFct)(T0, T1, T2, T3);
    SUIEventDispatchFct4(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v);
        deref_t<T1> a1; e.args.GetArg(1, a1.v);
        deref_t<T2> a2; e.args.GetArg(2, a2.v);
        deref_t<T3> a3; e.args.GetArg(3, a3.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g(), a2.g(), a3.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1, class T2, class T3, class T4>
struct SUIEventDispatchFct5 {
    typedef R (C::*TFct)(T0, T1, T2, T3, T4);
    SUIEventDispatchFct5(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v);
        deref_t<T1> a1; e.args.GetArg(1, a1.v);
        deref_t<T2> a2; e.args.GetArg(2, a2.v);
        deref_t<T3> a3; e.args.GetArg(3, a3.v);
        deref_t<T4> a4; e.args.GetArg(4, a4.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g(), a2.g(), a3.g(), a4.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1, class T2, class T3, class T4, class T5>
struct SUIEventDispatchFct6 {
    typedef R (C::*TFct)(T0, T1, T2, T3, T4, T5);
    SUIEventDispatchFct6(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v); deref_t<T1> a1; e.args.GetArg(1, a1.v);
        deref_t<T2> a2; e.args.GetArg(2, a2.v); deref_t<T3> a3; e.args.GetArg(3, a3.v);
        deref_t<T4> a4; e.args.GetArg(4, a4.v); deref_t<T5> a5; e.args.GetArg(5, a5.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g(), a2.g(), a3.g(), a4.g(), a5.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6>
struct SUIEventDispatchFct7 {
    typedef R (C::*TFct)(T0, T1, T2, T3, T4, T5, T6);
    SUIEventDispatchFct7(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v); deref_t<T1> a1; e.args.GetArg(1, a1.v);
        deref_t<T2> a2; e.args.GetArg(2, a2.v); deref_t<T3> a3; e.args.GetArg(3, a3.v);
        deref_t<T4> a4; e.args.GetArg(4, a4.v); deref_t<T5> a5; e.args.GetArg(5, a5.v);
        deref_t<T6> a6; e.args.GetArg(6, a6.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g(), a2.g(), a3.g(), a4.g(), a5.g(), a6.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
struct SUIEventDispatchFct8 {
    typedef R (C::*TFct)(T0, T1, T2, T3, T4, T5, T6, T7);
    SUIEventDispatchFct8(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v); deref_t<T1> a1; e.args.GetArg(1, a1.v);
        deref_t<T2> a2; e.args.GetArg(2, a2.v); deref_t<T3> a3; e.args.GetArg(3, a3.v);
        deref_t<T4> a4; e.args.GetArg(4, a4.v); deref_t<T5> a5; e.args.GetArg(5, a5.v);
        deref_t<T6> a6; e.args.GetArg(6, a6.v); deref_t<T7> a7; e.args.GetArg(7, a7.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g(), a2.g(), a3.g(), a4.g(), a5.g(), a6.g(), a7.g());
    }
    TFct m_fct;
};

template <class C, class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
struct SUIEventDispatchFct9 {
    typedef R (C::*TFct)(T0, T1, T2, T3, T4, T5, T6, T7, T8);
    SUIEventDispatchFct9(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) {
        deref_t<T0> a0; e.args.GetArg(0, a0.v); deref_t<T1> a1; e.args.GetArg(1, a1.v);
        deref_t<T2> a2; e.args.GetArg(2, a2.v); deref_t<T3> a3; e.args.GetArg(3, a3.v);
        deref_t<T4> a4; e.args.GetArg(4, a4.v); deref_t<T5> a5; e.args.GetArg(5, a5.v);
        deref_t<T6> a6; e.args.GetArg(6, a6.v); deref_t<T7> a7; e.args.GetArg(7, a7.v);
        deref_t<T8> a8; e.args.GetArg(8, a8.v);
        return (((C*)pThis)->*m_fct)(a0.g(), a1.g(), a2.g(), a3.g(), a4.g(), a5.g(), a6.g(), a7.g(), a8.g());
    }
    TFct m_fct;
};

// Legacy / dynamic-arg-count handlers receive the raw SUIEvent / SUIArguments.
template <class C, class R>
struct SUIEventDispatchFct1<C, R, const SUIEvent&> {
    typedef R (C::*TFct)(const SUIEvent&);
    SUIEventDispatchFct1(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) { return (((C*)pThis)->*m_fct)(e); }
    TFct m_fct;
};
template <class C, class R>
struct SUIEventDispatchFct1<C, R, const SUIArguments&> {
    typedef R (C::*TFct)(const SUIArguments&);
    SUIEventDispatchFct1(TFct fct) : m_fct(fct) {}
    R Dispatch(void* pThis, const SUIEvent& e) { return (((C*)pThis)->*m_fct)(e.args); }
    TFct m_fct;
};

// =====================================================================
// SUIEventReceiverDispatcher<C>
// =====================================================================
template<typename C>
struct SUIEventReceiverDispatcher : public Offsets::IUIEventListener {
    typedef std::map<unsigned int, IUIEventDispatchFct*> TFunctionMap;
    typedef typename TFunctionMap::iterator TFunctionMapIter;

    SUIEventReceiverDispatcher() : m_pEventSystem(nullptr), m_pThis(nullptr) {}

    void Init(Offsets::IUIEventSystem* pEventSystem, C* pThis = nullptr,
              const char* listenerName = "SUIEventReceiverDispatcher")
    {
        m_pEventSystem = pEventSystem;
        m_pThis = pThis;
        if (pThis)
            m_pEventSystem->RegisterListener(this, listenerName);
    }

    template <class R>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(void)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct0<C, R>>(fct);
    }
    template <class R, class T0>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct1<C, R, T0>>(fct);
    }
    template <class R, class T0, class T1>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct2<C, R, T0, T1>>(fct);
    }
    template <class R, class T0, class T1, class T2>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1, T2)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct3<C, R, T0, T1, T2>>(fct);
    }
    template <class R, class T0, class T1, class T2, class T3>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1, T2, T3)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct4<C, R, T0, T1, T2, T3>>(fct);
    }
    template <class R, class T0, class T1, class T2, class T3, class T4>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1, T2, T3, T4)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct5<C, R, T0, T1, T2, T3, T4>>(fct);
    }
    template <class R, class T0, class T1, class T2, class T3, class T4, class T5>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1, T2, T3, T4, T5)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct6<C, R, T0, T1, T2, T3, T4, T5>>(fct);
    }
    template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1, T2, T3, T4, T5, T6)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct7<C, R, T0, T1, T2, T3, T4, T5, T6>>(fct);
    }
    template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1, T2, T3, T4, T5, T6, T7)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct8<C, R, T0, T1, T2, T3, T4, T5, T6, T7>>(fct);
    }
    template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(T0, T1, T2, T3, T4, T5, T6, T7, T8)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct9<C, R, T0, T1, T2, T3, T4, T5, T6, T7, T8>>(fct);
    }
    template <class R>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(const SUIEvent&)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct1<C, R, const SUIEvent&>>(fct);
    }
    template <class R>
    void RegisterEvent(const SUIEventDesc& event, R (C::*fct)(const SUIArguments&)) {
        mFunctionMap[m_pEventSystem->RegisterEvent(event)] = new SUIEventDispatchFctImpl<R, SUIEventDispatchFct1<C, R, const SUIArguments&>>(fct);
    }

    SUIArgumentsRet Dispatch(C* pThis, const SUIEvent& event) {
        TFunctionMapIter it = mFunctionMap.find(event.event);
        if (it != mFunctionMap.end())
            return it->second->Dispatch((void*)pThis, event);
        return SUIArgumentsRet();
    }

    // --- IUIEventListener overrides ---
    SUIArguments* OnEvent(SUIArguments* sretArgs, const SUIEvent& event) override { *sretArgs = Dispatch(m_pThis, event); return sretArgs; }
    void OnEventSystemDestroyed(Offsets::IUIEventSystem* /*pEventSystem*/) override { m_pEventSystem = nullptr; }
    void Dtor(char /*flags*/) override {
        for (TFunctionMapIter it = mFunctionMap.begin(); it != mFunctionMap.end(); ++it) delete it->second;
        if (m_pThis && m_pEventSystem) m_pEventSystem->UnregisterListener(this);
    }

    TFunctionMap             mFunctionMap;   // +0x08
    Offsets::IUIEventSystem* m_pEventSystem; // +0x18
    C*                       m_pThis;        // +0x20
};

namespace detail { struct _SUIRecvDispatcherProbe {}; }
static_assert(sizeof(SUIEventReceiverDispatcher<detail::_SUIRecvDispatcherProbe>) == 0x28);
