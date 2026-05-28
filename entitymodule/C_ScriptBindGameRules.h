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
//
// Entity binding — largest scriptbind with 93 methods and 20 constants.

namespace wh::entitymodule {

class C_ScriptBindGameRules : public CScriptableBase {
public:
    Offsets::IScriptTable*  m_pTable1;          // +0x60  helper table
    Offsets::IScriptTable*  m_pTable2;          // +0x68  helper table
    Offsets::IScriptTable*  m_pTable3;          // +0x70  helper table
    Offsets::IScriptTable*  m_pTable4;          // +0x78  helper table
    void*                   m_pGameFramework;   // +0x80  IGameFramework*
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x88
    void*                   m_pModule;          // +0x90

    // -- Constants --
    enum ETextMessageType {
        TextMessageCenter  = 0,
        TextMessageConsole = 1,
        TextMessageError   = 2,
        TextMessageInfo    = 3,
        TextMessageServer  = 4,
    };

    enum EChatType {
        ChatToTarget = 0,
        ChatToTeam   = 1,
        ChatToAll    = 2,
    };

    enum ETextMessageTarget {
        TextMessageToAll       = 8,
        TextMessageToAllRemote = 0x10008,
        TextMessageToClient    = 1,
    };

    enum EObjectiveState {
        MO_DEACTIVATED = 0,
        MO_COMPLETED   = 1,
        MO_FAILED      = 2,
        MO_ACTIVATED   = 3,
    };

    enum EActionHoldType {
        AHT_PRESS = 0,
        AHT_HOLD  = 1,
    };

    enum EActionHoldCategory {
        AHC_BASIC = 0,
        AHC_DOG   = 1,
    };

