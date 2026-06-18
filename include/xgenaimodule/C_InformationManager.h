#pragma once

#include <cstdint>
#include <cstring>                               // strcmp (S_InformationEq)
#include <vector>
#include <unordered_map>                         // m_holders / m_byId are MSVC std::unordered_map (0x40)
#include <unordered_set>                         // m_records (MULTIset) / m_resolutions are MSVC std::unordered_(multi)set (0x40)
#include "../framework/HashPrimitives.h"         // wh::shared::fnv1a / fnv1_32 / hash_combine (S_InformationHash)
#include <boost/container/vector.hpp>            // boost::container::vector (holder index @+0x110)
#include "../framework/WUID.h"                   // wh::framework::WUID
#include "S_InformationRecord.h"                 // wh::xgenaimodule::S_InformationRecord
#include "S_InformationResolution.h"             // wh::xgenaimodule::S_InformationResolution (m_resolutions element)
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
// S_InformationRecord*. The same crime is stored once PER holder that knows it
// (m_records is a multiset; dedup is per-holder, in RegisterRecord) -- so one
// {perceivedEntity, label} can have many records sharing one informationId.
//
// FOUR INTERNAL CONTAINERS -- all stock MSVC std::unordered_map / std::unordered_set
// (0x40 _Hash header each; verified in IDA: float load@+0, list sentinel@+8, count@+0x10,
// bucket-vec@+0x18, mask@+0x30, maxidx@+0x38; node {next@0, prev@8, value@0x10}):
//
//   m_holders     @ +0x08  std::unordered_map<C_IntelligentObject*, std::vector<S_InformationRecord*>*>
//                          (0x20 node). Primary store. Query sub_1805127EC(mgr, holder).
//
//   m_byId        @ +0x48  std::unordered_map<uint32_t, std::vector<C_IntelligentObject*>*>
//                          (0x20 node). Reverse index. Query sub_1815D3E34 (empty vector on miss).
//
//   m_records     @ +0x88  std::unordered_MULTIset<S_InformationRecord*, S_InformationHash, S_InformationEq>
//                          (0x18 node). TRANSPARENT hash/eq over the pointee {perceivedEntity, label}
//                          (hash sub_1815DFDC8 = hash_combine(fnv1a_64(wuid), fnv1_32(label));
//                           eq sub_1815CDE7C = perceivedEntity== && strcmp(label)). NOT a unique set:
//                          the insert (sub_1815C6758) never rejects equal keys, so the same {entity,label}
//                          appears once per holder that knows it (3 NPCs -> 3 entries). Per-holder dedup
//                          lives in RegisterRecord, not here.
//
//   m_resolutions @ +0xD0  std::unordered_set<S_InformationResolution*>
//                          (0x18 node). Pending crime-resolution entries; built {holder,record} in
//                          sub_1815CE6B4 (insert sub_1815DFFD0 / find sub_1815E0E84). [hash/eq detail
//                          UNVERIFIED -- modeled with std defaults; layout-only, never invoked here.]
//
//   +0xC8  m_nextId   uint32_t — monotonic record-id allocator.
//   +0x110 m_holderIndex  boost::container::vector<C_IntelligentObject*> (sorted holder index).
//   +0x00  8 bytes the ctor does not touch (first map starts at +0x08).
//
// KEY FUNCTIONS:
//   ctor sub_181625C50 ; GetHolderRecords sub_1805127EC ; CollectRecords sub_1805124A0
//   (returns std::vector<S_InformationKey>) ; CreateRecord sub_1815D0744 -> sub_1815CB3C4 ;
//   RegisterRecord sub_1815CE6B4.
//
// LOOKUP + DESTROY FAMILY (all VERIFIED this session -- the crime-erase chain):
//   FindInformationId          sub_1815D3FEC (on m_records @+0x88): {wuid,label} -> informationId
//   DestroyInformationById     sub_1815DB7C0(mgr, id): remove from EVERY holder + finalize
//   RemoveInformationFromHolder sub_1815DB81C(mgr, id, holder, mkResolution, finalizeIfLast)
//   RemoveHolder               sub_180513938(mgr, holder): wipe ALL of one holder's records
//   (internal) bulk-remove     sub_1815DB658(mgr, holder, &recordVec)  [used by RemoveHolder]
// High-level entry: BT node "DestroyInformation" sub_1814D80C4 reads params "percievedWuid"
//   (sic) + "label", FindInformationId, then DestroyInformationById (node status 5=ok / 6=fail).
// Consumers (BT nodes via qword_183501790): sub_180512534 (GetKnownInformations), sub_180511FD0,
//   sub_1802B5470 ; AI-object teardown sub_1805135BC -> RemoveHolder.
// ===========================================================================

