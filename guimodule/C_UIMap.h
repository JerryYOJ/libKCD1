#pragma once

#include <cstdint>
#include <vector>
#include "CryEngine/CryCommon/CryPodArray.h"
#include "CryEngine/CryCommon/smartptr.h"
#include "rpgmodule/C_POI.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IUIElementEventListener.h"
#include "Offsets/vtables/IActionListener.h"
#include "Offsets/vtables/I_LocationListener.h"
#include "guimodule/SUIEventSenderBlock.h"
#include "guimodule/SUIEventReceiverDispatcher.h"
#include "guimodule/C_UIMapCloudAtlas.h"
#include "guimodule/C_ScriptBindMap.h"
#include "guimodule/SSpatialBucketContainer.h"
#include "guimodule/C_CompassMark.h"
#include "rpgmodule/I_POI.h"
#include "Offsets/vtables/IConsole.h"

// -----------------------------------------------
// C_UIMap — Map UI, fast travel, POI, checkpoint
// -----------------------------------------------
// RTTI: .?AVC_UIMap@guimodule@wh@@
// Constructor: sub_181128558
// Factory:     sub_18112ACE8 (allocates 0x4C8 bytes)
// Size:        0x4C8
//
// Singleton access:
//   Offsets::GetCUIManager()->GetUIMap()

namespace wh::guimodule {

class C_UIMap
    : public Offsets::IUIGameEventSystem        // +0x00  (8 slots)
    , public Offsets::IUIElementEventListener    // +0x08  (20 slots)
    , public Offsets::IActionListener            // +0x10  (3 slots)
    , public Offsets::I_LocationListener         // +0x18  (9 slots)
{
public:
    SUIEventSenderBlock     m_eventSender0;                 // +0x20
    SUIEventSenderBlock     m_eventSender1;                 // +0x60
    SUIEventSenderBlock     m_eventSender2;                 // +0xA0
    SUIEventSenderBlock     m_eventSender3;                 // +0xE0

    SUIEventReceiverDispatcher<C_UIMap> m_eventRecvDispatcher; // +0x120

    uint64_t                m_unk138;                       // +0x138
    uint64_t                m_unk140;                       // +0x140
    void*                   m_pFlashEventDispatcher;        // +0x148  C++→Flash event dispatch (sub_180730B28)
    uint64_t                m_unk150;                       // +0x150
    void*                   m_pFTSimulation;                // +0x158  FT simulation object
    char                    _pad160[0x8];                   // +0x160
    uint64_t                m_unk168;                       // +0x168
    void*                   m_pEventListenerObj;            // +0x170  (0x10 bytes, sub_1807304D0)
    uint64_t                m_unk178;                       // +0x178
    std::shared_ptr<C_CompassMark> m_pCheckpoint;             // +0x180  checkpoint/flag marker, null if none
    uint64_t                m_unk190;                       // +0x190
    uint8_t                 m_stateFlags;                   // +0x198  bit 4 (0x10) = FT in progress
    char                    _pad199[0x7];                   // +0x199
    char*                   m_szCurrentMapName;             // +0x1A0  CryString
    uint32_t                m_unk1A8;                       // +0x1A8
    char                    _pad1AC[0x4];                   // +0x1AC

    // --- Map legend display entries (loaded from mapLegend.xml) ---
    uint64_t                m_unk1B0;                       // +0x1B0
    uint64_t                m_unk1B8;                       // +0x1B8
    uint64_t                m_unk1C0;                       // +0x1C0
    uint64_t                m_unk1C8;                       // +0x1C8
    uint64_t                m_unk1D0;                       // +0x1D0
    uint64_t                m_unk1D8;                       // +0x1D8

    // --- POI list (PodArray + extra field) ---
    PodArray<_smart_ptr<rpgmodule::C_POI>> m_poiList;       // +0x1E0  (16 bytes: ptr + count + allocCount)
    uint64_t                m_unk1F0;                       // +0x1F0

    // --- FT-eligible POI list ---
    std::vector<rpgmodule::I_POI*> m_ftPoints;              // +0x1F8  (24 bytes)

    uint64_t                m_unk210;                       // +0x210
    uint64_t                m_unk218;                       // +0x218
    uint64_t                m_unk220;                       // +0x220

    static constexpr int kMaxPOITypes = 0x4B;               // 75 POI types
    bool                    m_ftEligibleTypes[kMaxPOITypes]; // +0x228  true = type is FT-eligible (init all true)
    char                    _pad273[0x5];                   // +0x273

    uint64_t                m_unk278;                       // +0x278
    uint64_t                m_unk280;                       // +0x280
    uint64_t                m_unk288;                       // +0x288

    C_UIMapCloudAtlas       m_cloudAtlas;                   // +0x290

    char*                   m_szUnk2A8;                     // +0x2A8  CryString
    uint64_t                m_unk2B0;                       // +0x2B0
    uint32_t                m_unk2B8;                       // +0x2B8
    char                    _pad2BC[0x4];                   // +0x2BC

    Offsets::ICVar*                  m_pCVar_ScaleStep;              // +0x2C0
    Offsets::ICVar*                  m_pCVar_MoveMapMult;            // +0x2C8
    Offsets::ICVar*                  m_pCVar_MoveCursorMult;         // +0x2D0
    Offsets::ICVar*                  m_pCVar_StickDeadZone;          // +0x2D8
    Offsets::ICVar*                  m_pCVar_MoveMapSens;            // +0x2E0
    Offsets::ICVar*                  m_pCVar_MoveCursorSens;         // +0x2E8
    Offsets::ICVar*                  m_pCVar_MapBlendMult;           // +0x2F0
    Offsets::ICVar*                  m_pCVar_MapScaleMult;           // +0x2F8
    Offsets::ICVar*                  m_pCVar_MapAccMult;             // +0x300
    Offsets::ICVar*                  m_pCVar_CursorAccMult;          // +0x308
    Offsets::ICVar*                  m_pCVar_DiscoverAll;            // +0x310
    Offsets::ICVar*                  m_pCVar_EnableZoom;             // +0x318
    Offsets::ICVar*                  m_pCVar_ShowFastTravelPoints;   // +0x320
    Offsets::ICVar*                  m_pCVar_ShowOnlyDiscoveredPOI;  // +0x328
    Offsets::ICVar*                  m_pCVar_DiscoveredMsgTimeout;   // +0x330

    float                   m_fMovingMarkUpdateOffsetSq;    // +0x334  default 0.1
    char                    _pad338[0x4];                   // +0x338  alignment

    SSpatialBucketContainer m_eventBuckets;                 // +0x340
    char                    _pad370[0x18];                  // +0x370

    char*                   m_szUnk388;                     // +0x388  CryString

    SSpatialBucketContainer m_nearbyPOIs0;                  // +0x390
    char                    _pad3C0[0x10];                  // +0x3C0
    SSpatialBucketContainer m_nearbyPOIs1;                  // +0x3D0
    char                    _pad400[0x10];                  // +0x400

    float                   m_fPlayerX;                     // +0x410
    float                   m_fPlayerY;                     // +0x414
    float                   m_fPlayerZ;                     // +0x418
    char                    _pad41C[0x4];                   // +0x41C

    C_ScriptBindMap         m_scriptBindMap;                // +0x420

    SSpatialBucketContainer m_unk490;                       // +0x490
    char                    _pad4C0[0x8];                   // +0x4C0
};
static_assert(sizeof(C_UIMap) == 0x4C8);

}  // namespace wh::guimodule
