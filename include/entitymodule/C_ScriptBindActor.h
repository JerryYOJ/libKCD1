#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindActor — entity script binding for actors
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindActor@entitymodule@wh@@
// vtable primary: 0x1826c60f8
// vtable secondary: 0x1826c60d8 (at +0x60)
// Constructor: sub_1810B7800
// Size: 0x90
//
// Entity binding — methods registered on entity script table, not global.
// Created by C_EntityModule (stored at module+0x88).

namespace wh::entitymodule {

class C_ScriptBindActor : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindActor;
    void*                   m_pVtable2;         // +0x60  secondary vftable
    Offsets::IScriptTable*  m_pEntityTable;     // +0x68  entity script table
    void*                   m_pGameFramework;   // +0x70  IGameFramework*
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x78
    void*                   m_pModule;          // +0x80  C_EntityModule*
    int32_t                 m_nFlags;           // +0x88
    int32_t                 _pad8C;             // +0x8C

    // -- Constants --
    enum EActorStance {
        E_ACTORSTANCE_COMBAT      = 0,
        E_ACTORSTANCE_CROUCH      = 1,
        E_ACTORSTANCE_NORMAL      = 3,
        E_ACTORSTANCE_CARRYCORPSE = 9,
        STANCE_ZEROG              = 9,
    };

    enum EStealthActionType {
        SAT_Undefined        = 0,
        SAT_KillDisabled     = 1,
        SAT_KnockoutDisabled = 2,
        SAT_KillEnabled      = 3,
        SAT_KnockoutEnabled  = 4,
    };

    enum EHorsePulldownState {
        HPS_Undefined = 0,
        HPS_Disabled  = 1,
        HPS_Enabled   = 2,
    };

    enum EHuntAttackState {
        HAS_Undefined = 0,
        HAS_Disabled  = 1,
        HAS_Enabled   = 2,
    };

    enum EMercyKillState {
        MKS_Undefined = 0,
        MKS_Disabled  = 1,
        MKS_Enabled   = 2,
    };

    enum EInventoryMode {
        E_IM_Player        = 0,
        E_IM_Map           = 1,
        E_IM_Store         = 2,
        E_IM_QuestReward   = 3,
        E_IM_QuestDelivery = 4,
        E_IM_Loot          = 5,
        E_IM_Shop          = 6,
        E_IM_Pickpocket    = 7,
        E_IM_StoreReadOnly = 8,
        E_IM_Filter        = 10,
        E_IM_Repair        = 11,
        E_IM_Sharpening    = 14,
    };