namespace wh::xgenaimodule {

// Transparent hash/eq functors for m_records: the set stores S_InformationRecord* but
// hashes/compares THROUGH the pointer by the pointee's {perceivedEntity, label} identity.
// These are stateless (EBO -> the set stays 0x40). NOTE: all live insert/find/erase go
// through the game's own functions, so std never actually invokes these -- they exist to
// give the set the correct type + document the engine's hashing.
//   hash VERIFIED from sub_1815DFDC8 (record+0x08 as 8 bytes, record+0x10 as a C string).
struct S_InformationHash {
    uint64_t operator()(const S_InformationRecord* r) const {
        uint64_t seed = wh::shared::fnv1a(&r->perceivedEntity, sizeof(r->perceivedEntity));
        return wh::shared::hash_combine(seed, wh::shared::fnv1_32(r->label.c_str()));
    }
};
//   eq VERIFIED from sub_1815CDE7C (perceivedEntity == && strcmp(label)).
struct S_InformationEq {
    bool operator()(const S_InformationRecord* a, const S_InformationRecord* b) const {
        return a->perceivedEntity == b->perceivedEntity
            && std::strcmp(a->label.c_str(), b->label.c_str()) == 0;
    }
};

class C_InformationManager {
public:
    uint8_t _pad00[8];                                                              // +0x00  (untouched by ctor)

    std::unordered_map<
        C_IntelligentObject*,
        std::vector<S_InformationRecord*>*
    >                           m_holders;          // +0x08  holder -> its record vector

    std::unordered_map<
        uint32_t,
        std::vector<C_IntelligentObject*>*
    >                           m_byId;             // +0x48  informationId -> holders that know it

    // NOTE: MULTIset, not a unique set. The insert (sub_1815C6758) is MSVC's non-unique
    // _Hash::_Insert -- it groups equal keys but never rejects, so it holds one record per
    // (holder x crime): N entries with the same {entity,label} == N distinct NPCs who know it.
    // De-duplication is enforced one level up, PER HOLDER, in RegisterRecord (sub_1815CE6B4),
    // which reaps a redundant record (sub_1815D105C) when a holder already knows that id.
    std::unordered_multiset<
        S_InformationRecord*,
        S_InformationHash,
        S_InformationEq
    >                           m_records;          // +0x88  every (holder,crime) record

    uint32_t                    m_nextId;           // +0xC8  monotonic record-id allocator
    uint8_t                     _padCC[4];          // +0xCC

    std::unordered_set<S_InformationResolution*> m_resolutions;  // +0xD0  pending crime-resolution entries

    // +0x110  Sorted index over the holders the manager tracks (a flat-set: a sorted
    // boost::container::vector of holder pointers, binary-searched). Maintained/erased by
    // RemoveHolder (sub_180513938 binary-searches it; sub_1806A232C erases: end =
    // m_start + 8*m_size). Was previously mislabeled three "listener hook" void*s.
    boost::container::vector<C_IntelligentObject*> m_holderIndex;  // +0x110 m_start / +0x118 m_size / +0x120 m_capacity

    // --- accessors (non-virtual; address forwarders in Offsets.cpp) ---
    static C_InformationManager* GetInstance();     // -> *qword_183501790

    // sub_1805127EC: the record vector for a holder (empty static vector on miss).
    const std::vector<S_InformationRecord*>* GetHolderRecords(C_IntelligentObject* holder) const;

    // --- lookup (locate an information before destroying it) ---

    // sub_1815D3FEC (operates on m_records @+0x88): resolve {perceivedEntity WUID, label}
    // to the record's informationId. Returns true and writes *outId on a hit. This is the
    // first step of the BT "DestroyInformation" node (sub_1814D80C4) before DestroyInformationById.
    bool FindInformationId(const wh::framework::WUID& perceivedEntity,
                           const CryStringT<char>& label, uint32_t* outId) const;

    // --- destruction / removal ---

    // sub_1815DB7C0: destroy an information GLOBALLY by id. Walks the reverse index
    // m_byId[id] and removes the record from EVERY holder that knows it (each via
    // RemoveInformationFromHolder with createResolution=finalizeIfLast=true), looping until
    // the final holder triggers the global finalize. This is the "erase a crime everywhere" call.
    void DestroyInformationById(uint32_t informationId);

    // sub_1815DB81C: remove ONE record (matched by informationId) from ONE holder's vector.
    //   createResolution -> also push an S_InformationResolution{holder, record} into m_resolutions
    //   finalizeIfLast   -> if this was the last holder, erase m_byId[id], free the holder list,
    //                       and fire the global removal notify (sub_1815E0118 / sub_180AD4C20).
    // Returns true iff it performed the global finalize (i.e. holder was the last to know it).
    bool RemoveInformationFromHolder(uint32_t informationId, C_IntelligentObject* holder,
                                     bool createResolution, bool finalizeIfLast);

    // sub_180513938: remove a holder ENTIRELY -- bulk-removes it from every record's reverse
    // index + builds resolutions (sub_1815DB658), erases each record from m_records, frees the
    // holder's record vector, and drops the holder from m_holders and the +0x110 holder index.
    // Wipes ALL of one NPC's knowledge; used by AI-object teardown (sub_1805135BC).
    void RemoveHolder(C_IntelligentObject* holder);
};
static_assert(sizeof(C_InformationManager) == 0x128);

}  // namespace wh::xgenaimodule
