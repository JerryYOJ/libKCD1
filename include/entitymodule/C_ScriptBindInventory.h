#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindInventory — entity script binding for inventories
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindInventory@entitymodule@wh@@
// vtable: 0x1822e44d8
// Constructor: sub_1810BA0D0
// Registration: sub_1810DFBB8
// Size: 0x70

namespace wh::entitymodule {

class C_ScriptBindInventory : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindInventory;
    void*  m_pContext;          // +0x60
    void*  m_pEntitySystem;    // +0x68  IEntitySystem*

    // -- Direct Lua methods --
    // int AddItem(IFunctionHandler* pH, SmartScriptTable item);                       // 0x1810BDF68
    // int RemoveItem(IFunctionHandler* pH, EntityId id, int count);                   // 0x1810C267C
    // int DeleteItem(IFunctionHandler* pH, EntityId id, int count);                   // 0x1810C2690
    // int MoveItemOfClass(IFunctionHandler* pH, SmartScriptTable inv, const char* guid, int count, bool changeOwner); // 0x1810D5998
    // int RemoveAllItems(IFunctionHandler* pH);                                       // 0x1810E0948
    // int Validate(IFunctionHandler* pH);                                             // 0x1810EDCD0 (noop)
    // int Dump(IFunctionHandler* pH);                                                 // 0x1810C4A28
    // int GetCount(IFunctionHandler* pH);                                             // 0x1810C8570
    // int GetCountOfCategory(IFunctionHandler* pH, const char* categoryName);         // 0x1810C85B8
    // int GetCountOfClass(IFunctionHandler* pH, const char* classId);                 // 0x1810C8614
    // int GetId(IFunctionHandler* pH);                                                // 0x1810C98CC
    // int HasItem(IFunctionHandler* pH, EntityId itemId);                             // 0x1810CD4E4
    // int FindItem(IFunctionHandler* pH, const char* classId);                        // 0x1810C61F4
    // int RemoveMoney(IFunctionHandler* pH, int count);                               // 0x1810E0E5C
    // int GetMoney(IFunctionHandler* pH);                                             // 0x1806CC1E4
    // int CreateItem(IFunctionHandler* pH, const char* classId, float health, int amount); // 0x1810C1AD4
    // int GetInventoryTable(IFunctionHandler* pH);                                    // 0x1810C99E0
};
static_assert(sizeof(C_ScriptBindInventory) == 0x70);

} // namespace wh::entitymodule
