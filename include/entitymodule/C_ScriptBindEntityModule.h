#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindEntityModule — Lua "EntityModule" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindEntityModule@entitymodule@wh@@
// vtable: 0x1822e4528
// Constructor: sub_1810B93B4
// Registration: sub_1810DE6C8
// Size: 0x68

namespace wh::entitymodule {

class C_ScriptBindEntityModule : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindEntityModule;
    void* m_pEntityModule;  // +0x60

    // -- Direct Lua methods --
    // int AcquireInventory(IFunctionHandler* pH);                                     // 0x1810BD6F0
    // int LoadInventoryFromDB(IFunctionHandler* pH);                                  // 0x1810D49BC
    // int ReleaseInventory(IFunctionHandler* pH, EntityId ownerEntityId);             // 0x1810E0730
    // int IsInventoryReadOnly(IFunctionHandler* pH, int inventoryId);                 // 0x1810D2A48
    // int GetInventoryOwner(IFunctionHandler* pH, int inventoryId);                   // 0x1810C9964
    // int CanUseInventory(IFunctionHandler* pH, int inventoryId);                     // 0x1810C0724
    // int EnableLayerProfile(IFunctionHandler* pH, const char* profileName, bool enable); // 0x1810C4CD0
    // int SequenceEntitiesCopyVisual(IFunctionHandler* pH, const char* sequenceName); // 0x1810E46C8
    // int AnimCharCopyVisual(IFunctionHandler* pH, EntityId entityId);                // 0x1810BE9BC
    // int AnimCharSetBodyBlood(IFunctionHandler* pH, EntityId entityId, const char* zone, float blood); // 0x1810BE9F4
    // int WillSleepingOnThisBedSave(IFunctionHandler* pH, EntityId entityId);         // 0x1810EDFDC
    // int GetEntityScriptMisc(IFunctionHandler* pH, EntityId entityId);               // 0x18027B160
    // int GetSlotHand(IFunctionHandler* pH, EntityId slotEntityId);                   // 0x18027B308
    // int GetSlotItemClassId(IFunctionHandler* pH, EntityId slotEntityId);            // 0x1810CAE5C
    // int GetSlotSpawnOnStart(IFunctionHandler* pH, EntityId slotEntityId);           // 0x1810CAFA0
    // int MakeParticleEffectActive(IFunctionHandler* pH, EntityId particleEffectEntityId); // 0x1810D5788
    // int MakeParticleEffectIdle(IFunctionHandler* pH, EntityId particleEffectEntityId);   // 0x1810D581C
};
static_assert(sizeof(C_ScriptBindEntityModule) == 0x68);

} // namespace wh::entitymodule
