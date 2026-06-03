#pragma once

#include "../framework/InplaceVector.h"
// <cstdint> / <vector> come from PCH.h.

// ===========================================================================
// wh::entitymodule  -  the per-item runtime-data store at C_Item+0x70.
//
// A keyed InplaceVector (inline cap 4) of {typeId, I_ItemRuntimeData*} records.
// Mutate in-process via C_Item::SetRuntimeData (sub_1804544CC) — it runs the records'
// Clone/Release (slot0/slot1) lifecycle; the C++ container API does not. Reads are
// fine. typeId = sub_1802D3114(itemClassData).
// ===========================================================================

namespace wh { namespace entitymodule {

class I_ItemRuntimeData;   // record element, held by its abstract base (see I_ItemRuntimeData.h)

struct S_ItemRuntimeDataEntry {
    uint32_t           typeId;                      // 00  runtime-data class id
    uint32_t           _pad04;                      // 04
    I_ItemRuntimeData* obj;                         // 08
};

using S_ItemRuntimeDataTable = wh::shared::InplaceVector<S_ItemRuntimeDataEntry, 4>;
static_assert(sizeof(S_ItemRuntimeDataTable) == 0x70);

}} // namespace wh::entitymodule
