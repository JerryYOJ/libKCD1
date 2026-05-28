#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindQuest — Lua "QuestSystem" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindQuest@questmodule@wh@@
// vtable: 0x182314ef8
// Constructor: sub_18129BC38
// Registration: sub_1812A0678
// Size: 0x70

namespace wh::questmodule {

class C_ScriptBindQuest : public CScriptableBase {
public:
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68

    // Lua methods (27)
    int StartQuest(IFunctionHandler* pH);                               // 0x1812A282C
    int UserEnteredTrigger(IFunctionHandler* pH, const char* placeAssetId, EntityId user); // 0x1812A2A90
    int StartObjective(IFunctionHandler* pH);                           // 0x1812A2648
    int CompleteObjective(IFunctionHandler* pH);                        // 0x18129CEC0
    int TriggerCondition(IFunctionHandler* pH);                         // 0x1812A29FC
    int IsQuestActivated(IFunctionHandler* pH);                         // 0x18129EB0C
    int IsQuestAvailable(IFunctionHandler* pH);                         // 0x18129EB5C
    int AreQuestVIPsAlive(IFunctionHandler* pH);                        // 0x18129C3C8
    int IsQuestStarted(IFunctionHandler* pH);                           // 0x18129ECD8
    int IsQuestCompleted(IFunctionHandler* pH);                         // 0x18129EBFC
    int IsQuestCanceled(IFunctionHandler* pH);                          // 0x18129EBAC
    int IsQuestUnchanged(IFunctionHandler* pH);                         // 0x18129ED7C
    int IsObjectiveStarted(IFunctionHandler* pH);                       // 0x18129E730
    int IsObjectiveUnchanged(IFunctionHandler* pH);                     // 0x18129E9B8
    int IsObjectiveCompleted(IFunctionHandler* pH);                     // 0x18129E608
    int IsObjectiveCanceled(IFunctionHandler* pH);                      // 0x18129E4E0
    int IsObjectiveTrackedCompleted(IFunctionHandler* pH);              // 0x18129E890
    int GetActiveObjectives(IFunctionHandler* pH);                      // 0x18129D90C
    int CanRepeatQuest(IFunctionHandler* pH);                           // 0x18129C7F0
    int CancelQuest(IFunctionHandler* pH, const char* questName, int flag); // 0x18129CB68
    int CancelObjective(IFunctionHandler* pH);                          // 0x18129CA04
    int ResetQuest(IFunctionHandler* pH);                               // 0x1812A19F8
    int ActivateQuest(IFunctionHandler* pH);                            // 0x18129C2B8
    int DeactivateQuest(IFunctionHandler* pH);                          // 0x18129D1C8
    int RegisterQuestEntity(IFunctionHandler* pH, EntityId entityId);   // 0x180F32EF0 (stub)
    int OpenInventory(IFunctionHandler* pH);                            // 0x1812A02E8
    int GetObjectiveExpCoeff(IFunctionHandler* pH);                     // 0x18129DDE4
};
static_assert(sizeof(C_ScriptBindQuest) == 0x70);

} // namespace wh::questmodule
