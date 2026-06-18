#pragma once

#include <cstdint>
#include <memory>     // std::weak_ptr
#include <vector>
#include "S_FactionAngriness.h"
#include "S_TimedFactionEvent.h"
#include "S_TimedFactionEventPool.h"
#include "S_FactionPersistentRecord.h"
#include "../framework/C_InlinePoolAllocator.h"

// ===========================================================================
// wh::rpgmodule::C_Faction  -  the runtime faction record (size 0x280).
// ===========================================================================
// Payload of a std::shared_ptr: creator sub_18118A908 allocs a std::_Ref_count_obj<C_Faction>
// (0x290; control block {vtable,uses@8,weaks@0xC} at this-0x10), ctor sub_18118D490(this, def)
// builds it from an S_FactionDef, then the creator writes the self weak_ptr at +0x00. The
// faction-manager loader inserts the shared_ptr into C_FactionManager::m_factions (+0x10).
namespace wh::rpgmodule {

struct S_FactionDef;   // +0x278 (pointer)

struct C_Faction {
    std::weak_ptr<C_Faction> m_weakSelf;       // +0x000  self weak_ptr {_Ptr=this, _Rep=ctrl}; set by creator sub_18118A908
    float                    m_reputation;     // +0x010  player reputation [-1,1]; init = def->baseReputation; writer sub_18118F47C
    uint8_t                  _pad014[4];       // +0x014
    S_FactionAngriness       m_angriness;      // +0x018  angriness sub-object (0x1D8)
    S_TimedFactionEventPool  m_timedEventPool; // +0x1F0  inline arena for m_timedEvents (0x48; flag @+0x230)
    S_TimedFactionEventPool* m_pTimedEventPool;// +0x238  back-ref to m_timedEventPool (ctor sub_18118D490 sets &m_timedEventPool)

    // +0x240  pending delayed reputation/angriness events; pool-backed std::vector (alloc = &m_timedEventPool),
    //         so 0x20. Push sub_18118A09C (stride 0x40); deserialize tag 0x1EAB.
    std::vector<S_TimedFactionEvent,
                wh::framework::C_InlinePoolAllocator<S_TimedFactionEvent, S_TimedFactionEventPool>> m_timedEvents;

    // +0x260  persistent (saved) faction records; plain heap std::vector (0x18). Deserialize tag 0x1EAC.
    std::vector<S_FactionPersistentRecord> m_persistentRecords;

    S_FactionDef*            m_pDef;           // +0x278  static faction.xml definition (ctor stores arg)
};
static_assert(sizeof(C_Faction) == 0x280, "_Ref_count_obj<C_Faction> new(0x290) - 0x10 control header (sub_18118A908)");

}  // namespace wh::rpgmodule
