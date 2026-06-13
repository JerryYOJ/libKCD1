#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "guimodule/SUITypes.h"   // Vec3 (project-local, binary-exact)
#include "playermodule/I_RandomEventListener.h"
#include "playermodule/S_FTSlowdownTracker.h"
#include "playermodule/S_PendingEventPrompt.h"
#include "playermodule/S_FTEventState.h"
#include "framework/I_ReadinessDebuggable.h"
#include "framework/S_GameTimer.h"
#include "guimodule/SUIEventSenderBlock.h"

// -----------------------------------------------
// C_FastTravel — fast travel simulation controller
// -----------------------------------------------
// RTTI: .?AVC_FastTravel@playermodule@wh@@
// sizeof = 0x188 (allocation in C_PlayerModule ctor sub_1812816E4 @0x181281B05)
// Constructor:  sub_18121BF58 (zero-inits pointers/vector/timer; flags &= 0xF0;
//               +0xCC..+0xE7 and timer+0x4 stay uninitialized — written only
//               during travel)
// Registration: sub_181220D6C (preloads random-event options, creates the
//               S_FTSlowdownTracker at +0x140, registers perception callback
//               sub_180B1B03C; sub_18121C03C is the TRACKER's ctor, not FT::Init)
// BindToUIMap:  sub_1812269BC (stores +0x90/+0x98/+0xA0, subscribes the
//               handlers below to the map's SUIEventSenderBlock signals, and
//               writes this+8 — the I_ReadinessDebuggable subobject — into the
//               AfterFastTravel fader's +0x18)
// Update:       sub_1802113E4 (per-frame from C_PlayerModule::Update
//               sub_18020FE50; ICF cold-split into 0x180B8Bxxx/0x180B8Cxxx —
//               lerps m_path.back() into m_currentPos, SetWorldTM's
//               m_pTravelActor, ticks the pending prompt + stop timer)
// ComputePath:  sub_18121E04C (xgenai S_PathFindingRequest → m_path, REVERSED)
// Inherits:
//   [+0x00] I_RandomEventListener (wh::playermodule)  primary vtable 0x1826dd700
//   [+0x08] I_ReadinessDebuggable (wh)                2 slots (vtable 0x1826dd728)
//
// Accessed via S_GameContext::GetInstance()->m_pPlayerModule->m_pFastTravel
//   (S_GameContext+0xE8 = C_PlayerModule* VERIFIED; C_PlayerModule+0xB0 VERIFIED;
//    the stored pointer is the true object base — no this-adjustment anywhere
//    in the FT function set)
//
// Signal wiring (sub_1812269BC) — C_UIMap sender block → C_FastTravel handler:
//   map+0x20 → AnswerRandomEvent  (sub_181226864)
//   map+0x60 → SetDestination     (sub_181226B24: dest + actor/speed + ComputePath)
//   map+0xA0 → StartTravelling    (via thunk sub_181226E6C)
//   map+0xE0 → Stop               (sub_181226EA8)
//
// The "travel to a destination" entry point is NOT on this class: the
// destination request goes through C_UIMap::RequestFastTravelTo (sub_18112C494,
// what wh_pl_FastTravelTo calls after resolving `x y z -or- entityname`). That
// fires the system→UI event "OnForceStartFastTravel{Pos, PlayerId, IconType}";
// the Flash map then requests the path and auto-fires the UI→system
// "StartFastTravel" function, which reaches StartTravelling via map+0xA0.
//
// Debug CVars (registered blockwise in sub_1812851F0 from base 0x1836E4980):
//   wh_pl_FastTravelDebug   (dword_1836E4990) nonzero = visualized travel —
//                           skip-time CVar overrides and menu-mode switch bypassed
//   wh_pl_FastTravelEnabled (dword_1836E4994) ComputePath mode: 0 = skip
//                           pathfind, 2 = require start in map-discovery list

namespace wh { class C_ReadinessObserver; }
namespace wh::guimodule {
    class C_UIMap;
    class C_UIMenuEvents;
    class C_UIHUDElements;
    class C_FaderController;
    template<typename T> class C_BasicFader;
}
namespace wh::entitymodule { class C_Actor; class C_Player; }

namespace wh::playermodule {

// Fast-travel start validation / result codes. Names from the game's own
// code→message table registered in sub_181220D6C ("@ui_dlg_ft*" strings).
enum class E_FastTravelResult : uint32_t {
    Ok              = 0,
    NotAllowed      = 1,    // @ui_dlg_ftcant_travel_now (blocked / not permitted)
    NoPathFromHere  = 2,    // @ui_dlg_ftcant_travel_from_here (interior start / path < 2 points)
    InCombat        = 3,    // @ui_dlg_ftcombat
    Hungry          = 4,    // @ui_dlg_fthungry
    Poisoned        = 5,    // @ui_dlg_ftpoison
    Bleeding        = 6,    // @ui_dlg_ftbleeding
    TimePaused      = 7,    // @ui_dlg_ftpaused_time
    Trespassing     = 8,    // @ui_dlg_fttrespasing
    Fatigued        = 9,    // @ui_dlg_ftfatigue
    Encumbered      = 0xA,  // @ui_dlg_ftencumbered
};

class C_FastTravel
    : public I_RandomEventListener      // +0x00  (3 slots; FT overrides: [1] refresh
                                        //         pending prompt, [2] stop-if-travelling)
    , public I_ReadinessDebuggable      // +0x08  (2 slots)
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FastTravel;

