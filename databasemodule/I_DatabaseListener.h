#pragma once

// -----------------------------------------------
// I_DatabaseListener — database change callback interface
// -----------------------------------------------
// RTTI: .?AVI_DatabaseListener@databasemodule@wh@@
// Inherited by C_SoulList, C_FactionManager, etc. to receive
// notifications when database tables are modified.

namespace wh::databasemodule {

class I_DatabaseListener {
public:
    virtual ~I_DatabaseListener() = default;
};
static_assert(sizeof(I_DatabaseListener) == 0x08);

}  // namespace wh::databasemodule
