#pragma once

#include <cstdint>
#include "../Offsets/vtables/IActor.h"
#include "../Offsets/vtables/IGameObjectView.h"
#include "../Offsets/vtables/IGameObjectProfileManager.h"
#include "../framework/C_Signal.h"
#include "../rpgmodule/I_Soul.h"

// -----------------------------------------------
// C_Actor — Warhorse base actor class
// -----------------------------------------------
// RTTI:  .?AVC_Actor@entitymodule@wh@@
// Source: g:\workspace\kcdx_0109\code\game\modules\entitymodule\actor\actor.cpp
// Constructor: 0x1804F03B0  |  Destructor: 0x1804F0D0C
// Scalar deleting dtor: 0x180FE76B4 (frees 0x930)
//
// vtable (IActor primary):         0x1821B6610  (+0x00)
// vtable (IGameObjectView):       0x1821B6DA8  (+0x40)
// vtable (IGameObjectProfileMgr): 0x1821B6DC8  (+0x48)
//
// ClassInformer MI chain:
//   C_Actor, CGameObjectExtensionHelper<C_Actor,IActor,64>,
//   IActor, IGameObjectExtension, IComponent,
//   enable_shared_from_this<IComponent>,
//   IGameObjectView, IGameObjectProfileManager
//
// Derived: C_Human(0x9F0), C_Animal(0x958)
// Total size: 0x930

struct IScriptTable;
struct IMovementController;
#ifndef WH_VEC3_DEFINED
#define WH_VEC3_DEFINED
struct Vec3 { float x, y, z; };
#endif

namespace wh::animationmodule {
    class C_AnimatedCharacter;
    class C_AnimatedHuman;
}
namespace wh::combatmodule {
    class I_CombatActor;
    class C_CombatActor;
}

