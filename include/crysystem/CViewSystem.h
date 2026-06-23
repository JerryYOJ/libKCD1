#pragma once
#include <cstdint>
#include <cstddef>
#include "Offsets/vtables/IViewSystem.h"
#include "Offsets/vtables/IMovieUser.h"
#include "Offsets/vtables/ILevelSystemListener.h"
#include "crysystem/SCameraParams.h"

// -----------------------------------------------
// CViewSystem — stock CryEngine/CryAction view system.
// -----------------------------------------------
// RTTI: .?AVCViewSystem@@ (bare-named -> stock CryEngine, not Warhorse). It owns
// the CView map and the active CCamera, and implements IMovieUser so CMovieSystem
// can drive the cut-scene camera through it (SetActiveCamera). Warhorse grafted
// the cinematic-aspect (letterbox) feature onto this path; the class itself is stock.
//
// Bases (RTTI base-class array, mdisp-confirmed):
//   [+0x00] IViewSystem            (primary)
//   [+0x08] IMovieUser             <- cut-scene letterbox hook target (SetActiveCamera)
//   [+0x10] ILevelSystemListener
//
// PARTIAL field map: only the cut-scene/letterbox-relevant members are pinned,
// recovered from the IMovieUser methods (whose `this` == CViewSystem + 0x08:
// SetActiveCamera sub_181ABA1E8, BeginCutScene sub_181A99304). Full size not pinned.

struct CViewSystem
    : Offsets::IViewSystem            // +0x00  primary
    , Offsets::IMovieUser             // +0x08  SetActiveCamera lives here (vtable @ VTABLE[1])
    , Offsets::ILevelSystemListener   // +0x10
{
    inline static constexpr auto VTABLE = Offsets::VTABLE_CViewSystem;  // [0]=primary [1]=IMovieUser [2]=ILevelSystemListener

    uint8_t  _pad18[0x48 - 0x18];     // +0x18
    void**   m_listenersBegin;        // +0x48  IViewSystemListener* vector (begin/end/capacity)
    void**   m_listenersEnd;          // +0x50
    void**   m_listenersCapacity;     // +0x58
    uint8_t  _unk60[0x70 - 0x60];     // +0x60  active/previous view-id + flags (not individually pinned)
    int32_t  m_cutSceneCount;         // +0x70  IsPlayingCutScene counter (BeginCutScene ++ / EndCutScene --)
    uint8_t  _unk74[0x94 - 0x74];     // +0x74
    float    m_defaultWidth;          // +0x94  default/screen width  (SetActiveCamera dim fallback)
    float    m_defaultHeight;         // +0x98  default/screen height
};

static_assert(offsetof(CViewSystem, m_listenersBegin) == 0x48, "CViewSystem.m_listenersBegin @ +0x48");
static_assert(offsetof(CViewSystem, m_cutSceneCount)  == 0x70, "CViewSystem.m_cutSceneCount @ +0x70");
static_assert(offsetof(CViewSystem, m_defaultWidth)   == 0x94, "CViewSystem.m_defaultWidth @ +0x94");
static_assert(offsetof(CViewSystem, m_defaultHeight)  == 0x98, "CViewSystem.m_defaultHeight @ +0x98");