    virtual ~C_FastTravel() = default;  // primary vtable [3] (sub_18121DE9C)

    guimodule::SUIEventSenderBlock m_signalStarted;  // +0x10  fired by start-success helper sub_181223610
    guimodule::SUIEventSenderBlock m_signalStopped;  // +0x50  fired by finish finalizer sub_181223138

    guimodule::C_UIMap*         m_pUIMap;            // +0x90  "UIMap" element: path polyline, travel result, event dialogs
    guimodule::C_UIMenuEvents*  m_pMenuEvents;       // +0x98  CUIManager+0x18; menu-mode switch on start/stop (sub_181147B18)
    guimodule::C_UIHUDElements* m_pHUDElements;      // +0xA0  "UIHelpBar" (stored as element-8); shows event-answer info

    bool m_isTravelling : 1;                         // +0xA8.0  set StartTravelling / cleared Stop
    bool m_timeSkipActive : 1;                       // +0xA8.1  engine skip-time engaged (CVar overrides via sub_180555010)
    bool m_startInInterior : 1;                      // +0xA8.2  start pos in 'interior' location → CanStart = NoPathFromHere
    bool m_forcedTravel : 1;                         // +0xA8.3  SetDestination bool arg; CanStart short-circuits Ok
                                                     //          bits 4-7: uninitialized (ctor only does &= 0xF0)
    char _padA9[0x7];                                // +0xA9

    entitymodule::C_Player* m_pPlayer;               // +0xB0  local player, cached at SetDestination
    entitymodule::C_Actor*  m_pTravelActor;          // +0xB8  moved actor: mount if riding else player; nulled on Stop
    Vec3 m_destination;                              // +0xC0  travel goal (world); pathfind target
    Vec3 m_currentPos;                               // +0xCC  simulated position (= m_path.back(), lerped per tick;
                                                     //        getter sub_1806FFAE0 bound as position provider)
    Vec3 m_moveDir;                                  // +0xD8  normalized horizontal heading; z forced to 0 each tick
    char _padE4[0x4];                                // +0xE4
    std::vector<Vec3> m_path;                        // +0xE8  waypoints REVERSED (back = next, front = destination);
                                                     //        Update pop_backs consumed segments; done when < 2 left
    float m_remainingDistance;                       // +0x100 metres left; -= dt * m_travelSpeed per tick
    float m_travelSpeed;                             // +0x104 m/s, from the soul's C_RPGMovement gait entry (mount if riding)
    S_PendingEventPrompt* m_pPendingEventPrompt;     // +0x108 displayed encounter prompt (owned, nullable; auto-answers at 0)
    C_ReadinessObserver* m_pAfterFastTravelObserver; // +0x110 "AfterFastTravel" (0x70 bytes, owned); its byte +0x68 is the
                                                     //        second clause of IsFastTravelling (post-arrival streaming/fade)
    guimodule::C_BasicFader<guimodule::C_FaderController>* m_pAfterFastTravelFader; // +0x118 owned 0x20-byte fader;
                                                     //        its +0x18 = this+8, Stop schedules the post-stop continuation on it
    framework::S_GameTimer m_scheduledStopTimer;     // +0x120 ScheduleStopAtEvent timer (ctor flags=0x11; Update: Armed+expired → Stop)
    S_FTSlowdownTracker* m_pSlowdownTracker;         // +0x140 owned 0x90-byte tracker; speed factor read while m_timeSkipActive
    std::unordered_map<int, S_FTEventState> m_eventStates; // +0x148 per-random-event-id marks (fired-mode dedup + stop-here)

    // IsFastTravelling = m_isTravelling || m_pAfterFastTravelObserver->active(+0x68)
    bool IsFastTravelling() const;                          // sub_1803DBE28 (forwarded)

    // --- Native methods (RVA-forwarded in C_FastTravel.cpp) ---
    void Stop();                                            // sub_181226EA8 (Lua FastTravel.Stop)
    void SetDestination(const Vec3& worldPos,               // sub_181226B24 (UIMap signal +0x60 handler): stores dest,
                        bool forced);                       //   caches actor+speed, ComputePath; no-op while travelling
    E_FastTravelResult CanStartTravelling();                // sub_18121E530 (m_forcedTravel skips all checks)
    E_FastTravelResult StartTravelling();                   // sub_181226C54 (UIMap signal +0xA0 handler;
                                                            //   takes save lock 5 — saving disabled while travelling)
    bool AnswerRandomEvent(uint32_t eventId, uint32_t optionId); // sub_181226864 (wh_pl_RandomEventAnswer)
    void ScheduleStopAtEvent(float seconds, int eventId);   // sub_1812271B0 (Lua FastTravel.StopToEvent)

    // Full programmatic journey (time acceleration + random encounters):
    //   SetDestination(pos, true); StartTravelling();

    // Visual-only debug warp via the map UI (= wh_pl_FastTravelTo): teleports
    // without time passage or encounters — the sim is pre-blocked (BlockSources
    // 0x80) so the Flash echo fails validation.
    bool DebugTravelTo(const Vec3& worldPos);
};
static_assert(sizeof(C_FastTravel) == 0x188);

}  // namespace wh::playermodule
