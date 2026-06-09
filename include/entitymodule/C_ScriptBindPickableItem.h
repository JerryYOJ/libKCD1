#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindPickableItem — entity script binding for pickable items
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindPickableItem@entitymodule@wh@@
// vtable: 0x1826c5eb0
// Constructor: sub_1810BA1BC
// Registration: sub_1810DFFFC
// Size: 0x88

namespace wh::entitymodule {

class C_ScriptBindPickableItem : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindPickableItem;
    void*                   m_pContext;          // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68
    void*                   m_pModule;          // +0x70
    Offsets::IScriptTable*  m_pEntityTable1;    // +0x78
    Offsets::IScriptTable*  m_pEntityTable2;    // +0x80

    // -- Direct Lua methods --
    // int SetExtensionActivation(IFunctionHandler* pH, const char* extension, bool bActivate); // 0x1810E5BC0
    // int SetExtensionParams(IFunctionHandler* pH, const char* extension, SmartScriptTable params); // 0x1810E5CF8
    // int GetExtensionParams(IFunctionHandler* pH, const char* extension, SmartScriptTable params); // 0x1810C8940
    // int GetStats(IFunctionHandler* pH);                                             // 0x1810CBAC4
    // int GetParams(IFunctionHandler* pH);                                            // 0x1810CA4B8
    // int Reset(IFunctionHandler* pH);                                                // 0x1810E2670
    // int Select(IFunctionHandler* pH, bool select);                                  // 0x1810E4314
    // int CanPickUp(IFunctionHandler* pH, EntityId userId);                           // 0x1810C0238
    // int CanUse(IFunctionHandler* pH, EntityId userId);                              // 0x1810C06AC
    // int IsMounted(IFunctionHandler* pH);                                            // 0x1810D2D9C
    // int PlayAnimation(IFunctionHandler* pH, const char* animationName);             // 0x1810DA7C4
    // int GetOwnerId(IFunctionHandler* pH);                                           // 0x1810CA46C
    // int StartUse(IFunctionHandler* pH, EntityId userId);                            // 0x1810E8F18
    // int StopUse(IFunctionHandler* pH, EntityId userId);                             // 0x1810E9410
    // int Use(IFunctionHandler* pH, EntityId userId);                                 // 0x1810EDB98
    // int IsUsed(IFunctionHandler* pH);                                               // 0x1810D3550
    // int GetMountedDir(IFunctionHandler* pH);                                        // 0x1810CA320
    // int GetMountedAngleLimits(IFunctionHandler* pH);                                // 0x1810CA2B0
    // int SetMountedAngleLimits(IFunctionHandler* pH, float min_pitch, float max_pitch, float yaw_range); // 0x180F32EF0 (noop)
    // int OnHit(IFunctionHandler* pH, SmartScriptTable hit);                          // 0x1810D80BC
    // int IsDestroyed(IFunctionHandler* pH);                                          // 0x1810D2868
    // int IsOversized(IFunctionHandler* pH);                                          // 0x1810D2F34
    // int IsFromShop(IFunctionHandler* pH);                                           // 0x1810D2918
    // int BelongsToDeadBody(IFunctionHandler* pH);                                    // 0x1810BF514 (noop)
    // int GetLinkedOwner(IFunctionHandler* pH);                                       // 0x1810C9E8C
    // int OnUsed(IFunctionHandler* pH, EntityId userId);                              // 0x1810D9798
    // int CanSteal(IFunctionHandler* pH, EntityId userId);                            // 0x1810C03EC
    // int OnSteal(IFunctionHandler* pH, EntityId userId);                             // 0x1810D9350
    // int GetHealth(IFunctionHandler* pH);                                            // 0x180F32EF0 (noop)
    // int GetMaxHealth(IFunctionHandler* pH);                                         // 0x180F32EF0 (noop)
    // int GetUIName(IFunctionHandler* pH);                                            // 0x1810CC234
    // int GetId(IFunctionHandler* pH);                                                // 0x1810C9914
    // int SetPhase(IFunctionHandler* pH, const char* phase);                          // 0x1810E6CF0
    // int SetPhaseById(IFunctionHandler* pH, int id);                                 // 0x1810E6DB4
    // int GetPhase(IFunctionHandler* pH);                                             // 0x1810CA5D8
    // int GetPhaseById(IFunctionHandler* pH);                                         // 0x1810CA64C
    // int SetIgnoreSaveFlag(IFunctionHandler* pH, bool doIgnoreSave);                 // 0x1810E6184
};
static_assert(sizeof(C_ScriptBindPickableItem) == 0x88);

} // namespace wh::entitymodule
