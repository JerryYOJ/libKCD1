#pragma once

#include "C_EquippableItemRuntimeData.h"
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"
#include "../framework/WUID.h"

// ===========================================================================
// wh::entitymodule::C_WeaponRuntimeData  -  per-instance weapon runtime state
//                                            (the concrete weapon leaf).
//
// Reverse-engineered from WHGame.dll (KCD1 retail). VERIFIED 2026-06.
//   vtable 0x1821cf660 ; ctor sub_18062B21C (calls the C_EquippableItemRuntimeData
//   ctor, then sets the weapon fields below). CONCRETE — slot0 (Clone) = sub_18062BB00.
//   RTTI: .?AVC_WeaponRuntimeData@entitymodule@wh@@ (td @ 0x182a45a28).
//
// THE WEAPON-COATING / POISON RECORD (VERIFIED):
//   +0xC0  CryGUID  m_coatingBuff   : the applied weapon-buff/poison GUID.
//            Null sentinel = xmmword_18300F970 (all-0xFF / null GUID) = no coating.
//            Set on apply; serialized as save-tag 0x1E8 (16 bytes) by sub_18108AB3C.
//            sub_1810844E0 detects "has non-default coating" by comparing this vs
//            the item-class default (itemClass->vtable[0xB0]()+0xF8).
//   +0xD0  int32    m_coatingCharges: remaining hits. On each hit the combat path
//            sub_1806B2BC4 reads +0xC0, does `if (guid != null && (*+0xD0)-- == 1)
//            then +0xC0 = null` (last charge clears the coating), and applies the
//            buff GUID to the victim's soul (sub_18056A074). Serialized after the
//            GUID (tag 0x1E8 second field, 4 bytes). rpg_param Min/MaxWeaponBuffCharge
//            + DerivStat_WeaponBuffCharges bound the count.
//   Other ctor-init fields:
//   +0xA8  uint8   (=0; save tag 0x1E4)
//   +0xA9  uint8   (=0; save tag 0x1E5)
//   +0xAA  WUID    (=-1 sentinel; save tag 0x1E6) — likely the applier/source actor [role UNVERIFIED]
//   +0xB4  int32   (=3; default after load) [UNVERIFIED meaning — a state/kind enum?]
//   +0xB8  int32   (=0xFF; default after load) [UNVERIFIED]
// ===========================================================================

namespace wh { namespace entitymodule {

class C_WeaponRuntimeData : public C_EquippableItemRuntimeData {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_WeaponRuntimeData;
    I_ItemRuntimeData* Clone() override;    // slot0 = sub_18062BB00 (alloc from pool + deep-copy)

    uint8_t              m_flagA8;          // +0xA8  save tag 0x1E4
    uint8_t              m_flagA9;          // +0xA9  save tag 0x1E5
    wh::framework::WUID  m_sourceWuid;      // +0xAA  save tag 0x1E6 (=-1 none) — applier/source [role UNVERIFIED]
    uint8_t              _padB2[2];         // +0xB2
    int32_t              m_unkB4;           // +0xB4  default 3 [UNVERIFIED]
    int32_t              m_unkB8;           // +0xB8  default 0xFF [UNVERIFIED]
    uint8_t              _padBC[4];         // +0xBC
    CryGUID              m_coatingBuff;     // +0xC0  applied weapon-coating/poison buff GUID (null = all-0xFF)
    int32_t              m_coatingCharges;  // +0xD0  remaining hits; decremented per hit, 0 -> clears m_coatingBuff
    uint8_t              _padD4[4];         // +0xD4
};

}} // namespace wh::entitymodule
