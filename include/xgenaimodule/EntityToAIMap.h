#pragma once

#include <cstdint>
#include "../framework/C_HashMap.h"   // wh::shared::C_HashMap, S_HashNode, S_DefaultHash (FNV-1a-64)
#include "../framework/WUID.h"        // wh::framework::WUID

// ===========================================================================
// wh::xgenaimodule — the ENTITY-GUID -> AI bridge map.
//
// Global heap map  *qword_18378D6E8  (accessor sub_180705E50; lazy init/ctor
// sub_18167041C — the ONLY writer of the global, @0x181670545). It maps a
// CryEngine IEntity (by its 8-byte GUID = IEntity::GetGuid(), vtbl+0x10) to the
// AI object that drives it: the C_AIPuppet host plus that puppet's WUID.
//
// It is NOT a bespoke manager class and has NO RTTI / NO vtable: the init writes
// only the 1.0f load factor (0x3F800000 @0x181670535), the circular sentinel
// (sub_180255920), count=0, and the 8-bucket pool (sub_18071265C). It is a bare
// instantiation of the existing wh::shared::C_HashMap template (whose 0x40 header
// matches a raw MSVC std::unordered_map: load-factor@+0x00, sentinel@+0x08,
// count@+0x10, bucket-vector begin/end/cap @+0x18/+0x20/+0x28, mask@+0x30,
// bucketCount@+0x38 — all VERIFIED, see C_HashMap.h).
//
//   map header        0x40   (== sizeof(wh::shared::C_HashMap<...>))
//   hash node         0x28   (sentinel/node alloc sub_180255920 uses size 0x28)
//   mapped value      0x10   (S_AIPuppetMapping)
//
//   node layout (VERIFIED):
//     +0x00 link (forward chain; lookup walks via *(node))      [0x18023be35]
//     +0x08 link (other dir)                                    [0x1805b0285]
//     +0x10 EntityGUID key  (IEntity::GetGuid)                  [0x18023be19]
//     +0x18 C_AIPuppet*     value.m_pPuppet                     [0x1805b0003]
//     +0x20 WUID            value.m_wuid                        [0x1805b0003]
//
//   Ops:  Find   sub_18023BDCC -> &value.m_wuid (miss -> &kInvalidWuid = -1)
//         Insert sub_1805AFF9C (core sub_1805B009C / node sub_1805B0140)
//         Erase  sub_1805B0018
//         (registered by C_AIPuppet ctor sub_1805AFE64; removed by dtor sub_1805AFEFC)
//
//   PURPOSE: IEntity -> AI translation. Given an engine entity you get its AI WUID
//   (and the owning C_AIPuppet); the reverse direction (WUID -> object) is the
//   central registry qword_1837999E0. One entry per live AI puppet.
// ===========================================================================

namespace wh::xgenaimodule {

class C_AIPuppet;   // the AI host (vtable 0x1821C7D10); see C_AIPuppet.h

// CryEngine 8-byte entity GUID (IEntity::GetGuid, vtbl+0x10). [type INFERRED: the
// key is hashed as 8 raw bytes (sub_1804BF50C, len 8); the map has no RTTI.]
using EntityGUID = uint64_t;

// Mapped value stored inline at node+0x18 (0x10 bytes): the puppet that drives the
// entity, plus that puppet's WUID (== the value the C_AIPuppet ctor copies to +0x30).
struct S_AIPuppetMapping {
    C_AIPuppet*          m_pPuppet;   // +0x00  (node+0x18) — the AI host           [VERIFIED 0x1805b0003]
    wh::framework::WUID  m_wuid;      // +0x08  (node+0x20) — its WUID; Find returns &this  [VERIFIED]
};
static_assert(sizeof(S_AIPuppetMapping) == 0x10);

// The map type. Key = EntityGUID; default hash = FNV-1a-64 over 8 bytes (sub_1804BF50C).
using C_EntityToAIMap = wh::shared::C_HashMap<EntityGUID, S_AIPuppetMapping>;
static_assert(sizeof(C_EntityToAIMap) == 0x40);
static_assert(sizeof(wh::shared::S_HashNode<EntityGUID, S_AIPuppetMapping>) == 0x28);

// --- global accessors / ops (free funcs; the map is a bare global) ---------------------------

// *qword_18378D6E8 (sub_180705E50). Null before the AI module's lazy init (sub_18167041C) runs.
C_EntityToAIMap* GetEntityToAIMap();

// Find by entity GUID (sub_18023BDCC). Returns a pointer to the stored WUID (node+0x20) on hit,
// or to the all-FF invalid-WUID sentinel (qword_183017830) on miss. NOTE: the engine lookup yields
// &value.m_wuid specifically (the puppet sits one qword earlier at node+0x18, reachable as
// ((S_AIPuppetMapping*)((char*)ret - 8))->m_pPuppet).
const wh::framework::WUID* FindWuidByEntity(C_EntityToAIMap* map, EntityGUID guid);

// Register a puppet (sub_1805AFF9C). Keyed by puppet->GetEntity()->GetGuid(); stores
// {puppet, *wuid} at node+0x18. No-op if the puppet has no entity. Called from the C_AIPuppet ctor.
void RegisterPuppet(C_EntityToAIMap* map, C_AIPuppet* puppet, const wh::framework::WUID* wuid);

// Unlink + free the node for the given key (sub_1805B0018). Called from the C_AIPuppet dtor.
void ErasePuppet(C_EntityToAIMap* map, const EntityGUID* key, void* outResult);

}  // namespace wh::xgenaimodule
