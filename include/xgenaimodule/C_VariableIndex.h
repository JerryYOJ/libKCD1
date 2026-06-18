#pragma once

#include <cstdint>
#include <vector>
#include "I_VariableIndex.h"

namespace wh::xgenaimodule {

class C_Variable;

// -----------------------------------------------
// S_VariableSlot -- one entry of C_VariableIndex's sorted variable vector (0x10 bytes).
// -----------------------------------------------
// The vector is kept sorted ascending by id; all lookups are a lower-bound binary search on id.
struct S_VariableSlot {
    uint16_t    m_id;        // +0x00  interned name id (global registry)
    uint8_t     m_flags;     // +0x02  bit0 = borrowed (not owned -> not released on Clear/Remove)
    uint8_t     _pad03[5];   // +0x03
    C_Variable* m_pVariable; // +0x08  the variable (owned unless borrowed)
};
static_assert(sizeof(S_VariableSlot) == 0x10);

// ===========================================================================
// C_VariableIndex -- the concrete AI/brain variable container.
// ===========================================================================
// RTTI: .?AVC_VariableIndex@xgenaimodule@wh@@ ; vtable 0x1821A39B0 (22 slots; adds 1 over the base).
// This is what C_AIBrain::GetVarContainer (brain vtbl[0x50]) returns -- the b_*/t_* variable store.
// Stored as a sorted std::vector<S_VariableSlot> (binary search by id). Size 0x28.
// Subclasses C_LocalVariableIndex / C_GlobalVariableIndex / C_OverwatchVariableIndex differ only by
// vtable (Local adds nothing; Global has no parent + extra state; Overwatch is MI -- not modeled).
class C_VariableIndex : public I_VariableIndex {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_VariableIndex;
    virtual void* _vf21_getParent2() { return nullptr; }   // [21] 0xA8  C_VariableIndex-added (ICF-folded with GetParent)

    std::vector<S_VariableSlot> m_variables;  // +0x10  (0x18) sorted-by-id variable slots
};
static_assert(sizeof(C_VariableIndex) == 0x28);

}  // namespace wh::xgenaimodule
