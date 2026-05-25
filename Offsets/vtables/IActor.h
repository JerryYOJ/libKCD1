#pragma once

#include <cstdint>

// -----------------------------------------------
// IActor — Binary vtable order (interfuscated)
// -----------------------------------------------
// Merged interface: IComponent + IGameObjectExtension + IActor
// C_Actor vtable: 0x1821B6610 (100 slots)
// C_Player vtable: 0x1826C3E30 (100 slots, 26 overridden)
// RTTI chain: IActor → IGameObjectExtension → IComponent → enable_shared_from_this<IComponent>
//
// This struct includes IComponent/IGameObjectExtension data members (+0x08..+0x3F)
// so that sizeof == 0x40, allowing MI with IGameObjectView (+0x40) and
// IGameObjectProfileManager (+0x48) to produce the correct binary layout.
//
// Stubs: NOP = 0x1802E39B0, ret_false = 0x180434C90, ret_0 = 0x1803953E0

struct IEntity;

namespace Offsets {

struct IGameObject;

// IGameObjectExtension — SDK base of IActor.
// In the SDK this has both virtuals and data; here the virtuals are on IActor
// (merged by interfuscator) so only data remains. Includes IComponent data.
struct IGameObjectExtension {
    uint64_t        m_weakPtr[2];              // +0x08  enable_shared_from_this<IComponent>
    void*           m_pDistributer;            // +0x18  IComponentEventDistributer*
    uint32_t        m_componentEntityId;       // +0x20
    uint32_t        m_componentFlags;          // +0x24  CCryFlags<uint>
    IGameObject*    m_pGameObject;             // +0x28
    uint32_t        m_entityId;                // +0x30  EntityId
    uint32_t        _pad34;                    // +0x34
    IEntity*        m_pEntity;                 // +0x38
};

struct IActor : IGameObjectExtension {
    // ======================== Virtual methods (binary slot order) ========================

