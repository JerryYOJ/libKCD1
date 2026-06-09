#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindGameRules — entity script binding for game rules
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindGameRules@entitymodule@wh@@
// vtable: 0x1826c6098
// Constructor: sub_1810B9434
// Registration: sub_1810DE9A8 (methods), sub_1810DE3D4 (constants)
// Size: 0x98

namespace wh::entitymodule {

class C_ScriptBindGameRules : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindGameRules;
    Offsets::IScriptTable*  m_pTable1;          // +0x60
    Offsets::IScriptTable*  m_pTable2;          // +0x68
    Offsets::IScriptTable*  m_pTable3;          // +0x70
    Offsets::IScriptTable*  m_pTable4;          // +0x78
    void*                   m_pGameFramework;   // +0x80
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x88
    void*                   m_pModule;          // +0x90

    enum ETextMessageType { TextMessageCenter = 0, TextMessageConsole = 1, TextMessageError = 2, TextMessageInfo = 3, TextMessageServer = 4 };
    enum EChatType { ChatToTarget = 0, ChatToTeam = 1, ChatToAll = 2 };
    enum ETextMessageTarget { TextMessageToClient = 1, TextMessageToAll = 8, TextMessageToAllRemote = 0x10008 };
    enum EObjectiveState { MO_DEACTIVATED = 0, MO_COMPLETED = 1, MO_FAILED = 2, MO_ACTIVATED = 3 };
    enum EActionHoldType { AHT_PRESS = 0, AHT_HOLD = 1 };
    enum EActionHoldCategory { AHC_BASIC = 0, AHC_DOG = 1 };

