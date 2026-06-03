#pragma once

#include "WUID.h"
#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"

// -----------------------------------------------
// I_WUIDMappingProvider — WUID<->entity mapping interface
// -----------------------------------------------
// RTTI: .?AVI_WUIDMappingProvider@framework@wh@@
// Implemented by the per-type WUID registries: rpgmodule::C_SoulList,
// entitymodule::C_InventoryManager, entitymodule::C_ItemManager (each as a secondary base).
//
// VERIFIED 2026-06 from those vtables: the interface is exactly TWO pure virtual methods and
// has NO virtual destructor (the concrete registry owns the dtor — e.g. C_ItemManager's dtor
// is the third slot, after these two). [An earlier model had a placeholder ~dtor — corrected.]

namespace wh::framework {

class I_WUIDMappingProvider {
public:
    // [0] reverse: given a 16-byte object key (a CryGUID), return the owning WUID (or an invalid
    //     sentinel if not registered).
    //     impls: C_InventoryManager sub_1810653BC, C_ItemManager sub_18108BB9C.
    virtual WUID GetWuidForKey(const CryGUID& key) const = 0;

    // [1] forward: given a WUID, return the registered object's 16-byte mapped value (its
    //     entity/owner GUID), or a sentinel. Internally does the registry's slot lookup
    //     (C_InventoryManager -> sub_18055E7D8, C_ItemManager -> sub_180454638).
    //     impls: C_InventoryManager sub_181065380, C_ItemManager sub_18108BB5C.
    virtual CryGUID GetValueForWuid(WUID w) const = 0;
};
static_assert(sizeof(I_WUIDMappingProvider) == 0x08);

}  // namespace wh::framework
