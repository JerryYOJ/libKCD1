#pragma once
#include <cstdint>
#include <cstddef>
#include "vtables/IGameFramework.h"
#include "vtables/I3DEngine.h"

// -----------------------------------------------
// Global singleton offsets
// -----------------------------------------------
// Getter declarations are on each class as static GetInstance() methods.
// All implementations are in Offsets.cpp.
//
//   SSystemGlobalEnvironment::GetInstance()          — crysystem/SSystemGlobalEnvironment.h
//   wh::game::S_GameContext::GetInstance()           — game/S_GameContext.h
//   wh::rpgmodule::C_RPGModule::GetInstance()        — rpgmodule/C_RPGModule.h
//   wh::guimodule::CUIManager::GetInstance()         — guimodule/CUIManager.h
//   wh::guimodule::uielement::C_UIEHud::GetInstance() — guimodule/C_UIEHud.h
//   wh::combatmodule::C_CombatModule::GetInstance()  — combatmodule/C_CombatModule.h
//   wh::combatmodule::C_CombatScene::GetInstance()   — combatmodule/C_CombatScene.h
//   wh::combatmodule::S_CombatSettings::GetInstance() — combatmodule/S_CombatSettings.h
//   wh::rpgmodule::C_BuffManager::GetInstance()        — rpgmodule/buff/C_BuffManager.h
//   wh::rpgmodule::S_RpgParamValues::Get()             — rpgmodule/S_RpgParams.h
//   wh::rpgmodule::S_RpgParamDefs::Get()               — rpgmodule/S_RpgParams.h

