#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBind_Dice — Lua "Dice" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBind_Dice@playermodule@wh@@
// vtable: 0x182312cf8
// Constructor: sub_1812825D8
// Registration: sub_1812862B4
// Size: 0x68

namespace wh::playermodule {

class C_ScriptBind_Dice : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBind_Dice;
    void* m_pOwner;  // +0x60

    // -- Direct Lua methods --
    // int RollDie(IFunctionHandler* pH);                                                // 0x181286B0C
    // int HoldDie(IFunctionHandler* pH, EntityId userId, EntityId dieEntityId, int dieNumber, bool hold); // 0x181284424
    // int ToggleHoldDie(IFunctionHandler* pH);                                          // 0x1812879FC
    // int OverrideNextThrow(IFunctionHandler* pH, int playerIndex, SmartScriptTable dieValues); // 0x181284D9C
    // int SetAdvantage(IFunctionHandler* pH, int playerIndex, float advantage);         // 0x180F32EF0 (noop)
    // int SetAIDifficulty(IFunctionHandler* pH, float difficulty);                      // 0x181286E28
    // int SetAIRiskTaking(IFunctionHandler* pH, float riskTaking);                      // 0x181286F08
    // int SetScore(IFunctionHandler* pH, int player1Score, int player2Score);           // 0x1812871F0
};
static_assert(sizeof(C_ScriptBind_Dice) == 0x68);

} // namespace wh::playermodule
