#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../CryEngine/CryCommon/BaseTypes.h"            // uint64 (needed by CryGUID.h)
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h" // CryGUID map keys
#include "../framework/WUID.h"                           // wh::framework::WUID map key/value
#include "../framework/HashPrimitives.h"                 // wh::shared::S_DefaultHash (CryGUID/WUID/string keys)
#include "I_RPGLocationManager.h"                        // primary base
#include "C_RPGLocation.h"                               // map value (RPG locations)
#include "../Offsets/vtables/ISystemEventListener.h"     // 2nd base
#include "../Offsets/vtables/I_LocationListener.h"       // listener element
// CryStringT<char> is provided by the PCH prelude.

// ===========================================================================
// wh::rpgmodule::C_RPGLocationManager  (size 0x298)  RTTI .?AVC_RPGLocationManager@rpgmodule@wh@@
// ===========================================================================
// Singleton = *(qword_1835AC728 + 0x580); ctor sub_18118DCC8; dtor sub_1811A2DEC.
// Manages TWO location families plus an id<->guid translation, all stock MSVC std::unordered
// containers (0x40 _Hash each; bucket-init sub_18071265C / sub_180F39820 / sub_181023FC4 /
// sub_18118D424). [hash/eq functors are the game's own; modeled with S_DefaultHash for the
// non-std-hashable keys so the layout-mirror compiles -- the 0x40 size is functor-independent.]
//   POIs (C_POI, 0x90, ctor sub_18118D954): +0x18 guid, +0x70 group, +0xB0 guid-set, +0xF8 name, +0x58 spatial tree.
//   RPG locations (C_RPGLocation, 0x38): +0x1B8 guid, +0x208 id.
//   id<->guid: +0x138 id->guid, +0x178 guid->id.
// Map values for C_RPGLocation are intrusive-refcounted (_smart_ptr semantics, +0x08 refcount);
// modeled as raw C_RPGLocation* (layout-identical, 8 bytes).
namespace wh::rpgmodule {

class C_POI;                 // POI object (0x90; I_Location @+0x10; ctor sub_18118D954) -- forward only
struct S_RPGSpatialNode;     // +0x58 tree node (~0x38: Vec3 min/max + entry/child ranges) [layout not certified]

// Spatial acceleration tree over the POIs (lazily built; sub_181199A74 inserts by position).
struct S_LocationSpatialIndex {
    S_RPGSpatialNode* m_root;          // +0x00  lazily-allocated root node (ctor=0)
    uint32_t          m_count;         // +0x08  inserted count (ctor=0)
    uint32_t          m_maxItemsPerNode;// +0x0C  ctor=0x10 [INFERRED config]
    uint32_t          m_splitParam;    // +0x10  ctor=4    [INFERRED config]
};
static_assert(sizeof(S_LocationSpatialIndex) == 0x18, "spatial index descriptor (ctor sub_18118DCC8)");

class C_RPGLocationManager
    : public I_RPGLocationManager           // +0x00
    , public Offsets::ISystemEventListener  // +0x08
{
public:
    uint16_t m_state;                  // +0x10  folded C_RPGBase state word (ctor=0) [UNVERIFIED meaning]
    uint8_t  _pad12[6];                // +0x12

    // ---- POI registries (value = C_POI*) ----
    std::unordered_map<CryGUID, C_POI*, wh::shared::S_DefaultHash<CryGUID>> m_poisByGuid;            // +0x18  init sub_18118D424; get-or-create sub_181193694
    S_LocationSpatialIndex                                                  m_poiSpatialIndex;       // +0x58  AABB tree (ctor {0,0,0x10,4})
    std::unordered_map<CryGUID, std::vector<C_POI*>, wh::shared::S_DefaultHash<CryGUID>> m_poisByGroup; // +0x70  group guid -> member POIs [value INFERRED C_POI]
    std::unordered_set<CryGUID, wh::shared::S_DefaultHash<CryGUID>>         m_poiGuidSet;            // +0xB0  set of POI guids (init sub_1807402B4) [semantic INFERRED]
    uint32_t                                                                m_unkF0;                 // +0xF0  ctor=0 [UNVERIFIED]
    uint8_t                                                                 _padF4[4];               // +0xF4
    std::unordered_map<CryStringT<char>, C_POI*, wh::shared::S_DefaultHash<CryStringT<char>>> m_poisByName; // +0xF8  name -> POI (insert sub_181189FFC) [value INFERRED C_POI]

    // ---- id <-> guid translation ----
    std::unordered_map<wh::framework::WUID, CryGUID, wh::shared::S_DefaultHash<wh::framework::WUID>> m_idToGuid; // +0x138 (FNV-1a key hash sub_181192FA8)
    std::unordered_map<CryGUID, wh::framework::WUID, wh::shared::S_DefaultHash<CryGUID>>            m_guidToId;  // +0x178 (init sub_18118D424; resolver sub_1804989DC)

    // ---- RPG location registry (value = intrusive-refcounted C_RPGLocation*) ----
    std::unordered_map<CryGUID, C_RPGLocation*, wh::shared::S_DefaultHash<CryGUID>> m_locationsByGuid; // +0x1B8 init sub_181023FC4; get-or-create sub_180208CA8

    // node-pool / block-allocator descriptor shared by the location maps [INFERRED, not fully RE'd]
    uintptr_t m_nodePoolFreeList;      // +0x1F8  ctor=0
    uint32_t  m_nodePoolBlockCount;    // +0x200  ctor=0x10
    uint32_t  m_nodePoolStride;        // +0x204  ctor=8

    std::unordered_map<int32_t, C_RPGLocation*> m_locationsById;  // +0x208  init sub_180F39820; insert sub_18118994C

    // ---- +0x248 region: zero-init only; no reader/writer found [UNRESOLVED] ----
    uint64_t m_unk248;                 // +0x248
    uint64_t m_unk250;                 // +0x250
    uint64_t m_unk258;                 // +0x258
    uint64_t m_unk260;                 // +0x260
    uint8_t  m_unk268;                 // +0x268
    uint8_t  _pad269[7];               // +0x269

    // ---- change-notify listener list (deferred-removal "callbacks notify stack") ----
    std::vector<Offsets::I_LocationListener*> m_listeners;  // +0x270  init sub_18118D2B0 (reserve 16); add sub_1806CB684 / remove sub_1806BD5F8
    uint64_t m_notifyDepth;            // +0x288  ++ before notifying; >0 defers removals (sub_18027CFC4)
    uint8_t  m_hasNullEntries;         // +0x290  a listener was nulled mid-notify -> needs compaction (sub_1806BD5F8)
    uint8_t  m_shrinkOnCompact;        // +0x291  free buffer once empty after compaction (read sub_1806F7828) [writer not located]
    uint8_t  _pad292[6];               // +0x292
};
static_assert(sizeof(C_RPGLocationManager) == 0x298, "ctor operator new(0x298) via C_RPGModule sub_1811B9994");

}  // namespace wh::rpgmodule