    // -- Virtual Lua methods (vtable-dispatched) --
    virtual int RequestDialog(IFunctionHandler* pH);                        // 0x1810E149C
    virtual int CanTalk(IFunctionHandler* pH);                              // 0x1810C0504
    virtual int Revive(IFunctionHandler* pH);                               // 0x1810E2DC0
    virtual int ReviveToDefaults(IFunctionHandler* pH);                     // 0x1810E2F78
    virtual int StandUp(IFunctionHandler* pH);                              // 0x1810E8974
    virtual int RagDollize(IFunctionHandler* pH);                           // 0x1810DCCE8
    virtual int PostPhysicalize(IFunctionHandler* pH);                      // 0x1810DACD0
    virtual int GetLinkedEntity(IFunctionHandler* pH);                      // 0x1810C9DFC
    virtual int SimulateOnAction(IFunctionHandler* pH);                     // 0x1810E7A84
    virtual int SetPhysicalizationProfile(IFunctionHandler* pH);            // 0x1810E6EDC
    virtual int GetPhysicalizationProfile(IFunctionHandler* pH);            // 0x1810CA6E4
    virtual int GetFrozenAmount(IFunctionHandler* pH);                      // 0x1810C91F0
    virtual int AddFrost(IFunctionHandler* pH);                             // 0x1810BD974
    virtual int DumpActorInfo(IFunctionHandler* pH);                        // 0x1810C4A78
    virtual int SetStats(IFunctionHandler* pH);                             // 0x1810E7164
    virtual int SetMovementRestriction(IFunctionHandler* pH);               // 0x1810E6AD8
    virtual int GetHeadPos(IFunctionHandler* pH);                           // 0x1810C9304
    virtual int GetHeadDir(IFunctionHandler* pH);                           // 0x1810C9228
    virtual int GetChannel(IFunctionHandler* pH);                           // 0x1810C7A04
    virtual int IsPlayer(IFunctionHandler* pH);                             // 0x1810D2C20
    virtual int IsLocalClient(IFunctionHandler* pH);                        // 0x1810D2C20
    virtual int IsGhostPit(IFunctionHandler* pH);                           // 0x1810D2984
    virtual int IsFlying(IFunctionHandler* pH);                             // 0x1810D28A4
    virtual int SetAngles(IFunctionHandler* pH);                            // 0x1810C7918
    virtual int PlayerSetViewAngles(IFunctionHandler* pH);                  // 0x1810DA940
    virtual int GetAngles(IFunctionHandler* pH);                            // 0x1810E5270
    virtual int SetViewLimits(IFunctionHandler* pH);                        // 0x1810E7580
    virtual int CameraShake(IFunctionHandler* pH);                          // 0x1810BFC4C
    virtual int SetViewShake(IFunctionHandler* pH);                         // 0x1810E7630
    virtual int VectorToLocal(IFunctionHandler* pH);                        // 0x1810EDD00
    virtual int EnableAspect(IFunctionHandler* pH);                         // 0x1810C4AA8
    virtual int SetExtensionActivation(IFunctionHandler* pH);               // 0x1810E5B30
    virtual int SetExtensionParams(IFunctionHandler* pH);                   // 0x1810E5C50
    virtual int GetExtensionParams(IFunctionHandler* pH);                   // 0x1810C8898
    virtual int SetMovementControlledByAnimation(IFunctionHandler* pH);     // 0x1810E6A44
    virtual int CanInteractWith(IFunctionHandler* pH);                      // 0x1802B7564
    virtual int SetHealth(IFunctionHandler* pH);                            // 0x18069311C
    virtual int SetMaxHealth(IFunctionHandler* pH);                         // 0x18069315C
    virtual int GetHealth(IFunctionHandler* pH);                            // 0x1806EE2B8
    virtual int IsUnconscious(IFunctionHandler* pH);                        // 0x1810D350C
    virtual int GetMaxHealth(IFunctionHandler* pH);                         // 0x1810C9F80
    virtual int GetArmor(IFunctionHandler* pH);                             // 0x1810C79BC
    virtual int GetMaxArmor(IFunctionHandler* pH);                          // 0x1810C9F38
    virtual int GetClosestAttachment(IFunctionHandler* pH);                 // 0x1810C7F34
    virtual int AttachVulnerabilityEffect(IFunctionHandler* pH);            // 0x1810BF278
    virtual int ResetVulnerabilityEffects(IFunctionHandler* pH);            // 0x1810E2AEC
    virtual int GetCloseColliderParts(IFunctionHandler* pH);                // 0x1810C7B6C
    virtual int CreateCodeEvent(IFunctionHandler* pH);                      // 0x1806EEF68
    virtual int GetCurrentAnimationState(IFunctionHandler* pH);             // 0x1810C8694
    virtual int TrackViewControlled(IFunctionHandler* pH);                  // 0x1810E97C4
    virtual int Fall(IFunctionHandler* pH);                                 // 0x1810C5D08
    virtual int ResetScores(IFunctionHandler* pH);                          // 0x1810E1420
    virtual int RenderScore(IFunctionHandler* pH);                          // 0x1810E1420
    virtual int SetSearchBeam(IFunctionHandler* pH);                        // 0x180F32EF0 (noop)
    virtual int SetSpectatorMode(IFunctionHandler* pH);                     // 0x1810E7114
    virtual int GetSpectatorMode(IFunctionHandler* pH);                     // 0x1810CB614
    virtual int SetLookIK(IFunctionHandler* pH);                            // 0x1806E61C0
    virtual int SetDialogAnimationState(IFunctionHandler* pH);              // 0x1806D93B8
    virtual int CanStealthKill(IFunctionHandler* pH);                       // 0x1810C043C
    virtual int CanStealthKnockout(IFunctionHandler* pH);                   // 0x1810C04A0
    virtual int RequestStealthKill(IFunctionHandler* pH);                   // 0x1810E1BC8
    virtual int RequestKnockOut(IFunctionHandler* pH);                      // 0x1810E1A4C
    virtual int AcceptStealthActionByVictim(IFunctionHandler* pH);          // 0x1810BD6B0
    virtual int CanHorsePullDown(IFunctionHandler* pH);                     // 0x1810C008C
    virtual int RequestHorsePullDown(IFunctionHandler* pH);                 // 0x1810E18A8
    virtual int CanHuntAttack(IFunctionHandler* pH);                        // 0x1810C00F0
    virtual int RequestHuntAttack(IFunctionHandler* pH);                    // 0x1810E1920
    virtual int CanDoMercyKill(IFunctionHandler* pH);                       // 0x1810BFF68
    virtual int RequestMercyKill(IFunctionHandler* pH);                     // 0x1810E1A54
    virtual int IsCarryingCorpse(IFunctionHandler* pH);                     // 0x1810D277C
    virtual int CanGrabCorpse(IFunctionHandler* pH);                        // 0x1810C003C
    virtual int RequestGrabCorpse(IFunctionHandler* pH);                    // 0x1810E1868
    virtual int CanPutCorpse(IFunctionHandler* pH);                         // 0x1810C0288
    virtual int RequestPutCorpse(IFunctionHandler* pH);                     // 0x1810E1B08
    virtual int CanLoot(IFunctionHandler* pH);                              // 0x1810C01A4
    virtual int EquipInventoryItem(IFunctionHandler* pH);                   // 0x1810C52CC
    virtual int UnequipInventoryItem(IFunctionHandler* pH);                 // 0x1810E9A7C
    virtual int CheckInventoryRestrictions(IFunctionHandler* pH);           // 0x1810C0B64
    virtual int CheckVirtualInventoryRestrictions(IFunctionHandler* pH);    // 0x1810C0BF0
    virtual int OpenInventory(IFunctionHandler* pH);                        // 0x1810D5708
    virtual int EquipClothingPreset(IFunctionHandler* pH);                  // 0x1810C51D8
    virtual int GetInitialClothingPreset(IFunctionHandler* pH);             // 0x18030D7F0
    virtual int EquipWeaponPreset(IFunctionHandler* pH);                    // 0x1810C5318
    virtual int GetInitialWeaponPreset(IFunctionHandler* pH);               // 0x1806C4708
    virtual int StartInteractiveActionByName(IFunctionHandler* pH);         // 0x1810E8E0C
    virtual int RequestItemExchange(IFunctionHandler* pH);                  // 0x1810E1998
    virtual int MakeLookAsActor(IFunctionHandler* pH);                      // 0x1810D567C
    virtual int MakeLookAsSoul(IFunctionHandler* pH);                       // 0x1810D5708

