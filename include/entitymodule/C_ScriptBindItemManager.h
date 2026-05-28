#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindItemManager — Lua "ItemManager" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindItemManager@entitymodule@wh@@
// vtable: 0x1822e44b0
// Constructor: sub_1810BA13C
// Registration: sub_1810DFE84
// Size: 0x68

namespace wh::entitymodule {

class C_ScriptBindItemManager : public CScriptableBase {
public:
    void* m_pContext;  // +0x60

    // -- Direct Lua methods --
    // int CreateItem(IFunctionHandler* pH, const char* classId, float health, int amount);    // 0x1810C1BB8
    // int RemoveItem(IFunctionHandler* pH, EntityId itemId);                                  // 0x1810E0BD0
    // int GetItem(IFunctionHandler* pH, EntityId itemId);                                     // 0x1810C9A98
    // int GetItemUIName(IFunctionHandler* pH, const char* classId);                           // 0x1810C9D28
    // int GetItemName(IFunctionHandler* pH, const char* classId);                             // 0x1810C9C48
    // int SetItemOwner(IFunctionHandler* pH, EntityId itemId, EntityId ownerId, bool markAsStolen); // 0x1810E6298
    // int GetItemOwner(IFunctionHandler* pH, EntityId id);                                    // 0x1810C9CC8
    // int IsItemOversized(IFunctionHandler* pH, EntityId id);                                 // 0x1810D2B2C
    // int AddOnEquipBuff(IFunctionHandler* pH, EntityId itemId, const char* buff_id, bool add); // 0x1810BE0C4
};
static_assert(sizeof(C_ScriptBindItemManager) == 0x68);

} // namespace wh::entitymodule
