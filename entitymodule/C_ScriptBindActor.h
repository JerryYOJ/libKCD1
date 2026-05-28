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
// Entity binding — methods are registered on the entity's script table,
// NOT as a global Lua table. Created as one of several independent
// scriptbind objects by C_EntityModule (stored at module+0x88).

namespace wh::entitymodule {

class C_ScriptBindActor : public CScriptableBase {
public:
    void*                   m_pVtable2;         // +0x60  secondary vftable
    Offsets::IScriptTable*  m_pEntityTable;     // +0x68  entity script table (via sub_18044478C)
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

    // -- Lua methods (73) --
    int RequestDialog(IFunctionHandler* pH);                                        // 0x180B1AC3C
    int CanTalk(IFunctionHandler* pH);                                              // 0x180B1AC44
    int Revive(IFunctionHandler* pH, bool fromGameModeInit);                        // 0x180B1AB4C
    int ReviveToDefaults(IFunctionHandler* pH);                                     // 0x180B1AC14
    int StandUp(IFunctionHandler* pH);                                              // 0x180B1AC1C
    int RagDollize(IFunctionHandler* pH);                                           // 0x180B1AC24
    int PostPhysicalize(IFunctionHandler* pH);                                      // 0x180B1AC2C
    int GetLinkedEntity(IFunctionHandler* pH);                                      // 0x180B1AC34
    int SimulateOnAction(IFunctionHandler* pH, const char* action, int mode, float value); // 0x180B1AC4C
    int SetPhysicalizationProfile(IFunctionHandler* pH, const char* profile);       // 0x180B1AC54
    int GetPhysicalizationProfile(IFunctionHandler* pH);                            // 0x180B1AC5C
    int GetFrozenAmount(IFunctionHandler* pH);                                      // 0x180B1AC68
    int AddFrost(IFunctionHandler* pH, float frost);                                // 0x180B1AC74
    int DumpActorInfo(IFunctionHandler* pH);                                        // 0x180B1AC80
    int SetStats(IFunctionHandler* pH);                                             // 0x180B1AC8C
    int SetMovementRestriction(IFunctionHandler* pH, bool bAllowSprint, bool bAllowRun); // 0x180B1AC98
    int GetHeadPos(IFunctionHandler* pH);                                           // 0x180B1ACBC
    int GetHeadDir(IFunctionHandler* pH);                                           // 0x180B1ACB0
    int GetChannel(IFunctionHandler* pH);                                           // 0x180B1ACC8
    int IsPlayer(IFunctionHandler* pH);                                             // 0x180B1ACD4
    int IsLocalClient(IFunctionHandler* pH);                                        // 0x180B1ACE0
    int IsGhostPit(IFunctionHandler* pH);                                           // 0x180B1ACEC
    int IsFlying(IFunctionHandler* pH);                                             // 0x180B1ACF8
    int SetAngles(IFunctionHandler* pH, Vec3 vAngles);                              // 0x180B1AD04
    int PlayerSetViewAngles(IFunctionHandler* pH, Vec3 vAngles);                    // 0x180B1A948
    int GetAngles(IFunctionHandler* pH);                                            // 0x180B1AD10
    int SetViewLimits(IFunctionHandler* pH, Vec3 dir, float rangeH, float rangeV);  // 0x180B1A954
    int CameraShake(IFunctionHandler* pH, float amount, float duration, float frequency, Vec3 pos); // 0x180B1A960
    int SetViewShake(IFunctionHandler* pH, Vec3 shakeAngle, Vec3 shakeShift, float duration, float frequency, float randomness); // 0x180B1A96C
    int VectorToLocal(IFunctionHandler* pH);                                        // 0x180B1A978
    int EnableAspect(IFunctionHandler* pH, int aspects, bool enable);               // 0x180B1A984
    int SetExtensionActivation(IFunctionHandler* pH, const char* extension, bool bActivate); // 0x180B1A990
    int SetExtensionParams(IFunctionHandler* pH);                                   // 0x180B1A57C
    int GetExtensionParams(IFunctionHandler* pH);                                   // 0x180B1A588
    int SetMovementControlledByAnimation(IFunctionHandler* pH, bool enable);        // 0x180B1A9E4
    int CanInteractWith(IFunctionHandler* pH, EntityId entityId);                   // 0x180B1A9FC
    int SetHealth(IFunctionHandler* pH, float health);                              // 0x180B1A594
    int SetMaxHealth(IFunctionHandler* pH, float health);                           // 0x180B1A99C
    int GetHealth(IFunctionHandler* pH);                                            // 0x180B1A9A8
    int IsUnconscious(IFunctionHandler* pH);                                        // 0x180B1A9B4
    int GetMaxHealth(IFunctionHandler* pH);                                         // 0x180B1A9C0
    int GetArmor(IFunctionHandler* pH);                                             // 0x180B1A9CC
    int GetMaxArmor(IFunctionHandler* pH);                                          // 0x180B1A9D8
    int GetClosestAttachment(IFunctionHandler* pH, int characterSlot, Vec3 testPos, float maxDistance, const char* suffix); // 0x180B1AA2C
    int AttachVulnerabilityEffect(IFunctionHandler* pH, int characterSlot, int partid, Vec3 hitPos, float radius, const char* effect, const char* attachmentIdentifier); // 0x180B1AA38
    int ResetVulnerabilityEffects(IFunctionHandler* pH, int characterSlot);         // 0x180B1AA44
    int GetCloseColliderParts(IFunctionHandler* pH, int characterSlot, Vec3 hitPos, float radius); // 0x180B1AA50
    int CreateCodeEvent(IFunctionHandler* pH, SmartScriptTable params);             // 0x180B1A9F0
    int GetCurrentAnimationState(IFunctionHandler* pH);                             // 0x180B1AA08
    int TrackViewControlled(IFunctionHandler* pH, int characterSlot);               // 0x180B1AA14
    int Fall(IFunctionHandler* pH, float hitPosX, float hitPosY, float hitPosZ);    // 0x180B1AA20
    int ResetScores(IFunctionHandler* pH);                                          // 0x180B1AA5C
    int RenderScore(IFunctionHandler* pH);                                          // 0x180B1AA68
    int SetSearchBeam(IFunctionHandler* pH, Vec3 dir);                              // 0x180B1AA74
    int SetSpectatorMode(IFunctionHandler* pH, int mode, EntityId target);          // 0x180B1AA80
    int GetSpectatorMode(IFunctionHandler* pH);                                     // 0x180B1AA8C
    int SetLookIK(IFunctionHandler* pH, bool enable);                               // 0x180B1ACA4
    int SetForcedLookDir(IFunctionHandler* pH, Vec3 dir);                           // 0x1810E6088
    int ClearForcedLookDir(IFunctionHandler* pH);                                   // 0x1810C0F30
    int SetForcedLookObjectId(IFunctionHandler* pH, EntityId objectId);             // 0x1810E6100
    int ClearForcedLookObjectId(IFunctionHandler* pH);                              // 0x1810C0F64
    int SetDialogAnimationState(IFunctionHandler* pH, bool state);                  // 0x180B1AA98
    int CanStealthKill(IFunctionHandler* pH, EntityId victimEntityId);              // 0x180B1AAA4
    int CanStealthKnockout(IFunctionHandler* pH, EntityId victimEntityId);          // 0x180B1AAB0
    int RequestStealthKill(IFunctionHandler* pH, EntityId victimEntityId);          // 0x180B1AABC
    int RequestKnockOut(IFunctionHandler* pH, EntityId victimEntityId);             // 0x180B1AAC8
    int AcceptStealthActionByVictim(IFunctionHandler* pH);                          // 0x180B1AAD4
    int CanHorsePullDown(IFunctionHandler* pH, EntityId victimEntityId);            // 0x180B1AAE0
    int RequestHorsePullDown(IFunctionHandler* pH, EntityId victimEntityId);        // 0x180B1AAEC
    int CanHuntAttack(IFunctionHandler* pH, EntityId victimEntityId);               // 0x180B1AAF8
    int RequestHuntAttack(IFunctionHandler* pH, EntityId victimEntityId);           // 0x180B1AB04
    int CanDoMercyKill(IFunctionHandler* pH, EntityId victimEntityId);              // 0x180B1AB10
    int RequestMercyKill(IFunctionHandler* pH, EntityId victimEntityId);            // 0x180B1AB1C
    int IsCarryingCorpse(IFunctionHandler* pH);                                     // 0x180B1AB28
    int CanGrabCorpse(IFunctionHandler* pH, EntityId victimEntityId);               // 0x180B1AB34
    int RequestGrabCorpse(IFunctionHandler* pH, EntityId victimEntityId);           // 0x180B1AB40
    int CanPutCorpse(IFunctionHandler* pH);                                         // 0x180B1AB54
    int RequestPutCorpse(IFunctionHandler* pH);                                     // 0x180B1AB60
    int CanLoot(IFunctionHandler* pH, EntityId victimEntityId);                     // 0x180B1AB6C
    int EquipInventoryItem(IFunctionHandler* pH, EntityId itemId);                  // 0x180B1AB78
    int UnequipInventoryItem(IFunctionHandler* pH, EntityId itemId);                // 0x180B1AB84
    int CheckInventoryRestrictions(IFunctionHandler* pH, const char* itemClassName); // 0x180B1AB90
    int CheckVirtualInventoryRestrictions(IFunctionHandler* pH, SmartScriptTable inventory, const char* itemClassName); // 0x180B1AB9C
    int OpenInventory(IFunctionHandler* pH, EntityId entityId, int mode, EntityId inventoryId, const char* filter); // 0x180B1AC08
    int EquipClothingPreset(IFunctionHandler* pH, const char* presetGuid);          // 0x180B1ABA8
    int GetInitialClothingPreset(IFunctionHandler* pH);                             // 0x180B1ABB4
    int AddDirt(IFunctionHandler* pH, float dirtDelta);                             // 0x1802ABCCC
    int CleanDirt(IFunctionHandler* pH, float maxCleaningEffect);                   // 0x1802AC508
    int AddBlood(IFunctionHandler* pH, const char* zoneName, float bloodDelta);     // 0x1810BD884
    int EquipWeaponPreset(IFunctionHandler* pH, const char* presetGuid);            // 0x180B1ABC0
    int GetInitialWeaponPreset(IFunctionHandler* pH);                               // 0x180B1ABCC
    int MakeLookAsActor(IFunctionHandler* pH, const char* sourceEntityGuid, bool inHand); // 0x180B1ABF0
    int MakeLookAsSoul(IFunctionHandler* pH, const char* sourceSoulGuid);           // 0x180B1ABFC
    int StartInteractiveActionByName(IFunctionHandler* pH, const char* ActionName, EntityId ObjectId, bool UpdateVisibility, float AnimSpeed); // 0x180B1ABD8
    int RequestItemExchange(IFunctionHandler* pH);                                  // 0x180B1ABE4
    int WashDirtAndBlood(IFunctionHandler* pH, float maxCleaningEffect);            // 0x1810EDE40
    int WashItems(IFunctionHandler* pH, float maxCleaningEffect);                   // 0x1810EDEB0
    int IsMoreDirty(IFunctionHandler* pH, float dirtLevel);                         // 0x1810D2C6C
};
static_assert(sizeof(C_ScriptBindActor) == 0x90);

} // namespace wh::entitymodule