namespace wh::entitymodule {

class C_ActorModel;
class C_RagdollManager;
class C_ActionActor;
class C_ClothingAttachmentOwnerActor;
class C_Item;

class C_Actor : public Offsets::IActor,                    // +0x00  (0x40 bytes)
                public Offsets::IGameObjectView,            // +0x40  (0x08 bytes)
                public Offsets::IGameObjectProfileManager   // +0x48  (0x08 bytes)
{
public:
    // ---- Non-virtual methods ----

    // sub_1803A107C: returns m_pCombatActor, creating it if null (lazy init).
    wh::combatmodule::C_CombatActor* GetOrCreateCombatActor();

    // ===================================================================
    // Data members (+0x50 onwards, after MI base classes)
    // Base class data at +0x08..+0x3F (IActor: weak_ptr, distributer,
    //   gameObject, entityId, entity) — see Offsets::IActor
    // ===================================================================

    // CStateMachine<C_Actor> (+0x50, size 0x68)
    uint8_t                 m_stateMachineData[0x68];                       // +0x50

    // Signals
    wh::shared::C_Signal<wh::combatmodule::I_CombatActor&> m_signalCombatChanged1; // +0xB8
    wh::shared::C_Signal<wh::combatmodule::I_CombatActor&> m_signalCombatChanged2; // +0xE8
    wh::shared::C_Signal<C_Item*>                           m_signalItemChanged;    // +0x118

    // Basic stats
    uint8_t                 m_specMode;                         // +0x148
    uint8_t                 _pad149[3];                         // +0x149
    float                   m_health;                           // +0x14C  (init 100.0, serialized)
    float                   m_maxHealth;                        // +0x150  (init 100.0)
    float                   m_gravity;                          // +0x154  (init 9.81)
    uint8_t                 _pad158[8];                         // +0x158

    // Sub-objects
    IScriptTable*           m_pActorStats;                      // +0x160  "actorStats" entity property
    wh::animationmodule::C_AnimatedCharacter* m_pAnimatedCharacter; // +0x168  (size 0xA10)
    IMovementController*    m_pMovementController;              // +0x170
    C_RagdollManager*       m_pRagdollManager;                  // +0x178  (size 0x148)
    void*                   m_pCritSection;                     // +0x180
    void*                   m_pSmartPtr188;                     // +0x188
    void*                   m_pSmartPtr190;                     // +0x190
    void*                   m_pSmartPtr198;                     // +0x198
    wh::combatmodule::C_CombatActor* m_pCombatActor;             // +0x1A0  lazy-created by sub_1803A107C, VERIFIED
    C_ActionActor*          m_pActionActor;                     // +0x1A8  (size 0xF0)

    // Look/Aim IK (+0x1B0, size 0x110, "Bip01 Head")
    uint8_t                 m_lookAimIK[0x110];                 // +0x1B0

    // Stance parameters (+0x2C0, size 0x38)
    uint8_t                 m_stanceParams[0x38];               // +0x2C0

    wh::animationmodule::C_AnimatedHuman* m_pAnimatedModel;    // +0x2F8
    uint8_t                 _pad300[4];                         // +0x300

    float                   m_ragdollWakeupTimer;               // +0x304
    uint8_t                 _pad308[8];                         // +0x308
    float                   m_regenTimer;                       // +0x310
    uint8_t                 m_stateBlock[0x94];                 // +0x314
    bool                    m_flagA8;                           // +0x3A8
    uint8_t                 _pad3A9[7];                         // +0x3A9

    void*                   m_pSmartPtr3B0;                     // +0x3B0
    void*                   m_pSmartPtr3B8;                     // +0x3B8
    void*                   m_pSmartPtr3C0;                     // +0x3C0
    void*                   m_pString3C8;                       // +0x3C8  CryStringT
    void*                   m_pString3D0;                       // +0x3D0  CryStringT

    float                   m_turnSpeed;                        // +0x3D8
    float                   m_maxTurnSpeed;                     // +0x3DC
    float                   m_viewDist1;                        // +0x3E0  (init 11.0)
    float                   m_viewDist2;                        // +0x3E4  (init 11.0)
    uint8_t                 _pad3E8[0x20];                      // +0x3E8

    uint8_t                 m_damageZones[0xB8];                // +0x408

    void*                   m_pPhysicsState;                    // +0x4C0  (alloc 0x98)
    uint8_t                 _pad4C8[0x14];                      // +0x4C8
    uint32_t                m_timer4DC;                         // +0x4DC
    uint32_t                m_unk4E0;                           // +0x4E0
    uint32_t                m_unk4E4;                           // +0x4E4
    C_Actor*                m_pSelf;                            // +0x4E8
    bool                    m_flag4F0;                          // +0x4F0
    uint8_t                 _pad4F1[3];                         // +0x4F1
    uint32_t                m_linkedEntityId;                   // +0x4F4  EntityId
    uint8_t                 _pad4F8[8];                         // +0x4F8

    uint8_t                 m_physIgnoreEntity[0x20];           // +0x500
    uint8_t                 m_physIgnoreAdditional[0x20];       // +0x520

    void*                   m_pAIController;                    // +0x540
    void*                   m_pAIHelper;                        // +0x548
    void*                   m_pHitTimingHelper;                 // +0x550

    int32_t                 m_foleyAudioId;                     // +0x558
    int32_t                 m_footstepAudioId;                  // +0x55C
    int32_t                 m_footstepImpulseAudioId;           // +0x560

    bool                    m_bIsAIControlled;                  // +0x564
    bool                    m_flag565;                          // +0x565
    uint8_t                 _pad566[2];                         // +0x566

    float                   m_perceptionMinAngle;               // +0x568  (5°)
    float                   m_perceptionConeHalfAngle;          // +0x56C  (30°)
    float                   m_perceptionRangeScale;             // +0x570  (init 1.0)
    // +0x574/+0x580: two adjacent Vec3s read by C_AIPuppet (xgenaimodule) slots 15/14
    // (sub_18066DFF8 reads +0x574, sub_18023B290 reads +0x580). Names/semantics INFERRED
    // from the puppet's use; the no-actor fallbacks query the physics proxy (GetStatus).
    float                   m_physBodyPos[3];                   // +0x574  Vec3 [INFERRED] (C_AIPuppet GetPhysWorldPos; fallback 0,0,0)
    float                   m_physVelocity[3];                  // +0x580  Vec3 [INFERRED] (C_AIPuppet GetVelocity; fallback phys GetStatus)
    uint8_t                 _pad58C[0x38];                      // +0x58C  (remainder of the former _pad574[0x50] block)

    float                   m_moveSpeedModifier;                // +0x5C4  (init 1.0)
    uint8_t                 _pad5C8[8];                         // +0x5C8
    float                   m_maxSpeed;                         // +0x5D0  (init 80.0)
    float                   m_unk5D4;                           // +0x5D4  (init -1.0)
    uint8_t                 _pad5D8[8];                         // +0x5D8
    int32_t                 m_unk5E0;                           // +0x5E0
    int32_t                 m_invalidId5E4;                     // +0x5E4  (0xFFFFFFFF)

    uint8_t                 _pad5E8[0x20];                      // +0x5E8

    float                   m_aabbMinX;                         // +0x608  (-1000000.0)
    uint8_t                 _pad60C[4];                         // +0x60C
    float                   m_aabbMinZ;                         // +0x610  (-1000000.0)
    float                   m_aabbMaxX;                         // +0x614  (1000000.0)
    float                   m_aabbMinY;                         // +0x618  (-1000.0)
    uint8_t                 _pad61C[0x14];                      // +0x61C

    uint8_t                 _pad630[0x18];                      // +0x630
    void*                   m_pUnk648;                          // +0x648
    wh::rpgmodule::I_Soul*  m_pSoul;                            // +0x650  set by AttachSoul (0x18030E184)

    void*                   m_fragmentName;                     // +0x658  CryStringT, "m_FragmentID"

    void*                   m_pSmartPtr660;                     // +0x660
    C_ClothingAttachmentOwnerActor* m_pClothingOwner;           // +0x668
    void*                   m_pNavigation;                      // +0x670
    void*                   m_pSmartPtr678;                     // +0x678
    void*                   m_pBodyData;                        // +0x680  I_BodyData*
    bool                    m_flag688;                          // +0x688
    uint8_t                 _pad689[7];                         // +0x689

    void*                   m_pString690;                       // +0x690
    uint64_t                m_unk698;                           // +0x698
    uint32_t                m_unk6A0;                           // +0x6A0
    uint8_t                 _pad6A4[4];                         // +0x6A4
    C_Actor*                m_pSelf2;                           // +0x6A8
    void*                   m_pUnk6B0;                          // +0x6B0

    void*                   m_pUnk6B8;                          // +0x6B8
    void*                   m_pLinkedListNode;                  // +0x6C0
    uint64_t                m_unk6C8;                           // +0x6C8
    uint32_t                m_unk6D0;                           // +0x6D0
    uint8_t                 m_movementFlags;                    // +0x6D4
    uint8_t                 _pad6D5[0x23];                      // +0x6D5

    int32_t                 m_archetypeAudioId;                 // +0x6F8
    uint8_t                 _pad6FC[0x0C];                      // +0x6FC
    void*                   m_pArchetypeAudioData;              // +0x708
    void*                   m_pAIPath;                          // +0x710
    uint8_t                 _pad718[0x10];                      // +0x718

    // Bone/slot system (+0x728, 0x1D0 bytes)
    C_Actor*                m_pBoneSystemOwner;                 // +0x728
    int32_t                 m_boneStanceId;                     // +0x730
    int32_t                 m_boneSubState;                     // +0x734
    uint8_t                 m_boneSlotEntries[0x168];           // +0x738
    bool                    m_boneSystemEnabled;                // +0x8A0
    uint8_t                 _pad8A1[0x57];                      // +0x8A1

    Vec3                    m_lastNavMeshPos;                   // +0x8F8  serialized as "LastNavMeshPos"
    uint32_t                _pad904;                            // +0x904

    C_ActorModel*           m_pActorModel;                      // +0x908  (size 0x540)
    uint64_t                m_unk910;                           // +0x910
    uint32_t                m_unk918;                           // +0x918
    float                   m_modelScale;                       // +0x91C  (init 1.0)
    void*                   m_pArchetypeData;                   // +0x920
    uint64_t                m_unk928;                           // +0x928
};
static_assert(sizeof(C_Actor) == 0x930);

} // namespace wh::entitymodule
