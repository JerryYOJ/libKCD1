#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindPlayer — entity script binding for the player
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindPlayer@entitymodule@wh@@
// vtable: 0x1826c5d88
// Constructor: sub_1810BA284
// Size: 0x78

namespace wh::entitymodule {

class C_ScriptBindPlayer : public CScriptableBase {
public:
    Offsets::IScriptTable*  m_pEntityTable;     // +0x60
    void*                   m_pGameFramework;   // +0x68
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x70

    enum EMountActionType { MAT_Undefined = 0, MAT_MountDisabled = 1, MAT_Mount = 2 };

    virtual int OnEnterInteractive(IFunctionHandler* pH);              // 0x1810D6E4C
    virtual int OnEndInteractive(IFunctionHandler* pH);                // 0x1810D6BA8
    virtual int OnEndItemInteraction(IFunctionHandler* pH);            // 0x1810D6C24
    virtual int OnSleeping(IFunctionHandler* pH);                      // 0x1810D900C
    virtual int GetPlayerHorse(IFunctionHandler* pH);                  // 0x1810C5060
    virtual int ClearPlayerHorse(IFunctionHandler* pH);                // 0x1810C4C30
    virtual int SetPlayerHorse(IFunctionHandler* pH);                  // 0x1810C964C
    virtual int EnablePlayerHorseInventory(IFunctionHandler* pH);      // 0x1810E7078
    virtual int EnableFastTravel(IFunctionHandler* pH);                // 0x1810CA910
    virtual int ToggleWeaponSet(IFunctionHandler* pH);                 // 0x1810C0F90
    virtual int TryDrawTorch(IFunctionHandler* pH);                    // 0x1810E7738
    virtual int PushBack(IFunctionHandler* pH);                        // 0x1810E6FE4
    virtual int SetWhistling(IFunctionHandler* pH);                    // 0x1810E1804
    virtual int AddLuaActions(IFunctionHandler* pH);                   // 0x1810C0AB0
    virtual int AddSoAction(IFunctionHandler* pH);                     // 0x1810CD5CC
    virtual int OnBedStop(IFunctionHandler* pH);                       // 0x1810C5E80
    virtual int CanSleepAndReportProblem(IFunctionHandler* pH);        // 0x1802AA530
    virtual int IsSitting(IFunctionHandler* pH);                       // 0x1810BE350
    virtual int IsLaying(IFunctionHandler* pH);                        // 0x1810C2590
    virtual int OnBedInterrupt(IFunctionHandler* pH);                  // 0x1810C2548
    virtual int OnBedPrepareForDialog(IFunctionHandler* pH);           // 0x1810C2600
    virtual int HorseInspect(IFunctionHandler* pH);                    // 0x1810E978C
    virtual int GetHorseId(IFunctionHandler* pH);                      // 0x1810E9A40
    virtual int RequestDogObjective(IFunctionHandler* pH);             // 0x1810DC020
    virtual int CancelDogObjective(IFunctionHandler* pH);              // 0x1810D680C
    virtual int HasRunningDogObjective(IFunctionHandler* pH);          // 0x1810D33F4
    virtual int FeedDog(IFunctionHandler* pH);                         // 0x1810D2B74

    // -- Direct Lua methods --
    // int CanMountHorse(IFunctionHandler* pH, EntityId horseId);      // 0x1810C01F0
};
static_assert(sizeof(C_ScriptBindPlayer) == 0x78);

} // namespace wh::entitymodule
