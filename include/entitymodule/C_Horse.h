#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include "CryEngine/CryCommon/CryThread.h"
#include "C_Animal.h"

// C_Horse - ridable horse actor.
// RTTI: .?AVC_Horse@entitymodule@wh@@
// Ctor: 0x181056468. Dtor: 0x1810575F4 / 0x1810583C4.
// Factory CActorCreator<C_Horse>::Create: 0x18215C1B4, alloc size 0xE38.

struct ICVar;
struct IAnimationPoseModifier;

namespace wh::entitymodule {

class C_Rider;

class C_Horse : public C_Animal {
public:
    struct S_UnalignedHandle {
        uint32_t m_lo;
        uint32_t m_hi;
    };

    struct S_MountedStateCallback {
        C_Horse* m_pHorse;      // +0x00
        uint8_t  m_state[0x30]; // +0x08 callback/list state, ctor 0x181056F50
    };

    struct S_BridleParams {
        int32_t  m_type;               // +0x00 init 13
        float    m_length;             // +0x04 Lua RopePhysics.length
        float    m_mass;               // +0x08 Lua RopePhysics.mass
        float    m_collisionDistance;  // +0x0C Lua RopePhysics.collDist
        uint32_t m_unk10;              // +0x10
        float    m_friction;           // +0x14 Lua RopePhysics.friction
        uint8_t  m_pad18[0x04];        // +0x18
        float    m_stiffness;          // +0x1C Lua RopePhysics.stiffness
        float    m_stiffnessAnim;      // +0x20 Lua RopePhysics.stiffnessAnim
        float    m_stiffnessDecayAnim; // +0x24 Lua RopePhysics.stiffnessDecayAnim
        float    m_dampingAnim;        // +0x28 Lua RopePhysics.dampingAnim
        int32_t  m_targetPoseActive;   // +0x2C Lua RopePhysics.targetPoseActive
        uint8_t  m_pad30[0x30];        // +0x30
        float    m_attachmentZone;     // +0x60 Lua RopePhysics.attachmentZone
        uint8_t  m_pad64[0x04];        // +0x64
        float    m_unprojectionLimit;  // +0x68 Lua RopePhysics.unprojLimit
        float    m_noCollisionDistance;// +0x6C Lua RopePhysics.noCollDist
        int32_t  m_maxIterations;      // +0x70 Lua RopePhysics.maxIters
        int32_t  m_segmentCount;       // +0x74 Lua RopePhysics.nSegments
        uint8_t  m_pad78[0x70];        // +0x78 physics payload, partly filled from attachment
        Vec3     m_attachmentOffset;   // +0xE8 Lua RopePhysics.attachmentOffset
        uint32_t m_unkF4;              // +0xF4
        int32_t  m_attachmentJointId;  // +0xF8 resolved attachment joint id
        uint32_t m_unkFC;              // +0xFC
    };

    struct S_RopeParams {
        int32_t  m_type;        // +0x00 init 10
        uint32_t m_unk04;       // +0x04
        float    m_maxTimeStep; // +0x08 Lua RopePhysics.maxTimeStep
        uint32_t m_unk0C;       // +0x0C
        float    m_damping;     // +0x10 Lua RopePhysics.damping
        uint8_t  m_pad14[0x38]; // +0x14
    };

    void Dtor(char flags) override;                         // 0x1810583C4
    void ProcessEvent(void* pEntityEvent) override;         // 0x180644DFC
    bool Init(Offsets::IGameObject* pGameObject) override;  // 0x181062A18
    void HandleEvent(void* pEvent) override;                // 0x181061E14

    uint16_t  m_riderAnimVariant;    // +0x958 rider animation variant
    uint8_t   _pad95A[2];            // +0x95A
    float     m_desiredGaitSpeed;    // +0x95C desired "horse_speed" anim input

    int32_t   m_unkId0;              // +0x960 -1 sentinel, paired with +0x964
    int32_t   m_unkId1;              // +0x964 -1 sentinel
    uint8_t   m_flag968;             // +0x968
    uint8_t   _pad969[3];            // +0x969
    int32_t   m_unk96C;              // +0x96C
    void*     m_unk970Ptr;           // +0x970
    void*     m_unkPtr978;           // +0x978
    bool      m_flag980;             // +0x980
    uint8_t   _pad981[3];            // +0x981
    S_UnalignedHandle m_unk984;      // +0x984 unaligned 64-bit handle in the binary
    uint16_t  m_unk98C;              // +0x98C
    uint8_t   _pad98E[2];            // +0x98E

