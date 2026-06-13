#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "CryEngine/CryCommon/CryPodArray.h"
#include "CryEngine/CryCommon/smartptr.h"
#include "rpgmodule/C_POI.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
// consolidated into IFlashUI.h
#include "Offsets/vtables/IActionListener.h"
#include "Offsets/vtables/I_LocationListener.h"
#include "guimodule/SUIEventSenderBlock.h"
// consolidated into IFlashUI.h
#include "guimodule/C_UIMapCloudAtlas.h"
#include "guimodule/C_ScriptBindMap.h"
#include "guimodule/C_CompassMark.h"
#include "rpgmodule/I_POI.h"
#include "Offsets/vtables/IConsole.h"

// -----------------------------------------------
// C_UIMap 鈥?Map UI, fast travel, POI, checkpoint
// -----------------------------------------------
// RTTI: .?AVC_UIMap@guimodule@wh@@
// Constructor: sub_181128558
// Factory:     sub_18112ACE8 (allocates 0x4C8 bytes)
// Size:        0x4C8
//
// Singleton access:
//   Offsets::GetCUIManager()->GetUIMap()

namespace wh::guimodule {

// Element types of the C_UIMap spatial/POI hash maps below. The maps are stock
// MSVC std::unordered_map (the old "SSpatialBucketContainer" was a misRE — it is
// the 0x40-byte _Hash base, NOT a custom type; ctor sub_180F993F0 etc. = the
// _Hash init: max_load=1.0f@+0, list head@+8, bucket-vec@+0x18, mask@+0x30,
// maxidx@+0x38). The int32 key + the dispatch map's value are verified; these
// two value layouts are sized from the heap node (0x30 / 0x28) but their fields
// are NOT yet RE'd.
struct S_UIMapBucketValue20 { uint8_t _unverified[0x1C]; };   // node 0x30 → element 0x20
static_assert(sizeof(S_UIMapBucketValue20) == 0x1C);
struct S_UIMapBucketValue18 { uint8_t _unverified[0x14]; };   // node 0x28 → element 0x18
static_assert(sizeof(S_UIMapBucketValue18) == 0x14);

class C_UIMap
    : public Offsets::IUIGameEventSystem        // +0x00  (8 slots)
    , public Offsets::IUIElementEventListener    // +0x08  (8 slots; [0] OnUIEvent = sub_1811368C8)
    , public Offsets::IActionListener            // +0x10  (3 slots)
    , public Offsets::I_LocationListener         // +0x18  (9 slots)
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_UIMap;
    // C_FastTravel subscribes to these four signals (C_FastTravel::BindToUIMap
    // = sub_1812269BC): +0x20 → AnswerRandomEvent, +0x60 → ComputePath,
    // +0xA0 → StartTravelling, +0xE0 → Stop.
    SUIEventSenderBlock     m_signalRandomEventAnswer;      // +0x20
    SUIEventSenderBlock     m_signalFTPathComputed;         // +0x60
    SUIEventSenderBlock     m_signalFTStart;                // +0xA0
    SUIEventSenderBlock     m_signalFTStop;                 // +0xE0

    // Embedded dispatcher (0x28: vtable 0x1826d15d8, mFunctionMap @+0x128,
    // m_pEventSystem @+0x138, m_pThis @+0x140 鈥?set by Init; the former
    // m_unk138/m_unk140 members were this tail).
    SUIEventReceiverDispatcher<C_UIMap> m_eventRecvDispatcher; // +0x120 .. 0x148

    // +0x148/+0x150 look like a std::map (head sentinel from sub_180730B28 鈥?
    // which is a std::map sentinel-node allocator, NOT a "FlashEventDispatcher"
    // as previously labeled; likely a sender-dispatcher m_EventMap, pairing
    // UNVERIFIED).
    void*                   m_senderMapHead148;             // +0x148  std::map sentinel (sub_180730B28)
    uint64_t                m_senderMapSize150;             // +0x150
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
    // NOTE: previously mis-typed as ICVar* m_pCVar_DiscoveredMsgTimeout. The ctor
    // sub_181128558 writes the float below at +0x334, so this slot is only 4 bytes
    // — it cannot be an 8-byte CVar pointer. It is the discovered-message timeout
    // VALUE (type float/int not yet pinned).
    uint32_t                m_discoveredMsgTimeout;         // +0x330

    float                   m_fMovingMarkUpdateOffsetSq;    // +0x334  default 0.1

    // Flash UI-event dispatch table: hash(event name) → internal handler id.
    // Verified in OnUIEvent sub_1811368C8 (key@node+0x10, value dword@node+0x14,
    // hash sub_1804BF50C over 4 bytes) and ctor sub_181128558 (@+0x338).
    std::unordered_map<int32_t, uint32_t> m_uiEventDispatch;  // +0x338  (0x40)

    uint64_t                m_unk378;                       // +0x378  (uninit in ctor)
    char*                   m_szUnk380;                     // +0x380  CryString (StringHash sub_18028CEA4)

    // Spatial/POI hash maps (purpose UNVERIFIED; see value-type note above the class).
    std::unordered_map<int32_t, S_UIMapBucketValue20> m_unk388;  // +0x388  (0x40, node 0x30)
    std::unordered_map<int32_t, S_UIMapBucketValue20> m_unk3C8;  // +0x3C8  (0x40, node 0x30)

    Vec3                    m_unk408_focus;                 // +0x408  default copied from globals
                                                            //   (qword_1829DA4E0 + dword_1829DA4E8);
                                                            //   likely map focus / player position
    char                    _pad414[0x4];                   // +0x414

    C_ScriptBindMap         m_scriptBindMap;                // +0x418  (Lua "UIMap"; ctor sub_18110CD28)

    std::unordered_map<int32_t, S_UIMapBucketValue18> m_unk488;  // +0x488  (0x40, node 0x28)

    // --- Native methods (forwarded by RVA in C_UIMap.cpp) ---
    // Fires "OnForceStartFastTravel{Pos, PlayerId, IconType}" to Flash and
    // blocks the FT sim (BlockSources 0x80) — visual-only warp, no time
    // passage/encounters (= wh_pl_FastTravelTo). Caller must check FT idle.
    void ForceStartFastTravel(const Vec3& worldPos, int iconType = 0);  // sub_18112C494
};
static_assert(sizeof(C_UIMap) == 0x4C8);

}  // namespace wh::guimodule
