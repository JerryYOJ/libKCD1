#pragma once

#include <cstdint>
#include <vector>
#include "C_Human.h"
#include "I_ExactPosHelperListener.h"
#include "I_EquipmentManagerListener.h"
#include "I_ItemAttachmentListener.h"
#include "../Offsets/vtables/IGameFrameworkListener.h"

// -----------------------------------------------
// C_Player — Player actor class
// -----------------------------------------------
// RTTI: .?AVC_Player@entitymodule@wh@@
// Constructor: 0x181097454  |  Factory: 0x182156CFC (allocs 0xC70)
// Init:        0x1810A18B8  |  Destructor: 0x181098768 / 0x181099190
//
// vtable (primary):                  0x1826C3E30  (+0x00)
// vtable (IGameObjectView):         0x1826C3E10  (+0x40)
// vtable (IGameObjectProfileMgr):   0x1826C3DA0  (+0x48)
// vtable (I_ExactPosHelperListener): 0x1826C3D90  (+0x9F0)
// vtable (I_EquipmentManagerListener):0x1826C3D70 (+0x9F8)
// vtable (I_ItemAttachmentListener): 0x1826C3D50  (+0xA00)
// vtable (IGameFrameworkListener):   0x1826C3DC0  (+0xA08)
//
// Total size: 0xC70
//
// Henry vs Theresa: InitLocalPlayer checks mode at +0x650 to select
// Wwise switch "player_henry" or "player_theresa".
//
// C_Soul access: C_Actor+0x650 holds a direct I_Soul* (set by AttachSoul at 0x18030E184).
// Alternative WUID-based lookup also exists:
//   RPG Module singleton: qword_1835AC728
//   C_SoulList: RPGModule + 0x548
//   sub_180284B04(soulList + 0x48, &wuid) → C_Soul*
//
// ============================================================================
// OVERRIDDEN VTABLE SLOTS (26 of 100):
//
// [0]  0x181099190  ~C_Player (frees 0xC70)
// [1]  0x18065DB40  ProcessEvent (0x0/0xD/0xF/0x27/0x29/0x2A/0x38)
// [5]  0x1810A0EBC  Serialize — 0xC70 + optional 0x340 from m_pPlayerInput
// [6]  0x1810A18B8  Init — allocates sub-objects, registers "Player"
// [11] 0x1810A5464  PostInit — checks horse mount state
// [12] 0x1810A0DF8  GetEntityClassName — "Player"
// [13] 0x1810A78FC  Release — unregisters env listener
// [14] 0x18109D340  Serialize — horseInventoryEnabled, fastTravelEnabled, m_CanCallHorse
// [20] 0x180595610  Update — manages sub-objects, decrements timers
// [21] 0x1806E8B54  HandleEvent — horse/inventory/death
// [25] 0x18057CCC8  UpdateView — player camera
// [49] 0x1804A7648  SetProfile — triggers appearance reload
// [60] 0x18053DA94  GetLocalEyePos — from anim state machine
// [76] 0x1810A8FA4  SetFlyMode — writes m_stanceControlMode, toggles physics
// [77] 0x18021C580  GetFlyMode — returns m_stanceControlMode
// [82] 0x1810A1CF0  InitLocalPlayer — Wwise "player_henry"/"player_theresa"
// [83] 0x1806FE130  GetActorClassName — "C_Player"
// [84] 0x1806FE110  GetActorClass — 0x11
// ============================================================================

