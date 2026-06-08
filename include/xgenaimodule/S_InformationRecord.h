#pragma once

#include <cstdint>
#include "../framework/WUID.h"
#include "../CryEngine/CryCommon/CryString.h"   // CryStringT<char> (8-byte refcounted string handle)

// ===========================================================================
// wh::xgenaimodule::S_InformationRecord
// ===========================================================================
// One piece of "known information" in the crime/perception system: an NPC's
// knowledge that a particular entity did something identifiable by a label at
// a world position.
//
// RTTI: NONE (plain struct, no vtable).
// ctor:  sub_1815CB3C4(this, id, perceivedWuid, label, posX, posY, posZ)
// alloc: sub_1815D0744 (operator new 0x28 + ctor)
// size:  0x28 (40 bytes). VERIFIED from ctor field writes + alloc size.
//
// Records are OWNED by the C_InformationManager and stored in per-holder
// vectors (m_holders map value = std::vector<S_InformationRecord*>*).
// The {perceivedEntity, label} composite is the dedup key (comparison
// sub_1815CDE7C: match if wuid==wuid AND label==label).
//
// Hash for the composite key (used in m_byLabelWuid set):
//   boost::hash_combine(fnv1_32(label.c_str()), fnv1a_64(&perceivedEntity, 8))
//   (see framework/C_HashMap.h for the hash primitives).
// ===========================================================================

namespace wh::xgenaimodule {

struct S_InformationRecord {
    uint32_t              informationId;    // +0x00  unique id (assigned by C_InformationManager::m_nextId)
    int32_t               version;          // +0x04  version counter (incremented on update)
    wh::framework::WUID   perceivedEntity;  // +0x08  the entity this info is ABOUT (perceived target)
    CryStringT<char>      label;            // +0x10  information label string (e.g. crime type / event name)
    float                 posX;             // +0x18  world position where the event was perceived
    float                 posY;             // +0x1C
    float                 posZ;             // +0x20
    uint8_t               _pad24[4];        // +0x24  (align to 0x28)
};
static_assert(sizeof(S_InformationRecord) == 0x28);

}  // namespace wh::xgenaimodule
