#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindSoul — entity script binding for souls (RPG stats/skills/perks)
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindSoul@rpgmodule@wh@@
// vtable: 0x182306a58
// Constructor: sub_1811BA498
// Registration: sub_1811CCC44
// Size: 0x78

namespace wh::rpgmodule {

class C_ScriptBindSoul : public CScriptableBase {
public:
    void* m_pScriptSystem;    // +0x60
    void* m_pEntitySystem;    // +0x68
    void* m_pContext;          // +0x70

    // -- Direct Lua methods --
    // int GetId(IFunctionHandler* pH);                                                // 0x1806C2768
    // int GetState(IFunctionHandler* pH, const char* state);                          // 0x1802ACB48
    // int SetState(IFunctionHandler* pH, const char* state, float value);             // 0x1802ACAD8
    // int GetStatLevel(IFunctionHandler* pH, const char* stat);                       // 0x1811C3EE4
    // int GetStatProgress(IFunctionHandler* pH, const char* stat);                    // 0x1811C3F00
    // int AdvanceToStatLevel(IFunctionHandler* pH, const char* stat, int level);      // 0x1811BBF90
    // int AddStatXP(IFunctionHandler* pH, const char* stat, float xp);               // 0x1811BBE60
    // int GetNextLevelStatXP(IFunctionHandler* pH, const char* stat, int level);      // 0x1811C2894
    // int GetDerivedStat(IFunctionHandler* pH, const char* derivedStat);              // 0x1811C0C7C
    // int HaveSkill(IFunctionHandler* pH, const char* skill);                         // 0x1811C46B0
    // int GetSkillLevel(IFunctionHandler* pH, const char* skill);                     // 0x1811C3E04
    // int GetSkillProgress(IFunctionHandler* pH, const char* skill);                  // 0x1811C3E40
    // int HasAbility(IFunctionHandler* pH, const char* ability);                      // 0x1811C44CC
    // int AdvanceToSkillLevel(IFunctionHandler* pH, const char* skill, int level);    // 0x1811BBE70
    // int AddSkillXP(IFunctionHandler* pH, const char* skill, float xp);             // 0x1811BBD84
    // int GetNextLevelSkillXP(IFunctionHandler* pH, const char* skill, int level);    // 0x1811C280C
    // int AddBuff(IFunctionHandler* pH, const char* buff_id);                         // 0x1811BB6C0
    // int RemoveBuff(IFunctionHandler* pH, int buff_instance);                        // 0x1811CDAC8
    // int RemoveAllBuffsByGuid(IFunctionHandler* pH, const char* buff_guid);          // 0x1811CD8EC
    // int AddPerk(IFunctionHandler* pH, const char* perk_id);                         // 0x1811BBC38
    // int RemovePerk(IFunctionHandler* pH, const char* perk_id);                      // 0x1811CDE60
    // int AddMetaRole(IFunctionHandler* pH, const char* id);                          // 0x1811BBBA0
    // int RemoveMetaRole(IFunctionHandler* pH, const char* id);                       // 0x1811CDE20
    // int AddMetaRoleByName(IFunctionHandler* pH, const char* name);                  // 0x18056D6F0
    // int RemoveMetaRoleByName(IFunctionHandler* pH, const char* name);               // 0x18056D8B0
    // int DealDamage(IFunctionHandler* pH, float stamina, float health);              // 0x1811BE8F4
    // int HealBleeding(IFunctionHandler* pH, float heal, int bodyPartId);             // 0x1811C4720
    // int AddInjury(IFunctionHandler* pH, const char* injury, const char* bodyPartName); // 0x1811BBA64
    // int ModifyPlayerReputation(IFunctionHandler* pH, const char* repChangeName, bool propagateToFaction); // 0x1811C6950
    // int GetRelationship(IFunctionHandler* pH, const char* otherSoulWuid);           // 0x1802B5360
    // int CalculateBarterDominance(IFunctionHandler* pH, const char* shopkeeperSoulWuid); // 0x1811BDBC4
    // int IsInCombatDanger(IFunctionHandler* pH);                                     // 0x1806A720C
    // int GetNameStringId(IFunctionHandler* pH);                                      // 0x1811C27C8
    // int GetReadCaptionObjectText(IFunctionHandler* pH);                             // 0x1811C3450
    // int IsPublicEnemy(IFunctionHandler* pH);                                        // 0x1811C5C18
    // int IsDialogRestricted(IFunctionHandler* pH);                                   // 0x18056D534
    // int RestrictDialog(IFunctionHandler* pH, bool bRestrict);                       // 0x1802B51D8
    // int HasRoleByName(IFunctionHandler* pH, const char* roleName);                  // 0x1811C4574
    // int GetHobbies(IFunctionHandler* pH);                                           // 0x1806F0604
    // int GetRoles(IFunctionHandler* pH);                                             // 0x1811C3874
    // int GetMetaRoles(IFunctionHandler* pH);                                         // 0x1811C237C
    // int HasMetaRoleByName(IFunctionHandler* pH, const char* metaroleName);          // 0x1806D2360
    // int GetSchedule(IFunctionHandler* pH);                                          // 0x1811C391C
    // int GetSocialClass(IFunctionHandler* pH);                                       // 0x1802B5270
    // int GetArchetype(IFunctionHandler* pH);                                         // 0x1802B686C
    // int GetGender(IFunctionHandler* pH);                                            // 0x1806D9C7C
    // int GetGatherMult(IFunctionHandler* pH);                                        // 0x1811C1040
    // int GetFactionID(IFunctionHandler* pH);                                         // 0x18064D714
    // int GetSuperfaction(IFunctionHandler* pH);                                      // 0x1806EB968
    // int GetPerceivedSuperfaction(IFunctionHandler* pH);                              // 0x1811C2A64
    // int OnPerkUsed(IFunctionHandler* pH, const char* perkDefId);                    // 0x1811C8C58
    // int OverrideHead(IFunctionHandler* pH, const char* headGuid);                   // 0x1811CB5A8
    // int OverrideHair(IFunctionHandler* pH, const char* hairGuid);                   // 0x1811CB59C
    // int OnCompanionEvent(IFunctionHandler* pH, const char* companion, int eventType); // 0x1811C72BC
};
static_assert(sizeof(C_ScriptBindSoul) == 0x78);

} // namespace wh::rpgmodule
