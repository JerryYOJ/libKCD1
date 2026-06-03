#pragma once

#include <cstdint>
#include "C_CachedPuppet.h"
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::C_AIPuppet : C_CachedPuppet : I_AIPuppet
// ===========================================================================
// RTTI: .?AVC_AIPuppet@xgenaimodule@wh@@   (COL 0x1824431A8, TD 0x182B367F8)
// vtable: 0x1821C7D10 (24 slots). Concrete leaf: overrides slots 0..21 with
//         IEntity/C_Actor-delegating bodies; inherits slot 22 (returns true,
//         sub_1806F8140) and slot 23 (no-op, sub_1802E39B0) from I_AIPuppet.
//
// THE IO HOST. This is the embodied AI agent: it binds a CryEngine IEntity (and
// its Warhorse C_Actor) to the AI WUID of the C_IntelligentObject it hosts.
// C_IntelligentObject::m_pHost (+0x58) points here; the puppet's m_wuid (+0x30)
// is a copy of that hosted object's WUID.
//
// Ctor: sub_1805AFE64(this, IEntity* entity, const WUID* wuid)
//   sub_1804509AC(this);                       // C_CachedPuppet base ctor
//   this->vftable      = &C_AIPuppet::vftable;
//   this->m_wuid       = *wuid;                 // +0x30
//   this->m_pEntity    = entity;                // +0x38
//   sub_1805AFF9C(qword_18378D6E8, this, wuid); // register into EntityGUID->AI map
//   this->m_pActor     = sub_18042C360(entity); // +0x40 = IActorSystem::GetActor(entity->GetId())
//
// Registration (sub_1805AFF9C, into the global EntityGUID->AI map qword_18378D6E8):
//   only if GetEntity() != null. Key = entity->vtbl[+0x10]() (IEntity::GetGuid,
//   8-byte EntityGUID). The found/created node stores, as a 16-byte inline pair:
//       node+0x18 = this (C_AIPuppet*)
//       node+0x20 = *wuid (the AI WUID, inline)
//   (node+0x10 holds the 8-byte GUID key; node+0x00/+0x08 are the chain next/prev.)
//
// Deregistration (dtor sub_1805AFEFC): re-derives the key via
//   m_pEntity->vtbl[+0x10]() and erases this puppet's node from qword_18378D6E8,
//   then tail-calls the C_CachedPuppet dtor body sub_18044FAC8.
//
// NOTE: C_AIPuppet is NOT part of the C_AIObject WUID-registry chain; its base
//       ctor is sub_1804509AC (C_CachedPuppet), not sub_1804505F4 (C_AIObject).
//
// size 0x48.
// ===========================================================================

struct IEntity;   // forward (CryEngine)

namespace wh::xgenaimodule {

class C_AIPuppet : public C_CachedPuppet {
public:
    // --- vtable overrides (slots 0..21; 22/23 inherited from I_AIPuppet) ---
    // Behavior is the verified vtable-body semantics; see I_AIPuppet for slot map.
    ~C_AIPuppet() override;                                   // [0]  sub_1805AFEC8 / sub_1805AFEFC (unregisters)
    uint32_t GetEntityId() override;                          // [1]  sub_180246C4C -> m_pEntity->GetId()
    IEntity* GetEntity() override;                            // [2]  sub_1806F8C30 -> m_pEntity
    IEntity* GetEntityConst() override;                       // [3]  sub_1806F8C30 -> m_pEntity (same body)
    const wh::framework::WUID* GetWUID() override;            // [4]  sub_1806F9160 -> &m_wuid
    const Vec3* GetWorldPos() override;                      // [5]  sub_18033C404 (cached world pos, +0x08)
    const Vec3* GetWorldDir() override;                      // [6]  sub_1802866A0 (cached forward dir, +0x14)
    Vec3* vf07_GetClampedVec(Vec3* out) override;             // [7]  sub_18167E7A4
    bool vf08() override;                                     // [8]  sub_18167E6C8
    int64_t vf09() override;                                  // [9]  sub_1802CB2BC
    int64_t vf10() override;                                  // [10] sub_18027AEA8
    int64_t vf11() override;                                  // [11] sub_1802CFD2C
    void* vf12(void* out) override;                           // [12] sub_18167EB38
    void* vf13(void* out) override;                           // [13] sub_180245130
    Vec3* vf14_GetBodyAnchorA(Vec3* out) override;            // [14] sub_18023B290 (actor +0x580)
    Vec3* vf15_GetBodyAnchorB(Vec3* out) override;            // [15] sub_18066DFF8 (actor +0x574)
    int64_t vf16() override;                                  // [16] sub_180244784 -> entity vtbl[+0x240]
    void* vf17(void* out) override;                           // [17] sub_18042A62C
    void* vf18(void* out) override;                           // [18] sub_1806BABC8
    void* vf19(void* out) override;                           // [19] sub_18042CF64
    int64_t vf20() override;                                  // [20] sub_18040594C (thunk)
    C_Actor* GetActor() override;                             // [21] sub_180705F70 -> m_pActor
    // [22] vf22_IsValid()  : inherited (I_AIPuppet default returns true)
    // [23] vf23_Hook()     : inherited (I_AIPuppet no-op)

    // --- fields (verified from ctor sub_1805AFE64) ---
    wh::framework::WUID m_wuid;     // +0x30  AI WUID of the hosted C_IntelligentObject (copy)
    IEntity*            m_pEntity;  // +0x38  bound CryEngine entity (ctor arg)
    C_Actor*            m_pActor;   // +0x40  IActorSystem::GetActor(m_pEntity->GetId()); may be null
};
static_assert(sizeof(C_AIPuppet) == 0x48);

}  // namespace wh::xgenaimodule
