#include "entitymodule/C_ItemManager.h"
#include "Offsets/Offsets.h"

// C_ItemManager engine-function forwarder. The lookup takes the embedded slot-table base
// (this + 0x18) and a WUID, and returns the C_Item* (or null). See Offsets.h for the offset.

namespace wh { namespace entitymodule {

C_Item* C_ItemManager::LookupByWUID(wh::framework::WUID w) const
{
    using Fn = C_Item* (__fastcall*)(const void*, const wh::framework::WUID*);
    const void* slotTable = reinterpret_cast<const uint8_t*>(this) + 0x18;
    return reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kItemLookupByWUIDOffset)(slotTable, &w);
}

}} // namespace wh::entitymodule
