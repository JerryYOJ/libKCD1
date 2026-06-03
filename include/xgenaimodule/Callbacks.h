#pragma once

#include <cstdint>
#include "../framework/WUID.h"

// ===========================================================================
// The Warhorse "Callbacks" notification mixin family + the E_AIONotifyEvent the AI-object
// managers broadcast. These are the base classes of every T_ObjectManagerBase (see
// T_ObjectManagerBase.h) — e.g. C_LinkablesManager. The chain (deepest -> derived) is:
//
//   Callbacks::C_NoDataExtensionBase   (owns the primary vtable @+0x00; aggregates the 2 holders)
//     <- Callbacks::C_Extension        (no data)
//        <- Callbacks::C_NoDataExtension(no data)
//           <- T_ObjectManagerBase     (adds the map)
//
// Verified from C_LinkablesManager's RTTI base-class array (PMD member offsets) + its ctor
// (sub_181676778) + the notify dispatcher (sub_180450730).
// ===========================================================================

// CryEngine 2-arg delegate (RE/include/CryEngine/CryCommon/functor.h, ::Functor2<P1,P2>). It is
// only referenced *by name* below (the subscriber nodes are never instantiated in this header), so
// a forward declaration is enough and avoids pulling functor.h. Matches the type the binary uses.
template<typename P1, typename P2> class Functor2;

namespace wh::xgenaimodule {

// ---------------------------------------------------------------------------
// E_AIONotifyEvent — what an object-manager broadcasts (together with the object's WUID) when its
// set of registered objects changes. Modeled as the enum-in-struct idiom the binary uses
// (E_AIONotifyEvent::Type). VERIFIED: insert (sub_180450678) fires Added; erase (sub_180450130)
// and clear (sub_1815A7308) fire Removed.
// ---------------------------------------------------------------------------
struct E_AIONotifyEvent {
    enum Type : uint32_t {
        Added   = 0,   // an object was registered
        Removed = 1,   // an object was unregistered / the manager was cleared
    };
};

namespace Callbacks {

// A single subscriber node held in a manager's callback set. Embeds a CryEngine Functor2; the
// notify dispatcher (sub_180450730) invokes the thunk at this+0x20 as (this+0x08, event, &wuid).
// Never instantiated here (the holder keeps only a type-erased set pointer) — declared for fidelity.
template<class R, class TFunctor, class Ctx>
class C_Callback;

// +0x08 of the manager: lazily-allocated pointer to the subscriber set (a pooled hash-set of
// TCallback). Null until the first subscribe; freed when the last subscriber leaves (sub_180450830).
template<class TCallback>
class C_CallbackListHolder {
public:
    void* m_pCallbackSet = nullptr;   // +0x00
};

// +0x10 of the manager: a single re-entrancy guard byte the dispatcher raises while iterating the
// subscriber set, so (un)subscribes issued from inside a broadcast are handled safely.
template<int N>
class C_TrackSequencing {
public:
    uint8_t m_dispatching = 0;   // +0x00  1 while Notify() is running, else 0
    uint8_t _pad[7];
};

// The polymorphic notification base: it OWNS the primary vtable (+0x00) and aggregates the two
// holder bases (callback set @+0x08, guard byte @+0x10). "NoData" = it adds no fields of its own.
// vtable [0]=dtor, [1]=OnChanged (a default no-op, folded to the CFG guard stub in the binary).
// The non-virtual Notify() broadcast = sub_180450730.
template<class TFunctor, int N>
class C_NoDataExtensionBase
    : public C_CallbackListHolder<C_Callback<void, TFunctor, void>>   // +0x08
    , public C_TrackSequencing<N>                                      // +0x10
{
public:
    virtual ~C_NoDataExtensionBase();   // vtable [0]
    virtual void OnChanged();           // vtable [1]  default no-op hook

protected:
    // Raise m_dispatching, walk the subscriber set, invoke each C_Callback with (event, &object). [sub_180450730]
    void Notify(E_AIONotifyEvent::Type ev, const wh::framework::WUID& object);
};

// Thin behaviour mixins in the chain; neither adds data. C_Extension<R, TFunctor, A, B> (R=void here).
template<class R, class TFunctor, int A, int B>
class C_Extension : public C_NoDataExtensionBase<TFunctor, A> {};

template<class TFunctor, int N>
class C_NoDataExtension : public C_Extension<void, TFunctor, N, N> {};

}  // namespace Callbacks
}  // namespace wh::xgenaimodule
