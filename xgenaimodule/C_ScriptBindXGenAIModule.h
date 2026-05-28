#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindXGenAIModule — Lua "XGenAIModule" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindXGenAIModule@xgenaimodule@wh@@
// vtable: 0x18239d8f8
// Constructor: sub_18166BF04
// Registration: sub_1816725C0
// Size: 0x78

namespace wh::xgenaimodule {

class C_ScriptBindXGenAIModule : public CScriptableBase {
public:
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68
    void*                   m_pUnk70;           // +0x70

    // Lua methods (28)
    int OnSpawn(IFunctionHandler* pH, EntityId entityId, const char* assetName);    // 0x180F32EF0 (stub)
    int OnDestroy(IFunctionHandler* pH, EntityId entityId);                         // 0x180F32EF0 (stub)
    int OnPropertyChange(IFunctionHandler* pH, EntityId entityId);                  // 0x180F32EF0 (stub)
    int OnStart(IFunctionHandler* pH, bool enable);                                 // 0x180F32EF0 (stub)
    int SendMessageToEntity(IFunctionHandler* pH, const char* wuid, int type, float value); // 0x181672CF4
    int SendMessageToEntityData(IFunctionHandler* pH, const char* wuid, int type, SmartScriptTable data); // 0x181672DD4
    int GetEntityByWUID(IFunctionHandler* pH, const char* wuid);                    // 0x1802B5E8C
    int GetEntityIdByWUID(IFunctionHandler* pH, const char* wuid);                  // 0x1802B6EB4
    int RemoveDaycyclePatch(IFunctionHandler* pH, const char* wuid, int handle);    // 0x181672B5C
    int SpawnPerceptibleVolume(IFunctionHandler* pH, Vec3 pos, float radius, float height, float visibility, float conspicuousness, const char* label, float timer, float worldTime); // 0x181673714
    int SpawnPerceptibleVolumeOnWUID(IFunctionHandler* pH, const char* wuid, float radius, float height, float visibility, float conspicuousness, const char* label, float timer, float worldTime); // 0x1816738F8
    int DespawnPerceptibleVolume(IFunctionHandler* pH, const char* wuid);           // 0x18166D998
    int IsPointInAreaWithLabelWUID(IFunctionHandler* pH, const char* wuid, const char* label); // 0x1816710E0
    int LootBegin(IFunctionHandler* pH, const char* wuid);                          // 0x181671480
    int LootInventoryBegin(IFunctionHandler* pH, const char* wuid);                 // 0x181671540
    int LootEnd(IFunctionHandler* pH, const char* wuid);                            // 0x1816714E0
    int GetWuidDebugString(IFunctionHandler* pH, const char* wuid);                 // 0x18166FB74
    int GetMyWUID(IFunctionHandler* pH, SmartScriptTable table);                    // 0x18166FA60
    int GetBrainVariable(IFunctionHandler* pH, const char* wuid, const char* name); // 0x1802B5FF0
    int SetBrainVariable(IFunctionHandler* pH, const char* wuid, const char* name, SmartScriptTable data); // 0x1802B6280
    int MakeTableFromType(IFunctionHandler* pH, const char* typeName);              // 0x1805518C8
    int _GetDataVariable(IFunctionHandler* pH, const char* name);                   // 0x1802B60B4
    int _SetDataVariable(IFunctionHandler* pH, const char* name);                   // 0x1806584F4
    int ProduceSound(IFunctionHandler* pH, int type, Vec3 pos, float mult);         // 0x1816720B8
    int ProduceSoundWUID(IFunctionHandler* pH, int type, const char* wuid, float mult); // 0x181672284
    int AddRecordedIntellectForFaderProfiling(IFunctionHandler* pH, const char* wuid); // 0x180F32EF0 (stub)
    int PlaceToSlotFromInventory(IFunctionHandler* pH, const char* itemWuid, const char* slotWuid); // 0x181671F48
    int SetPlayerDogMode(IFunctionHandler* pH, const char* sMode);                  // 0x180B1B17C
};
static_assert(sizeof(C_ScriptBindXGenAIModule) == 0x78);

} // namespace wh::xgenaimodule
