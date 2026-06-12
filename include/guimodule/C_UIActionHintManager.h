#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IInputEventListener.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "Offsets/vtables/IConsole.h"
#include "guimodule/SUIEventReceiverDispatcher.h"
#include "guimodule/SUIEventSenderDispatcher.h"

// -----------------------------------------------
// C_UIActionHintManager — HUD action hints / crosshair / input device ("ActionHints")
// -----------------------------------------------
// RTTI: .?AVC_UIActionHintManager@@   *** GLOBAL namespace — declared at
// global scope; file lives in guimodule/ for organization only. ***
// Constructor:     sub_18110CDDC
// Factory:         sub_18110D7BC  (SAutoRegUIEventSystem<C_UIActionHintManager>
//                  vtable 0x1822e6b90; allocates 0x1B0, returns this+0)
// GetName:         sub_1806FE670  -> "ActionHintManager"
// InitEventSystem: sub_18110DE2C  (IUIGameEventSystem slot [2])
// Size:            0x1B0
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] IUIGameEventSystem (: IUIPseudoRTTI)  (vtable 0x1826ccf70)
//   [+0x08] IInputEventListener                    (vtable 0x1826ccfb8)
// The ctor tail registers the IInputEventListener subobject (this+8) with an
// engine system via a gEnv slot vfunc+0x18 — the IDA gEnv struct labels that
// slot pStatoscope, but the receiver being an input listener makes this
// almost certainly IInput::AddEventListener. UNVERIFIED label.
//
// InitEventSystem (sub_18110DE2C):
//   - creates system->UI IUIEventSystem "ActionHints" (direction 1), registers
//     events 0..8 (see E_UIActionHintEvent);
//   - creates UI->system IUIEventSystem "ActionHints" (direction 0), registers
//     the receiver dispatcher as listener "C_UIActionHintManager" and one
//     function:
//       "GetActionButtons" ("GetActionsButtons") — "Sets list of key names
//        for all actions received."; params: ActionMapName(String, "Action
//        map name, if empty, it will search all maps"), Actions(String,
//        "List of actions which needs to be converted into key names."),
//        RequestId(String); handler sub_18110F054 (via sub_18110AE44).
//   - cvars: wh_ui_InputDevice (callback sub_18110F170, +0x128) and
//     wh_ui_PreferredInputDevice (callback sub_18110F1C8, +0x130); the
//     preferred-device callback is invoked once, then if wh_ui_InputDevice's
//     GetIVal() is 1, 2 or 4 it is applied via sub_18110FAF4(this, val).
//
// Ctor also loads "Libs/UI/ActionHintControls.xml" (sub_18110E5BC; control/
// device records for keyboard/xboxpad/pspad).

// Flash event ids on the "ActionHints" system->UI event system (key = enum
// value passed to the m_eventSender map insert in sub_18110DE2C; registration
// order was 0,2,1,3,5,4,6,7,8).
enum class E_UIActionHintEvent {
    OnActionShow            = 0x00,  // ActionId(Int), Control(String "Name of assigned input control (mouse1, xi_dpad_up,...)"), Hint(String "TextId for this hint.")
    OnActionHide            = 0x01,  // ActionId(Int)
    OnItemHintShow          = 0x02,  // Hint(String)
    OnPositionChange        = 0x03,  // Pos(Vec3 "Position")
    OnCrossPositionChange   = 0x04,  // Pos(Vec3)
    OnOutlinePositionChange = 0x05,  // Pos(Vec3)
    OnCrosshairStateChange  = 0x06,  // Flag(Int "Flag with states")
    OnSetActionsButtons     = 0x07,  // KeyNames(String "Delimited list of keys."), Actions(String), RequestId(String)
    OnInputDeviceChanged    = 0x08,  // InputDevice(Int "1=keyboard, 2=xboxpad, 4=ps4pad")
};

class C_UIActionHintManager
    : public Offsets::IUIGameEventSystem        // +0x00  (: IUIPseudoRTTI)
    , public Offsets::IInputEventListener       // +0x08
{
public:
    // Embedded dispatcher (0x28: vtable 0x1826cce18, mFunctionMap @+0x18,
    // m_pEventSystem @+0x28 = UI->system "ActionHints", m_pThis @+0x30).
    SUIEventReceiverDispatcher<C_UIActionHintManager>
                              m_eventRecvDispatcher;   // +0x10 .. 0x38

    SUIEventSenderDispatcher<E_UIActionHintEvent>
                              m_eventSender;           // +0x38  (map @0x38, m_pEventSystem @0x48)
    Offsets::IUIEventSystem*  m_pUIFunctions;          // +0x50  UI->system "ActionHints"
    Offsets::IUIEventSystem*  m_pUIEvents;             // +0x58  system->UI "ActionHints"

    uint32_t                  _unk60;                  // +0x60  ctor = 0
    char                      _pad64[0x4];             // +0x64

    // 14 pointer-sized elements zero-constructed via eh-vector-ctor
    // (sub_1804217C8(this+0x68, 8, 0xE, unknown_libname_19); the element ctor
    // just writes 0). Element type UNVERIFIED (pointers or handles).
    void*                     _unkArray68[0xE];        // +0x68 .. 0xD8

    // std::map with 0x40-byte nodes (sentinel sub_18073F5AC; payload 0x20 =
    // two pointer-sized fields). Key/value types UNVERIFIED — plausibly the
    // control->device data parsed from Libs/UI/ActionHintControls.xml.
    std::map<uint64_t, uint64_t> m_mapD8;              // +0xD8  {head @0xD8, size @0xE0}

    void*                     _unkE8;                  // +0xE8  result of S_GameContext+8 object vfunc +0xE0 (unidentified)
    uint64_t                  _unkF0;                  // +0xF0  ctor = 0
    float                     _unkF8;                  // +0xF8  ctor = 1.0f
    uint32_t                  _unkFC;                  // +0xFC  ctor = 0
    uint32_t                  _unk100;                 // +0x100 ctor = 0
    float                     _unk104;                 // +0x104 ctor = 1.0f
    uint32_t                  _unk108;                 // +0x108 ctor = 0
    uint32_t                  _unk10C;                 // +0x10C ctor = 0
    float                     _unk110;                 // +0x110 ctor = 1.0f
    char                      _pad114[0x4];            // +0x114 (not written by ctor)

    Offsets::ICVar*           m_pCVarWidth;                 // +0x118  "r_Width"
    Offsets::ICVar*           m_pCVarHeight;                // +0x120  "r_Height"
    Offsets::ICVar*           m_pCVarInputDevice;           // +0x128  "wh_ui_InputDevice" (on-change sub_18110F170)
    Offsets::ICVar*           m_pCVarPreferredInputDevice;  // +0x130  "wh_ui_PreferredInputDevice" (on-change sub_18110F1C8)

    CryStringT<char>          m_str138;                // +0x138  ctor = empty string
    char                      _unk140[0x70];           // +0x140  memset 0 by ctor (unidentified block)

    // Overrides (vtables inherited, not re-declared):
    //   IUIGameEventSystem::GetName          -> sub_1806FE670 ("ActionHintManager")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18110DE2C
    //   IInputEventListener::OnInputEvent    -> sub_1803E6900 (device-change detection)
};
static_assert(sizeof(C_UIActionHintManager) == 0x1B0);
