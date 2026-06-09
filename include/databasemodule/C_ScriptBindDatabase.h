#pragma once
#include "../crysystem/CScriptableBase.h"

// C_ScriptBindDatabase — Lua "Database" table
// RTTI: .?AVC_ScriptBindDatabase@databasemodule@wh@@  vtable: 0x1822c1fb8
// Constructed inline in sub_180F37930  Registration: sub_180F3A708  Size: 0x68

namespace wh::databasemodule {
class C_ScriptBindDatabase : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindDatabase;
    void* m_pDatabaseManager;  // +0x60
    // int LoadTable(IFunctionHandler* pH);                                            // 0x180F3A278
    // int GetTableInfo(IFunctionHandler* pH);                                         // 0x180F39F54
    // int GetColumnInfo(IFunctionHandler* pH, const char* tableName, int columnIdx);  // 0x180F39B5C
    // int GetTableLine(IFunctionHandler* pH, const char* tableName, int lineIdx);     // 0x180F3A064
    // int GetTableColumnData(IFunctionHandler* pH, const char* tableName, int columnIdx); // 0x180F39D3C
};
static_assert(sizeof(C_ScriptBindDatabase) == 0x68);
} // namespace wh::databasemodule
