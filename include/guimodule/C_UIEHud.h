#pragma once
#include <cstdint>
#include "Offsets/vtables/IMovieListener.h"
#include "Offsets/vtables/I_HUD.h"
#include "guimodule/C_UIEBase.h"

// -----------------------------------------------
// C_UIEHud — in-game HUD root element (the "hud" Flash element controller)
// -----------------------------------------------
// RTTI: .?AVC_UIEHud@uielement@guimodule@wh@@  (wh::guimodule::uielement::C_UIEHud)
// Constructor: sub_1811123AC  — stores the singleton instance into the global
//              qword_183785948 (RVA 0x3785948); getter sub_180555720; dtor
//              sub_18111274C clears the global.
// Built by:    sub_1811034FC — the HUD-elements builder (allocates 0x178). This
//              is NOT a process-lifetime singleton: it is torn down and rebuilt
//              with the HUD/UI subsystem, and EACH build re-zeroes the refcount
//              array (memset C_UIEHud+0x50, 0, 0x60).
// Reached at runtime via S_GameContext+0xB8 -> +0x98 (that pointer is `this`;
//              the I_HUD subobject the game calls is `this+8`).
// Size:        0x178
//
// Inheritance (3 polymorphic bases — from the ctor's three vptr stores, the
// RTTI COL offsets, and the per-vtable slot counts):
//   [+0x00] IMovieListener (2 slots)  — cutscene/sequence event sink
//   [+0x08] I_HUD          (5 slots)  — HUD-element visibility API (the refcount)
//   [+0x10] C_UIEBase      (11 slots) — Flash-element-bound UI controller base
//                                       (its members occupy +0x18..+0x30)
//
// Cinematic letterbox: the dialogue "RatioStrips" bars are HUD element bit 20
// (mask 0x100000). Dialogue-camera entry (sub_18056C654) calls
// RemoveElementHideRequest(0x100000) to drop that element's hide-count to 0 and
// reveal the bars. Holding m_elementHideRefcount[20] permanently >= 1 keeps the
// bars hidden no matter how the dialogue toggles it.

namespace wh::guimodule::uielement {

// HUD element bit indices (index into m_elementHideRefcount). Only RatioStrips
// is verified for this class (mask 0x100000 == bit 20, from the bitmask->name
// table sub_181113D84). Others are intentionally omitted until verified.
enum E_HUDElement : uint32_t {
    HUDELEMENT_RatioStrips = 20,   // mask 0x100000 — cinematic letterbox bars
};

class C_UIEHud
    : public Offsets::IMovieListener   // +0x00 (2 slots)
    , public Offsets::I_HUD            // +0x08 (5 slots)
    , public C_UIEBase                 // +0x10 (11 slots; its members at +0x18..+0x30)
{
public:
    // Singleton accessor — the live instance pointer is the global qword_183785948.
    static C_UIEHud* GetInstance();        // impl in guimodule/C_UIEHud.cpp (REL::ID 0x3785948)

    void*    _unk38;                       // +0x38  (not touched by the ctor)
    void*    _unk40;                       // +0x40  (not touched by the ctor)
    void*    _unk48;                       // +0x48  zeroed by the ctor
    int32_t  m_elementHideRefcount[24];    // +0x50  per-element HIDE refcount (0 == visible); memset by ctor
    uint8_t  _unkB0[0xC0];                 // +0xB0  zeroed by the ctor (sub-objects / arrays)
    uint8_t  m_flags;                      // +0x170 ctor clears bit 0
    uint8_t  _pad171[3];                   // +0x171
    int32_t  m_combatState;                // +0x174 last value set by I_HUD::SetCombatState
};
static_assert(sizeof(C_UIEHud) == 0x178, "C_UIEHud must be 0x178 (factory allocates 0x178)");

}  // namespace wh::guimodule::uielement
