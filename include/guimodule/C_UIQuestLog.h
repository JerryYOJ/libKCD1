#pragma once

#include <cstdint>
#include "Offsets/vtables/I_QuestUIController.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "guimodule/SUIEventSenderDispatcher.h"
#include "guimodule/SUIEventReceiverDispatcher.h"

// -----------------------------------------------
// C_UIQuestLog — quest log UI bridge ("UIQuestLog")
// -----------------------------------------------
// RTTI: .?AVC_UIQuestLog@guimodule@wh@@  (2 vtables: +0x00 0x1826d2950,
// +0x08 0x1826d2998)
// Constructor:     sub_181143BCC
// Factory:         sub_18114848C  (SAutoRegUIEventSystem<C_UIQuestLog>
//                  vtable 0x1822ed180; allocates 0x60, returns this+8 — the
//                  IUIGameEventSystem subobject CUIManager registers)
// GetName:         sub_1806FE850  -> "UIQuestLog"
// InitEventSystem: sub_18114E254  (IUIGameEventSystem slot [2])
// Deleting dtor:   sub_181146D0C  (= I_QuestUIController [0])
// Size:            0x60
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::questmodule::I_QuestUIController  (8 slots)
//   [+0x08] IUIGameEventSystem (: IUIPseudoRTTI)
//
// InitEventSystem (sub_18114E254):
//   1. system->UI IUIEventSystem "QuestLog" (dir 1) -> m_pUIEvents; events =
//      E_UIQuestLogEvent below.
//   2. UI->system IUIEventSystem "Quest" (dir 0) -> m_pUIFunctions;
//      m_eventRecvDispatcher.Init(es, this, "C_UIQuestLog") and registers:
//        "RequestQuests"      "Request all quests (force to call QuestAdded
//                              for each quest)"                 -> sub_1811524F0
//        "RequestQuestInfoEx" "Request extended info for the quest"
//                              QuestName:Str                    -> sub_181152488
//        "RequestQuestDiary"  "Request diary text for the quest"
//                              QuestName:Str                    -> sub_181152420
//        "CancelQuest"        "Request canceling the quest"
//                              QuestName:Str                    -> sub_18115170C
//        "TrackQuest"         "Request tracking quest objective on map and on
//                              compass" QuestName:Str, StartTracking:Int
//                              "0 - stop tracking/previw, 1-x tracking ui id"
//                                                               -> sub_181154BE4
//        "SetQuestRead"       "Set quest was read" QuestName:Str, Read:Bool
//                                                               -> sub_181153800
// Full param tables: analysis/ui_infra/ui_elements_batch2.md.

namespace wh::guimodule {

// System->UI events on the "QuestLog" event system (ids are the literal
// map-insert keys in sub_18114E254).
enum class E_UIQuestLogEvent {
    OnQuestInfo          = 0x00,  // Name:Str, UIName:Str, Type:Int, State:Int, Index:Int, Tracking:Int (0=none), OnMap:Bool, Read:Bool, RepeatCnt:Int
    OnQuestInfoEx        = 0x01,  // QuestName:Str + dyn "QuestInfoEx" (short desc, objectives)
    OnQuestDiary         = 0x02,  // QuestName:Str + dyn "QuestDiary" (detailed desc, completed steps)
    OnQuestCanceled      = 0x03,  // QuestName:Str
    OnQuestObjectTracked = 0x04,  // EntityId:Int, Tracking:Bool (true=start)
};

class C_UIQuestLog
    : public Offsets::I_QuestUIController       // +0x00
    , public Offsets::IUIGameEventSystem        // +0x08  (: IUIPseudoRTTI)
{
public:
    // Embedded dispatcher (0x28: vtable 0x1826d27b8, mFunctionMap @+0x18,
    // m_pEventSystem @+0x28 = "Quest" UI->system, m_pThis @+0x30).
    SUIEventReceiverDispatcher<C_UIQuestLog>
                             m_eventRecvDispatcher; // +0x10 .. 0x38

    SUIEventSenderDispatcher<E_UIQuestLogEvent>
                             m_eventSender;     // +0x38  (map @0x38, m_pEventSystem @0x48)
    Offsets::IUIEventSystem* m_pUIEvents;       // +0x50  "QuestLog" system->UI (same object as m_eventSender.m_pEventSystem)
    Offsets::IUIEventSystem* m_pUIFunctions;    // +0x58  "Quest" UI->system (ctor-init 0; same object as m_eventRecvDispatcher.m_pEventSystem)

    // Overrides (vtables inherited, not re-declared):
    //   I_QuestUIController [0]              -> deleting dtor sub_181146D0C
    //   IUIGameEventSystem::GetName          -> sub_1806FE850 ("UIQuestLog")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18114E254
};
static_assert(sizeof(C_UIQuestLog) == 0x60);

}  // namespace wh::guimodule
