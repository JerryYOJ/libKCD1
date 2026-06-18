#pragma once

#include <cstdint>

namespace wh::xgenaimodule::Callbacks {

// -----------------------------------------------
// C_PlainCallbackExtension -- the callback/observer mixin base of C_Variable.
// -----------------------------------------------
// COLLAPSED representation of the RTTI-proven base spine of C_Variable:
//   C_PlainCallbackExtension -> C_NoDataExtension<Functor0,1> -> C_Extension<void,Functor0,1,1>
//   -> C_NoDataExtensionBase<Functor0,1> : C_CallbackListHolder<C_Callback<...>>, C_TrackSequencing<1>
// The intermediate template bases contribute NO data beyond the two fields below (verified from
// the C_Variable ctor sub_180253B98 / base dtor sub_180253D5C), so the whole spine is modeled as
// this single base. It provides the shared vptr@+0x00 and occupies [0x00,0x18) of every C_Variable.
// It lets a variable register/fire change callbacks.
struct C_PlainCallbackExtension {
    virtual ~C_PlainCallbackExtension() = default;  // shared vptr @ +0x00 (the derived spine's vtable)
    void*   m_changeCallbacks;   // +0x08  C_CallbackListHolder head (change-observer list); 0 by default
    uint8_t m_seqGuard;          // +0x10  C_TrackSequencing<1> re-entrancy guard
    uint8_t _pad11[7];           // +0x11
};
static_assert(sizeof(C_PlainCallbackExtension) == 0x18);

}  // namespace wh::xgenaimodule::Callbacks
