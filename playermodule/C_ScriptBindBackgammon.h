#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindBackgammon — Lua "Backgammon" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindBackgammon@playermodule@wh@@
// vtable: 0x182312d20
// Constructor: sub_1812823D8
// Registration: sub_181285DF4
// Size: 0x68

namespace wh::playermodule {

class C_ScriptBindBackgammon : public CScriptableBase {
public:
    void* m_pOwner;  // +0x60

    // Lua methods
    int RequestGame(IFunctionHandler* pH, EntityId playerId, EntityId opponentId, EntityId boardId);  // 0x181286884
    int AcceptGame(IFunctionHandler* pH, EntityId playerId, EntityId opponentId);   // 0x181282DF4
    int OfferBet(IFunctionHandler* pH, EntityId playerId, int money);               // 0x181284B88
    int RollDice(IFunctionHandler* pH);              // 0x181286A48
    int RolledDice(IFunctionHandler* pH);            // 0x181286B7C
    int MoveChecker(IFunctionHandler* pH, EntityId playerId, int pointFrom, int pointTo);  // 0x181284AB8
    int EndGame(IFunctionHandler* pH);               // 0x181283790
};
static_assert(sizeof(C_ScriptBindBackgammon) == 0x68);

} // namespace wh::playermodule
