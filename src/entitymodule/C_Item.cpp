#include "entitymodule/C_Item.h"
#include "Offsets/Offsets.h"

// C_Item engine-function forwarders.

namespace wh { namespace entitymodule {

I_ItemRuntimeData* C_Item::GetRuntimeData()
{
    using Fn = I_ItemRuntimeData* (__fastcall*)(C_Item*);
    static REL::Relocation<Fn> fn{ REL::ID(32) };  // C_Item::GetRuntimeData
    return fn(this);
}

void C_Item::SetRuntimeData(uint32_t typeId, I_ItemRuntimeData* obj)
{
    using Fn = void (__fastcall*)(C_Item*, uint32_t, I_ItemRuntimeData*);
    static REL::Relocation<Fn> fn{ REL::ID(15) };  // C_Item::SetRuntimeData
    fn(this, typeId, obj);
}

}} // namespace wh::entitymodule
