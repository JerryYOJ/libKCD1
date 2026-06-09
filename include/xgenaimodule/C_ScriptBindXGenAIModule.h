#pragma once
#include "../crysystem/CScriptableBase.h"

// C_ScriptBindXGenAIModule — Lua "XGenAIModule" table
// RTTI: .?AVC_ScriptBindXGenAIModule@xgenaimodule@wh@@  vtable: 0x18239d8f8
// Constructor: sub_18166BF04  Registration: sub_1816725C0  Size: 0x78

namespace wh::xgenaimodule {
class C_ScriptBindXGenAIModule : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindXGenAIModule;
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68
    void*                   m_pUnk70;           // +0x70
    // int OnSpawn(IFunctionHandler* pH);                          // 0x180F32EF0 (noop)
    // int OnDestroy(IFunctionHandler* pH);                        // 0x180F32EF0 (noop)
    // int OnPropertyChange(IFunctionHandler* pH);                 // 0x180F32EF0 (noop)
    // int OnStart(IFunctionHandler* pH);                          // 0x180F32EF0 (noop)
    // int SendMessageToEntity(IFunctionHandler* pH);              // 0x181672CF4
    // int SendMessageToEntityData(IFunctionHandler* pH);          // 0x181672DD4
    // int GetEntityByWUID(IFunctionHandler* pH);                  // 0x1802B5E8C
    // int GetEntityIdByWUID(IFunctionHandler* pH);                // 0x1802B6EB4
    // int RemoveDaycyclePatch(IFunctionHandler* pH);              // 0x181672B5C
    // int SpawnPerceptibleVolume(IFunctionHandler* pH);           // 0x181673714
    // int SpawnPerceptibleVolumeOnWUID(IFunctionHandler* pH);     // 0x1816738F8
    // int DespawnPerceptibleVolume(IFunctionHandler* pH);         // 0x18166D998
    // int IsPointInAreaWithLabelWUID(IFunctionHandler* pH);       // 0x1816710E0
    // int LootBegin(IFunctionHandler* pH);                        // 0x181671480
    // int LootInventoryBegin(IFunctionHandler* pH);               // 0x181671540
    // int LootEnd(IFunctionHandler* pH);                          // 0x1816714E0
    // int GetWuidDebugString(IFunctionHandler* pH);               // 0x18166FB74
    // int GetMyWUID(IFunctionHandler* pH);                        // 0x18166FA60
    // int GetBrainVariable(IFunctionHandler* pH);                 // 0x1802B5FF0
    // int SetBrainVariable(IFunctionHandler* pH);                 // 0x1802B6280
    // int MakeTableFromType(IFunctionHandler* pH);                // 0x1805518C8
    // int _GetDataVariable(IFunctionHandler* pH);                 // 0x1802B60B4
    // int _SetDataVariable(IFunctionHandler* pH);                 // 0x1806584F4
    // int ProduceSound(IFunctionHandler* pH);                     // 0x1816720B8
    // int ProduceSoundWUID(IFunctionHandler* pH);                 // 0x181672284
    // int AddRecordedIntellectForFaderProfiling(IFunctionHandler* pH); // 0x180F32EF0 (noop)
    // int PlaceToSlotFromInventory(IFunctionHandler* pH);         // 0x181671F48
    // int SetPlayerDogMode(IFunctionHandler* pH);                 // 0x180B1B17C
};
static_assert(sizeof(C_ScriptBindXGenAIModule) == 0x78);
} // namespace wh::xgenaimodule
