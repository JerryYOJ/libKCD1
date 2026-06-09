#pragma once

#include <cstdint>

namespace Offsets { struct IEntity; }

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatActor -- pure interface for combat actors.
//
// RTTI: .?AVI_CombatActor@combatmodule@wh@@
// vtable @ 0x18222a648
// Scalar deleting dtor: sub_180F460A4 (frees 8 bytes -- interface-only)
// Size: 0x08 (just a vtable pointer)
//
// Implemented by C_CombatActor and C_CombatPlayer.
//
// Warhorse classes are NOT interfuscator-shuffled — slot indices are stable.
// ---------------------------------------------------------------------------
class I_CombatActor {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatActor;
    virtual ~I_CombatActor() = default;                             // [0]

    // All slots below are purecall in I_CombatActor's own vtable.
    // Signatures and names are VERIFIED where noted from C_CombatActor
    // implementation vtable at 0x182228be8.
    // Slot ordering is NOT stable (interfuscator-shuffled).

    virtual void unk_1() = 0;                                       // [1] sub_180564390, reads *(entity+0xBD8) as byte
    virtual void unk_2() = 0;                                       // [2] sub_1804550E0, combat distance/range check
    virtual void unk_3() = 0;                                       // [3] sub_1806FABE0, reads *(entity+0xCFC) as byte
    virtual void unk_4() = 0;                                       // [4] sub_1805637FC (complex operation)
    virtual void unk_5() = 0;                                       // [5] sub_180563F10 (operation)
    virtual Offsets::IEntity* GetEntity() const = 0;                 // [6] sub_18045E1C0, VERIFIED: returns *(this+0x4A0)
    virtual uint32_t GetEntityId() const = 0;                       // [7] sub_180695320, VERIFIED: returns *(entity+0x30)
    virtual void unk_8() = 0;                                       // [8] sub_1804576A8, reads entity subsystem via *(entity+0xCA0)
    virtual void unk_9() = 0;                                       // [9] sub_18045883C, reads entity subsystem via *(entity+0xCA0)
    virtual void unk_10() = 0;                                      // [10] sub_180F49204, reads entity subsystem via *(entity+0xCA0), vfunc[1]
    virtual void unk_11() = 0;                                      // [11] sub_180F49224, reads entity subsystem via *(entity+0xCA0), vfunc[2]
    virtual void unk_12() = 0;                                      // [12] sub_180F49244, gets entity name string
    virtual uint32_t unk_13() const = 0;                             // [13] sub_1804936C0, returns *(entity+0xBEC) as uint
    virtual uint32_t unk_14() const = 0;                             // [14] sub_180493B80, returns *(entity+0xBE0) as uint
    virtual void unk_15() = 0;                                      // [15] sub_1804317F0 (complex, 0x1ad bytes)
};

}  // namespace wh::combatmodule
