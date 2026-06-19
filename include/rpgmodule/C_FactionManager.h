#pragma once

#include <cstdint>
#include <memory>                          // m_factions value: shared_ptr<C_Faction>
#include <vector>                          // m_locations value: std::vector<C_Faction*>
#include <boost/container/flat_map.hpp>
#include "../databasemodule/I_DatabaseListener.h"
#include "../CryEngine/CryCommon/BaseTypes.h"            // uint64 (needed by CryGUID.h)
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h" // m_locations key
#include "C_Faction.h"
#include "S_FactionRelation.h"             // m_relations value

// C_FactionManager  RTTI .?AVC_FactionManager@rpgmodule@wh@@  (size 0x70)
// Inherits I_FactionManager (primary) + I_DatabaseListener (secondary).
// Singleton qword_1836E39F0 (getter sub_18022877C); ctor sub_18118D588; dtor sub_180B33C20;
//   populate sub_18119B144 (faction table xmmword_1835A7D20).
// Vtables: primary 0x1822F85A8 (16 entries); secondary (I_DatabaseListener) 0x1822F8688.
// Lua: Faction tbl 0x1811CC058 (Get/Set/AddAngriness, GetReputation, GetLocationId);
//      Location tbl 0x1811CC304 (Get/SetWantedLevel, GetReputation, Get/SetState).

namespace wh::rpgmodule {

// Opaque owned block at C_FactionManager+0x58. NEVER allocated or written anywhere in
// WHGame.dll (xrefs = dtor free only), so its layout is unknown; forward-declared (not
// defined) purely to give the manager a typed owning pointer instead of a void*.
struct S_FactionManagerExtraData;

// The three maps are boost flat_maps (key-sorted vector<pair>, binary search sub_1811AC57C;
// grow sub_1811AB2F8). Each holder is one boost::container::vector {start,size,cap} = 0x18.
static_assert(sizeof(boost::container::flat_map<int32_t, std::shared_ptr<C_Faction>>) == 0x18);
static_assert(sizeof(std::pair<CryGUID, std::vector<C_Faction*>>) == 0x28, "m_locations element (sub_1811AC9A8)");

class I_FactionManager {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_FactionManager;
    virtual ~I_FactionManager() = 0;
};
// I_DatabaseListener: wh::databasemodule (C_SoulList.h)

// Primary vtable 0x1822F85A8:
//  [0] dtor  [1] Init  [2] LoadFromDatabase  [3] Serialize
//  [4] GetReputation(id,def)->float            sub_181198F34  (faction sub_18117EAD8, *(f+0x10) = m_reputation)
//      [was mislabeled "GetAngriness"; it returns reputation @+0x10, NOT angriness @+0x20]
//  [5] GetFactionByIndex(idx)->int             sub_181198F6C
//  [6] GetFactionName(locId)->CryString        sub_181198FA4  (loc sub_181196894, *(loc+0x08))
//  [7] GetLocationCount / GetLocation
//  [8] GetLocationReputation(locId,def)->float  sub_1811966E8  (*(loc+0x10))
//  [9] IterateFactions(cb)                      sub_181196168
//  [10] GetFactionRelation
//  [11] GetFactionDistance(a,b)->float          sub_1811978B0
class C_FactionManager : public I_FactionManager,
                         public wh::databasemodule::I_DatabaseListener {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FactionManager;
    // +0x00 / +0x08: the two base vtables.

    // +0x10  faction id -> faction record (lookup sub_1811AC57C). value->m_reputation @ C_Faction+0x10.
    boost::container::flat_map<int32_t, std::shared_ptr<C_Faction>> m_factions;

    // +0x28  location uuid (CryGUID = def+0x20) -> factions present there (find sub_1811AC9A8).
    boost::container::flat_map<CryGUID, std::vector<C_Faction*>> m_locations;

    // +0x40  faction<->faction relations. key = FNV-1a combine of both faction ids (sub_1802286B8);
    //         value = owned S_FactionRelation* (built by sub_18118B8D4 from the f2f def table).
    boost::container::flat_map<uint64_t, S_FactionRelation*> m_crossFactionRep;

    S_FactionManagerExtraData* m_pExtraData;  // +0x58  owned block, freed first in dtor (gated on m_field68); never written in this build
    bool     m_bInitialized;   // +0x60  zeroed in ctor; never set true in this build
    char     _pad61[7];        // +0x61
    int64_t  m_field68;        // +0x68  dtor free-gate for m_pExtraData; never written in this build (always 0)

    static C_FactionManager* GetInstance();   // sub_18022877C; impl in C_FactionManager.cpp
};
static_assert(sizeof(C_FactionManager) == 0x70);

}  // namespace wh::rpgmodule
