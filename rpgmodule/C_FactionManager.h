#pragma once

#include <cstdint>
#include "../databasemodule/I_DatabaseListener.h"

// -----------------------------------------------
// C_FactionManager — singleton managing faction/location state
// -----------------------------------------------
// RTTI: .?AVC_FactionManager@rpgmodule@wh@@
// Inherits: I_FactionManager (primary), I_DatabaseListener (secondary)
//
// Singleton global: qword_1836E39F0
// Getter: sub_18022877C() → returns &qword_1836E39F0
// Constructor: sub_18118D588
// Destructor: sub_180B33C20
// Populate: sub_18119B144 (loads from faction definition table at xmmword_1835A7D20)
//
// Primary vtable:   0x1822f85a8  (C_FactionManager, 16 entries)
// Secondary vtable: 0x1822f8688  (I_DatabaseListener adjustor thunk)
//
// Lua bindings:
//   Faction table (0x1811CC058): GetAngriness, SetAngriness, AddAngriness, GetReputation, GetLocationId
//   Location table (0x1811CC304): GetWantedLevel, SetWantedLevel, GetReputation, GetState, SetState

namespace wh::rpgmodule {

// -----------------------------------------------
// S_FactionMapEntry — one entry in the sorted faction/location map
// -----------------------------------------------
// Size: 0x18 bytes (confirmed: iterate function uses `v2 + 0x18 * count` as end)
// Stored in a sorted array, looked up via sub_1811AC57C (binary search by key).

struct S_FactionMapEntry {
    int32_t     key;                    // +0x00  faction/location ID (sort key)
    int32_t     _pad04;                 // +0x04
    void*       pData;                  // +0x08  pointer to faction/location data object
    uint64_t    extra;                  // +0x10  secondary data (e.g. pointer to location list)
};
static_assert(sizeof(S_FactionMapEntry) == 0x18);

// -----------------------------------------------
// Faction/Location data objects (pointed to by S_FactionMapEntry.pData)
// -----------------------------------------------
// These are heap-allocated objects with at least:
//   +0x08: CryStringT name (faction/location name string)
//   +0x10: float angriness/reputation value
//
// Faction lookup is done via global indexed arrays (NOT the sorted maps):
//   Faction by ID:  qword_1835AA3B8[id - dword_1835AA3D0]  (sub_18117EAD8)
//   Location by ID: qword_1835AA638[id - dword_1835AA650]  (sub_181196894)
// These globals are populated separately from the faction definition table.

// -----------------------------------------------
// S_SortedMap — a sorted array container
// -----------------------------------------------
// Used for both faction and location maps within C_FactionManager.
// Entries are S_FactionMapEntry, kept sorted by key for binary search.

template<typename T>
struct S_SortedMap {
    T*          begin;                  // +0x00  pointer to first entry
    int64_t     count;                  // +0x08  number of entries
    T*          capacity;              // +0x10  end of allocated storage (for growth)
};
static_assert(sizeof(S_SortedMap<S_FactionMapEntry>) == 0x18);

// -----------------------------------------------
// I_FactionManager — interface
// -----------------------------------------------
class I_FactionManager {
public:
    virtual ~I_FactionManager() = 0;
};

// I_DatabaseListener defined in C_SoulList.h (wh::databasemodule::I_DatabaseListener)
// RTTI: .?AVI_DatabaseListener@databasemodule@wh@@

// -----------------------------------------------
// C_FactionManager
// -----------------------------------------------
// Size: 0x70 bytes (constructor touches through +0x60; destructor uses +0x68)
//
// Primary vtable (0x1822f85a8):
//   [0]  destructor
//   [1]  Init/Reset
//   [2]  LoadFromDatabase
//   [3]  Serialize
//   [4]  GetAngriness(factionId, defaultVal) → float  (sub_181198f34)
//        Looks up faction via sub_18117EAD8, returns *(faction+0x10)
//   [5]  GetFactionByIndex(index) → int               (sub_181198f6c)
//        Searches tree at dword_1835AA3D8
//   [6]  GetFactionName(locationId) → CryStringT       (sub_181198fa4)
//        Looks up location via sub_181196894, returns CryString at *(loc+0x08)
//   [7]  GetLocationCount / GetLocation
//   [8]  GetLocationReputation(locId, default) → float (sub_1811966E8)
//        Uses global array qword_1835A7278, reads *(loc+0x10)
//   [9]  IterateFactions(callback)                     (sub_181196168)
//        Walks sorted map at +0x10, calls callback with each entry's pData
//   [10] GetFactionRelation
//   [11] GetFactionDistance(entityA, entityB) → float   (sub_1811978B0)
//        Looks up entities, gets positions via vtable[0x80/8], returns distance²

class C_FactionManager : public I_FactionManager,                        // vtable at +0x00
                         public wh::databasemodule::I_DatabaseListener  // vtable at +0x08
{
public:
    // +0x00: I_FactionManager vtable (C_FactionManager primary)
    // +0x08: I_DatabaseListener vtable (secondary)

    S_SortedMap<S_FactionMapEntry> m_factions;           // +0x10  sorted by faction ID
    // Iterate: begin[0..count-1], each entry is 0x18 bytes
    // Lookup: sub_1811AC57C does binary search by key

    S_SortedMap<S_FactionMapEntry> m_locations;          // +0x28  sorted by location ID

    // Location-to-faction mapping (populated from faction defs)
    S_FactionMapEntry* m_locFactionBegin;                // +0x40  (freed in destructor with element dtors)
    S_FactionMapEntry* m_locFactionEnd;                  // +0x48

    // Extra allocated data block (refcounted)
    void*       m_pExtraData;                            // +0x50  (freed in destructor if m_extraDataRefCount != 0)
    void*       m_pExtraDataAlloc;                       // +0x58  (allocation pointer, freed in destructor)

    uint8_t     m_bInitialized;                          // +0x60  (zeroed in ctor)
    char        _pad61[7];                               // +0x61

    int64_t     m_extraDataRefCount;                     // +0x68  (guards free of +0x58 in destructor; zero-init from .bss)
};
static_assert(sizeof(C_FactionManager) == 0x70);

// Singleton access:
// C_FactionManager* GetFactionManager() {
//     return (C_FactionManager*)sub_18022877C();   // → &qword_1836E39F0
// }

}  // namespace wh::rpgmodule
