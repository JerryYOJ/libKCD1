#pragma once
#include <cstdint>
#include <cstddef>
#include "Offsets/vtables/IEntitySystem.h"
#include "Offsets/vtables/IConsole.h"
#include "Offsets/vtables/ILog.h"
#include "Offsets/vtables/IScriptSystem.h"
#include "Offsets/vtables/ITimer.h"
#include "Offsets/vtables/IInput.h"
#include "Offsets/vtables/IFlashUI.h"
#include "Offsets/vtables/I3DEngine.h"
#include "Offsets/vtables/I3DEngine.h"

// -----------------------------------------------
// SSystemGlobalEnvironment — KCD1 binary layout
// -----------------------------------------------
// Address: WHGame+0x29D16B8 (confirmed in .data, IDA labels as gEnv)
//
// Every +0x08 slot from +0x00 to +0x198 was checked for xrefs.
// Slots marked CONFIRMED were verified from CSystem ctor, caller analysis, or IDA decompiler.
// Slots marked SDK are named from the CryEngine SDK header (ISystem.h:808).
// Slots marked NO XREFS have zero references in the binary.
//
// ANOMALIES vs SDK:
//   +0x20: SDK=pScriptSystem → NO XREFS (dead slot, pScriptSystem is at +0x30 instead)
//   +0x30: SDK=pFlowSystem → binary uses as IScriptSystem (SetGlobalValue, CreateTable, etc.)
//   +0x108: SDK=pRenderer → UC KCD2 says pRenderer is at +0x110 (shifted by 8, WH may have added a member)
//
// SIZE: Unknown for KCD1. UC KCD2 says 0x1C0 but this is KCD1.
//       Last xref'd slot is +0x198. No xrefs from +0x1A0 onward.

struct SSystemGlobalEnvironment {
    void*                       pDialogSystem;          // +0x00  SDK (no xrefs)
    void*                       p3DEngine_DEAD;         // +0x08  DEAD SDK slot — ALWAYS NULL in KCD (every reader guards it). Real engine = Offsets::Get3DEngine() (static C3DEngine* @ 0x3785BC0). C3DEngine vtable 0x1827160a8; GetTerrainElevation[87]/0x2B8
    void*                       pNetwork;               // +0x10  SDK (has xrefs)
    void*                       pLobby;                 // +0x18  SDK (has xrefs)
    void*                       _unk20;                 // +0x20  SDK=pScriptSystem — NO XREFS, dead slot
    void*                       pPhysicalWorld;         // +0x28  CONFIRMED: physics vtable calls
    Offsets::IScriptSystem*     pScriptSystem;          // +0x30  CONFIRMED: IScriptSystem ops (SDK calls this pFlowSystem)
    void*                       _unk38_view;            // +0x38  SDK=pInput but WRONG: vtable+0x78 returns a
                                                        //         camera/view object (sub_1802B9A24) — NOT IInput. Identity TBD.
    void*                       pMusicSystem;           // +0x40  SDK (has xrefs)
    Offsets::IInput*            pInput;                 // +0x48  VERIFIED IInput (SDK/IDA mislabel this pStatoscope):
                                                        //         input listeners register here via AddEventListener[3]/
                                                        //         RemoveEventListener[4] (C_UIActionHintManager ctor/dtor)
    void*                       pAnimationGraphSystem;  // +0x50  SDK (has xrefs)
    void*                       pCryPak;                // +0x58  SDK (has xrefs)
    void*                       pFileChangeMonitor;     // +0x60  SDK (no xrefs)
    void*                       pProfileLogSystem;      // +0x68  SDK (no xrefs)
    void*                       pParticleManager;       // +0x70  SDK (has xrefs)
    void*                       pOpticsManager;         // +0x78  SDK (has xrefs)
    void*                       pFrameProfileSystem;    // +0x80  CONFIRMED: CSystem ctor writes this+0xB18
    Offsets::ITimer*            pTimer;                 // +0x88  CONFIRMED: CSystem ctor writes this+0x28
    void*                       pCryFont;               // +0x90  SDK (has xrefs)
    void*                       pGame;                  // +0x98  CONFIRMED: IGame* (C_Game)
    void*                       pLocalMemoryUsage;      // +0xA0  SDK (has xrefs)
    Offsets::IEntitySystem*     pEntitySystem;          // +0xA8  CONFIRMED: soul lookup, qword_1829D1760
    Offsets::IConsole*          pConsole;               // +0xB0  CONFIRMED: CVar access, qword_1829D1768
    void*                       pTelemetrySystem;       // +0xB8  SDK (no xrefs)
    void*                       pSoundSystem;           // +0xC0  SDK (has xrefs)
    void*                       pSystem;                // +0xC8  CONFIRMED: CSystem writes self here
    void*                       pCharacterManager;      // +0xD0  SDK (has xrefs)
    void*                       pAISystem;              // +0xD8  SDK (has xrefs)
    Offsets::ILog*              pLog;                   // +0xE0  CONFIRMED: sub_18040EF74 calls vtable[1]
    void*                       pCodeCheckpointMgr;     // +0xE8  SDK (has xrefs)
    void*                       pMovieSystem;           // +0xF0  SDK (has xrefs)
    void*                       pNameTable;             // +0xF8  CONFIRMED: CSystem ctor writes this+0xB88
    void*                       pVisualLog;             // +0x100 SDK (no xrefs)
    void*                       _unk108;                // +0x108 has xrefs — SDK=pRenderer but UC KCD2 says +0x110
    void*                       _unk110;                // +0x110 has xrefs — pRenderer per UC KCD2
    void*                       _unk118;                // +0x118 has xrefs
    void*                       _unk120;                // +0x120 has xrefs
    void*                       _unk128;                // +0x128 has xrefs
    Offsets::IFlashUI*          pFlashUI;               // +0x130 CONFIRMED: CFlashUI singleton; GetUIElement("hud") sub_18111B2C8, CreateEventSystem callers (UI elements' InitEventSystem), RegisterModule (sub-controllers)
    void*                       _unk138;                // +0x138 has xrefs
    void*                       _unk140;                // +0x140 has xrefs
    void*                       _unk148;                // +0x148 no xrefs
    void*                       _unk150;                // +0x150 has xrefs
    void*                       _unk158;                // +0x158 has xrefs
    void*                       _unk160;                // +0x160 has xrefs
    void*                       _unk168;                // +0x168 has xrefs
    void*                       _unk170;                // +0x170 has xrefs (scalar? mMainThreadId?)
    void*                       _unk178;                // +0x178 no xrefs
    void*                       _unk180;                // +0x180 has xrefs (used in EntitySystem::Update)
    void*                       _unk188;                // +0x188 has xrefs
    void*                       _unk190;                // +0x190 no xrefs
    void*                       _unk198;                // +0x198 has xrefs — last xref'd slot
    void*                       _unk1A0;                // +0x1A0 no xrefs
    void*                       _unk1A8;                // +0x1A8 no xrefs
    void*                       _unk1B0;                // +0x1B0 no xrefs
    void*                       _unk1B8;                // +0x1B8 no xrefs

    static SSystemGlobalEnvironment* GetInstance();      // Offsets.cpp
};