    // -- Lua methods (93) --
    int IsServer(IFunctionHandler* pH);                                             // 0x1810D3384
    int IsClient(IFunctionHandler* pH);                                             // 0x1810D27C4
    int CanCheat(IFunctionHandler* pH);                                             // 0x1810BFE4C
    int SpawnPlayer(IFunctionHandler* pH, int channelId, const char* name, const char* className, Vec3 pos, Vec3 angles); // 0x1810E804C
    int ChangePlayerClass(IFunctionHandler* pH, int channelId, const char* className, Vec3 pos, Vec3 angles); // 0x1810C0AE0
    int RevivePlayer(IFunctionHandler* pH, EntityId playerId, Vec3 pos, Vec3 angles, int teamId, bool clearInventory); // 0x1810E2E08
    int RevivePlayerInVehicle(IFunctionHandler* pH, EntityId playerId, EntityId vehicleId, int seatId, int teamId, bool clearInventory); // 0x1810E2ED4
    int RenamePlayer(IFunctionHandler* pH, EntityId playerId, const char* name);    // 0x1810E1390
    int KillPlayer(IFunctionHandler* pH, EntityId playerId, bool dropItem, bool ragdoll, EntityId shooterId, EntityId weaponId, float damage, int material, bool headshot, bool melee, Vec3 impulse); // 0x1810D35F0
    int MovePlayer(IFunctionHandler* pH, EntityId playerId, Vec3 pos, Vec3 angles); // 0x1810D5A58
    int GetPlayerByChannelId(IFunctionHandler* pH, int channelId);                  // 0x1810CA808
    int GetChannelId(IFunctionHandler* pH, EntityId playerId);                      // 0x1810C7A50
    int GetPlayerCount(IFunctionHandler* pH);                                       // 0x1810CA87C
    int GetPlayers(IFunctionHandler* pH);                                           // 0x1810CA96C
    int IsPlayerInGame(IFunctionHandler* pH, EntityId playerId);                    // 0x1810D301C
    int IsProjectile(IFunctionHandler* pH, EntityId entityId);                      // 0x1810D31BC
    int IsSameTeam(IFunctionHandler* pH, EntityId entityId0, EntityId entityId1);   // 0x1810D32F4
    int IsNeutral(IFunctionHandler* pH, EntityId entityId);                         // 0x1810D2DD4
    int AddSpawnLocation(IFunctionHandler* pH, EntityId entityId);                  // 0x1810BE538
    int RemoveSpawnLocation(IFunctionHandler* pH, int id);                          // 0x1810E1120
    int GetSpawnLocationCount(IFunctionHandler* pH);                                // 0x1810CB478
    int GetSpawnLocationByIdx(IFunctionHandler* pH, int idx);                       // 0x1810CB40C
    int GetSpawnLocations(IFunctionHandler* pH);                                    // 0x1810CB538
    int GetSpawnLocation(IFunctionHandler* pH, EntityId playerId, int teamId, bool ignoreTeam, bool includeNeutral); // 0x1810CB2A4
    int GetFirstSpawnLocation(IFunctionHandler* pH, int teamId);                    // 0x1810C90C0
    int AddSpawnGroup(IFunctionHandler* pH, EntityId groupId);                      // 0x1810BE4E4
    int AddSpawnLocationToSpawnGroup(IFunctionHandler* pH, EntityId groupId, EntityId location); // 0x1810BE58C
    int RemoveSpawnLocationFromSpawnGroup(IFunctionHandler* pH, EntityId groupId, EntityId location); // 0x1810E1174
    int RemoveSpawnGroup(IFunctionHandler* pH, EntityId groupId);                   // 0x1810E10CC
    int GetSpawnLocationGroup(IFunctionHandler* pH, EntityId spawnId);              // 0x1810CB4CC
    int GetSpawnGroups(IFunctionHandler* pH);                                       // 0x1810CB168
    int IsSpawnGroup(IFunctionHandler* pH, EntityId entityId);                      // 0x1810D3440
    int GetTeamDefaultSpawnGroup(IFunctionHandler* pH, int teamId);                 // 0x1810CBED8
    int SetTeamDefaultSpawnGroup(IFunctionHandler* pH, int teamId, EntityId groupId); // 0x1810E7248
    int SetPlayerSpawnGroup(IFunctionHandler* pH, EntityId playerId, EntityId groupId); // 0x1810E70B0
    int AddMinimapEntity(IFunctionHandler* pH, EntityId entityId, int type, float lifetime); // 0x1810BDFD4
    int RemoveMinimapEntity(IFunctionHandler* pH, EntityId entityId);               // 0x1810E0E08
    int ResetMinimap(IFunctionHandler* pH);                                         // 0x1810E28E8
    int GetPing(IFunctionHandler* pH, int channelId);                               // 0x1810CA770
    int ResetEntities(IFunctionHandler* pH);                                        // 0x1810E2764
    int ServerExplosion(IFunctionHandler* pH);                                      // 0x180F32EF0
    int ServerHit(IFunctionHandler* pH);                                            // 0x1810E4F14
    int CreateTeam(IFunctionHandler* pH, const char* name);                         // 0x1810C24B8
    int RemoveTeam(IFunctionHandler* pH, int teamId);                               // 0x1810E1218
    int GetTeamName(IFunctionHandler* pH, int teamId);                              // 0x1810CBFD8
    int GetTeamId(IFunctionHandler* pH, const char* teamName);                      // 0x1810CBF44
    int GetTeamCount(IFunctionHandler* pH);                                         // 0x1810CBE7C
    int GetTeamPlayerCount(IFunctionHandler* pH, int teamId);                       // 0x1810CC044
    int GetTeamChannelCount(IFunctionHandler* pH, int teamId);                      // 0x1810CBDD8
    int GetTeamPlayers(IFunctionHandler* pH, int teamId);                           // 0x1810CC0E8
    int SetTeam(IFunctionHandler* pH, int teamId, EntityId playerId);               // 0x1810E71E4
    int GetTeam(IFunctionHandler* pH, EntityId playerId);                           // 0x1810CBD74
    int GetChannelTeam(IFunctionHandler* pH, int channelId);                        // 0x1810C7AB4
    int TextMessage(IFunctionHandler* pH, int type, const char* msg);               // 0x1810E944C
    int SendTextMessage(IFunctionHandler* pH, int type, const char* msg);           // 0x1810E43C8
    int SendChatMessage(IFunctionHandler* pH, int type, EntityId sourceId, EntityId targetId, const char* msg); // 0x1810E4354
    int ForbiddenAreaWarning(IFunctionHandler* pH, bool active, float timer, EntityId targetId); // 0x1810C68B8
    int ResetGameTime(IFunctionHandler* pH);                                        // 0x1810E27FC
    int GetRemainingGameTime(IFunctionHandler* pH);                                 // 0x1810CAC18
    int IsTimeLimited(IFunctionHandler* pH);                                        // 0x1810D34AC
    int ResetRoundTime(IFunctionHandler* pH);                                       // 0x1810E2AA8
    int GetRemainingRoundTime(IFunctionHandler* pH);                                // 0x1810CAD2C
    int IsRoundTimeLimited(IFunctionHandler* pH);                                   // 0x1810D3294
    int ResetPreRoundTime(IFunctionHandler* pH);                                    // 0x1810E2A20
    int GetRemainingPreRoundTime(IFunctionHandler* pH);                             // 0x1810CAC74
    int ResetReviveCycleTime(IFunctionHandler* pH);                                 // 0x1810E2A64
    int GetRemainingReviveCycleTime(IFunctionHandler* pH);                          // 0x1810CACD0
    int ResetGameStartTimer(IFunctionHandler* pH, float time);                      // 0x1810E27A8
    int GetRemainingStartTimer(IFunctionHandler* pH);                               // 0x1810CAD88
    int EndGame(IFunctionHandler* pH);                                              // 0x1810C5120
    int NextLevel(IFunctionHandler* pH);                                            // 0x1810D5ED0
    int RegisterHitMaterial(IFunctionHandler* pH, const char* materialName);        // 0x1810DE618
    int GetHitMaterialId(IFunctionHandler* pH, const char* materialName);           // 0x1810C9410
    int GetHitMaterialName(IFunctionHandler* pH, int materialId);                   // 0x1810C9468
    int ResetHitMaterials(IFunctionHandler* pH);                                    // 0x1810E2840
    int RegisterHitType(IFunctionHandler* pH, const char* type);                    // 0x1810DE670
    int GetHitTypeId(IFunctionHandler* pH, const char* type);                       // 0x1810C9530
    int GetHitType(IFunctionHandler* pH, int id);                                   // 0x1810C94D8
    int ResetHitTypes(IFunctionHandler* pH);                                        // 0x1810E2880
    int ForceScoreboard(IFunctionHandler* pH, bool force);                          // 0x1810C69D4
    int FreezeInput(IFunctionHandler* pH, bool freeze);                             // 0x1810C6D68
    int ScheduleEntityRespawn(IFunctionHandler* pH, EntityId entityId, bool unique, float timer); // 0x1810E42B0
    int AbortEntityRespawn(IFunctionHandler* pH, EntityId entityId, bool destroyData); // 0x1810BD650
    int ScheduleEntityRemoval(IFunctionHandler* pH, EntityId entityId, float timer, bool visibility); // 0x1810E424C
    int AbortEntityRemoval(IFunctionHandler* pH, EntityId entityId);                // 0x1810BD600
    int SetSynchedGlobalValue(IFunctionHandler* pH);                                // 0x180F32EF0 (stub)
    int GetSynchedGlobalValue(IFunctionHandler* pH);                                // 0x180F32EF0 (stub)
    int SetSynchedEntityValue(IFunctionHandler* pH);                                // 0x180F32EF0 (stub)
    int GetSynchedEntityValue(IFunctionHandler* pH);                                // 0x180F32EF0 (stub)
    int ResetSynchedStorage(IFunctionHandler* pH);                                  // 0x180F32EF0 (stub)
    int ForceSynchedStorageSynch(IFunctionHandler* pH, int channelId);              // 0x180F32EF0 (stub)
    int IsDemoMode(IFunctionHandler* pH);                                           // 0x1810D2818
    int GetTimeLimit(IFunctionHandler* pH);                                         // 0x1810CC20C
    int GetPreRoundTime(IFunctionHandler* pH);                                      // 0x1810CAA74
    int GetRoundTime(IFunctionHandler* pH);                                         // 0x1810CAE34
    int GetRoundLimit(IFunctionHandler* pH);                                        // 0x1810CAE0C
    int GetFragLimit(IFunctionHandler* pH);                                         // 0x1810C91A0
    int GetFragLead(IFunctionHandler* pH);                                          // 0x1810C9178
    int GetFriendlyFireRatio(IFunctionHandler* pH);                                 // 0x1810C91C8
    int GetReviveTime(IFunctionHandler* pH);                                        // 0x1810CADE4
    int GetMinPlayerLimit(IFunctionHandler* pH);                                    // 0x1810CA20C
    int GetMinTeamLimit(IFunctionHandler* pH);                                      // 0x1810CA234
    int GetTeamLock(IFunctionHandler* pH);                                          // 0x1810CBFB0
    int DebugCollisionDamage(IFunctionHandler* pH);                                 // 0x1810C2520
    int DebugHits(IFunctionHandler* pH);                                            // 0x1810C25D8
    int SendHitIndicator(IFunctionHandler* pH, EntityId shooterId);                 // 0x180F32EF0 (stub)
    int SendDamageIndicator(IFunctionHandler* pH, EntityId shooterId);              // 0x180F32EF0 (stub)
    int IsInvulnerable(IFunctionHandler* pH, EntityId playerId);                    // 0x1810D2AB0
    int SetInvulnerability(IFunctionHandler* pH, EntityId playerId, bool invulnerable); // 0x1810E6230
    int GameOver(IFunctionHandler* pH, int localWinner);                            // 0x1810C74E0
    int EnteredGame(IFunctionHandler* pH);                                          // 0x1810C51A4
    int EndGameNear(IFunctionHandler* pH, EntityId entityId);                       // 0x1810C5164
    int SPNotifyPlayerKill(IFunctionHandler* pH, EntityId targetId, EntityId weaponId, bool headShot); // 0x1810E3710
    int ProcessEMPEffect(IFunctionHandler* pH, EntityId targetId, float timeScale); // 0x1810DB9DC
    int PerformDeadHit(IFunctionHandler* pH);                                       // 0x1810D9E48
};
static_assert(sizeof(C_ScriptBindGameRules) == 0x98);

} // namespace wh::entitymodule
