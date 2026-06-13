#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include <map>
// consolidated into IFlashUI.h
#include "Offsets/vtables/IPlayerProfileListener.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
// consolidated into IFlashUI.h
#include "Offsets/vtables/IConsole.h"
// consolidated into IFlashUI.h

// -----------------------------------------------
// CUISettings 鈥?game/graphics/input/sound settings UI ("UISettings")
// -----------------------------------------------
// RTTI: .?AVCUISettings@guimodule@wh@@  (GameSDK-derived name; 3 vtables:
// +0x00 0x1822ecf98, +0x08 0x1822ecfe0, +0x10 0x1822ecf50)
// Constructor:     sub_1811419C4
// Factory:         sub_181148298  (SAutoRegUIEventSystem<CUISettings>,
//                  allocates 0x260, returns this+0x10 鈥?the IUIGameEventSystem
//                  subobject CUIManager registers)
// GetName:         sub_1806FE830  -> "UISettings"
// InitEventSystem: sub_18114B4E8  (IUIGameEventSystem slot [2])
// Deleting dtor:   sub_181146BC8
// Size:            0x260
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] IUIModule               (8 slots; pFlashUI->RegisterModule(this,
//           "CUISettings") at the END of InitEventSystem, vtbl+0xA8)
//   [+0x08] IPlayerProfileListener  (3 slots; ctor tail registers via
//           PlayerProfileManager::AddListener(this+8, true) 鈥?manager from
//           S_GameContext+8 vfunc+0x130, AddListener = vfunc+0xF0)
//   [+0x10] IUIGameEventSystem (: IUIPseudoRTTI) (8 slots; here slots [6]/[7]
//           are NOT nops: [6] sub_181150D40 = LoadFromProfile impl,
//           [7] sub_1811559C0 = SaveToProfile impl 鈥?the
//           IPlayerProfileListener slots are this+8 re-dispatch thunks into
//           them; both walk profile attributes "controls_sensitivity",
//           "controls_invertMouse", ...)
//
// InitEventSystem (sub_18114B4E8):
//   - system->UI IUIEventSystem "Settings" (dir 1) -> m_pUIEvents; event ids
//     are explicit map keys -> E_UISettingsEvent below (id 3 is unused/gap).
//   - UI->system IUIEventSystem "Settings" (dir 0) -> m_pUIFunctions;
//     m_pEventRecvDispatcher->Init (sub_18114B000) registers it with listener
//     name "CUISettings"; 37 UI->system functions (SetGraphics,
//     SetGameSettings, GetCurr*, Reset*, LogoutUser, ...) 鈥?full table with
//     handler addresses in analysis/ui_infra/ui_elements_batch2.md.
//
// Constructor (sub_1811419C4) also:
//   - registers CVars: wh_ui_SubtitlesEnabled, wh_ui_BubblesEnabled,
//     wh_ui_TutorialsEnabled, wh_pl_LockPickingMode, tobii_*, wh_eula_accepted,
//     wh_ui_InputDevice, wh_ui_PreferredInputDevice (+ registers
//     tobii_debug_gaze and sys_resetStartupEulaAcceptedState without storing)
//   - caches engine CVars (r_Width .. wh_r_HDTextures; missing ones replaced
//     by dummy sub_181149884 + "UISetting uses undefined CVar: %s" log)
//   - resolves audio RTPC ids volume_music/sfx/voice/video (pSoundSystem
//     vtbl+0x40) and registers s_*Volume CVar change-callback sub_181154DF8
//     (ICVar vtbl+0x90)

namespace wh::guimodule {

// System->UI event ids on the "Settings" event system (explicit map-insert
// keys in sub_18114B4E8; 0x3 is not registered).
enum class E_UISettingsEvent {
    OnGraphicChanged             = 0x00,  // Resolution:Int, Quality:Int, FullScreen:Int(0/1/2=Window), VSync:Int, FPS:Int, Gamma:Float[-1;1], FOV:Float[60;75], HDTextures:Bool
    OnSoundChanged               = 0x01,  // Music:Float, SFx:Float, Video:Float, Voice:Float
    OnGameSettingsChanged        = 0x02,  // EnableSubtitles:Bool, EnableBubbles:Bool, LanguageID:Int, LanguageAudioID:Int, EnableTutorials:Bool
    // 0x03 unused
    OnAdvancedGraphicChanged     = 0x04,  // 13x Int detail levels (Object..Vegetation, MotionBlur)
    OnAdvancedGraphicChanged2    = 0x05,  // AntiAliasing:Int
    OnDistanceSettingsChanged    = 0x06,  // ObjectDistance:Int, LodRatio:Int, GrassDistance:Int
    OnResolutions                = 0x07,  // dyn Resolutions "(x1,y1,x2,y2,...)"
    OnResolutionItem             = 0x08,  // ResString:Str "(X x Y)", ID:Int
    OnLevelItem                  = 0x09,  // LevelLabel:Str "@ui_<level>", LevelName:Str
    OnLanguageItem               = 0x0A,  // UIName:Str "@ui_<language>", ID:Int
    OnLanguageAudioItem          = 0x0B,  // UIName:Str, ID:Int, NotAvailable:Bool
    OnInputSettingsChanged       = 0x0C,  // MouseSensitivity:Float, InvertMouse:Bool, InvertController:Bool, ControllerSensitivity:Float, InvertCombatMouse:Bool, PreferredInputDevice:Int, LockPickingMode:Int
    OnGetConnectedControllerType = 0x0D,  // ConnectedController:Int (0=none, 2=xboxpad, 4=ps4pad)
    OnEulaAcceptedStateChanged   = 0x0E,  // wh_eula_accepted:Bool
    OnTobiiSettingsChanged       = 0x0F,  // ExtendedView:Bool, LockTargetAtGaze:Bool, ExtendedViewSensitivity:Float, InteractAtGaze:Bool, CleanUI:Bool, TobiiEnabled:Bool
};

class CUISettings
    : public Offsets::IUIModule                  // +0x00
    , public Offsets::IPlayerProfileListener     // +0x08
    , public Offsets::IUIGameEventSystem         // +0x10  (: IUIPseudoRTTI)
{
public:
    void*    _unk18;                            // +0x18  NOT initialized in ctor
    void*    _unk20;                            // +0x20  "
    void*    _unk28;                            // +0x28  "
    void*    _unk30;                            // +0x30  "
    void*    _unk38;                            // +0x38  "
    void*    _unk40;                            // +0x40  "
    void*    _unk48;                            // +0x48  "

    // Heap-allocated receiver dispatcher (0x28: vptr + map + m_pEventSystem
    // @+0x18 + m_pThis @+0x20; ctor sub_181141988, vtable 0x1826d2860;
    // initialized via sub_18114B000(disp, es, this, "CUISettings")).
    SUIEventReceiverDispatcher<CUISettings>* m_pEventRecvDispatcher; // +0x50

    Offsets::IUIEventSystem* m_pUIFunctions;    // +0x58  "Settings" UI->system (dir 0)
    Offsets::IUIEventSystem* m_pUIEvents;       // +0x60  "Settings" system->UI (dir 1)

    // Sender event-id map (E_UISettingsEvent -> engine event id from
    // IUIEventSystem::RegisterEvent). Open-coded here (insert helper
    // sub_181129A08) instead of the usual SUIEventSenderDispatcher member 鈥?    // m_pUIEvents sits BEFORE the map, not after it.
    std::map<E_UISettingsEvent, unsigned int> m_eventMap; // +0x68

    void*    _unk78[0x15];                      // +0x78..0x118  NOT initialized in ctor

    Offsets::ICVar* m_pCVarSubtitlesEnabled;    // +0x120  wh_ui_SubtitlesEnabled (def 1)
    Offsets::ICVar* m_pCVarBubblesEnabled;      // +0x128  wh_ui_BubblesEnabled (def 1)
    Offsets::ICVar* m_pCVarTutorialsEnabled;    // +0x130  wh_ui_TutorialsEnabled (def 1)
    Offsets::ICVar* m_pCVarInputDevice;         // +0x138  wh_ui_InputDevice (1=kbd,2=xbox,4=ps4)
    Offsets::ICVar* m_pCVarPreferredInputDevice;// +0x140  wh_ui_PreferredInputDevice (0=auto)
    uint32_t m_unk148;                          // +0x148  = sub_18114A1A8() (semantic UNVERIFIED)
    uint32_t m_unk14C;                          // +0x14C  = sub_18114A15C() (semantic UNVERIFIED)
    Offsets::ICVar* m_pCVarLockPickingMode;     // +0x150  wh_pl_LockPickingMode (def 0)
    Offsets::ICVar* m_pCVarWidth;               // +0x158  r_Width
    Offsets::ICVar* m_pCVarHeight;              // +0x160  r_Height
    Offsets::ICVar* m_pCVarNativeWidth;         // +0x168  r_NativeWidth
    Offsets::ICVar* m_pCVarNativeHeight;        // +0x170  r_NativeHeight
    Offsets::ICVar* m_pCVarSysSpec;             // +0x178  sys_spec
    Offsets::ICVar* m_pCVarSysSpecFull;         // +0x180  sys_spec_full
    Offsets::ICVar* m_pCVarFullscreen;          // +0x188  r_Fullscreen
    Offsets::ICVar* m_pCVarFullscreenWindow;    // +0x190  r_FullscreenWindow
    Offsets::ICVar* m_pCVarShowFPS;             // +0x198  wh_ui_fps
    Offsets::ICVar* m_pCVarVSync;               // +0x1A0  r_VSync
    Offsets::ICVar* m_pCVarMaxFPS;              // +0x1A8  sys_MaxFPS
    Offsets::ICVar* m_pCVarAntialiasingMode;    // +0x1B0  r_AntialiasingMode
    Offsets::ICVar* m_pCVarHDTextures;          // +0x1B8  wh_r_HDTextures

    void*    _unk1C0;                           // +0x1C0  NOT initialized in ctor
    void*    _unk1C8;                           // +0x1C8  "
    uint8_t  m_flag1D0;                         // +0x1D0  ctor-init 0
    char     _pad1D1[0x3];                      // +0x1D1
    uint32_t m_audioIdMusic;                    // +0x1D4  volume_music RTPC id (pSoundSystem vtbl+0x40)
    uint32_t m_audioIdSfx;                      // +0x1D8  volume_sfx
    uint32_t m_audioIdVoice;                    // +0x1DC  volume_voice
    uint32_t m_audioIdVideo;                    // +0x1E0  volume_video
    char     _pad1E4[0x4];                      // +0x1E4
    Offsets::ICVar* m_pCVarMusicVolume;         // +0x1E8  s_MusicVolume (on-change sub_181154DF8)
    Offsets::ICVar* m_pCVarSoundVolume;         // +0x1F0  s_SoundVolume (on-change sub_181154DF8)
    Offsets::ICVar* m_pCVarVideoVolume;         // +0x1F8  s_VideoVolume (on-change sub_181154DF8)
    Offsets::ICVar* m_pCVarVoiceVolume;         // +0x200  s_VoiceVolume (on-change sub_181154DF8)
    Offsets::ICVar* m_pCVarTobiiExtView;        // +0x208  tobii_ext_view_on
    Offsets::ICVar* m_pCVarTobiiLockTarget;     // +0x210  tobii_lock_target_on
    Offsets::ICVar* m_pCVarTobiiEViewSens;      // +0x218  tobii_eview_sensitivity
    Offsets::ICVar* m_pCVarTobiiInteract;       // +0x220  tobii_interact_on
    Offsets::ICVar* m_pCVarTobiiCleanUI;        // +0x228  tobii_cleanui_on
    Offsets::ICVar* m_pCVarTobiiEnabled;        // +0x230  tobii_enabled
    Offsets::ICVar* m_pCVarEulaAccepted;        // +0x238  wh_eula_accepted
    void*    _unk240;                           // +0x240  ctor-init 0
    void*    _unk248;                           // +0x248  ctor-init 0
    void*    _unk250;                           // +0x250  ctor-init 0
    uint32_t m_currentResolutionId;             // +0x258  sub_18114AAEC(width,height,nativeW,nativeH)
    char     _pad25C[0x4];                      // +0x25C

    // Overrides (documented; vtables inherited, not re-declared here):
    //   IUIModule [0]                        -> deleting dtor sub_181146BC8
    //   IUIGameEventSystem::GetName          -> sub_1806FE830 ("UISettings")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18114B4E8
    //   IUIGameEventSystem [6]               -> sub_181150D40 (LoadFromProfile impl)
    //   IUIGameEventSystem [7]               -> sub_1811559C0 (SaveToProfile impl)
    //   IPlayerProfileListener::SaveToProfile/LoadFromProfile -> this+8
    //     re-dispatch thunks (sub_181155EC0 / sub_181150AD0)
};
static_assert(sizeof(CUISettings) == 0x260);

}  // namespace wh::guimodule
