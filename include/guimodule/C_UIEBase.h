#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
// consolidated into IFlashUI.h

// -----------------------------------------------
// C_UIEBase 鈥?base class for Flash-element-bound UI controllers
// -----------------------------------------------
// RTTI: .?AVC_UIEBase@uielement@guimodule@wh@@  (namespace
// wh::guimodule::uielement)
// Base class (no own RTTI COL/factory); observed as base of
// wh::guimodule::C_UIRPGElements at +0x10 (vtable 0x1826d28f0, 11 slots
// = 8 IUIElementEventListener + 3 own).
//
// RTTI class-hierarchy descriptor: C_UIEBase : IUIElementEventListener (+0).
// IUIElementEventListener has EXACTLY 8 slots in declaration order (the SDK
// header IFlashUI.h is untagged 鈥?NOT interfuscated; the old 20-slot replica
// fused three adjacent vtables and has been corrected 鈥?see
// Offsets/vtables/IUIElementEventListener.h).
//
// Slot table for the C_UIRPGElements instantiation (vtable 0x1826d28f0):
//   [0]  0x00  sub_180501E90  OnUIEvent 鈥?main element-event entry
//   [1..6]     _guard_check_icall_nop (empty SDK default impls)
//   [7]  0x38  sub_180B1AF7C  adjustor thunk (this-0x10) -> deleting dtor
//              sub_181146D8C
//   --- C_UIEBase own virtuals ---
//   [8]  0x40  sub_18114B164  (0x21A; refs "RequestSkills",
//              "RequestSkillPerks", "RequestSoulValues", "RequestStatPerks",
//              "RequestLearnPerk", "GetStatisticsCategory", "GetStatistics" 鈥?//              element-function registration/dispatch for the bound element)
//   [9]  0x48  sub_181113030  = { if (m_pElement) m_pElement->vfunc+0x1F8; }
//   [10] 0x50  sub_1806FE690  returns "Inventory" 鈥?name of the bound Flash
//              element (C_UIRPGElements binds to the "Inventory" element)
//
// Data members: ctor is inlined into the derived ctor (C_UIRPGElements
// sub_181143C38 zero-fills exactly +0x08..+0x28 of this subobject).
// sizeof == 0x28 inferred from that layout (no factory allocation evidence 鈥?// static_assert intentionally based on member layout only). [UNVERIFIED size]

namespace wh::guimodule::uielement {

class C_UIEBase : public Offsets::IUIElementEventListener {  // +0x00 (8 slots)
public:
    // C_UIEBase own virtuals (slots [8]..[10] of the combined vtable):
    virtual void _vf8() = 0;             // [8]  0x40  sub_18114B164 (element function registry; "RequestSkills"...)
    virtual void _vf9() {}               // [9]  0x48  real impl sub_181113030 (calls m_pElement vtbl+0x1F8 if set)
    virtual const char* GetElementName() = 0; // [10] 0x50  sub_1806FE690 -> "Inventory" (name UNVERIFIED, behavior verified)

    void*    _unk08;        // +0x08  zero-inited by derived ctor
    void*    _unk10;        // +0x10  zero-inited by derived ctor
    void*    _unk18;        // +0x18  zero-inited by derived ctor
    void*    m_pElement;    // +0x20  bound UI element; dispatched via vtbl+0x1F8 (exact type UNVERIFIED, likely IUIElement*)
};
static_assert(sizeof(C_UIEBase) == 0x28);

}  // namespace wh::guimodule::uielement
