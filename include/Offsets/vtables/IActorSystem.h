#pragma once
#include <cstdint>

typedef unsigned int EntityId;

// -----------------------------------------------
// IActorSystem -- Binary vtable order (interfuscated)
// -----------------------------------------------
// CActorSystem RTTI: .?AVCActorSystem@@ (TypeDescriptor at 0x182b3fe18)
// Constructor: sub_181822624
// Primary vtable (IActorSystem): COL at 0x182733100, vfuncs start at 0x182733108
// Secondary vtable at this+0x08: IEntityPoolListener (0x1827331A8)
// Tertiary vtable at this+0x10: IEntitySystemSink  (0x1827330C8)
// Abstract IActorSystem vtable: 0x1823a9850 (all _purecall except dtor)
// Total: 19 vfunc slots (0x00-0x90)
//
// CActorSystem layout (from constructor):
//   +0x00  vftable*       IActorSystem
//   +0x08  vftable*       IEntityPoolListener
//   +0x10  vftable*       IEntitySystemSink
//   +0x18  EntityId       m_originalDemoSpectator
//   +0x1C  EntityId       m_currentDemoSpectator
//   +0x20  EntityId       m_demoPlaybackMappedOriginalServerPlayer
//   +0x28  IGameFramework* m_pGameFramework
//   +0x30  IEntitySystem*  m_pEntitySystem (?)
//   +0x38  CHashMap       m_actorMap  (EntityId -> IActor*)
//   +0x78  CTreeSet       m_actorClasses (IEntityClass*)
//   +0xA0  CTreeMap       m_actorParams  (string -> IItemParamsNode*)
//   +0xB0  IItemParamsNode* m_scanPath (?)

struct IActor;
struct IActorIterator;
struct IItemParamsNode;
struct IEntityClass;

namespace Offsets {

class IActorSystem {
public:
    virtual void Dtor() = 0;                                                  // [0]  0x00  sub_181826B48 -- scalar deleting destructor -> sub_18182576C (cleanup)
    virtual void Reset() = 0;                                                 // [1]  0x08  sub_18184CE44 -- clears actors of deleted entities, frees internal buffers
    virtual void Reload() = 0;                                                // [2]  0x10  sub_18184B308 -- calls Reset() then Scan(m_scanFolder)
    virtual IActor* GetActor(EntityId entityId) = 0;                          // [3]  0x18  sub_18033C360 -- hashmap lookup by EntityId in m_actorMap
    virtual IActor* GetActorByChannelId(uint16_t channelId) = 0;              // [4]  0x20  sub_18183A308 -- iterates linked list, compares channelId via vtable+0x80
    virtual IActor* CreateActor(uint16_t channelId, const char* name,         // [5]  0x28  sub_18182C8FC -- entity spawn + actor extension creation
        const char* actorClass, const void* pos, const void* rot,
        const void* scale, EntityId id) = 0;
    virtual int GetActorCount() const = 0;                                    // [6]  0x30  sub_1806F85B0 -- returns *(this+0x48) [m_actorMap count]
    virtual void* CreateActorIterator() = 0;                                  // [7]  0x38  sub_18060130C -- creates CActorSystem::CActorIterator (vtable 0x182b3f8c0)
    virtual void SetDemoPlaybackMappedOriginalServerPlayer(EntityId id) = 0;  // [8]  0x40  sub_180708890 -- sets *(this+0x20)
    virtual EntityId GetDemoPlaybackMappedOriginalServerPlayer() const = 0;   // [9]  0x48  sub_1806F8600 -- returns *(this+0x20)
    virtual void SwitchDemoSpectator(EntityId id) = 0;                        // [10] 0x50  sub_181853384 -- delegates to sub_181853394, updates m_currentDemoSpectator
    virtual IActor* GetCurrentDemoSpectator() = 0;                            // [11] 0x58  sub_18183A89C -- looks up m_currentDemoSpectator (this+0x1C) in actor map
    virtual IActor* GetOriginalDemoSpectator() = 0;                           // [12] 0x60  sub_18183B6BC -- looks up m_originalDemoSpectator (this+0x18) in actor map
    virtual void AddActor(EntityId entityId, IActor* pActor) = 0;             // [13] 0x68  sub_1805FF45C -- inserts into m_actorMap hashmap at this+0x38
    virtual void RemoveActor(EntityId entityId) = 0;                          // [14] 0x70  sub_1806E92E8 -- erases from m_actorMap by EntityId
    virtual void Scan(const char* folderName) = 0;                            // [15] 0x78  sub_18184F03C -- scans folder for xml/binxml actor param files via CryPak
    virtual bool ScanXML(void* xmlNodeRef, const char* xmlFile) = 0;          // [16] 0x80  sub_18184F460 -- parses "ActorParams"/"EntityClassParams" XML, extracts "type"
    virtual const IItemParamsNode* GetActorParams(const char* actorClass) const = 0; // [17] 0x88  sub_18183A45C -- string-keyed lookup in m_actorParams tree at this+0xA0
    virtual bool IsActorClass(IEntityClass* pClass) const = 0;                // [18] 0x90  sub_1803A37D0 -- searches m_actorClasses tree at this+0x78
};

}  // namespace Offsets
