#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindShop — Lua "Shops" table
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindShop@shopmodule@wh@@
// vtable: 0x182315530
// Constructor: sub_1812A4F44
// Registration: sub_1812A8964
// Size: 0x78

namespace wh::shopmodule {

class C_ScriptBindShop : public CScriptableBase {
public:
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68
    void*                   m_pUnk70;           // +0x70  initialized to 0

    // Lua methods (21)
    int OpenInventory(IFunctionHandler* pH, EntityId entityId);                     // 0x1812A83EC
    int OpenInventoryForItem(IFunctionHandler* pH, EntityId itemId);                // 0x1812A8450
    int AcceptTransaction(IFunctionHandler* pH, EntityId entityId, float priceMod); // 0x1812A5AE0
    int CancelTransaction(IFunctionHandler* pH, EntityId entityId);                 // 0x1812A6224
    int GetShopMoney(IFunctionHandler* pH, EntityId entityId);                      // 0x1812A6E7C
    int OnPropertyChange(IFunctionHandler* pH, const char* shopDBId, EntityId entityId); // 0x1812A8330
    int OpenShop(IFunctionHandler* pH, const char* shopDBId);                       // 0x18055DA80
    int CloseShop(IFunctionHandler* pH, const char* shopDBId);                      // 0x18055DB28
    int IsLinkedWithShop(IFunctionHandler* pH, EntityId entityId);                  // 0x1812A79D8
    int FindItemInShop(IFunctionHandler* pH, EntityId entityId);                    // 0x1812A6618
    int FindShopInventoryForItem(IFunctionHandler* pH, EntityId entityId);          // 0x1812A66A8
    int IsShopOpened(IFunctionHandler* pH, const char* shopDBId);                   // 0x1812A7A28
    int RestockShop(IFunctionHandler* pH, const char* shopDBId, bool clean);        // 0x1812A93F4
    int EnableRestockingOnOpen(IFunctionHandler* pH, const char* shopDBId, bool enable); // 0x1812A65E4
    int GetBusinessHoursBegin(IFunctionHandler* pH, const char* shopDBId);          // 0x1812A6738
    int GetBusinessHoursEnd(IFunctionHandler* pH, const char* shopDBId);            // 0x1812A679C
    int GetShopDBIdByLinkedEntityId(IFunctionHandler* pH, EntityId entityId);       // 0x1812A6C20
    int GetShopDBIdByKeeper(IFunctionHandler* pH, EntityId entityId);               // 0x18066E068
    int AssignShopKeeper(IFunctionHandler* pH, const char* shopDbId, EntityId entityId); // 0x1812A5FE0
    int UnassignShopKeeperFromShops(IFunctionHandler* pH, EntityId entityId);       // 0x1812A9A90
    int UnassignAllShopKeepersFromShop(IFunctionHandler* pH, const char* shopDbId); // 0x1812A9A58
};
static_assert(sizeof(C_ScriptBindShop) == 0x78);

} // namespace wh::shopmodule
