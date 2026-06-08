#pragma once

#include <cstdint>
#include <vector>
#include "../framework/C_HashMap.h"              // wh::shared::C_HashMap, C_Set, hash primitives
#include "../framework/WUID.h"                   // wh::framework::WUID
#include "../CryEngine/CryCommon/CryString.h"    // CryStringT<char>
#include "S_InformationRecord.h"                 // wh::xgenaimodule::S_InformationRecord
#include "C_IntelligentObject.h"                 // wh::xgenaimodule::C_IntelligentObject (holder type)

// ===========================================================================
// wh::xgenaimodule::C_InformationManager
// ===========================================================================
// The global crime/information knowledge store. Singleton: *qword_183501790
// (lazy alloc+ctor sub_181625C50; size 0x128). No RTTI / no vtable (name
// INFERRED from the information-system BT nodes + Lua bindings that reach it).
//
// ARCHITECTURE: decentralized per-NPC knowledge. Each C_IntelligentObject
// ("holder", gated by GetCapabilityFlags() & 0x40) owns a vector of
// S_InformationRecord*; records are deduped by {perceivedEntity WUID, label}.
//
// FOUR INTERNAL CONTAINERS (all the Warhorse pooled hash family == C_HashMap /
// C_Set, 0x40 header each; bucket pool sub_18071265C, 1.0f load factor):
//
//   m_holders     @ +0x08  C_HashMap (0x20 node, ctor sub_1807125EC)
//                          Key: C_IntelligentObject*  Value: std::vector<S_InformationRecord*>*
//                          Primary store. Query sub_1805127EC(mgr, holder); key hashed 8 bytes.
//
//   m_byId        @ +0x48  C_HashMap (0x20 node, ctor sub_180F39820 -> sub_1807125EC)
//                          Key: uint32_t informationId  Value: std::vector<C_IntelligentObject*>*
//                          Reverse index. Query sub_1815D3E34 (allocs an empty vector on miss).
//
//   m_byLabelWuid @ +0x88  C_Set (0x18 node, ctor sub_180F993F0 -> sub_180731290)
//                          Element: S_InformationRecord* (8-byte key). NOT an inline composite.
//                          TRANSPARENT hash over the pointee (sub_1815DFDC8/sub_1815E0050):
//                            hash_combine( fnv1a_64(&record->perceivedEntity, 8),
//                                          fnv1_32(record->label.c_str()) ).
//                          Equality sub_1815CDE7C: record->perceivedEntity == ... && strcmp(label).
//                          Dedup/find of a record by its {entity,label} identity.
//
//   m_resolutions @ +0xD0  C_Set (0x18 node, ctor sub_180F993F0 -> sub_180731290)
//                          Element: 8-byte key = a pending crime-resolution entry pointer.
//                          [ELEMENT TYPE UNVERIFIED — built {holder, record} in sub_1815CE6B4;
//                           insert sub_1815DFFD0/sub_1815E0E84, query path sub_1815CE6B4.]
//
//   +0xC8  m_nextId   uint32_t — monotonic record-id allocator.
//   +0x110/+0x118/+0x120  three void* (UNVERIFIED; ctor zeroes them — likely resolution-
//                         subsystem listener/callback hooks).
//   +0x00  8 bytes the ctor does not touch (first map starts at +0x08).
//
// KEY FUNCTIONS:
//   ctor sub_181625C50 ; GetHolderRecords sub_1805127EC ; CollectRecords sub_1805124A0
//   (returns std::vector<S_InformationKey>) ; CreateRecord sub_1815D0744 -> sub_1815CB3C4 ;
//   RegisterRecord sub_1815CE6B4 ; DestroyById sub_1815DB7C0 ; RemoveFromHolder sub_1815DB81C.
// Consumers (BT nodes via qword_183501790): sub_180512534 (GetKnownInformations), sub_180511FD0,
//   sub_1802B5470, sub_1805135BC (NPC teardown wipes the holder's records).
// ===========================================================================

namespace wh::xgenaimodule {

// Transparent hash functor for m_byLabelWuid: reads through the record pointer
// and folds fnv1a_64(wuid) with fnv1_32(label) via boost-style hash_combine.
// VERIFIED from sub_1815DFDC8 (hashes record+0x08 as 8 bytes, record+0x10 as a C string).
struct S_InformationHash {
    uint64_t operator()(const S_InformationRecord* r) const {
        uint64_t seed = wh::shared::fnv1a(&r->perceivedEntity, sizeof(r->perceivedEntity));
        return wh::shared::hash_combine(seed, wh::shared::fnv1_32(r->label.c_str()));
    }
};

class C_InformationManager {
public:
    uint8_t _pad00[8];                                                              // +0x00  (untouched by ctor)

    wh::shared::C_HashMap<
        C_IntelligentObject*,
        std::vector<S_InformationRecord*>*
    >                           m_holders;          // +0x08  holder -> its record vector (0x20 node)

    wh::shared::C_HashMap<
        uint32_t,
        std::vector<C_IntelligentObject*>*
    >                           m_byId;             // +0x48  informationId -> holders that know it (0x20 node)

    wh::shared::C_Set<
        S_InformationRecord*,
        S_InformationHash
    >                           m_records;      // +0x88  set of records (0x18 node)

    uint32_t                    m_nextId;           // +0xC8  monotonic record-id allocator
    uint8_t                     _padCC[4];          // +0xCC

    wh::shared::C_Set<void*>    m_resolutions;      // +0xD0  pending crime-resolution entries (0x18 node) [element UNVERIFIED]

    void*                       m_unk110;           // +0x110 [UNVERIFIED — likely resolution listener hooks]
    void*                       m_unk118;           // +0x118
    void*                       m_unk120;           // +0x120

    // --- accessors (non-virtual; address forwarders in Offsets.cpp) ---
    static C_InformationManager* GetInstance();     // -> *qword_183501790

    // sub_1805127EC: the record vector for a holder (empty static vector on miss).
    const std::vector<S_InformationRecord*>* GetHolderRecords(C_IntelligentObject* holder) const;
};
static_assert(sizeof(C_InformationManager) == 0x128);

}  // namespace wh::xgenaimodule
