#pragma once

#include <cstdint>

// -----------------------------------------------
// I_POI — POI interface (map points of interest)
// -----------------------------------------------
// RTTI: .?AVI_POI@rpgmodule@wh@@
// Pure interface — no data members. All member data lives in C_POI.
// Located at C_POI+0x10 (second base in MI layout)
// Binary vtable at 0x1826d3e38 (35+ slots, from C_POI impl)
//
// Flag bits (C_POI member, accessed via HasFlag/GetFlags):
//   bit 0 (0x01) = IsDiscoverable
//   bit 1 (0x02) = IsFastTravel
//   bit 2 (0x04) = IsProcedural
//   bit 3 (0x08) = IsBed
//   bit 4 (0x10) = IsFollowsEntity
//   bit 5 (0x20) = IsUnloaded
//   bit 6 (0x40) = IsNotDiscoverableByLocation

namespace wh::rpgmodule {

class I_POI {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_POI;
    virtual void* GetInlineData() {}            // [0]  0x00
    virtual void _vf1() {}                      // [1]  0x08
    virtual void _vf2() {}                      // [2]  0x10
    virtual void _vf3() {}                      // [3]  0x18
    virtual void _vf4() {}                      // [4]  0x20
    virtual void _vf5() {}                      // [5]  0x28
    virtual uint32_t GetInitialState() {}       // [6]  0x30
    virtual void _vf7() {}                      // [7]  0x38
    virtual uint32_t GetEntityId() {}           // [8]  0x40
    virtual void _vf9() {}                      // [9]  0x48
    virtual void _vf10() {}                     // [10] 0x50
    virtual void _vf11() {}                     // [11] 0x58
    virtual uint16_t GetFlags() {}              // [12] 0x60
    virtual void _vf13() {}                     // [13] 0x68
    virtual bool HasFlag(uint16_t f) {}         // [14] 0x70
    virtual void _vf15() {}                     // [15] 0x78
    virtual void _vf16() {}                     // [16] 0x80
    virtual void _vf17() {}                     // [17] 0x88
    virtual void _vf18() {}                     // [18] 0x90
    virtual void _vf19() {}                     // [19] 0x98
    virtual void _vf20() {}                     // [20] 0xA0
    virtual void _vf21() {}                     // [21] 0xA8
    virtual bool IsAvailable() {}               // [22] 0xB0
    virtual void _vf23() {}                     // [23] 0xB8
    virtual void _vf24() {}                     // [24] 0xC0
    virtual void _vf25() {}                     // [25] 0xC8
    virtual int32_t GetState() {}               // [26] 0xD0
    virtual void _vf27() {}                     // [27] 0xD8
    virtual void _vf28() {}                     // [28] 0xE0
    virtual void _vf29() {}                     // [29] 0xE8
    virtual void _vf30() {}                     // [30] 0xF0
    virtual void _vf31() {}                     // [31] 0xF8
    virtual void _vf32() {}                     // [32] 0x100
    virtual void _vf33() {}                     // [33] 0x108
    virtual void _vf34() {}                     // [34] 0x110
};
static_assert(sizeof(I_POI) == 0x08);

}  // namespace wh::rpgmodule
