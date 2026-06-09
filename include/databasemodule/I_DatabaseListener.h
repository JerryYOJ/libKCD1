#pragma once

// -----------------------------------------------
// I_DatabaseListener — database change callback interface (minimal)
// -----------------------------------------------
// RTTI: .?AVI_DatabaseListener@databasemodule@wh@@
// Inherited by C_SoulList, C_FactionManager, etc. to receive
// notifications when database tables are modified.
// NOTE: Full I_DatabaseListener with OnDatabaseLoaded/OnDatabaseUnloaded
// is defined in I_DatabaseModule.h. This is the minimal single-vfunc version
// used by soul/faction systems.

namespace wh::databasemodule {

class I_DatabaseListener {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_DatabaseListener;
    virtual ~I_DatabaseListener() = default;
};
static_assert(sizeof(I_DatabaseListener) == 0x08);

}  // namespace wh::databasemodule
