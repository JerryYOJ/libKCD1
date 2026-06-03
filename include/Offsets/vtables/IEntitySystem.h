#pragma once
#include <cstdint>

typedef unsigned int EntityId;
#include "IEntity.h"

// -----------------------------------------------
// IEntitySystem — Binary vtable order (interfuscated)
// -----------------------------------------------
// CEntitySystem RTTI: .?AVCEntitySystem@@ (TypeDescriptor at 0x182b68298)
// Vtable region: COL at 0x182796800, vfuncs start at 0x182796808
// Singleton: gEnv+0xA8 = qword_1829D1760
// Total: 104 vfunc slots (0x00-0x340)
//
// IMPORTANT: Offsets below are from the vtable pointer (first vfunc at [0]),
// NOT from the COL. This matches how code accesses: *(vtable + offset).
// The agent's raw offsets from 0x182796800 are 0x08 higher than these.

struct SEntitySpawnParams;
struct IEntityIt;
struct ICrySizer;
typedef uint64_t EntityGUID;

namespace Offsets {

struct IEntitySystem {
    virtual void Dtor() = 0;                                                             // [0]  0x00   sub_181D9CBC8
    virtual void RenderUpdateEntities() = 0;                                             // [1]  0x08   thunk→sub_180373C78 (AABB update, RegisterForRendering)
    virtual void _vf2() = 0;                                                            // [2]  0x10
    virtual void PrePhysicsUpdate() = 0;                                                 // [3]  0x18   "EntitySystem::PrePhysicsUpdate" string
    virtual void Update() = 0;                                                           // [4]  0x20   "EntitySystem::Update" string
    virtual void ResetEntities() = 0;                                                    // [5]  0x28   "reset_entities" string
    virtual void Release() = 0;                                                          // [6]  0x30   clears I3DEngine, entity class registry
    virtual void ClearEntitySinks() = 0;                                                 // [7]  0x38   walks listener list, fires dtor on each
    virtual void DeletePendingEntities() = 0;                                            // [8]  0x40   thunk→entity deletion queue flush
    virtual void* GetScriptSystem() = 0;                                                 // [9]  0x48   returns *(this+0x300280)
    virtual IEntity* SpawnEntity(SEntitySpawnParams& params, bool bAutoInit = true) = 0; // [10] 0x50   sub_1802B9CAC — "SpawnEntity" string xref
    virtual bool InitEntity(IEntity* pEntity, SEntitySpawnParams& params) = 0;           // [11] 0x58   sub_1802B916C — fires spawn listeners
    virtual IEntity* GetEntity(EntityId id) const = 0;                                   // [12] 0x60   sub_180378490 — confirmed from soul lookup code
    virtual void _vf13() = 0;                                                           // [13] 0x68   GetEntityFromIndex
    virtual void _vf14() = 0;                                                           // [14] 0x70   GetLinkedParentEntityId
    virtual IEntity* FindEntityByName(const char* name) const = 0;                       // [15] 0x78   sub_18069E150 — "FindEntityByName: %s" string
    virtual void _vf16() = 0;                                                           // [16] 0x80   LockSafeEntityDeletion
    virtual void _vf17() = 0;                                                           // [17] 0x88   UnlockSafeEntityDeletion
    virtual void RemoveEntity(EntityId entity, bool bForceRemoveNow = false) = 0;        // [18] 0x90   sub_1802B8E4C — "RemoveEntity" string xref
    virtual uint32_t GetNumEntities() const = 0;                                         // [19] 0x98   sub_181DA067C — iterates slot table, counts non-null
    virtual IEntityIt* GetEntityIterator() = 0;                                          // [20] 0xA0   sub_1806D6D5C — creates CEntityItMap
    virtual void SendEventToAll(void* pEvent) = 0;                                       // [21] 0xA8   sub_181DA3518
    virtual void _vf22() = 0;                                                           // [22] 0xB0
    virtual void* GetBreakableManager() = 0;                                             // [23] 0xB8
    virtual void _vf24() = 0;                                                           // [24] 0xC0   QueryProximity (AABB query)
    virtual void _vf25() = 0;                                                           // [25] 0xC8
    virtual void _vf26() = 0;                                                           // [26] 0xD0   sub_1803765C4 — entity->vtable[0x50](entity, 2)
    virtual void AddEntityEventListener(EntityId id, int event, void* pListener) = 0;    // [27] 0xD8   sub_181D9D02C
    virtual void RemoveEntityEventListener(EntityId id, int event, void* pListener) = 0; // [28] 0xE0   sub_181DA2B24
    virtual void _vf29() = 0;                                                           // [29] 0xE8   PauseTimers
    virtual bool IsEntitySlotValid(EntityId id) const = 0;                               // [30] 0xF0
    virtual void GetMemoryStatistics(ICrySizer* pSizer) const = 0;                       // [31] 0xF8   "Entities", "Partition Grid" etc.
    virtual void _vf32() = 0;                                                           // [32] 0x100
    virtual void _vf33() = 0;                                                           // [33] 0x108
    virtual void _vf34() = 0;                                                           // [34] 0x110
    virtual void _vf35() = 0;                                                           // [35] 0x118  LoadLayer delegate
    virtual void _vf36() = 0;                                                           // [36] 0x120  SpawnLayer delegate
    virtual void _vf37() = 0;                                                           // [37] 0x128  UnloadLayer delegate
    virtual void LoadEntities1(void* pXmlNode, bool bIsLoadingLevelFile) = 0;            // [38] 0x130  "CEntitySystem::LoadEntities" string
    virtual void LoadEntities2(void* pXmlNode) = 0;                                     // [39] 0x138  "CEntitySystem::LoadEntities" + pool prep
    virtual void _vf40() = 0;                                                           // [40] 0x140  PreloadLevelEntities
    virtual void ReserveEntityId(EntityId id) = 0;                                       // [41] 0x148  sub_181DA09BC
    virtual void _vf42() = 0;                                                           // [42] 0x150
    virtual void _vf43() = 0;                                                           // [43] 0x158
    virtual void _vf44() = 0;                                                           // [44] 0x160
    virtual void _vf45() = 0;                                                           // [45] 0x168
    virtual EntityId FindEntityByGuid(const EntityGUID& guid) const = 0;                 // [46] 0x170  sub_1803786F8 — "FindEntityByGuid: %I64X" string
    virtual void _vf47() = 0;                                                           // [47] 0x178
    virtual EntityId GenerateEntityId(bool bStaticId = false) = 0;                       // [48] 0x180  sub_181D9FBAC
    virtual void* GetEntityPoolManager() = 0;                                            // [49] 0x188  returns *(this+0x300290)
    virtual void* GetEntityClassRegistry() = 0;                                          // [50] 0x190  returns *(this+0x300298)
    virtual void* GetLayerManager() = 0;                                                 // [51] 0x198  returns *(this+0x301AB0)
};

}  // namespace Offsets
