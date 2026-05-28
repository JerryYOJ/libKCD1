#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindPlayer — entity script binding for the player
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindPlayer@entitymodule@wh@@
// vtable: 0x1826c5d88
// Constructor: sub_1810BA284
// Size: 0x78
//
// Entity binding — stored at C_EntityModule+0xA0.

namespace wh::entitymodule {

class C_ScriptBindPlayer : public CScriptableBase {
public:
    Offsets::IScriptTable*  m_pEntityTable;     // +0x60
    void*                   m_pGameFramework;   // +0x68  IGameFramework*
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x70

    // -- Constants --
    enum EMountActionType {
        MAT_Undefined     = 0,
        MAT_MountDisabled = 1,
        MAT_Mount         = 2,
    };

    // -- Lua methods (28) --
    int OnEnterInteractive(IFunctionHandler* pH);                                   // 0x180B1AB4C
    int OnEndInteractive(IFunctionHandler* pH);                                     // 0x180B1AC14
    int OnEndItemInteraction(IFunctionHandler* pH);                                 // 0x180B1AC1C
    int OnSleeping(IFunctionHandler* pH, int sleepQuality);                         // 0x180B1AC24
    int GetPlayerHorse(IFunctionHandler* pH);                                       // 0x180B1AC44
    int ClearPlayerHorse(IFunctionHandler* pH);                                     // 0x180B1AC4C
    int SetPlayerHorse(IFunctionHandler* pH, EntityId entityId);                    // 0x180B1AC3C
    int EnablePlayerHorseInventory(IFunctionHandler* pH, bool enable);              // 0x180B1AC2C
    int EnableFastTravel(IFunctionHandler* pH, bool enable);                        // 0x180B1AD1C
    int ToggleWeaponSet(IFunctionHandler* pH, int weaponSet);                       // 0x180B1ACD4
    int TryDrawTorch(IFunctionHandler* pH);                                         // 0x180B1ACE0
    int PushBack(IFunctionHandler* pH, float distance);                             // 0x180B1ACEC
    int SetWhistling(IFunctionHandler* pH, bool activate);                          // 0x180B1AC54
    int AddLuaActions(IFunctionHandler* pH, SmartScriptTable actions);              // 0x180B1AC98
    int AddSoAction(IFunctionHandler* pH, const char* wuid, const char* strPress, const char* strHold, const char* interaction); // 0x180B1ACA4
    int OnBedStop(IFunctionHandler* pH);                                            // 0x180B1ACF8
    int CanSleepAndReportProblem(IFunctionHandler* pH);                             // 0x180B1AD10
    int IsSitting(IFunctionHandler* pH);                                            // 0x180B1A954
    int IsLaying(IFunctionHandler* pH);                                             // 0x180B1A960
    int OnBedInterrupt(IFunctionHandler* pH);                                       // 0x180B1AD04
    int OnBedPrepareForDialog(IFunctionHandler* pH);                                // 0x180B1A948
    int HorseInspect(IFunctionHandler* pH, EntityId horseId);                       // 0x180B1A96C
    int GetHorseId(IFunctionHandler* pH);                                           // 0x180B1AC34
    int CanMountHorse(IFunctionHandler* pH, EntityId horseId);                      // 0x1810C01F0
    int RequestDogObjective(IFunctionHandler* pH, EntityId entityId);               // 0x180B1AC68
    int CancelDogObjective(IFunctionHandler* pH);                                   // 0x180B1AC74
    int HasRunningDogObjective(IFunctionHandler* pH);                               // 0x180B1AC80
    int FeedDog(IFunctionHandler* pH);                                              // 0x180B1AC8C
};
static_assert(sizeof(C_ScriptBindPlayer) == 0x78);

} // namespace wh::entitymodule