namespace wh::entitymodule {

class C_PlayerInteractor;
class C_LevelBarrierInteractor;
class C_PlayerInput;
class C_PlayerExactPosHelper;
class C_PlayerMaterialEffects;
class C_RigidOnlyCollision;
class C_FrontCollision;
class C_DogInteractionManager;

class C_Player : public C_Human,
                 public I_ExactPosHelperListener,       // +0x9F0
                 public I_EquipmentManagerListener,     // +0x9F8
                 public I_ItemAttachmentListener,       // +0xA00
                 public Offsets::IGameFrameworkListener  // +0xA08
{
public:
    // ===================================================================
    // IActor overrides
    // ===================================================================
    const char* GetActorClassName() override;             // [83] returns "C_Player"
    int         GetActorClass() override;               // [84] returns 0x11
    void        InitLocalPlayer() override;             // [82] sets Wwise "player_henry"/"player_theresa"

    // ===================================================================
    // Data members — C_Player specific (+0xA10 to +0xC6F)
    // ===================================================================

    std::vector<void*>      m_listeners;                // +0xA10  visibility/event listener array

    uint64_t                m_unkA28;                   // +0xA28

    // Flags
    uint8_t                 m_playerFlags;              // +0xA30  bits: 0x10=horseInventoryEnabled, 0x20=fastTravelEnabled
    bool                    m_bCanCallHorse;            // +0xA31  (init true, serialized)
    uint8_t                 _padA32[2];                 // +0xA32
    uint32_t                m_unkA34;                   // +0xA34

    // Timers
    float                   m_unkA38;                   // +0xA38
    float                   m_timerA3C;                 // +0xA3C
    float                   m_timerA40;                 // +0xA40
    uint32_t                m_unkA44;                   // +0xA44
    uint32_t                m_unkA48;                   // +0xA48
    uint32_t                m_unkA4C;                   // +0xA4C

    uint64_t                m_invalidEntitySentinel;    // +0xA50  (init INT64_MIN)

    // Interactors
    C_PlayerInteractor*     m_pInteractor;              // +0xA58  (size 0x368)
    C_LevelBarrierInteractor* m_pLevelBarrierInteractor; // +0xA60  (size 0x28)

    uint32_t                m_unkA68;                   // +0xA68
    uint8_t                 m_unkA6C;                   // +0xA6C
    uint8_t                 _padA6D[3];                 // +0xA6D
    uint32_t                m_unkA70;                   // +0xA70
    uint8_t                 m_stanceControlMode;        // +0xA74  (0, 1, or 2)
    uint8_t                 _padA75[3];                 // +0xA75
    uint64_t                m_unkA78;                   // +0xA78
    uint32_t                m_unkA80;                   // +0xA80
    uint8_t                 m_unkA84;                   // +0xA84
    uint8_t                 _padA85[3];                 // +0xA85
    uint32_t                m_unkA88;                   // +0xA88
    uint8_t                 _padA8C[4];                 // +0xA8C

    // Player input (allocated in Init, size 0x340)
    C_PlayerInput*          m_pPlayerInput;             // +0xA90

    void*                   m_pEntityProxy;             // +0xA98
    uint8_t                 m_embeddedProxy[0x38];      // +0xAA0  embedded proxy with release semantics

    uint64_t                m_unkAD8;                   // +0xAD8
    uint32_t                m_unkAE0;                   // +0xAE0
    uint8_t                 _padAE4[4];                 // +0xAE4

    // Exact positioning (allocated in Init, size 0x48)
    C_PlayerExactPosHelper* m_pExactPosHelper;          // +0xAE8
    void*                   m_pRefCountedAF0;           // +0xAF0

    // Camera/aiming sub-struct (+0xAF8, 0x78 bytes embedded)
    void*                   m_pCameraStr1;              // +0xAF8  CryStringT
    void*                   m_pCameraStr2;              // +0xB00  CryStringT
    uint32_t                m_cameraUnk08;              // +0xB08
    uint8_t                 _padB0C[4];                 // +0xB0C
    uint64_t                m_cameraUnk10;              // +0xB10
    uint32_t                m_cameraUnk18;              // +0xB18
    uint16_t                m_cameraWord1C;             // +0xB1C  (init 1)
    uint8_t                 _padB1E[2];                 // +0xB1E
    uint32_t                m_cameraUnk20;              // +0xB20
    uint8_t                 m_cameraByte24;             // +0xB24
    uint8_t                 _padB25[3];                 // +0xB25
    uint64_t                m_cameraUnk28;              // +0xB28
    uint64_t                m_cameraUnk30;              // +0xB30
    uint64_t                m_cameraUnk38;              // +0xB38
    float                   m_cameraFOV;                // +0xB40  (init 1.0)
    uint32_t                m_cameraUnk44;              // +0xB44
    float                   m_cameraCos45;              // +0xB48  cos(pi/4)
    float                   m_cameraSin45;              // +0xB4C  sin(pi/4)
    uint64_t                m_cameraUnk50;              // +0xB50
    uint64_t                m_cameraUnk58;              // +0xB58
    uint64_t                m_cameraUnk60;              // +0xB60
    uint64_t                m_cameraUnk68;              // +0xB68

    // Sub-object (allocated in Init, 0x50 bytes, has player backptr)
    void*                   m_pSubObjB70;               // +0xB70

    // C_PlayerMaterialEffects (embedded, ~0xC0 bytes)
    // Inherits C_ActorMaterialEffects, backptr to player at +0xB0
    uint8_t                 m_playerMaterialEffects[0xC0]; // +0xB78

    // Collision
    C_RigidOnlyCollision*   m_pRigidOnlyCollision;      // +0xC38  (size 0x30)
    C_FrontCollision*       m_pFrontCollision;           // +0xC40  (size 0x28, registers with pInput)

    // Action map
    void*                   m_pActionMapManager;        // +0xC48
    uint32_t                m_actionMapFilterId;        // +0xC50
    uint8_t                 _padC54[4];                 // +0xC54

    uint64_t                m_invalidEntityId;          // +0xC58  (0xFFFFFFFFFFFFFFFF)
    uint8_t                 m_unkC60;                   // +0xC60
    uint8_t                 _padC61[7];                 // +0xC61

    // Dog interaction
    C_DogInteractionManager* m_pDogInteractionMgr;      // +0xC68  (size 0x28)
};
static_assert(sizeof(C_Player) == 0xC70);

} // namespace wh::entitymodule
