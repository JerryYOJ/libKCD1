#pragma once

// -----------------------------------------------
// I_SoulResolver — soul lookup interface
// -----------------------------------------------
// RTTI: .?AVI_SoulResolver@rpgmodule@wh@@
// Primary base of C_SoulList. Provides entity→soul resolution.

namespace wh::rpgmodule {

class I_SoulResolver {
public:
    virtual ~I_SoulResolver() = default;
};
static_assert(sizeof(I_SoulResolver) == 0x08);

}  // namespace wh::rpgmodule
