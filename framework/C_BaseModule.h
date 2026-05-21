#pragma once

namespace wh::framework {

// C_BaseModule — base class for all Warhorse engine modules.
// Provides module lifecycle integration (Init, Shutdown, Update).
// Inherited by C_DatabaseModule, C_CombatModule, C_EntityModule, etc.
//
// RTTI: .?AVC_BaseModule@framework@wh@@
// vtable @ 0x1829ecbd0
//
// Layout not fully recovered. Provides virtual Init/Shutdown/Update
// and module name/registration with the framework module system.
struct C_BaseModule {
    virtual ~C_BaseModule() = default;
    // ... lifecycle virtuals
};

}  // namespace wh::framework