    // -- Direct Lua methods (non-virtual, direct dispatch) --
    // int SetForcedLookDir(IFunctionHandler* pH, Vec3 dir);                // 0x1810E6088
    // int ClearForcedLookDir(IFunctionHandler* pH);                        // 0x1810C0F30
    // int SetForcedLookObjectId(IFunctionHandler* pH, EntityId objectId);  // 0x1810E6100
    // int ClearForcedLookObjectId(IFunctionHandler* pH);                   // 0x1810C0F64
    // int AddDirt(IFunctionHandler* pH, float dirtDelta);                  // 0x1802ABCCC
    // int CleanDirt(IFunctionHandler* pH, float maxCleaningEffect);        // 0x1802AC508
    // int AddBlood(IFunctionHandler* pH, const char* zoneName, float bloodDelta); // 0x1810BD884
    // int WashDirtAndBlood(IFunctionHandler* pH, float maxCleaningEffect); // 0x1810EDE40
    // int WashItems(IFunctionHandler* pH, float maxCleaningEffect);        // 0x1810EDEB0
    // int IsMoreDirty(IFunctionHandler* pH, float dirtLevel);              // 0x1810D2C6C
};
static_assert(sizeof(C_ScriptBindActor) == 0x90);

} // namespace wh::entitymodule