namespace Offsets {

// WHGame.dll base address helper
uintptr_t GetBase();

inline static constexpr uintptr_t kGEnvOffset              = 0x29D16B8;
inline static constexpr uintptr_t kCCryActionOffset         = 0x3785D88;
inline static constexpr uintptr_t kC3DEngineOffset          = 0x3785BC0; // Cry3DEngineBase static C3DEngine* (qword_183785BC0; set in C3DEngine ctor). gEnv.p3DEngine(+0x08) is a DEAD slot in KCD (always null).
inline static constexpr uintptr_t kRPGModuleOffset          = 0x35AC728;
inline static constexpr uintptr_t kCUIManagerOffset         = 0x2F77888;
inline static constexpr uintptr_t kUIEHudOffset             = 0x3785948; // qword_183785948 — C_UIEHud* heap ptr (HUD singleton)
inline static constexpr uintptr_t kGameContextOffset        = 0x34FFD10;
inline static constexpr uintptr_t kCombatSettingsOffset     = 0x36DD8A0;
inline static constexpr uintptr_t kRPGParamsOffset          = 0x35004A0;
inline static constexpr uintptr_t kRPGParamDefsOffset       = 0x29C95D0;
inline static constexpr uintptr_t kActionTypeDbOffset       = 0x359B1E0;
inline static constexpr uintptr_t kBuffManagerOffset        = 0x3500F10;
inline static constexpr uintptr_t kCreateAndDispatchOffset  = 0x460934;
inline static constexpr uintptr_t kSetCommittedAttackZoneOffset = 0x45D1EC; // sub_18045D1EC: S_CombatActorState::SetCommittedAttackZone(zone) -> m_committedAttackZone(+0xC00, the PROVEN player swing-direction lever) via the change-notify setter
inline static constexpr uintptr_t kComboAdvanceStepOffset   = 0x602C34; // sub_180602C34: C_CombatComboManager combo-advance handler (normally the state+0x420 "attack-target-is-opponent" signal target). Direct call(this, owner, 1) = CLEAN combo FSM advance: ++m_currentStep + re-filter candidates + fire m_signal_078, WITHOUT writing state+0xC19 or emitting the +0x420 hit event. Reads executed key state+0xBF4; advances only when m_comboFlags(+0x228)==0 (else RESETS).
inline static constexpr uintptr_t kSetReactionWeightsOffset = 0x4F83C8; // sub_1804F83C8: C_CombatAutomationDefense::SetReactionWeights(this, const float w[5]). Frees the old +0x78 override, allocs 0x14, value-copies the 5 weights {noBlock,normalBlock,perfectBlock,specialPerfectBlock,dodge}; pass nullptr to clear. The picker (sub_1805F9408) overlays these over the RPG weights (REPLACE when >=0) -> per-NPC defense control.
// Attack-candidate ENUMERATION infra (RE: workflow wf_05aec32f). Lets a plugin enumerate
// candidates itself; the per-candidate DIRECTION is m_selectionKeyZone->m_matchKey (0..4),
// and the engine selects the candidate whose matchKey == sub_18045F3AC(live state).
inline static constexpr uintptr_t kQueryCtorOffset           = 0x4600BC; // sub_1804600BC: S_CombatActionAttackQueryData ctor (engine; 2nd arg ignored)
inline static constexpr uintptr_t kAttackSelectionResolveOffset = 0x45F3AC; // sub_18045F3AC(factory, state.inputClassId, &record) -> resolved swing zone (== the matchKey CreateAndDispatch selects); read-only
inline static constexpr uintptr_t kCombatAimConfigOffset      = 0x45F6E8; // sub_18045F6E8() -> the combat-aim config object; +0x9C (dword) = live directional aim-stance, the PLAYER's swing-direction lever (feeds sub_18045F66C -> src_zone)
inline static constexpr uintptr_t kQueryGetTypeNameHashOffset = 0xF49280; // sub_180F49280: S_CombatQueryData vtable[0] GetTypeNameHash(out)
inline static constexpr uintptr_t kQueryGetCacheKeyOffset    = 0x219730; // sub_180219730: S_CombatQueryData vtable[1] GetCacheKey (candidate-cache key)
inline static constexpr uintptr_t kBuildAttackQueryOffset    = 0x45FF90; // sub_18045FF90: C_CombatActionAttackFactory::BuildAttackQuery(input, &q)
inline static constexpr uintptr_t kEnumerateCandidatesOffset = 0x45FD18; // sub_18045FD18: fill candidate std::vector (arg1 ignored, &holder, &q)
inline static constexpr uintptr_t kPoolMallocOffset          = 0x28C040; // sub_18028C040: CryEngine bucket pool malloc (the candidate vector's heap path; pairs with the sized CryEngine::MemFree)
// (reserve + free are now real std::vector ops via C_InlinePoolAllocator's allocate/deallocate; the engine reserve sub_18045FB70 / free sub_18045FE70 offsets are no longer needed.)
inline static constexpr uintptr_t kQuerySubListDtorOffset    = 0x2185C4; // sub_1802185C4: destroy the query's +0xA8 intrusive sub-list
inline static constexpr uintptr_t kCryMemFreeOffset          = 0x5B72C0; // CryEngine::MemFree(ptr, size)

inline static constexpr uintptr_t kDispatchCounterActionOffset = 0x69536C;
inline static constexpr uintptr_t kSetOpponentOffset           = 0x63A634; // sub_18063A634: C_CombatActor::SetOpponent(target) -> opponent mgr UpdateOpponent (engage opponent; no-op unless m_isActive)
inline static constexpr uintptr_t kTypeFactoryEntryInitOffset  = 0x712B68;
inline static constexpr uintptr_t kActionTypeIdBase         = 0x359B330;
inline static constexpr uintptr_t kInputClassIdBase         = 0x359C2F0;
inline static constexpr uintptr_t kExecuteSaveOffset        = 0xF095F0; // C_PlayerProfileWHManager::ExecuteSave
inline static constexpr uintptr_t kSaveGameToSlotOffset     = 0xF12D64; // C_SaveGameManager::SaveGameToSlot
inline static constexpr uintptr_t kWriteSaveFileOffset      = 0xF0F088; // C_SaveGameManager::WriteSaveFile
inline static constexpr uintptr_t kGetOrCreateCombatActorOffset = 0x3A107C; // C_Actor::GetOrCreateCombatActor
inline static constexpr uintptr_t kItemGetRuntimeDataOffset  = 0x6B2D8C; // C_Item::GetRuntimeData  (get-or-create the +0x40 primary ExtraProperties)
inline static constexpr uintptr_t kItemSetRuntimeDataOffset  = 0x4544CC; // C_Item::SetRuntimeData  (+0xC0 keyed table; runs the record Clone/Release)
inline static constexpr uintptr_t kInventoryLookupByWUIDOffset = 0x55E7D8; // C_InventoryManager::LookupByWUID  (sub_18055E7D8; arg = this+0x10 slot table)
inline static constexpr uintptr_t kItemLookupByWUIDOffset      = 0x454638; // C_ItemManager::LookupByWUID       (sub_180454638; arg = this+0x18 slot table)
inline static constexpr uintptr_t kWuidObjectMapOffset         = 0x37999E0; // central WUID->C_AIObject* map (qword_1837999E0; holds a POINTER to the heap std::unordered_map)
inline static constexpr uintptr_t kLinkablesManagerOffset      = 0x37999D8; // C_LinkablesManager ptr (qword_1837999D8; WUID->C_LinkableObject map)
inline static constexpr uintptr_t kFindLinkableObjectOffset    = 0x24D6E4;  // sub_18024D6E4 (linkables-map find: (manager, &wuid) -> C_LinkableObject*)
inline static constexpr uintptr_t kGetInventoryForWuidOffset   = 0x15F457C; // sub_1815F457C (container WUID -> single C_Inventory; a1 unused)
inline static constexpr uintptr_t kFastTravelStopOffset             = 0x1226EA8; // C_FastTravel::Stop (sub_181226EA8; Lua FastTravel.Stop; UIMap signal +0xE0 handler)
inline static constexpr uintptr_t kFastTravelStartTravellingOffset  = 0x1226C54; // C_FastTravel::StartTravelling (sub_181226C54; UIMap signal +0xA0 handler; autosave + flags|=1)
inline static constexpr uintptr_t kFastTravelAnswerRandomEventOffset = 0x1226864; // C_FastTravel::AnswerRandomEvent(eventId, optionId) (sub_181226864; wh_pl_RandomEventAnswer)
inline static constexpr uintptr_t kFastTravelScheduleStopOffset     = 0x12271B0; // C_FastTravel::ScheduleStopAtEvent(seconds, eventId) (sub_1812271B0; Lua FastTravel.StopToEvent)
inline static constexpr uintptr_t kFastTravelCanStartOffset         = 0x121E530; // C_FastTravel::CanStartTravelling (sub_18121E530; E_FastTravelResult; first check = player+0xA30 & 0x20)
inline static constexpr uintptr_t kFastTravelIsTravellingOffset     = 0x3DBE28;  // C_FastTravel::IsFastTravelling (sub_1803DBE28; m_isTravelling || m_pAfterFastTravelObserver->active(+0x68))
inline static constexpr uintptr_t kFastTravelSetDestinationOffset   = 0x1226B24; // C_FastTravel::SetDestination(&pos, forced) (sub_181226B24; UIMap signal +0x60 handler; stores +0xC0, sets flag 0x8, ComputePath)
inline static constexpr uintptr_t kUIMapForceStartFastTravelOffset  = 0x112C494; // C_UIMap::ForceStartFastTravel(&pos, iconType) (sub_18112C494; wh_pl_FastTravelTo entry; blocks sim = visual-only)
inline static constexpr uintptr_t kGameTimerIsExpiredOffset         = 0x652DB4; // wh::framework::S_GameTimer::IsExpired (sub_180652DB4)
inline static constexpr uintptr_t kGameTimerArmOffset               = 0x652DEC; // wh::framework::S_GameTimer::Arm(ms)  (sub_180652DEC)

// C_InformationManager (crime/knowledge store; singleton + the crime-erase chain). RVAs = address - 0x180000000.
inline static constexpr uintptr_t kInformationManagerOffset         = 0x3501790; // C_InformationManager* singleton (qword_183501790)
// (GetHolderRecords needs no offset -- m_holders is a stock std::unordered_map, queried natively.)
inline static constexpr uintptr_t kInfoFindInformationIdOffset      = 0x15D3FEC; // FindInformationId (sub_1815D3FEC; arg = &m_records @+0x88)
inline static constexpr uintptr_t kInfoDestroyByIdOffset            = 0x15DB7C0; // DestroyInformationById (sub_1815DB7C0)
inline static constexpr uintptr_t kInfoRemoveFromHolderOffset       = 0x15DB81C; // RemoveInformationFromHolder (sub_1815DB81C)
inline static constexpr uintptr_t kInfoRemoveHolderOffset           = 0x513938;  // RemoveHolder (sub_180513938)

// Dynamic-info value store (C_DynamicInformationStore) -- backing for the *DynamicInformationValue BT nodes.
// Read this GLOBAL pointer DIRECTLY: it is null until the first dynamic value is touched in a session.
// Do NOT call the lazy creator sub_1814CEBBC -- it allocates the store (malloc + mutex) as a side effect.
inline static constexpr uintptr_t kDynInfoStoreOffset              = 0x3501560; // C_DynamicInformationStore* (qword_183501560; sibling global to the manager)

// C_FactionManager (faction reputation store). The manager is a Meyers-singleton OBJECT
// embedded at qword_1836E39F0; this accessor returns &it (and lazy-inits on first call).
inline static constexpr uintptr_t kFactionManagerAccessorOffset     = 0x22877C;  // sub_18022877C -> &C_FactionManager

// NPC reputation / soul access (RVAs = absolute address - 0x180000000).
inline static constexpr uintptr_t kSoulGetPlayerOpinionOffset       = 0x2287D0;  // sub_1802287D0: read soul opinion-of-player (root+0x6F8, master-walk)
inline static constexpr uintptr_t kSoulApplyRepDeltaOffset          = 0x11F3224; // sub_1811F3224: write opinion (soul+0x6F8) + optional faction-change route
inline static constexpr uintptr_t kSoulRepEffectApplyOffset         = 0x118F878; // sub_18118F878: C_SoulReputationEffect apply
inline static constexpr uintptr_t kSoulGetFactionIdOffset           = 0x64D750;  // sub_18064D750: faction id from soul (root+0x294)
inline static constexpr uintptr_t kModifyPlayerReputationOffset     = 0x11C6950; // sub_1811C6950: Lua Soul:ModifyPlayerReputation(repChangeName, propagate)
inline static constexpr uintptr_t kSoulResetInventoryOffset         = 0x30E278;  // sub_18030E278: C_Soul inventory reset (clear + repopulate from preset; args: soul, force, resetEquip, presetMul)
inline static constexpr uintptr_t kSoulListLookupByWuidOffset       = 0x284B04;  // sub_180284B04: C_SoulList::LookupByWUID(&slotmap@+0x48, &wuid)
inline static constexpr uintptr_t kGetSoulByEntityIdOffset          = 0x33B518;  // sub_18033B518: entityId -> C_Soul* (0 if not an actor; doubles as NPC test)
inline static constexpr uintptr_t kSoulHasAbilityOffset             = 0x23B6BC;  // sub_18023B6BC: C_Soul::HasSoulAbility(id) -- I_Soul vtable +0x1A8; binary-search m_soulAbilities(+0x180) + computed SteakTartare(17)/TwoHanded(61) cases

// AI-registry accessors (impl: AIRegistries.cpp). EntityToAIMap is a real std::unordered_map
// (indexed natively); the C_IntelligentObjectManager map is a custom T_WuidHashMap (uses engine Find).
inline static constexpr uintptr_t kEntityGuidWuidMapPtr             = 0x378D6E8; // qword_18378D6E8: ptr to the C_EntityToAIMap (std::unordered_map)
inline static constexpr uintptr_t kEntityGuidToWuidOffset           = 0x23BDCC;  // sub_18023BDCC(map, guid-by-value) -> WUID* (null sentinel on miss) [FindWuidByEntity]
inline static constexpr uintptr_t kIntelligentObjMgrPtr             = 0x3799950; // qword_183799950: ptr to the C_IntelligentObjectManager singleton
inline static constexpr uintptr_t kWuidToAIObjectOffset             = 0x2B620C;  // sub_1802B620C(mgr, &wuid) -> C_IntelligentObject* (0 if absent) [C_IntelligentObjectManager::Find]

// SmartArea layer (xgenaimodule). qword_183785A20 = C_SmartAreaManager (the WUID type-7 registry). The spatial
// point-query grid is a SEPARATE process-global wh::shared::C_RegularGrid (holder qword_1835012A8, getter sub_180498DE8).
inline static constexpr uintptr_t kSmartAreaManagerPtr             = 0x3785A20; // C_SmartAreaManager* singleton (qword_183785A20; getter sub_180705E80)
inline static constexpr uintptr_t kSmartAreaGridHolderPtr          = 0x35012A8; // holder of the global SmartArea C_RegularGrid (qword_1835012A8; getter sub_180498DE8); grid = *(holder)

// Game CRT allocator thunks (WHGame.dll, all jmp -> __imp_*). CrySDKStubs' CryModule*
// allocator forwards here so plugin allocations live on the GAME's heap (matched malloc/free).
inline static constexpr uintptr_t kGameMallocOffset                 = 0x28D0A8;  // malloc  (thunk -> __imp_malloc)
inline static constexpr uintptr_t kGameFreeOffset                   = 0xA2CB19;  // free    (thunk -> __imp_free)
inline static constexpr uintptr_t kGameCallocOffset                 = 0xA2CB13;  // calloc  (thunk -> __imp_calloc)
inline static constexpr uintptr_t kGameReallocOffset                = 0xA2CB31;  // realloc (thunk -> __imp_realloc)

// CryAction has no RE'd header — getter stays here
IGameFramework* GetCCryAction();

// I3DEngine: gEnv.p3DEngine (+0x08) is a DEAD SDK slot in KCD (always null) — read
// the Cry3DEngineBase static C3DEngine* instead (set in the C3DEngine ctor).
I3DEngine* Get3DEngine();

// CryEngine bucket allocator forwarders (the candidate std::vector's heap path).
// CryMemAlloc -> sub_18028C040 (bucket pool malloc); CryMemFree -> CryEngine::MemFree
// (sub_1805B72C0, SIZED). Matched pair — do NOT free these with CryModuleFree (CRT free),
// which would corrupt the bucket heap.
void* CryMemAlloc(std::size_t size);
void  CryMemFree(void* p, std::size_t size);

// -----------------------------------------------
// Combat action type IDs (runtime-assigned globals)
// -----------------------------------------------
// Registered in C_CombatActionTypeDatabase::Init (sub_18071C6E4).
// Each ID is assigned at startup via BST insertion — NOT compile-time constants.
// Read from globals the same way game code does.
struct ActionTypeId {
    static int32_t Attack();                    // 0x359B330
    static int32_t FreeAttack();                // 0x359B334
    static int32_t Leap();                      // 0x359B338
    static int32_t MercyAttack();               // 0x359B33C
    static int32_t Block();                     // 0x359B340
    static int32_t BlockMoveBack();             // 0x359B344
    static int32_t BlockStepBack();             // 0x359B348
    static int32_t PerfectBlock();              // 0x359B34C
    static int32_t PerfectNormalBlock();        // 0x359B350
    static int32_t RipostePerfectBlock();       // 0x359B354
    static int32_t PerfectBlockDodge();         // 0x359B358
    static int32_t SyncPerfectBlock();          // 0x359B35C
    static int32_t SyncPerfectBlockHit();       // 0x359B360
    static int32_t SyncDodge();                 // 0x359B364
    static int32_t SyncDodgeHit();              // 0x359B368
    static int32_t SyncRiposte();               // 0x359B36C
    static int32_t SyncRiposteHit();            // 0x359B370
    static int32_t HitTorso();                  // 0x359B374
    static int32_t HitBlockBroken();            // 0x359B378
    static int32_t HitBlockWeapon();            // 0x359B37C
    static int32_t HitMovement();               // 0x359B380
    static int32_t GuardIdleUpperBody();        // 0x359B384
    static int32_t GuardSyncMovementMaster();   // 0x359B388
    static int32_t GuardSyncMovementSlave();    // 0x359B38C
    static int32_t GuardStartSyncMovementMaster(); // 0x359B390
    static int32_t GuardStartSyncMovementSlave();  // 0x359B394
    static int32_t Movement();                  // 0x359B398
    static int32_t GuardPreBlock();             // 0x359B39C
    static int32_t GuardAttackStart();          // 0x359B3A0
    static int32_t FailedAttackOnBlock();       // 0x359B3A4
    static int32_t FailedAttackOnPB();          // 0x359B3A8
    static int32_t SyncAttack();                // 0x359B3AC
    static int32_t SyncHit();                   // 0x359B3B0
    static int32_t ComboAttack();               // 0x359B3B4
    static int32_t ComboHit();                  // 0x359B3B8
    static int32_t StealthAttackSuccess();      // 0x359B3BC
    static int32_t StealthAttackFail();         // 0x359B3C0
    static int32_t StealthHitSuccess();         // 0x359B3C4
    static int32_t StealthHitFail();            // 0x359B3C8
    static int32_t SyncTransitionMaster();      // 0x359B3CC
    static int32_t SyncTransitionSlave();       // 0x359B3D0
    static int32_t HuntAttackMaster();          // 0x359B3D4
    static int32_t HuntAttackSlave();           // 0x359B3D8
};

// -----------------------------------------------
// Combat input class IDs (runtime-assigned globals)
// -----------------------------------------------
// Registered in C_CombatInputClassDatabase::Init (sub_18071EA94).
// Each ID is assigned at startup via BST insertion.
// VERIFIED: names from StringHash calls in the init function.
struct InputClassId {
    static int32_t AttackLight();               // 0x359C2F0  "attack_light"
    static int32_t AttackHeavy();               // 0x359C2F4  "attack_heavy"
    static int32_t AttackSpecial();             // 0x359C2F8  "attack_special"
    static int32_t MoveLeft();                  // 0x359C2FC  "move_left"
    static int32_t MoveRight();                 // 0x359C300  "move_right"
    static int32_t MoveBack();                  // 0x359C304  "move_back"
    static int32_t MoveForward();               // 0x359C308  "move_forward"
    static int32_t Block();                     // 0x359C30C  "block"
};

}  // namespace Offsets