    C_Rider*  m_pRider;              // +0x990 active rider link; C_Rider+0x10 is the rider actor

    // Refcounted handles released through sub_180222688; concrete pointee types are not recovered.
    void*     m_pSmart998;           // +0x998
    void*     m_pSmart9A0;           // +0x9A0
    void*     m_pSmart9A8;           // +0x9A8
    void*     m_pSmart9B0;           // +0x9B0
    float     m_unkFloat9B8;         // +0x9B8 scalar float, -1.0 init
    uint8_t   _pad9BC[4];            // +0x9BC
    void*     m_pSmart9C0;           // +0x9C0
    void*     m_pSmart9C8;           // +0x9C8 released on reset
    void*     m_unkBlock9D0;         // +0x9D0

    uint64_t  m_brainVarBinding0;    // +0x9D8 AI brain-variable binding handle
    uint64_t  m_brainVarBinding1;    // +0x9E0 AI brain-variable binding handle
    uint64_t  m_brainVarBinding2;    // +0x9E8 AI brain-variable binding handle

    float     m_lastPlayerCommandTime; // +0x9F0 GetCurrTime of last player command
    float     m_unkFloat9F4;         // +0x9F4 paired -1.0 sentinel
    uint32_t  m_unk9F8;              // +0x9F8
    int32_t   m_capturedAnimStateId; // +0x9FC event 0x24 captured animation state id

    S_MountedStateCallback m_mountedStateCallback; // +0xA00 registered callback state
    C_Horse*  m_pSelf;               // +0xA38

    int32_t   m_mountedActionCtxId;  // +0xA40 -1 sentinel
    uint32_t  m_animGraphParamId;    // +0xA44 "horse_speed" / "horse_stamina" anim param id
    int32_t   m_neckPhysPartId;      // +0xA48 physics part id of neck-mass geometry
    float     m_neckGeomLength;      // +0xA4C neck geometry length
    int32_t   m_watchedAnimId0;      // +0xA50 matched in HandleEvent event 2
    int32_t   m_watchedAnimId1;      // +0xA54 matched in HandleEvent event 2
    int32_t   m_collisionCapsulePartId; // +0xA58 physics part id of collision capsule
    Vec3      m_collisionCapsuleOffset; // +0xA5C capsule pos offset

    float     m_speed;               // +0xA68 -1.0 init
    float     m_appliedGaitSpeed;    // +0xA6C last value pushed to "horse_speed"

    CryCriticalSection m_lock;       // +0xA70

    std::shared_ptr<IAnimationPoseModifier> m_pBridlePoseModifier; // +0xA98
    ICVar*    m_pUseBridleParamsFromLua; // +0xAA8 "wh_horse_UseBridleParamsFromLua"

    S_BridleParams m_bridleParams;   // +0xAB0
    S_RopeParams   m_ropeParams;     // +0xBB0

    Vec3      m_reinSegmentPositions[2][0x17]; // +0xBFC two reins, 23 segments each

    int32_t   m_reinRopeSegmentParam; // +0xE24 lazily set to 6
    int32_t   m_rope1BoneId;         // +0xE28 bone id "Rope1 Seg015"
    int32_t   m_rope2BoneId;         // +0xE2C bone id "Rope2 Seg015"
    void*     m_unkPtrE30;           // +0xE30
};

static_assert(sizeof(C_Horse::S_UnalignedHandle) == 0x08);
static_assert(sizeof(C_Horse::S_MountedStateCallback) == 0x38);
static_assert(sizeof(C_Horse::S_BridleParams) == 0x100);
static_assert(sizeof(C_Horse::S_RopeParams) == 0x4C);
static_assert(sizeof(CryCriticalSection) == 0x28);
static_assert(sizeof(std::shared_ptr<IAnimationPoseModifier>) == 0x10);
static_assert(offsetof(C_Horse, m_desiredGaitSpeed) == 0x95C);
static_assert(offsetof(C_Horse, m_pRider) == 0x990);
static_assert(offsetof(C_Horse, m_mountedStateCallback) == 0xA00);
static_assert(offsetof(C_Horse, m_pBridlePoseModifier) == 0xA98);
static_assert(offsetof(C_Horse, m_bridleParams) == 0xAB0);
static_assert(offsetof(C_Horse, m_ropeParams) == 0xBB0);
static_assert(offsetof(C_Horse, m_reinSegmentPositions) == 0xBFC);
static_assert(sizeof(C_Horse) == 0xE38);

} // namespace wh::entitymodule
