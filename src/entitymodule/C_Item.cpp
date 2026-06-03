#include "entitymodule/C_Item.h"
#include "Offsets/Offsets.h"

// C_Item engine-function forwarders. Each casts (WHGame.dll base + offset) to the game
// function's signature and calls it with `this`. See Offsets.h for the offsets.

namespace wh { namespace entitymodule {

I_ItemRuntimeData* C_Item::GetRuntimeData()
{
    using Fn = I_ItemRuntimeData* (__fastcall*)(C_Item*);
    return reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kItemGetRuntimeDataOffset)(this);
}

void C_Item::SetRuntimeData(uint32_t typeId, I_ItemRuntimeData* obj)
{
    using Fn = void (__fastcall*)(C_Item*, uint32_t, I_ItemRuntimeData*);
    reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kItemSetRuntimeDataOffset)(this, typeId, obj);
}

}} // namespace wh::entitymodule
