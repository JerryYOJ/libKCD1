#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindCalendar — Lua "Calendar" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindCalendar@rpgmodule@wh@@
// vtable: 0x182306bf8
// Constructor: sub_1811BA2E8
// Registration: sub_1811CC634
// Size: 0x68

namespace wh::rpgmodule {

class C_ScriptBindCalendar : public CScriptableBase {
public:
    void* m_pCalendar;  // +0x60

    // Lua methods (14)
    int SetWorldTimeRatio(IFunctionHandler* pH, float worldTimeRatio);     // 0x1811CF660
    int GetWorldTimeRatio(IFunctionHandler* pH);                           // 0x1811C43C0
    int SetWorldTimePaused(IFunctionHandler* pH, bool worldTimePaused);    // 0x1811CF628
    int IsWorldTimePaused(IFunctionHandler* pH);                           // 0x1811C5E74
    int SetWorldTime(IFunctionHandler* pH, float worldTime);               // 0x1811CF5EC
    int GetWorldTime(IFunctionHandler* pH);                                // 0x1811C4380
    int GetWorldDay(IFunctionHandler* pH);                                 // 0x1806E3AB4
    int GetWorldDayOfWeek(IFunctionHandler* pH);                           // 0x1811C4324
    int GetWorldHourOfDay(IFunctionHandler* pH);                           // 0x1802B6E58
    int GetGameTime(IFunctionHandler* pH);                                 // 0x1811C1000
    int SetFakeTimeOfDay(IFunctionHandler* pH, float fakeHour);            // 0x1811CF220
    int UnfakeTimeOfDay(IFunctionHandler* pH);                             // 0x1811CFE84
    int IsFakedTimeOfDay(IFunctionHandler* pH);                            // 0x1811C598C
    int IsNightTimeOfDay(IFunctionHandler* pH);                            // 0x1811C5B68
};
static_assert(sizeof(C_ScriptBindCalendar) == 0x68);

} // namespace wh::rpgmodule
