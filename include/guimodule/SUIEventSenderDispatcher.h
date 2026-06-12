#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/IUIEventSystem.h"

// -----------------------------------------------
// SUIEventSenderDispatcher<TEventType> — CryEngine template (system->UI send)
// -----------------------------------------------
// SDK: CryCommon/IFlashUI.h:2092. GLOBAL namespace (binary RTTI inside
// std::function wrappers: ...SUIEventSenderDispatcher@W4E_UIHUDElementEvent@
// C_UIHUDElements@guimodule@wh@@@@...). Maps a game-side event enum to the
// engine event id returned by IUIEventSystem::RegisterEvent, then sends
// events through m_pEventSystem. NO vtable (plain struct, unlike
// SUIEventReceiverDispatcher).
//
// Binary evidence (pattern identical in C_UICombatListener sub_18110CF6C,
// C_UIEventLog factory sub_18111A9D8, C_UIActionHintManager sub_18110CDDC,
// C_UIInventoryElements sub_181128494, C_UIKeybinds sub_1811284FC):
//   ctor:  m_EventMap.head = sub_180730B28() (sentinel node, node size 0x28
//          = 0x20 header + pair<int,uint>), m_EventMap.size = 0,
//          m_pEventSystem = nullptr
//   InitEventSystem: m_pEventSystem = pFlashUI->CreateEventSystem(name,
//          eEST_SYSTEM_TO_UI); per event: map-insert enum key
//          (sub_180E318C4), node+0x20 = m_pEventSystem->RegisterEvent(desc).
//
// Size: 0x18 (std::map 0x10 + IUIEventSystem* 8); _ITERATOR_DEBUG_LEVEL=0.

template<typename TEventType>
struct SUIEventSenderDispatcher {
    std::map<TEventType, unsigned int> m_EventMap;     // +0x00  game enum -> engine event id
    Offsets::IUIEventSystem*           m_pEventSystem; // +0x10
};

static_assert(sizeof(SUIEventSenderDispatcher<int>) == 0x18);
