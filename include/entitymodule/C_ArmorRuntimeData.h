#pragma once

#include "C_EquippableItemRuntimeData.h"

// ===========================================================================
// wh::entitymodule::C_ArmorRuntimeData  -  per-instance armor runtime state
//                                           (concrete equippable leaf).
//
// Reverse-engineered from WHGame.dll (KCD1 retail). VERIFIED 2026-06.
//   vtable 0x1821cf5c8 ; ctor sub_18062B0B8 ; create sub_18062B060 (pool-alloc + ctor,
//   passes a3=7 -> m_kind). slot0 (Clone) = sub_18062BC80 ; (de)serializer slot7 =
//   sub_18108A700 (save tags 0x230E/0x230F/0x2310; the base +0x90 GUID set uses 0x2125).
//
// PURPOSE (VERIFIED behaviourally): this is the armor item's VISUAL / MATERIAL maintenance
// state — dirt / blood / damage levels stored as 0..255 bytes and pushed onto the item's
// render IMaterial(s). slot8 (sub_180633474) runs an `IMaterial&` query (flag 0x2000000)
// to apply the state then clears the dirty fields; slot1/slot5 mutate a level, raise a
// dirty bit, and fire the base change-signal (the +0x30 delegate vector). The level bytes
// are stored inverted: slot1 writes (1 - fraction) * 255.
// ===========================================================================

namespace wh { namespace entitymodule {

class C_ArmorRuntimeData : public C_EquippableItemRuntimeData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ArmorRuntimeData;
    I_ItemRuntimeData* Clone() override;        // slot0 = sub_18062BC80 (alloc from pool + deep-copy)

    uint8_t   m_flagA8;          // +0xA8  flag; slot5 (sub_18069AFF4) clears it & raises m_dirtyBits bit0. save tag 0x230E
    uint8_t   m_levels[0x24];    // +0xA9  36 per-aspect level bytes (0..255); slot4 (sub_1802CF028) tests "any non-zero".
                                 //        save tag 0x230F. Pushed to the material in slot8. [per-byte aspect map UNVERIFIED]
    uint8_t   m_levelCD;         // +0xCD  level byte = (1 - fraction)*255; slot1 (sub_18056C5DC) sets it & raises bit1. save tag 0x2310
    uint8_t   _padCE[2];         // +0xCE
    uint32_t  m_dirtyBits;       // +0xD0  which aspects changed (bit0=slot5, bit1=slot1); load |= 3; slot8 clears after applying
    uint32_t  m_aspectMask;      // +0xD4  per-aspect mask; load = 0x1FF (9 bits); slot8 clears [exact bit meanings UNVERIFIED]
    uint32_t  m_kind;            // +0xD8  ctor arg (create passes 7) [role UNVERIFIED]
};

}} // namespace wh::entitymodule
