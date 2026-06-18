#pragma once

#include <cstdint>

namespace wh::xgenaimodule {

class C_VariableIndex;
class C_Variable;
class C_IntelligentObject;

// ===========================================================================
// I_Intellect -- abstract base interface of an AI brain.
// ===========================================================================
// RTTI: .?AVI_Intellect@xgenaimodule@wh@@ ; vtable 0x1821a49b8 (25 slots, vptr-only, size 0x08).
// C_AIBrain implements all 25 of these and adds 11 more. Slot names recovered from the C_AIBrain
// overrides; pure slots (_vfNN) are subbrain-specific (implemented by C_AIBrainSingleSubb/MultiSubb).
// wh:: type -> vtable slot order == declaration order.
class I_Intellect {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_Intellect;
    virtual ~I_Intellect() = default;                                       // [0]  0x00
    virtual int64_t           SetOwner(C_IntelligentObject* owner) = 0;     // [1]  0x08
    virtual int64_t           ClearOwner() = 0;                             // [2]  0x10
    virtual bool              ConnectListener(void** listener) = 0;         // [3]  0x18  signal subscribe
    virtual void*             GetSignal() = 0;                              // [4]  0x20  &m_signal
    virtual int64_t           Enable(int mode) = 0;                         // [5]  0x28
    virtual bool              InitBuiltinVariables() = 0;                   // [6]  0x30
    virtual void              _vf07() = 0;                                  // [7]  0x38  (subbrain-specific)
    virtual void              ClearActiveFlag() = 0;                        // [8]  0x40
    virtual void              SetActiveFlag() = 0;                          // [9]  0x48
    virtual C_VariableIndex*  GetVarContainer() = 0;                        // [10] 0x50  -> &brain->m_varIndex
    virtual int64_t           _vf0B() = 0;                                  // [11] 0x58
    virtual bool              Serialize(void* node, void* ctx) = 0;         // [12] 0x60
    virtual bool              VisitVariables(void* reader, void* ctx) = 0;  // [13] 0x68
    virtual void              _vf0E() = 0;                                  // [14] 0x70  (subbrain-specific)
    virtual int64_t           QueryStateVariable(void* sink, void* ctx) = 0;// [15] 0x78
    virtual void              _vf10() = 0;                                  // [16] 0x80  (subbrain-specific)
    virtual void              _vf11() = 0;                                  // [17] 0x88  (subbrain-specific)
    virtual bool              GetFlagBit1() = 0;                            // [18] 0x90  m_flags & 2
    virtual bool              GetFlagBit2() = 0;                            // [19] 0x98  m_flags & 4
    virtual void              _vf14() = 0;                                  // [20] 0xA0  (subbrain-specific)
    virtual bool              GetFlagBit3() = 0;                            // [21] 0xA8  m_flags & 8
    virtual bool              GetFlagBit4() = 0;                            // [22] 0xB0  m_flags & 0x10
    virtual void              _vf17() = 0;                                  // [23] 0xB8  (subbrain-specific)
    virtual int64_t           GetSignalState() = 0;                         // [24] 0xC0
};
static_assert(sizeof(I_Intellect) == 0x08);

}  // namespace wh::xgenaimodule
