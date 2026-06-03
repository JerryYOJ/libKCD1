#pragma once

#include <cstdint>
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::I_AIPuppet  -  abstract "AI puppet" interface.
// ===========================================================================
// RTTI: .?AVI_AIPuppet@xgenaimodule@wh@@  (root of the C_AIPuppet hierarchy;
//       RTTI base-class array: { C_AIPuppet, C_CachedPuppet, I_AIPuppet }, all
//       single-inheritance, mdisp=0).
// vtable: 0x182227380 (24 slots, COL 0x182452950).
//   slot 0          = deleting dtor (sub_1815B78CC: just resets vtable + free)
//   slots 1..14     = _purecall  (pure virtual; 0x180A2CA89)
//   slot 15         = default body sub_180706030 (returns a constant Vec3)
//   slots 16..20    = _purecall  (pure virtual)
//   slot 21         = default body sub_1803953E0 (returns 0 / null)
//   slot 22         = default body sub_1806F8140 (returns true)
//   slot 23         = default body sub_1802E39B0 (no-op)
//
// This is the abstract contract every AI "puppet" (the embodied agent that an
// engine IEntity is bound to) must satisfy: identity (EntityId / IEntity* /
// WUID), world transform queries (position / direction / aux body anchors),
// and an optional backing actor accessor. The concrete leaf is C_AIPuppet,
// which fulfils every slot by delegating to its bound IEntity* / C_Actor*.
//
// No data members of its own (pure interface): size 0x08 (vtable pointer only).
// ===========================================================================

// CryEngine math vector (3x float). Defined here (guarded) so the puppet
// headers stand alone; replace with the project Vec3 once it is RE'd.
#ifndef WH_VEC3_DEFINED
#define WH_VEC3_DEFINED
struct Vec3 { float x, y, z; };
static_assert(sizeof(Vec3) == 0x0C, "Vec3 must be 3 floats");
#endif

struct IEntity;   // CryEngine entity interface (forward; bound at C_AIPuppet+0x38)

namespace wh::xgenaimodule {

class C_Actor;    // Warhorse actor (IActorSystem::GetActor result; C_AIPuppet+0x40)

// 24-slot abstract interface. Names that are not directly evidenced are marked
// [UNVERIFIED]; the documented behavior is the verified vtable-body semantics.
class I_AIPuppet {
public:
    // [0]  +0x00  virtual (deleting) destructor.
    virtual ~I_AIPuppet();

    // [1]  +0x08  identity: the bound entity's EntityId. (C_AIPuppet -> IEntity vtbl[+0x08])
    virtual uint32_t GetEntityId() = 0;

    // [2]  +0x10  the bound engine entity. (C_AIPuppet -> returns m_pEntity)
    virtual IEntity* GetEntity() = 0;

    // [3]  +0x18  the bound engine entity (second slot; C_AIPuppet folds it onto
    //             the same body as slot 2 -> returns m_pEntity). Likely a const
    //             overload in the original source. [name UNVERIFIED]
    virtual IEntity* GetEntityConst() = 0;

    // [4]  +0x20  this puppet's WUID handle (C_AIPuppet -> &m_wuid).
    virtual const wh::framework::WUID* GetWUID() = 0;

    // [5]  +0x28  cached world position. (C_AIPuppet: lazily refreshes the cache
    //             from the entity transform, keyed by a global frame token, and
    //             returns &C_CachedPuppet::m_cachedPos.)
    virtual const Vec3* GetWorldPos() = 0;

    // [6]  +0x30  cached forward (look) DIRECTION unit vector = column 1 of the
    //             entity's orthonormalized rotation matrix; refreshed alongside
    //             slot 5, returns &C_CachedPuppet::m_cachedForward (sub_18033C404).
    //             [name GetWorldDir inferred from the verified forward-vector body]
    virtual const Vec3* GetWorldDir() = 0;

    // [7]  +0x38  out-param Vec3 derived from the entity transform (vtbl[+0x108]),
    //             component-wise clamped to >= 0. [name UNVERIFIED]
    virtual Vec3* vf07_GetClampedVec(Vec3* out) = 0;

    // [8]  +0x40  pokes the entity transform (vtbl[+0x108]); returns true.
    //             [name UNVERIFIED]
    virtual bool vf08() = 0;

    // [9]  +0x48  delegates to entity vtbl[+0x88]. [name UNVERIFIED]
    virtual int64_t vf09() = 0;

    // [10] +0x50  delegates to helper(this, m_pEntity) (sub_18027AEB4).
    //             [name UNVERIFIED]
    virtual int64_t vf10() = 0;

    // [11] +0x58  GetEntity()->vtbl[+0x18]()->vtbl[+0x10](). [name UNVERIFIED]
    virtual int64_t vf11() = 0;

    // [12] +0x60  out-param query via helper(this, out, m_pEntity) (sub_18167EF68).
    //             [name UNVERIFIED]
    virtual void* vf12(void* out) = 0;

    // [13] +0x68  out-param query via helper(this, out, m_pEntity) (sub_18024514C).
    //             [name UNVERIFIED]
    virtual void* vf13(void* out) = 0;

    // [14] +0x70  out Vec3 anchor read from the backing actor (C_Actor +0x580),
    //             else queried from the entity. [name UNVERIFIED, e.g. eye/head pos]
    virtual Vec3* vf14_GetBodyAnchorA(Vec3* out) = 0;

    // [15] +0x78  out Vec3 anchor read from the backing actor (C_Actor +0x574).
    //             I_AIPuppet default returns a constant Vec3. [name UNVERIFIED]
    virtual Vec3* vf15_GetBodyAnchorB(Vec3* out);

    // [16] +0x80  delegates to entity vtbl[+0x240]. [name UNVERIFIED]
    virtual int64_t vf16() = 0;

    // [17] +0x88  out-param query via helper(this, out, m_pEntity) (sub_18042A638).
    //             [name UNVERIFIED]
    virtual void* vf17(void* out) = 0;

    // [18] +0x90  out-param query via helper(this, out, m_pEntity) (sub_1806BABD4).
    //             [name UNVERIFIED]
    virtual void* vf18(void* out) = 0;

    // [19] +0x98  out-param query via helper(this, out, m_pEntity) (sub_18042CF70).
    //             [name UNVERIFIED]
    virtual void* vf19(void* out) = 0;

    // [20] +0xA0  thunk -> sub_180405954. [name UNVERIFIED]
    virtual int64_t vf20() = 0;

    // [21] +0xA8  the backing Warhorse actor. I_AIPuppet default returns null;
    //             C_AIPuppet returns m_pActor.
    virtual C_Actor* GetActor();

    // [22] +0xB0  capability/validity predicate; default returns true. [name UNVERIFIED]
    virtual bool vf22_IsValid();

    // [23] +0xB8  empty hook (no-op).
    virtual void vf23_Hook();
};
static_assert(sizeof(I_AIPuppet) == 0x08);

}  // namespace wh::xgenaimodule
