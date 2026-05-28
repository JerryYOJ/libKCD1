#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindMinigame — Lua "Minigame" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindMinigame@playermodule@wh@@
// vtable: 0x182312be0
// Constructor: sub_181282458
// Registration: sub_181285EFC
// Size: 0x68

namespace wh::playermodule {

class C_ScriptBindMinigame : public CScriptableBase {
public:
    void* m_pOwner;  // +0x60

    // Lua methods
    int StartHerbGathering(IFunctionHandler* pH, int areaId);                                   // 0x180B1B17C
    int StartLockPicking(IFunctionHandler* pH, EntityId entityId);                              // 0x180B1AB4C
    int StartHoleDigging(IFunctionHandler* pH, EntityId entityId);                              // 0x180B1AC14
    int BookTranscriptionNextPage(IFunctionHandler* pH);                                        // 0x181282FD0
    int StartDice(IFunctionHandler* pH, EntityId playerId, EntityId tableId, EntityId opponentId); // 0x180B1AC1C
    int StartDiceWithScore(IFunctionHandler* pH, int targetScore);                              // 0x180B1AC24
    int StartDiceByName(IFunctionHandler* pH, const char* entityName);                          // 0x180B1AC2C
    int WasBookOpened(IFunctionHandler* pH, const char* documentGuidStr);                       // 0x181287CCC
    int GetBookStudyProgress(IFunctionHandler* pH, const char* documentGuidStr);                // 0x1812839F8
    int CloseInventory(IFunctionHandler* pH);                                                   // 0x180B1AD1C
};
static_assert(sizeof(C_ScriptBindMinigame) == 0x68);

} // namespace wh::playermodule
