#pragma once

#include <cstdint>

// -----------------------------------------------
// I_SoulResolver — soul lookup/creation interface
// -----------------------------------------------
// RTTI: .?AVI_SoulResolver@rpgmodule@wh@@
// Primary base of C_SoulList. Provides entity→soul resolution.
// vtable: 0x1826d9fc0 (C_SoulList implementation)
//
// The module registry singleton (sub_180430AA4 → qword_1834FFD10)
// stores C_SoulList* at offset +0x158, enabling:
//   *(registry + 0x158)->FindOrCreateSoulByEntity(entity)
//
// C_Actor::AttachSoul (0x18030E184) uses this path to resolve
// the soul for its entity and stores the result at C_Actor+0x650.

struct IEntity;

namespace wh::rpgmodule {

class I_Soul;

class I_SoulResolver {
public:
    virtual ~I_SoulResolver() = default;                                // [0]
    virtual void vf01() {}                                              // [1]
    virtual void vf02() {}                                              // [2]
    virtual void vf03() {}                                              // [3]
    virtual void vf04() {}                                              // [4]
    virtual void vf05() {}                                              // [5]
    virtual void vf06() {}                                              // [6]
    virtual void vf07() {}                                              // [7]
    virtual void vf08() {}                                              // [8]
    virtual void vf09() {}                                              // [9]
    virtual void vf10() {}                                              // [10]
    virtual void vf11() {}                                              // [11]
    virtual I_Soul* FindOrCreateSoulByEntity(Offsets::IEntity* pEntity) = 0;     // [12] 0x18030E510
};

} // namespace wh::rpgmodule
