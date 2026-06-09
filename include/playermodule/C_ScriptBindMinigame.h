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
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindMinigame;
    void* m_pOwner;  // +0x60

    // -- Virtual Lua methods --
    virtual int StartHerbGathering(IFunctionHandler* pH);        // 0x1812877D8
    virtual int StartLockPicking(IFunctionHandler* pH);          // 0x1812878A0
    virtual int StartHoleDigging(IFunctionHandler* pH);          // 0x18128783C
    virtual int StartDice(IFunctionHandler* pH);                 // 0x181287460
    virtual int StartDiceWithScore(IFunctionHandler* pH);        // 0x18128778C
    virtual int StartDiceByName(IFunctionHandler* pH);           // 0x181287664
    virtual int CloseInventory(IFunctionHandler* pH);            // 0x181283160

    // -- Direct Lua methods --
    // int BookTranscriptionNextPage(IFunctionHandler* pH);      // 0x181282FD0
    // int WasBookOpened(IFunctionHandler* pH);                  // 0x181287CCC
    // int GetBookStudyProgress(IFunctionHandler* pH);           // 0x1812839F8
};
static_assert(sizeof(C_ScriptBindMinigame) == 0x68);

} // namespace wh::playermodule