    // -- Direct Lua methods (93) --
    // int IsServer(IFunctionHandler* pH);                           // 0x1810D3384
    // int IsClient(IFunctionHandler* pH);                           // 0x1810D27C4
    // int CanCheat(IFunctionHandler* pH);                           // 0x1810BFE4C
    // int SpawnPlayer(IFunctionHandler* pH);                        // 0x1810E804C
    // int ChangePlayerClass(IFunctionHandler* pH);                  // 0x1810C0AE0
    // int RevivePlayer(IFunctionHandler* pH);                       // 0x1810E2E08
    // int RevivePlayerInVehicle(IFunctionHandler* pH);              // 0x1810E2ED4
    // int RenamePlayer(IFunctionHandler* pH);                       // 0x1810E1390
    // int KillPlayer(IFunctionHandler* pH);                         // 0x1810D35F0
    // int MovePlayer(IFunctionHandler* pH);                         // 0x1810D5A58
    // int GetPlayerByChannelId(IFunctionHandler* pH);               // 0x1810CA808
    // int GetChannelId(IFunctionHandler* pH);                       // 0x1810C7A50
    // int GetPlayerCount(IFunctionHandler* pH);                     // 0x1810CA87C
    // int GetPlayers(IFunctionHandler* pH);                         // 0x1810CA96C
    // int IsPlayerInGame(IFunctionHandler* pH);                     // 0x1810D301C
    // int IsProjectile(IFunctionHandler* pH);                       // 0x1810D31BC
    // int IsSameTeam(IFunctionHandler* pH);                         // 0x1810D32F4
    // int IsNeutral(IFunctionHandler* pH);                          // 0x1810D2DD4
    // int AddSpawnLocation(IFunctionHandler* pH);                   // 0x1810BE538
    // int RemoveSpawnLocation(IFunctionHandler* pH);                // 0x1810E1120
    // int GetSpawnLocationCount(IFunctionHandler* pH);              // 0x1810CB478
    // int GetSpawnLocationByIdx(IFunctionHandler* pH);              // 0x1810CB40C
    // int GetSpawnLocations(IFunctionHandler* pH);                  // 0x1810CB538
    // int GetSpawnLocation(IFunctionHandler* pH);                   // 0x1810CB2A4
    // int GetFirstSpawnLocation(IFunctionHandler* pH);              // 0x1810C90C0
    // int AddSpawnGroup(IFunctionHandler* pH);                      // 0x1810BE4E4
    // int AddSpawnLocationToSpawnGroup(IFunctionHandler* pH);       // 0x1810BE58C
    // int RemoveSpawnLocationFromSpawnGroup(IFunctionHandler* pH);  // 0x1810E1174
    // int RemoveSpawnGroup(IFunctionHandler* pH);                   // 0x1810E10CC
    // int GetSpawnLocationGroup(IFunctionHandler* pH);              // 0x1810CB4CC
    // int GetSpawnGroups(IFunctionHandler* pH);                     // 0x1810CB168
    // int IsSpawnGroup(IFunctionHandler* pH);                       // 0x1810D3440
    // int GetTeamDefaultSpawnGroup(IFunctionHandler* pH);           // 0x1810CBED8
    // int SetTeamDefaultSpawnGroup(IFunctionHandler* pH);           // 0x1810E7248
    // int SetPlayerSpawnGroup(IFunctionHandler* pH);                // 0x1810E70B0
    // int AddMinimapEntity(IFunctionHandler* pH);                   // 0x1810BDFD4
    // int RemoveMinimapEntity(IFunctionHandler* pH);                // 0x1810E0E08
    // int ResetMinimap(IFunctionHandler* pH);                       // 0x1810E28E8
    // int GetPing(IFunctionHandler* pH);                            // 0x1810CA770
    // int ResetEntities(IFunctionHandler* pH);                      // 0x1810E2764
    // int ServerExplosion(IFunctionHandler* pH);                    // 0x180F32EF0 (noop)
    // int ServerHit(IFunctionHandler* pH);                          // 0x1810E4F14
    // int CreateTeam(IFunctionHandler* pH);                         // 0x1810C24B8
    // int RemoveTeam(IFunctionHandler* pH);                         // 0x1810E1218
    // int GetTeamName(IFunctionHandler* pH);                        // 0x1810CBFD8
    // int GetTeamId(IFunctionHandler* pH);                          // 0x1810CBF44
    // int GetTeamCount(IFunctionHandler* pH);                       // 0x1810CBE7C
    // int GetTeamPlayerCount(IFunctionHandler* pH);                 // 0x1810CC044
    // int GetTeamChannelCount(IFunctionHandler* pH);                // 0x1810CBDD8
    // int GetTeamPlayers(IFunctionHandler* pH);                     // 0x1810CC0E8
    // int SetTeam(IFunctionHandler* pH);                            // 0x1810E71E4
    // int GetTeam(IFunctionHandler* pH);                            // 0x1810CBD74
    // int GetChannelTeam(IFunctionHandler* pH);                     // 0x1810C7AB4
    // int TextMessage(IFunctionHandler* pH);                        // 0x1810E944C
    // int SendTextMessage(IFunctionHandler* pH);                    // 0x1810E43C8
    // int SendChatMessage(IFunctionHandler* pH);                    // 0x1810E4354
    // int ForbiddenAreaWarning(IFunctionHandler* pH);               // 0x1810C68B8
    // int ResetGameTime(IFunctionHandler* pH);                      // 0x1810E27FC
    // int GetRemainingGameTime(IFunctionHandler* pH);               // 0x1810CAC18
    // int IsTimeLimited(IFunctionHandler* pH);                      // 0x1810D34AC
    // int ResetRoundTime(IFunctionHandler* pH);                     // 0x1810E2AA8
    // int GetRemainingRoundTime(IFunctionHandler* pH);              // 0x1810CAD2C
    // int IsRoundTimeLimited(IFunctionHandler* pH);                 // 0x1810D3294
    // int ResetPreRoundTime(IFunctionHandler* pH);                  // 0x1810E2A20
    // int GetRemainingPreRoundTime(IFunctionHandler* pH);           // 0x1810CAC74
    // int ResetReviveCycleTime(IFunctionHandler* pH);               // 0x1810E2A64
    // int GetRemainingReviveCycleTime(IFunctionHandler* pH);        // 0x1810CACD0
    // int ResetGameStartTimer(IFunctionHandler* pH);                // 0x1810E27A8
    // int GetRemainingStartTimer(IFunctionHandler* pH);             // 0x1810CAD88
    // int EndGame(IFunctionHandler* pH);                            // 0x1810C5120
    // int NextLevel(IFunctionHandler* pH);                          // 0x1810D5ED0
    // int RegisterHitMaterial(IFunctionHandler* pH);                // 0x1810DE618
    // int GetHitMaterialId(IFunctionHandler* pH);                   // 0x1810C9410
    // int GetHitMaterialName(IFunctionHandler* pH);                 // 0x1810C9468
    // int ResetHitMaterials(IFunctionHandler* pH);                  // 0x1810E2840
    // int RegisterHitType(IFunctionHandler* pH);                    // 0x1810DE670
    // int GetHitTypeId(IFunctionHandler* pH);                       // 0x1810C9530
    // int GetHitType(IFunctionHandler* pH);                         // 0x1810C94D8
    // int ResetHitTypes(IFunctionHandler* pH);                      // 0x1810E2880
    // int ForceScoreboard(IFunctionHandler* pH);                    // 0x1810C69D4
    // int FreezeInput(IFunctionHandler* pH);                        // 0x1810C6D68
    // int ScheduleEntityRespawn(IFunctionHandler* pH);              // 0x1810E42B0
    // int AbortEntityRespawn(IFunctionHandler* pH);                 // 0x1810BD650
    // int ScheduleEntityRemoval(IFunctionHandler* pH);              // 0x1810E424C
    // int AbortEntityRemoval(IFunctionHandler* pH);                 // 0x1810BD600
    // int SetSynchedGlobalValue(IFunctionHandler* pH);              // 0x180F32EF0 (noop)
    // int GetSynchedGlobalValue(IFunctionHandler* pH);              // 0x180F32EF0 (noop)
    // int SetSynchedEntityValue(IFunctionHandler* pH);              // 0x180F32EF0 (noop)
    // int GetSynchedEntityValue(IFunctionHandler* pH);              // 0x180F32EF0 (noop)
    // int ResetSynchedStorage(IFunctionHandler* pH);                // 0x180F32EF0 (noop)
    // int ForceSynchedStorageSynch(IFunctionHandler* pH);           // 0x180F32EF0 (noop)
    // int IsDemoMode(IFunctionHandler* pH);                         // 0x1810D2818
    // int GetTimeLimit(IFunctionHandler* pH);                       // 0x1810CC20C
    // int GetPreRoundTime(IFunctionHandler* pH);                    // 0x1810CAA74
    // int GetRoundTime(IFunctionHandler* pH);                       // 0x1810CAE34
    // int GetRoundLimit(IFunctionHandler* pH);                      // 0x1810CAE0C
    // int GetFragLimit(IFunctionHandler* pH);                       // 0x1810C91A0
    // int GetFragLead(IFunctionHandler* pH);                        // 0x1810C9178
    // int GetFriendlyFireRatio(IFunctionHandler* pH);               // 0x1810C91C8
    // int GetReviveTime(IFunctionHandler* pH);                      // 0x1810CADE4
    // int GetMinPlayerLimit(IFunctionHandler* pH);                  // 0x1810CA20C
    // int GetMinTeamLimit(IFunctionHandler* pH);                    // 0x1810CA234
    // int GetTeamLock(IFunctionHandler* pH);                        // 0x1810CBFB0
    // int DebugCollisionDamage(IFunctionHandler* pH);               // 0x1810C2520
    // int DebugHits(IFunctionHandler* pH);                          // 0x1810C25D8
    // int SendHitIndicator(IFunctionHandler* pH);                   // 0x180F32EF0 (noop)
    // int SendDamageIndicator(IFunctionHandler* pH);                // 0x180F32EF0 (noop)
    // int IsInvulnerable(IFunctionHandler* pH);                     // 0x1810D2AB0
    // int SetInvulnerability(IFunctionHandler* pH);                 // 0x1810E6230
    // int GameOver(IFunctionHandler* pH);                           // 0x1810C74E0
    // int EnteredGame(IFunctionHandler* pH);                        // 0x1810C51A4
    // int EndGameNear(IFunctionHandler* pH);                        // 0x1810C5164
    // int SPNotifyPlayerKill(IFunctionHandler* pH);                 // 0x1810E3710
    // int ProcessEMPEffect(IFunctionHandler* pH);                   // 0x1810DB9DC
    // int PerformDeadHit(IFunctionHandler* pH);                     // 0x1810D9E48
};
static_assert(sizeof(C_ScriptBindGameRules) == 0x98);

} // namespace wh::entitymodule
