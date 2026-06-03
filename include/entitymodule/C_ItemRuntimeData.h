#pragma once

// ===========================================================================
// Aggregator for the item runtime-data class family. Each class now lives in its
// own header (one class per file); include this to pull in the whole hierarchy.
//
//   I_ItemRuntimeData            (root, abstract)         I_ItemRuntimeData.h
//     C_EquippableItemRuntimeData  (intermediate, abstract) C_EquippableItemRuntimeData.h
//       C_WeaponRuntimeData        (concrete)              C_WeaponRuntimeData.h
//       C_ArmorRuntimeData         (concrete)              C_ArmorRuntimeData.h
//       C_ConsumableRuntimeData    (concrete)              C_ConsumableRuntimeData.h
//   S_ItemRuntimeDataEntry / S_ItemRuntimeDataTable        S_ItemRuntimeDataTable.h
//
// C_Item only needs the table (S_ItemRuntimeDataTable.h); it does not pull this in.
// ===========================================================================

#include "I_ItemRuntimeData.h"
#include "C_EquippableItemRuntimeData.h"
#include "C_WeaponRuntimeData.h"
#include "C_ArmorRuntimeData.h"
#include "C_ConsumableRuntimeData.h"
#include "S_ItemRuntimeDataTable.h"
