#pragma once
#include <cstdint>

typedef unsigned int EntityId;

// -----------------------------------------------
// IGameFramework — Binary vtable order (interfuscated)
// -----------------------------------------------
// CCryAction vtable at 0x182734E30 (COL at 0x182734E28)
// RTTI: .?AVCCryAction@@
// Singleton: qword_183785D88 (WHGame+0x3785D88)
//
// Subsystem member layout in CCryAction (from Init constructor):
//   +0x500: CLevelSystem          +0x508: CActorSystem
//   +0x510: CItemSystem           +0x518: CVehicleSystem
//   +0x520: CSharedParamsManager  +0x528: CActionMapManager
//   +0x530: CViewSystem           +0x540: CGameRulesSystem
//   +0x550: CGameObjectSystem     +0x558: CUIDraw
//   +0x570: CMannequinInterface   +0x578: CMaterialEffects
//   +0x588: CPlayerProfileManager +0x598: CSubtitleManager
//   +0x5A0: CGameTokenSystem      +0x5A8: CEffectSystem
//   +0x5E0: CCustomActionManager  +0x5E8: CCustomEventManager
//   +0x5F8: CGameStatistics       +0x600: CCooperativeAnimationManager
//   +0x608: CGameSessionHandler (lazy-init)

struct IActor;
struct IEntity;
struct IActorSystem;

// Action event dispatched to IGameFrameworkListeners via OnActionEvent.
// Types observed from CCryAction::SaveGame (sub_181893C1C) and LoadGame (sub_181886648).
struct SActionEvent {
    int         m_event;        // +0x00  event type
    uint32_t    m_value;        // +0x04  context-dependent (e.g. save reason)
    const char* m_description;  // +0x08  optional string (e.g. checkpoint name)

    enum : int {
        eAE_PreSave  = 0xA,    // before save is written
        eAE_PostSave = 0xB,    // after save is written
        eAE_PreLoad  = 0xC,    // before save is loaded
        eAE_PostLoad = 0xD,    // after save is loaded
    };
};

