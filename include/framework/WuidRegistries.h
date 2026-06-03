#pragma once

#include <cstddef>
#include <unordered_map>                     // the central registry is a std::unordered_map
#include "WUID.h"                            // wh::framework::WUID + E_WUIDType
#include "I_WUIDMappingProvider.h"           // the interface every registry implements
#include "S_WuidSlot.h"                       // the generic generation-counted slot
#include "../entitymodule/C_InventoryManager.h"
#include "../entitymodule/C_ItemManager.h"

// ===========================================================================
// WUID resolution overview. A WUID is resolved by dispatching on its type tag
// (WUID::type(), the high byte) to a per-type registry — there is no single flat table:
//
//   Soul      (5)        -> wh::rpgmodule::C_SoulList            [rpgmodule/C_SoulList.h]
//   Inventory (3)        -> wh::entitymodule::C_InventoryManager [entitymodule/C_InventoryManager.h]
//   Item      (2)        -> wh::entitymodule::C_ItemManager      [entitymodule/C_ItemManager.h]
//   linkable  (8/10/...) -> the central std::unordered_map below
//
// All three per-type registries implement I_WUIDMappingProvider and use the same
// generation-counted SLOT TABLE (an inline S_WuidSlot[] indexed by the WUID's low slot bits).
// They are built by the C_EntityModule ctor (sub_18103F5B0). See each header for details.
// ===========================================================================

namespace wh { namespace xgenaimodule { class C_AIObject; class C_LinkableObject; } }

namespace wh { namespace framework {

// --- Central registry: every AI object, keyed by WUID ---------------------------------------
// The global qword_1837999E0 is a std::unordered_map<WUID, C_AIObject*> (find sub_1802D1D6C;
// insert sub_180450678 writes node+0x10 = WUID, node+0x18 = C_AIObject*). It holds every
// C_AIObject and derived (C_LinkableObject -> ... -> C_NPC / C_SmartEntity). [A value's host is
// C_AIObject::m_pHost @+0x58; host->GetEntityId() (host vtable[1]) is the owning entity.]
using C_WuidObjectMap = std::unordered_map<WUID, xgenaimodule::C_AIObject*>;

// Access the live central map. The global holds a POINTER to the heap map (the call sites do
// `mov rcx, cs:qword_1837999E0`, not `lea`); null before the AI/entity module is up. Impl in
// Offsets.cpp. Enumerable: iterate it.
C_WuidObjectMap* GetWuidObjectMap();

// --- Container / chest helper ---------------------------------------------------------------
// A chest/container is a C_LinkableObject in the linkables manager (xgenaimodule::C_LinkablesManager
// = *qword_1837999D8); look one up with C_LinkablesManager::Find (see xgenaimodule/C_LinkablesManager.h).
// This free helper goes straight from a container WUID to its inventory:
entitymodule::C_Inventory* GetInventoryForWuid(WUID w);  // sub_1815F457C: linkables lookup, then extract
                                                         //   the single C_Inventory. Returns the engine
                                                         //   null-inventory SENTINEL (not nullptr) if the
                                                         //   object has 0 or >1 inventories.

}}  // namespace wh::framework
