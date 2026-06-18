#pragma once

#include <cstdint>
// CryStringT<char> is provided by the PCH prelude (CryString.h is in PCH.h).

// ===========================================================================
// wh::xgenaimodule::S_InformationResolution  (size 0x40)
// ===========================================================================
// Pointee of C_InformationManager::m_resolutions (the std::unordered_set<S_InformationResolution*>
// at manager+0xD0). Stored as a POINTER: the set node payload is 8 bytes and the clear
// sub_1815CF610 derefs node+0x10 then passes the value to the dtor (NOT inline-by-value).
//   ctor      sub_1815CB0D0  (zeroes +0x00/+0x08/+0x20/+0x28/+0x30; weight=1.0f; flags=0x12; empty text)
//   copy-ctor sub_1815DB24C  (qword-copies +0x00/+0x08/+0x20/+0x28/+0x30; dword +0x10/+0x18; deep-copies text)
//   dtor      sub_1815CE204  (frees ONLY +0x38 -> every pointer-ish slot is non-owning)
//   set key   {record pointer-identity, *(uint32*)informationKey} via comparator sub_1815CDF04
// Built+inserted by the registrar sub_1815CE6B4 (sub_1815DFFD0 insert / sub_1815E0E84 find).
namespace wh::xgenaimodule {

struct S_InformationRecord;   // +0x00 points to one

struct S_InformationResolution {
    S_InformationRecord*  record;          // +0x00  the record this resolution concerns                 [CONFIRMED]
    const uint32_t*       informationKey;  // +0x08  -> manager-owned key entry (registry +0x88); leading uint32 = information id [CONFIRMED]
    float                 weight;          // +0x10  init 1.0f                                            [CONFIRMED]
    uint32_t              _pad14;          // +0x14
    uint32_t              flags;           // +0x18  init 0x12 (0x11 & ~1 | 2)                            [CONFIRMED]
    uint32_t              _pad1C;          // +0x1C
    uint64_t              _reserved20;     // +0x20  zero-init, shallow-copied, never freed; NO writer found in any path [UNRESOLVED]
    uint64_t              _reserved28;     // +0x28  zero-init, shallow-copied, never freed; NO writer found in any path [UNRESOLVED]
    uint64_t              _reserved30;     // +0x30  zero-init, shallow-copied, never freed; NO writer found in any path [UNRESOLVED]
    CryStringT<char>      text;            // +0x38  refcounted string (init = empty-string singleton)    [CONFIRMED]
};
static_assert(sizeof(S_InformationResolution) == 0x40, "0x40 (last field CryString @+0x38; ctor sub_1815CB0D0)");

}  // namespace wh::xgenaimodule
