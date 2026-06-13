#pragma once

#include <cstdint>
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::I_AIPuppet  -  abstract "AI puppet" interface.
// ===========================================================================
// RTTI: .?AVI_AIPuppet@xgenaimodule@wh@@  (root of the C_AIPuppet hierarchy;
//       RTTI base-class array: { C_AIPuppet, C_CachedPuppet, I_AIPuppet }, all
//       single-inheritance, mdisp=0).
// vtable: 0x182227380 (24 slots, COL 0x182452950) - VERIFIED dump:
//   [0]        deleting dtor (sub_1815B78CC: resets vtable + free)
//   [1..14]    _purecall (0x180A2CA89, pure virtual)
//   [15]       default body sub_180706030 (returns a constant Vec3, qword_1829DA4E0)
//   [16..20]   _purecall (0x180A2CA89, pure virtual)
//   [21]       default body sub_1803953E0 (returns 0/null)  -> GetActor default
//   [22]       default body sub_1806F8140 (returns true)
//   [23]       default body sub_1802E39B0 (no-op)
//
// This is the abstract contract every AI "puppet" (the embodied agent that an
// engine IEntity is bound to) must satisfy: identity (EntityId / IEntity* /
// WUID), world-transform queries (position / direction / rotation / transform),
// physics readouts, deferred spatial-operation setters, and an optional backing
// C_Actor accessor. The concrete leaf is C_AIPuppet, which fulfils every slot by
// delegating to its bound IEntity* (m_pEntity) / C_Actor* (m_pActor) and the
// C_CachedPuppet transform cache.
//
// No data members of its own (pure interface): size 0x08 (vtable pointer only).
//
// Confidence tags below: [V]=verified body+delegation, [L]=likely, [S]=speculative.
// ===========================================================================

// Vec3 / Quat / QuatT are the real SDK Cry_Math.h types (included by kcd.h).

struct IEntity;          // CryEngine entity interface (forward; bound at C_AIPuppet+0x38)
struct IPhysicalEntity;  // CryEngine physics interface (forward; returned by slot 16)

namespace wh::xgenaimodule {

class C_Actor;    // Warhorse actor (IActorSystem::GetActor result; C_AIPuppet+0x40)

// 24-slot abstract interface. Names that are not directly evidenced are flagged.
class I_AIPuppet {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_AIPuppet;
    // [0]  +0x00  virtual (deleting) destructor.
    virtual ~I_AIPuppet();

    // [1]  +0x08  [V] the bound entity's EntityId  (C_AIPuppet -> IEntity vtbl[+0x08] GetId).
    virtual uint32_t GetEntityId() = 0;

    // [2]  +0x10  [V] the bound engine entity  (C_AIPuppet -> returns m_pEntity).
    virtual IEntity* GetEntity() = 0;

    // [3]  +0x18  [L] const overload of GetEntity (folded onto the same body -> m_pEntity).
    virtual IEntity* GetEntityConst() = 0;

    // [4]  +0x20  [V] this puppet's WUID handle  (C_AIPuppet -> &m_wuid).
    virtual const wh::framework::WUID* GetWUID() = 0;

    // [5]  +0x28  [V] cached world position. C_AIPuppet lazily refreshes the cache
    //             (token vs global frame counter dword_1829C8B94): m_cachedPos from
    //             entity vtbl[+0x158] (GetWorldPos), m_cachedForward from vtbl[+0x170];
    //             returns &C_CachedPuppet::m_cachedPos.
    virtual const Vec3* GetWorldPos() = 0;

    // [6]  +0x30  [V] cached forward (look) DIRECTION unit vector = column 1 of the
    //             entity's orthonormalized rotation matrix; refreshed alongside slot 5,
    //             returns &C_CachedPuppet::m_cachedForward.
    virtual const Vec3* GetWorldDir() = 0;

    // [7]  +0x38  [L] world-bounds size: entity vtbl[+0x108] yields an AABB {min,max};
    //             out = (max - min). NOTE: a single gate g = (max.x-min.x >= 0 ? 1 : 0)
    //             multiplies ALL three components, so a degenerate/empty AABB
    //             (X-extent < 0) returns the zero vector (NOT a per-component clamp).
    virtual Vec3* GetWorldBoundsSize(Vec3* out) = 0;