namespace Offsets {

struct IGameFramework {
    virtual void _vf0() = 0;                                            // [0]  0x00   RegisterExtension
    virtual void _vf1() = 0;                                            // [1]  0x08
    virtual void _vf2() = 0;                                            // [2]  0x10
    virtual void _vf3() = 0;                                            // [3]  0x18
    virtual void _vf4() = 0;                                            // [4]  0x20
    virtual void _vf5() = 0;                                            // [5]  0x28
    virtual void Dtor() = 0;                                             // [6]  0x30
    virtual void Init() = 0;                                             // [7]  0x38   sub_18187F730 (8855 bytes)
    virtual void PostInit() = 0;                                         // [8]  0x40   handles AISystem re-init
    virtual void CompleteInit() = 0;                                     // [9]  0x48   registers extensions, loads scripts, calls OnInit
    virtual void Shutdown() = 0;                                         // [10] 0x50   destroys all subsystems
    virtual void PreUpdate() = 0;                                        // [11] 0x58   game entity update
    virtual void PostUpdate() = 0;                                       // [12] 0x60   "CCryAction::PostUpdate" string
    virtual void Reset() = 0;                                            // [13] 0x68
    virtual void PauseGame(bool bPause, EntityId playerId = 0, bool bForce = false) = 0; // [14] 0x70
    virtual bool IsGamePaused() const = 0;                               // [15] 0x78
    virtual bool IsInLevelLoad() const = 0;                              // [16] 0x80
    virtual bool IsLoadingSaveGame() const = 0;                          // [17] 0x88
    virtual void SetLoadingSaveGame(bool bLoading) = 0;                  // [18] 0x90
    virtual void* GetISystem() = 0;                                      // [19] 0x98   returns CCryAction+0x38
    virtual void* _vf20() = 0;                                          // [20] 0xA0   returns CCryAction+0x5D8
    virtual void* GetIUIDraw() = 0;                                      // [21] 0xA8   returns CCryAction+0x558
    virtual void* GetIMannequin() = 0;                                   // [22] 0xB0   returns CCryAction+0x570 (CMannequinInterface)
    virtual void* GetIGameObjectSystem() = 0;                            // [23] 0xB8   returns CCryAction+0x550 (CGameObjectSystem)
    virtual void* GetILevelSystem() = 0;                                 // [24] 0xC0   returns CCryAction+0x500 (CLevelSystem)
    virtual IActorSystem* GetIActorSystem() = 0;                         // [25] 0xC8   returns CCryAction+0x508 (confirmed)
    virtual void* GetIItemSystem() = 0;                                  // [26] 0xD0   returns CItemSystem inner ptr (+0x510+8)
    virtual void* GetITimeDemoRecorder() = 0;                            // [27] 0xD8   returns global qword_183785D98+8
    virtual void* GetIActionMapManager() = 0;                            // [28] 0xE0   returns CCryAction+0x528 (CActionMapManager)
    virtual void* GetIViewSystem() = 0;                                  // [29] 0xE8   returns CCryAction+0x530 (CViewSystem)
    virtual void _vf30() = 0;                                           // [30] 0xF0
    virtual void* GetIVehicleSystem() = 0;                               // [31] 0xF8   returns CCryAction+0x518 (CVehicleSystem)
    virtual void* GetIGameRulesSystem() = 0;                             // [32] 0x100  returns CCryAction+0x540 (CGameRulesSystem)
    virtual void _vf33() = 0;                                           // [33] 0x108  returns CCryAction+0x548
    virtual void* GetIGameTokenSystem() = 0;                             // [34] 0x110  returns CCryAction+0x5A0 (CGameTokenSystem)
    virtual void* GetIEffectSystem() = 0;                                // [35] 0x118  returns CCryAction+0x5A8 (CEffectSystem)
    virtual void* GetIMaterialEffects() = 0;                             // [36] 0x120  returns CCryAction+0x578 (CMaterialEffects)
    virtual void _vf37() = 0;                                           // [37] 0x128  returns CCryAction+0x590
    virtual void* GetIPlayerProfileManager() = 0;                        // [38] 0x130  returns CCryAction+0x588
    virtual void* GetISubtitleManager() = 0;                             // [39] 0x138  returns CCryAction+0x598
    virtual void _vf40() = 0;                                           // [40] 0x140
    virtual void* GetIGameStatistics() = 0;                              // [41] 0x148  returns CCryAction+0x5F8 (CGameStatistics)
    virtual void _vf42() = 0;                                           // [42] 0x150
    virtual void* GetICooperativeAnimationManager() = 0;                 // [43] 0x158  returns CCryAction+0x600
    virtual void _vf44() = 0;                                           // [44] 0x160
    virtual void _vf45() = 0;                                           // [45] 0x168  returns CCryAction+0x5D0
    virtual void* GetICustomActionManager() = 0;                         // [46] 0x170  returns CCryAction+0x5E0
    virtual void* GetICustomEventManager() = 0;                          // [47] 0x178  returns CCryAction+0x5E8
    virtual void* GetIGameSessionHandler() = 0;                          // [48] 0x180  lazy-init at CCryAction+0x608
    virtual void* GetISharedParamsManager() = 0;                         // [49] 0x188  returns CCryAction+0x520
    virtual void _vf50() = 0;                                           // [50] 0x190
    virtual void _vf51() = 0;                                           // [51] 0x198
    virtual void _vf52() = 0;                                           // [52] 0x1A0
    virtual void _vf53() = 0;                                           // [53] 0x1A8
    virtual void _vf54() = 0;                                           // [54] 0x1B0
    virtual void _vf55() = 0;                                           // [55] 0x1B8
    virtual void _vf56() = 0;                                           // [56] 0x1C0
    virtual void _vf57() = 0;                                           // [57] 0x1C8
    virtual void _vf58() = 0;                                           // [58] 0x1D0
    virtual void _vf59() = 0;                                           // [59] 0x1D8  NOT SaveGame — reset/cleanup func (restores entity state, clears containers)
    virtual void _vf60() = 0;                                           // [60] 0x1E0
    virtual void _vf61() = 0;                                           // [61] 0x1E8
    virtual void _vf62() = 0;                                           // [62] 0x1F0
    virtual void _vf63() = 0;                                           // [63] 0x1F8
    virtual void _vf64() = 0;                                           // [64] 0x200
    virtual void _vf65() = 0;                                           // [65] 0x208
    virtual void _vf66() = 0;                                           // [66] 0x210
    virtual void _vf67() = 0;                                           // [67] 0x218
    virtual IActor* GetClientActor() const = 0;                          // [68] 0x220  sub_180208DDC (confirmed)
    virtual EntityId GetClientActorId() const = 0;                       // [69] 0x228  sub_180306470 (confirmed)
    virtual IEntity* GetClientEntity() const = 0;                        // [70] 0x230  calls [69] then IEntitySystem::GetEntity
    virtual EntityId GetClientEntityId() const = 0;                      // [71] 0x238  reads channel chain → entity ID
    virtual void* GetClientChannel() const = 0;                          // [72] 0x240  returns ptr from channel chain
    virtual void _vf73() = 0;                                           // [73] 0x248
    virtual void _vf74() = 0;                                           // [74] 0x250
    virtual void _vf75() = 0;                                           // [75] 0x258
    virtual void _vf76() = 0;                                           // [76] 0x260
    virtual void* GetClientChannelById(int channelId) const = 0;         // [77] 0x268  returns *(NetworkChannel+0x8)
    virtual void _vf78() = 0;                                           // [78] 0x270  NOT GetGameObject(EntityId) — ignores this+id, gets client game object via gEnv.pEntitySystem
    virtual void _vf79() = 0;                                           // [79]  0x278
    virtual void _vf80() = 0;                                           // [80]  0x280
    virtual void _vf81() = 0;                                           // [81]  0x288
    virtual void _vf82() = 0;                                           // [82]  0x290
    virtual void _vf83() = 0;                                           // [83]  0x298
    virtual void _vf84() = 0;                                           // [84]  0x2A0
    virtual void _vf85() = 0;                                           // [85]  0x2A8
    virtual void _vf86() = 0;                                           // [86]  0x2B0
    virtual void _vf87() = 0;                                           // [87]  0x2B8
    virtual void _vf88() = 0;                                           // [88]  0x2C0
    virtual void _vf89() = 0;                                           // [89]  0x2C8
    virtual void _vf90() = 0;                                           // [90]  0x2D0
    virtual void _vf91() = 0;                                           // [91]  0x2D8
    virtual void _vf92() = 0;                                           // [92]  0x2E0
    virtual void _vf93() = 0;                                           // [93]  0x2E8
    virtual void _vf94() = 0;                                           // [94]  0x2F0
    virtual void _vf95() = 0;                                           // [95]  0x2F8
    virtual void _vf96() = 0;                                           // [96]  0x300
    virtual void _vf97() = 0;                                           // [97]  0x308
    virtual void _vf98() = 0;                                           // [98]  0x310
    virtual void _vf99() = 0;                                           // [99]  0x318
    virtual void _vf100() = 0;                                          // [100] 0x320
    virtual void _vf101() = 0;                                          // [101] 0x328
    virtual void _vf102() = 0;                                          // [102] 0x330
    virtual void _vf103() = 0;                                          // [103] 0x338
    virtual void _vf104() = 0;                                          // [104] 0x340
    virtual void _vf105() = 0;                                          // [105] 0x348
    virtual void _vf106() = 0;                                          // [106] 0x350
    virtual void _vf107() = 0;                                          // [107] 0x358
    virtual void _vf108() = 0;                                          // [108] 0x360
    virtual void _vf109() = 0;                                          // [109] 0x368
    virtual void _vf110() = 0;                                          // [110] 0x370
    virtual void _vf111() = 0;                                          // [111] 0x378
    virtual void _vf112() = 0;                                          // [112] 0x380
    virtual void _vf113() = 0;                                          // [113] 0x388
    virtual void _vf114() = 0;                                          // [114] 0x390
    virtual void _vf115() = 0;                                          // [115] 0x398
    virtual void _vf116() = 0;                                          // [116] 0x3A0
    virtual void _vf117() = 0;                                          // [117] 0x3A8
    virtual void _vf118() = 0;                                          // [118] 0x3B0
    virtual void _vf119() = 0;                                          // [119] 0x3B8
    virtual void _vf120() = 0;                                          // [120] 0x3C0
    virtual void _vf121() = 0;                                          // [121] 0x3C8
    virtual void _vf122() = 0;                                          // [122] 0x3D0
    virtual void OnActionEvent(SActionEvent* pEvent) = 0;               // [123] 0x3D8  sub_1803E8584 — dispatches to IGameFrameworkListeners
};

}  // namespace Offsets
