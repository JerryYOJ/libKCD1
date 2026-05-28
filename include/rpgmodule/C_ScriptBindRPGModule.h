#pragma once

#include "../crysystem/CScriptableBase.h"
#include "C_FactionScriptBind.h"
#include "C_LocationScriptBind.h"

// C_ScriptBindRPGModule — Lua "RPG" table (composite)
// RTTI: .?AVC_ScriptBindRPGModule@rpgmodule@wh@@  vtable: 0x1826d93c8
// Constructor: sub_1811BA368  Destructor: sub_1811BAC98
// Registration: sub_1811CC9E8  Size: 0x130

namespace wh::rpgmodule {
class C_ScriptBindRPGModule : public CScriptableBase {
public:
    void*                m_pScriptSystem;    // +0x60
    void*                m_pContext;          // +0x68
    C_FactionScriptBind  m_factionBind;      // +0x70  (0x60 bytes)
    C_LocationScriptBind m_locationBind;     // +0xD0  (0x60 bytes)

    // int GetHobbies(IFunctionHandler* pH);                                           // 0x1811C11C4
    // int _GetConstant(IFunctionHandler* pH, SmartScriptTable table, const char* key); // 0x1806B7A84
    // int UnlockRecipe(IFunctionHandler* pH, EntityId userId, const char* recipeId, const char* stepId); // 0x1811CFEAC
    // int GetLocations(IFunctionHandler* pH);                                         // 0x1811C1B38
    // int GetLocationById(IFunctionHandler* pH, int id);                              // 0x18027CDD0
    // int GetLocationByName(IFunctionHandler* pH, const char* name);                  // 0x1811C19D0
    // int GetFactions(IFunctionHandler* pH);                                          // 0x1811C0E6C
    // int GetFactionById(IFunctionHandler* pH, int factionId);                        // 0x1811C0D88
    // int IsPublicEnemy(IFunctionHandler* pH, const char* wuid);                      // 0x1811C5B90
    // int CaptionObjectUsed(IFunctionHandler* pH, EntityId objectEntityId, bool isDiscovered); // 0x1811BDFB4
    // int NotifyLevelXpGain(IFunctionHandler* pH, const char* skill);                 // 0x1811C6A4C
    // int AddStatXP(IFunctionHandler* pH);                                            // 0x1811BBD94
};
static_assert(sizeof(C_ScriptBindRPGModule) == 0x130);
} // namespace wh::rpgmodule
