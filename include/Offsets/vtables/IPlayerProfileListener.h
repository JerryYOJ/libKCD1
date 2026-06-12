#pragma once

// -----------------------------------------------
// IPlayerProfileListener — Binary vtable order
// -----------------------------------------------
// SDK: CryEngine CryAction/IPlayerProfiles.h:97 (class, GLOBAL namespace,
// NOT interfuscator-tagged -> declaration order == binary order).
// RTTI: .?AVIPlayerProfileListener@@
//
// SDK declaration (in-tree RE/include/CryEngine/CryAction/IPlayerProfiles.h):
//   virtual ~IPlayerProfileListener(){}
//   virtual void SaveToProfile(IPlayerProfile*, bool online, unsigned int reason) = 0;
//   virtual void LoadFromProfile(IPlayerProfile*, bool online, unsigned int reason) = 0;
//
// Binary vtable for wh::guimodule::CUISettings @ 0x1822ecfe0 (3 slots):
//   [0] sub_180B1AF40  adjustor thunk (this-8) -> deleting dtor sub_181146BC8
//   [1] sub_181155EC0  thunk: this+8, re-dispatch via IUIGameEventSystem
//                      vtbl+0x38 ([7] = sub_1811559C0) — SaveToProfile
//   [2] sub_181150AD0  thunk: this+8, re-dispatch via IUIGameEventSystem
//                      vtbl+0x30 ([6] = sub_181150D40) — LoadFromProfile
// i.e. Warhorse routes the profile save/load through two extra virtuals on its
// extended IUIGameEventSystem (slots [6]/[7], nop in other implementers).
//
// Listeners register through IPlayerProfileManager::AddListener(pListener,
// updateNow) — CUISettings ctor (sub_1811419C4) tail: profile manager from
// S_GameContext+8 vfunc+0x130, then vfunc+0xF0(this+8, true).

struct IPlayerProfile;  // CryAction/IPlayerProfiles.h:345 (GLOBAL namespace)

namespace Offsets {

struct IPlayerProfileListener {
    virtual void Dtor(char flags) = 0;                                                          // [0] 0x00
    virtual void SaveToProfile(::IPlayerProfile* pProfile, bool online, unsigned int reason) = 0;   // [1] 0x08
    virtual void LoadFromProfile(::IPlayerProfile* pProfile, bool online, unsigned int reason) = 0; // [2] 0x10
};

}  // namespace Offsets
