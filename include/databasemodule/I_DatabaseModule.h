#pragma once

#include <cstdint>

namespace wh::databasemodule {

class I_ObjectDatabase;
class C_ObjectDatabaseManager;

// I_DatabaseModule — interface for the database module singleton.
// Provides access to all loaded databases and the dynamic enum system.
//
// vtable @ 0x1822c1e10 (all pure virtual)
class I_DatabaseModule {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_DatabaseModule;
    virtual ~I_DatabaseModule() = 0;                                    // [0]
    virtual bool Initialize() = 0;                                      // [1]
    virtual void Shutdown() = 0;                                        // [2]
    virtual void Update() = 0;                                          // [3]
    virtual int GetDatabaseCount() const = 0;                           // [4]
    virtual C_ObjectDatabaseManager* GetDatabaseManager() const = 0;    // [5]
    virtual I_ObjectDatabase* FindDatabase(const char* name) const = 0; // [6]
    virtual I_ObjectDatabase* GetDatabase(int index) const = 0;         // [7]
    virtual void RegisterDatabase(I_ObjectDatabase* db) = 0;            // [8]
    virtual bool IsLoaded() const = 0;                                  // [9]
    virtual bool IsEditorMode() const = 0;                              // [10]
    virtual void LoadAll() = 0;                                         // [11]
    virtual bool ReloadDatabase(const char* name) = 0;                  // [12]
    virtual void* GetDynamicEnumManager() const = 0;                    // [13]
    virtual void* GetDynamicEnum(const char* name) const = 0;           // [14]
};

}  // namespace wh::databasemodule
