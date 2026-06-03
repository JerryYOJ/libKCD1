#include "entitymodule/C_InventoryManager.h"
#include "Offsets/Offsets.h"

// C_InventoryManager engine-function forwarder. The lookup takes the embedded slot-table base
// (this + 0x10) and a WUID, and returns the C_Inventory* (or null). See Offsets.h for the offset.

namespace wh { namespace entitymodule {

C_Inventory* C_InventoryManager::LookupByWUID(wh::framework::WUID w) const
{
    using Fn = C_Inventory* (__fastcall*)(const void*, const wh::framework::WUID*);
    const void* slotTable = reinterpret_cast<const uint8_t*>(this) + 0x10;
    return reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kInventoryLookupByWUIDOffset)(slotTable, &w);
}

}} // namespace wh::entitymodule