    // [8]  +0x40  [S] invokes entity vtbl[+0x108] for side effect (no out buffer),
    //             discards the result and returns true. Purpose UNVERIFIED
    //             (bounds touch / validity predicate).
    virtual bool vf08_TouchBounds() = 0;

    // [9]  +0x48  [V] the bound entity's engine name  (IEntity vtbl[+0x88] GetName,
    //             returns CEntity+0xE8 const char*).
    virtual const char* GetEntityName() = 0;

    // [10] +0x50  [L] the puppet's cached display name: if C_CachedPuppet::m_name is
    //             empty it is resolved from the entity via wh::framework::S_GameContext
    //             (sub_18027B1E4 -> entity GetProxy(0x12), vtbl[+0x218]) and cached;
    //             returns m_name. This is the writer of C_CachedPuppet::m_name.
    virtual const char* GetName() = 0;

    // [11] +0x58  [L] the bound entity's class name  (GetEntity()->GetClass()
    //             (IEntity vtbl[+0x18]) -> CEntityClass::GetName (vtbl[+0x10],
    //             returns class+0x10 const char*)).
    virtual const char* GetEntityClassName() = 0;

    // [12] +0x60  [V] out Quat: world rotation = Quat::CreateRotationVDir(cached
    //             forward dir). Refreshes the transform cache first (sub_1802452C4).
    virtual Quat* GetWorldRotation(Quat* out) = 0;

    // [13] +0x68  [V] out QuatT: world transform = { CreateRotationVDir(cached forward),
    //             cached position }.
    virtual QuatT* GetWorldTransform(QuatT* out) = 0;

    // [14] +0x70  [L] out Vec3 ground-relative velocity, read from the backing actor
    //             (C_Actor::m_physVelocity, +0x580). No-actor fallback queries
    //             GetPhysicalEntity()->GetStatus(type 2). [name from velocity use]
    virtual Vec3* GetVelocity(Vec3* out) = 0;

    // [15] +0x78  [L] out Vec3 physics body world position, read from the backing actor
    //             (C_Actor::m_physBodyPos, +0x574). I_AIPuppet default + no-actor
    //             fallback return the constant Vec3(0,0,0).
    virtual Vec3* GetPhysWorldPos(Vec3* out);

    // [16] +0x80  [V] the entity's physics object  (IEntity vtbl[+0x240] GetPhysics
    //             -> IPhysicalEntity*).
    virtual IPhysicalEntity* GetPhysicalEntity() = 0;

    // [17] +0x88  [L] deferred set-world-position: optimistically updates the cached
    //             position and enqueues a wh::xgenaimodule::C_PositionSpatialOperation
    //             (built by sub_18042A6A0) onto the global spatial-op queue
    //             qword_183501990. Op TYPE verified via RTTI vftable; in/out direction
    //             of the argument is inferred. Returns the pooled operation.
    virtual void* EnqueuePositionSpatialOp(const Vec3& pos) = 0;

    // [18] +0x90  [L] deferred set-world-direction: quaternion from the input dir,
    //             enqueues a C_RotationSpatialOperation (sub_18042D08C).
    virtual void* EnqueueDirectionSpatialOp(const Vec3& dir) = 0;

    // [19] +0x98  [L] deferred set-world-rotation from a Quat: enqueues a
    //             C_RotationSpatialOperation (sub_18042D08C).
    virtual void* EnqueueRotationSpatialOp(const Quat& rot) = 0;

    // [20] +0xA0  [L] deferred set-world-transform from a QuatT: writes the cache
    //             (pos + forward), stamps the cache token, enqueues a
    //             C_TransformSpatialOperation (sub_180405A84). Thunk sub_18040594C.
    virtual void* EnqueueTransformSpatialOp(const QuatT& tm) = 0;

    // [21] +0xA8  [V] the backing Warhorse actor. I_AIPuppet default returns null;
    //             C_AIPuppet returns m_pActor.
    virtual C_Actor* GetActor();

    // [22] +0xB0  [V] capability/validity predicate; default returns true.
    virtual bool vf22_IsValid();

    // [23] +0xB8  [V] empty hook (no-op).
    virtual void vf23_Hook();
};
static_assert(sizeof(I_AIPuppet) == 0x08);

}  // namespace wh::xgenaimodule
