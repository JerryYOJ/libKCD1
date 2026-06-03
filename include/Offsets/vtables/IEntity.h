#pragma once
#include <cstdint>

typedef unsigned int EntityId;
#include "IScriptTable.h"

// -----------------------------------------------
// IEntity — Binary vtable order (interfuscated)
// -----------------------------------------------
// CEntity RTTI: .?AVCEntity@@ (vtable at 0x1821A54C8). Cracked by tracing vtable calls.
// Verified: GetId, GetName, GetWorldPos, GetProxy, GetFlags/SetFlags, local transform accessors.
//
// CEntity memory layout (key offsets):
//   +0x0C: EntityId (uint32)
//   +0x30: local pos Vec3 (3 floats)
//   +0x3C: local rot Quat (4 floats)
//   +0x4C: local scale Vec3 (3 floats)
//   +0x58: world Matrix34 (12 floats, 3x4 row-major)
//   +0x64/0x74/0x84: world pos X/Y/Z (readable directly)
//   +0xE8: entity name (char*)
//   +0xF8: reference count (uint16)

struct IEntityProxy;
struct Matrix34;
struct Vec3;
struct Quat;

namespace Offsets {

struct IEntityScriptProxy {
    virtual void _vf0() = 0;                                        // [0]  0x00
    virtual void _vf1() = 0;                                        // [1]  0x08
    virtual void _vf2() = 0;                                        // [2]  0x10
    virtual void _vf3() = 0;                                        // [3]  0x18
    virtual void _vf4() = 0;                                        // [4]  0x20
    virtual void _vf5() = 0;                                        // [5]  0x28
    virtual void _vf6() = 0;                                        // [6]  0x30
    virtual void _vf7() = 0;                                        // [7]  0x38
    virtual void _vf8() = 0;                                        // [8]  0x40
    virtual void _vf9() = 0;                                        // [9]  0x48
    virtual void _vf10() = 0;                                       // [10] 0x50
    virtual void _vf11() = 0;                                       // [11] 0x58
    virtual void _vf12() = 0;                                       // [12] 0x60
    virtual void _vf13() = 0;                                       // [13] 0x68
    virtual void _vf14() = 0;                                       // [14] 0x70
    virtual void _vf15() = 0;                                       // [15] 0x78
    virtual void _vf16() = 0;                                       // [16] 0x80
    virtual IScriptTable* GetScriptTable() = 0;                      // [17] 0x88  confirmed from sub_1803B9A0C
};

struct IEntity {
    virtual void _vf0() = 0;                                        // [0]  0x00
    virtual EntityId GetId() const = 0;                              // [1]  0x08  return *(uint32*)(this+0xC)
    virtual uint64_t GetGuid() const = 0;                            // [2]  0x10  return *(QWORD*)(this+0x10)
    virtual void* GetClass() const = 0;                              // [3]  0x18  return *(this+0x20) (IEntityClass*)
    virtual void* GetArchetype() const = 0;                          // [4]  0x20  return *(this+0x28)
    virtual void SetFlags(uint32_t flags) = 0;                       // [5]  0x28  *(this+0x18) = flags, notifies proxies
    virtual uint32_t GetFlags() const = 0;                           // [6]  0x30  return *(uint32*)(this+0x18)
    virtual void _vf7() = 0;                                        // [7]  0x38
    virtual void _vf8() = 0;                                        // [8]  0x40
    virtual bool CheckFlags(uint32_t mask) const = 0;                // [9]  0x48  return (mask & *(this+0x18)) == mask
    virtual void SetFlagsExtended(uint16_t flags) = 0;               // [10] 0x50  *(uint16*)(this+0x1C) = flags
    virtual uint16_t GetFlagsExtended() const = 0;                   // [11] 0x58  return *(uint16*)(this+0x1C)
    virtual void _vf12() = 0;                                       // [12] 0x60
    virtual void _vf13() = 0;                                       // [13] 0x68
    virtual void _vf14() = 0;                                       // [14] 0x70
    virtual void _vf15() = 0;                                       // [15] 0x78
    virtual void _vf16() = 0;                                       // [16] 0x80
    virtual const char* GetName() const = 0;                         // [17] 0x88  return *(char**)(this+0xE8)
    virtual const char* GetDebugName() const = 0;                    // [18] 0x90  returns "name(ClassName)"
    virtual void _vf19() = 0;                                       // [19] 0x98
    virtual void _vf20() = 0;                                       // [20] 0xA0
    virtual void _vf21() = 0;                                       // [21] 0xA8
    virtual void _vf22() = 0;                                       // [22] 0xB0
    virtual void _vf23() = 0;                                       // [23] 0xB8
    virtual void _vf24() = 0;                                       // [24] 0xC0
    virtual void _vf25() = 0;                                       // [25] 0xC8
    virtual void _vf26() = 0;                                       // [26] 0xD0
    virtual void GetWorldTM(Matrix34& out) const = 0;                // [27] 0xD8  fills 12-float Matrix34
    virtual void _vf28() = 0;                                       // [28] 0xE0
    virtual void SetWorldTM(const Matrix34& tm) = 0;                 // [29] 0xE8
    virtual void _vf30() = 0;                                       // [30] 0xF0
    virtual const Matrix34* GetWorldTMPtr() const = 0;               // [31] 0xF8  return this+0x58
    virtual void _vf32() = 0;                                       // [32] 0x100
    virtual void _vf33() = 0;                                       // [33] 0x108
    virtual void _vf34() = 0;                                       // [34] 0x110
    virtual void _vf35() = 0;                                       // [35] 0x118
    virtual void SetLocalPos(const Vec3& pos, int flags = 0) = 0;   // [36] 0x120  writes this+0x30, marks dirty |2
    virtual Vec3* GetLocalPosPtr() = 0;                              // [37] 0x128  return this+0x30
    virtual void SetLocalRot(const Quat& rot, int flags = 0) = 0;   // [38] 0x130  writes this+0x3C, marks dirty |4
    virtual Quat* GetLocalRotPtr() = 0;                              // [39] 0x138  return this+0x3C
    virtual void SetLocalScale(const Vec3& scale, int flags = 0) = 0;// [40] 0x140  writes this+0x4C, marks dirty |8
    virtual Vec3* GetLocalScalePtr() = 0;                            // [41] 0x148  return this+0x4C
    virtual void SetPosRotScale(const Vec3& pos, const Quat& rot, const Vec3& scale, int flags = 0) = 0; // [42] 0x150
    virtual void GetWorldPos(Vec3& out) const = 0;                   // [43] 0x158  reads translation from world matrix
    virtual void _vf44() = 0;                                       // [44] 0x160
    virtual void _vf45() = 0;                                       // [45] 0x168
    virtual void _vf46() = 0;                                       // [46] 0x170
    virtual void _vf47() = 0;                                       // [47] 0x178
    virtual void _vf48() = 0;                                       // [48] 0x180
    virtual void _vf49() = 0;                                       // [49] 0x188
    virtual void _vf50() = 0;                                       // [50] 0x190
    virtual void _vf51() = 0;                                       // [51] 0x198
    virtual void _vf52() = 0;                                       // [52] 0x1A0
    virtual void _vf53() = 0;                                       // [53] 0x1A8
    virtual void _vf54() = 0;                                       // [54] 0x1B0
    virtual void _vf55() = 0;                                       // [55] 0x1B8
    virtual void _vf56() = 0;                                       // [56] 0x1C0
    virtual void _vf57() = 0;                                       // [57] 0x1C8
    virtual void _vf58() = 0;                                       // [58] 0x1D0
    virtual void _vf59() = 0;                                       // [59] 0x1D8
    virtual void _vf60() = 0;                                       // [60] 0x1E0
    virtual void _vf61() = 0;                                       // [61] 0x1E8
    virtual void _vf62() = 0;                                       // [62] 0x1F0
    virtual void _vf63() = 0;                                       // [63] 0x1F8
    virtual void _vf64() = 0;                                       // [64] 0x200
    virtual void _vf65() = 0;                                       // [65] 0x208
    virtual void _vf66() = 0;                                       // [66] 0x210
    virtual IEntityProxy* GetProxy(int proxyType) const = 0;         // [67] 0x218  confirmed: arg 2=ENTITY_PROXY_SCRIPT
    virtual void _vf68() = 0;                                       // [68] 0x220
    virtual void _vf69() = 0;                                       // [69] 0x228
    virtual void _vf70() = 0;                                       // [70] 0x230
    virtual void _vf71() = 0;                                       // [71] 0x238
    virtual void _vf72() = 0;                                       // [72] 0x240
    virtual void _vf73() = 0;                                       // [73] 0x248
    virtual void _vf74() = 0;                                       // [74] 0x250
    virtual void _vf75() = 0;                                       // [75] 0x258
    virtual void _vf76() = 0;                                       // [76] 0x260
    virtual void _vf77() = 0;                                       // [77] 0x268
    virtual void _vf78() = 0;                                       // [78] 0x270
    virtual void _vf79() = 0;                                       // [79] 0x278
    virtual void _vf80() = 0;                                       // [80] 0x280
    virtual void _vf81() = 0;                                       // [81] 0x288
    virtual void _vf82() = 0;                                       // [82] 0x290
    virtual void _vf83() = 0;                                       // [83] 0x298
    virtual void _vf84() = 0;                                       // [84] 0x2A0
    virtual void _vf85() = 0;                                       // [85] 0x2A8
    virtual void _vf86() = 0;                                       // [86] 0x2B0
    virtual void _vf87() = 0;                                       // [87] 0x2B8
    virtual void _vf88() = 0;                                       // [88] 0x2C0
    virtual void _vf89() = 0;                                       // [89] 0x2C8
    virtual void _vf90() = 0;                                       // [90] 0x2D0
    virtual void _vf91() = 0;                                       // [91] 0x2D8  complex 3-arg proxy function (NOT SetFlags)
    virtual void _vf92() = 0;                                       // [92] 0x2E0  complex 2-arg proxy function (NOT GetFlags)
};

}  // namespace Offsets
