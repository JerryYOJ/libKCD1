#pragma once

// -----------------------------------------------
// I_WUIDMappingProvider — WUID mapping interface
// -----------------------------------------------
// RTTI: .?AVI_WUIDMappingProvider@framework@wh@@
// Inherited by C_SoulList to provide entity WUID mappings.

namespace wh::framework {

class I_WUIDMappingProvider {
public:
    virtual ~I_WUIDMappingProvider() = default;
};
static_assert(sizeof(I_WUIDMappingProvider) == 0x08);

}  // namespace wh::framework