    virtual void Dtor(char flags) = 0;                                 // [0]  0x000  0x180FE76B4
    virtual void ProcessEvent(void* pEntityEvent) = 0;                 // [1]  0x008  0x1803F03D8  SEntityEvent&
    virtual int  GetEventMask() = 0;                                   // [2]  0x010  0x18061B2AC
    virtual int  GetEventPriority(int eventID) = 0;                    // [3]  0x018  0x180224460
    virtual void _vf04() = 0;                                         // [4]  0x020  NOP
    virtual void _vf05() = 0;                                         // [5]  0x028  _purecall in C_Actor
    virtual bool Init(IGameObject* pGameObject) = 0;                   // [6]  0x030  0x1805FF71C
    virtual void PostInit(IGameObject* pGameObject) = 0;               // [7]  0x038  0x1805627F4
    virtual void _vf08() = 0;                                         // [8]  0x040  NOP
    virtual void _vf09() = 0;                                         // [9]  0x048  NOP
    virtual void InitClient(int channelId) = 0;                       // [10] 0x050  0x180FF3290
    virtual void PostReloadExtension(void*, void*) = 0;               // [11] 0x058  0x180FF2804
    virtual void GetEntityClassName(void* pSer) = 0;                  // [12] 0x060  0x180FEDBD0  writes "Actor"
    virtual void Release() = 0;                                        // [13] 0x068  0x1802C2A0C
    virtual void FullSerialize(void* pSer) = 0;                       // [14] 0x070  0x180FED23C  "health" at +0x14C
    virtual bool _vf15() = 0;                                         // [15] 0x078  ret false
    virtual int  _vf16() = 0;                                         // [16] 0x080  0x1806F83D0  returns -1
    virtual void PostSerialize() = 0;                                  // [17] 0x088  0x180FF28D0
    virtual void _vf18() = 0;                                         // [18] 0x090  NOP
    virtual void _vf19() = 0;                                         // [19] 0x098  0x180EDD1E8  sets output to 0
    virtual void Update(void* pCtx, int slot) = 0;                    // [20] 0x0A0  0x1803710AC
    virtual void HandleEvent(void* pEvent) = 0;                       // [21] 0x0A8  0x1805DC998
    virtual void _vf22() = 0;                                         // [22] 0x0B0  NOP
    virtual void _vf23() = 0;                                         // [23] 0x0B8  _purecall in C_Actor
    virtual void* GetAnimationGraphState() = 0;                       // [24] 0x0C0  0x1806FCF80
    virtual void PostUpdate(float dt) = 0;                             // [25] 0x0C8  0x180370D64
    virtual void _vf26() = 0;                                         // [26] 0x0D0  NOP
    virtual void SetHealth(float health) = 0;                          // [27] 0x0D8  0x1806931B0
    virtual float GetHealth() = 0;                                     // [28] 0x0E0  0x18036DBAC  reads via m_pSoul
    virtual int  GetHealthAsRoundedPercentage() = 0;                   // [29] 0x0E8  0x180FEDD44
    virtual void SetMaxHealth(float maxHealth) = 0;                    // [30] 0x0F0  0x18069319C
    virtual float GetMaxHealth() = 0;                                  // [31] 0x0F8  0x1806F9CE0  *(float*)(this+0x150)
    virtual int  GetArmor() = 0;                                       // [32] 0x100  ret 0
    virtual int  GetMaxArmor() = 0;                                    // [33] 0x108  ret 0
    virtual bool IsFallen() = 0;                                       // [34] 0x110  ret 0
    virtual bool IsDead() = 0;                                         // [35] 0x118  0x1803713F8  via ragdoll component
    virtual bool IsDeadByHealth() = 0;                                 // [36] 0x120  0x18036DB90  GetHealth() <= 0.0
    virtual int  _vf37() = 0;                                         // [37] 0x128  ret 0
    virtual void Fall(void* hitPos) = 0;                               // [38] 0x130  0x180FECB58
    virtual bool _vf39() = 0;                                         // [39] 0x138  ret false
    virtual bool IsFriendlyEntity(uint32_t entityId, bool bAI) = 0;   // [40] 0x140  0x1803DCEFC
    virtual bool IsThirdPerson() = 0;                                  // [41] 0x148  0x1804FC674
    virtual bool _vf42() = 0;                                         // [42] 0x150  0x1803F1CEC  alt faction check
    virtual void _vf43() = 0;                                         // [43] 0x158  NOP
    virtual void* GetCurrentItem(bool includeVehicle) = 0;            // [44] 0x160  0x180594450
    virtual void _vf45() = 0;                                         // [45] 0x168  NOP
    virtual void CreateScriptEvent(const char* e, float v, const char* s) = 0; // [46] 0x170  0x180401698
    virtual bool _vf47() = 0;                                         // [47] 0x178  ret false
    virtual void _vf48() = 0;                                         // [48] 0x180  NOP
    virtual void PlayAction(void* pParams) = 0;                       // [49] 0x188  0x180FF3750
    virtual void _vf50() = 0;                                         // [50] 0x190  NOP
    virtual void* _vf51() = 0;                                        // [51] 0x198  ret 0
    virtual void _vf52() = 0;                                         // [52] 0x1A0  NOP
    virtual void _vf53() = 0;                                         // [53] 0x1A8  NOP
    virtual void _vf54() = 0;                                         // [54] 0x1B0  NOP
    virtual void SetViewRotation(const void* pQuat) = 0;              // [55] 0x1B8  0x18030748C
    virtual void GetViewRotation(void* pOutQuat) = 0;                 // [56] 0x1C0  0x1803058E0
    virtual void SetViewInVehicle(const void* pQuat) = 0;             // [57] 0x1C8  0x18042AF34
    virtual float GetEyeHeight() = 0;                                 // [58] 0x1D0  0x1803058D0  *(float*)(stance+0x48)
    virtual bool AllowLandingBob() = 0;                                // [59] 0x1D8  0x1806F8140  ret true
    virtual void GetLocalEyePos(void* pOutVec3) = 0;                  // [60] 0x1E0  0x180616A78
    virtual void CameraShake(void* pParams) = 0;                      // [61] 0x1E8  0x180FED654
    virtual void _vf62() = 0;                                         // [62] 0x1F0  NOP
    virtual void* _vf63() = 0;                                        // [63] 0x1F8  ret 0
    virtual void _vf64() = 0;                                         // [64] 0x200  NOP
    virtual void* GetHolsteredItem() = 0;                              // [65] 0x208  ret 0
    virtual void* HolsterItem() = 0;                                   // [66] 0x210  ret 0
    virtual void _vf67() = 0;                                         // [67] 0x218  NOP
    virtual void* GetMovementController() = 0;                        // [68] 0x220  0x1806FCE90  *(this+0x170)
    virtual void* _vf69() = 0;                                        // [69] 0x228  ret 0
    virtual IEntity* GetLinkedEntity() = 0;                            // [70] 0x230  0x1805E2180
    virtual bool IsStillWaitingOnServerUseResponse() = 0;              // [71] 0x238  ret false
    virtual bool IsClient() = 0;                                       // [72] 0x240  0x180371060
    virtual void _vf73() = 0;                                         // [73] 0x248  NOP
    virtual bool IsMigrating() = 0;                                    // [74] 0x250  ret false
    virtual void SetMigrating(bool) = 0;                               // [75] 0x258  NOP
    virtual void SetFlyMode(uint8_t mode) = 0;                        // [76] 0x260  NOP (C_Player: writes +0xA74)
    virtual uint8_t GetFlyMode() = 0;                                  // [77] 0x268  ret 0 (C_Player: reads +0xA74)
    virtual bool IsPlayer() = 0;                                       // [78] 0x270  0x180370ED4  channelId != 0
    virtual bool IsPlayer2() = 0;                                      // [79] 0x278  0x180550CC4  thunk to [78]
    virtual bool _vf80() = 0;                                         // [80] 0x280  ret false
    virtual void _vf81() = 0;                                         // [81] 0x288  NOP
    virtual void InitLocalPlayer() = 0;                                // [82] 0x290  NOP (C_Player: Wwise "player_henry")
    virtual const char* GetActorClassName() = 0;                       // [83] 0x298  0x1806FCDF0  "C_Actor"
    virtual int  GetActorClass() = 0;                                  // [84] 0x2A0  ret 0 (C_Player: 0x11)
    virtual bool ShouldMuteWeaponSoundStimulus() = 0;                  // [85] 0x2A8  0x18033C3E4
    virtual void* GetAnimatedCharacter() = 0;                          // [86] 0x2B0  0x180FEDBB4
    virtual void _vf87() = 0;                                         // [87] 0x2B8  _purecall in C_Actor
    virtual void _vf88() = 0;                                         // [88] 0x2C0  NOP
    virtual void* GetInventory() = 0;                                  // [89] 0x2C8  0x1802244BC
    virtual void* GetAnimatedCharacterConst() = 0;                     // [90] 0x2D0  0x18033E984
    virtual void _vf91() = 0;                                         // [91] 0x2D8  NOP
    virtual void _vf92() = 0;                                         // [92] 0x2E0  NOP
    virtual void _vf93() = 0;                                         // [93] 0x2E8  NOP
    virtual bool Respawn() = 0;                                        // [94] 0x2F0  0x180FF3A64  "not implemented"
    virtual void ResetToSpawnLocation() = 0;                           // [95] 0x2F8  0x180FF3A50  "not implemented"
    virtual bool CanBreakGlass() = 0;                                  // [96] 0x300  ret false
    virtual bool MustBreakGlass() = 0;                                 // [97] 0x308  ret false
    virtual void _vf98() = 0;                                         // [98] 0x310  NOP
    virtual void _vf99() = 0;                                         // [99] 0x318  NOP

};
static_assert(sizeof(IActor) == 0x40);

} // namespace Offsets
