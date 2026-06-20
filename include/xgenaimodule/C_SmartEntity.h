#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "C_IntelligentObject.h"            // primary spine (C_AIObject..C_IntelligentObject, 0x178)
#include "I_SmartEntitySubbrainListener.h"  // MI base @+0x178
#include "I_SmartEntity.h"                  // MI base @+0x180 (XGenPublic)
#include "I_TemplateIdentification.h"       // virtual base (vbptr @+0x188)
#include "../framework/CryStringHash.h"     // std::hash<CryStringT<char>> for the subbrain map
// CryStringT<char> comes from the PCH prelude.

// ===========================================================================
// wh::xgenaimodule::C_SmartEntity : C_IntelligentObject, I_SmartEntitySubbrainListener,
//                                   XGenPublic::I_SmartEntity, virtual I_TemplateIdentification
// ===========================================================================
// RTTI: .?AVC_SmartEntity@xgenaimodule@wh@@ (TD 0x182b1e468). Abstract parent of C_SmartArea and
// C_InteractiveSmartEntity; never instantiated standalone. Ctor sub_181676814. It INTRODUCES the
// virtual base I_TemplateIdentification (so MSVC places a vbptr at +0x188, right after the two MI
// interface vtables at +0x178/+0x180; the shared vbase lands at the end of the most-derived object
// -- in C_SmartArea at +0x438). Non-virtual subobject extent = 0x218 (own fields +0x190..+0x217).
// Holds the entity's subbrain set/state. Layout VERIFIED from ctor sub_181676814 + sub_1815CC0F0.
// ===========================================================================

namespace wh::xgenaimodule {

// element of m_subbrainStates (0xC bytes; byte[0] is the state enum read by I_SmartEntity::GetSubbrainState).
struct S_SubbrainEntry {
    uint8_t state;        // +0x00
    uint8_t _unk[0xB];    // +0x01  remaining bytes [UNVERIFIED]
};
static_assert(sizeof(S_SubbrainEntry) == 0xC);

class C_SmartEntity
    : public C_IntelligentObject                 // +0x000  (0x178)
    , public I_SmartEntitySubbrainListener       // +0x178
    , public XGenPublic::I_SmartEntity           // +0x180
    , public virtual I_TemplateIdentification    // vbptr @+0x188; vbase appended by most-derived
{
public:
    // --- own fields (+0x190 .. non-virtual end 0x218) ---
    void*                               m_pSubbrainContainer;  // +0x190  non-owning subbrain holder (its subbrain array is at holder+0x28,
                                                               //         0x20-byte entries; I_SmartEntity slots deref this)
    void*                               m_pSubbrainQueryA;     // +0x198  owned helper object (released+nulled in sub_181677EEC) [UNVERIFIED type]
    std::vector<S_SubbrainEntry>        m_subbrainStates;      // +0x1A0  per-subbrain state byte (GetSubbrainState)
    std::unordered_map<CryStringT<char>, void*> m_subbrainMap; // +0x1B8  key = CryStringT subbrain name (GetSubbrainMap; node dtor sub_1805B0E2C)
    void*                               m_pSubbrainQueryB;     // +0x1F8  owned helper object (released+nulled in sub_181677EEC) [UNVERIFIED type]
    void*                               m_pSubbrain;           // +0x200  non-owning; queried via vtbl+0x48 by the listener
    uint32_t                            _unk208;               // +0x208  (not ctor-inited) [UNVERIFIED]
    uint32_t                            _unk20C;               // +0x20C  [UNVERIFIED]
    uint32_t                            _unk210;               // +0x210  [UNVERIFIED]
    uint8_t                             m_flags;               // +0x214  low 3 bits (bit0 = subbrain-notified)
    uint8_t                             _pad215[3];            // +0x215  -> non-virtual end 0x218
};

}  // namespace wh::xgenaimodule
