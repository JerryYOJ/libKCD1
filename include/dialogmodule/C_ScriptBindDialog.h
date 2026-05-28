#pragma once
#include "../crysystem/CScriptableBase.h"

// C_ScriptBindDialog — Lua "DialogModule" table
// RTTI: .?AVC_ScriptBindDialog@dialogmodule@wh@@  vtable: 0x1822d4a18
// Constructor: sub_180FE0E38  Registration: sub_180FE35B4  Size: 0x78

namespace wh::dialogmodule {
class C_ScriptBindDialog : public CScriptableBase {
public:
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68
    void*                   m_pDialogModule;    // +0x70
    // int ForceDialog(IFunctionHandler* pH, EntityId speakerId, EntityId listenerId);             // 0x180FE2200
    // int StartMonolog(IFunctionHandler* pH, EntityId speakerId, const char* topicId);            // 0x180FE2264
    // int SetAIInteractionState(IFunctionHandler* pH, const char* soulid, int state);             // 0x180FE22C4
    // int IsSequenceAvailable(IFunctionHandler* pH);                                              // 0x180FE2BEC
    // int IsSequenceUsed(IFunctionHandler* pH);                                                   // 0x180FE2C9C
    // int ResetSequenceTimer(IFunctionHandler* pH);                                               // 0x180FE3864
    // int IsDialogInterruptibleByPlayer(IFunctionHandler* pH);                                    // 0x18069B534
    // int IsSoulInDialog(IFunctionHandler* pH);                                                   // 0x180FE2D28
    // int SetPlayerInteractiveState(IFunctionHandler* pH, const char* stateName);                 // 0x180FE3984
    // int AnalyzeRequest(IFunctionHandler* pH);                                                   // 0x180FE1760
    // int ResetHaggle(IFunctionHandler* pH);                                                      // 0x180FE3804
    // int ResetHaveDialogCache(IFunctionHandler* pH);                                             // 0x180FE383C
};
static_assert(sizeof(C_ScriptBindDialog) == 0x78);
} // namespace wh::dialogmodule
