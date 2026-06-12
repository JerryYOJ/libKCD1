#pragma once
#include <cstdint>

// -----------------------------------------------
// IUIElementIterator — Binary vtable order (NOT interfuscated)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashUI.h:1034 (UNIQUE_IFACE struct
// IUIElementIterator). No <interfuscator:shuffle> tags -> slot order ==
// C++ declaration order.
//
// Implementation: CUIElementIterator, vtable @ 0x1821b7818 (5 slots,
// this_off 0). RTTI: .?AUCUIElementIterator@@ : IUIElementIterator.
// The pure IUIElementIterator base vtable itself is at 0x1821b77e8
// (dtor + 4x _purecall). 5 binary slots == 5 SDK declarations: matches our
// SDK header copy EXACTLY (no inserted slot).
//
// Instances are handed out by IUIElement::GetInstances() as
// IUIElementIteratorPtr (ref-counted smart ptr -> AddRef/Release).
// CUIElementIterator layout: +0x10 = owning CFlashUIElement*, +0x18 = current
// position inside the owner's instances vector (owner+0xC8 .. owner+0xD0).

namespace Offsets {

struct IUIElement;

struct IUIElementIterator {
    virtual void Dtor(char flags) = 0;          // [0] 0x00  0x180503650 (scalar deleting dtor; pure-base slot: sub_181869830)
    virtual void AddRef() = 0;                  // [1] 0x08  sub_1806F8400  (decl-mapped)
    virtual void Release() = 0;                 // [2] 0x10  sub_18050363C  (decl-mapped)

    virtual IUIElement* Next() = 0;             // [3] 0x18  sub_18050353C  VERIFIED: returns *cur and advances this+0x18 until owner's instances end (owner+0xD0)
    virtual int GetCount() const = 0;           // [4] 0x20  sub_180708C50  VERIFIED: (owner+0xD0 - owner+0xC8) >> 3 — size of the same instances vector Next walks
};

}  // namespace Offsets
