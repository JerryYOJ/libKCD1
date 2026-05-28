#pragma once

#include <cstdint>
#include <map>

// -----------------------------------------------
// C_UIMapCloudAtlas
// -----------------------------------------------
// RTTI: .?AVC_UIMapCloudAtlas@guimodule@wh@@
// Constructor: sub_181142590
// Binary vtable at 0x1826d2a38 (4 slots)
// Size: 0x18

namespace wh::guimodule {

class C_UIMapCloudAtlas {
public:
    virtual void _vf0() {};   // [0] 0x00
    virtual void _vf1() {};   // [1] 0x08
    virtual void _vf2() {};   // [2] 0x10
    virtual void _vf3() {};   // [3] 0x18

    std::map<const char*, void*, CStrLess> m_cloudMap; // +0x08
};
static_assert(sizeof(C_UIMapCloudAtlas) == 0x18);

}  // namespace wh::guimodule
