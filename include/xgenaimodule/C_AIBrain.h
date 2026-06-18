#pragma once

#include <cstdint>
#include <vector>
#include "I_Intellect.h"
#include "C_VariableIndex.h"

namespace wh::xgenaimodule {

class C_IntelligentObject;
class C_Variable;

// ===========================================================================
// C_AIBrain -- an NPC's AI brain (the b_*/t_* brain-variable owner).
// ===========================================================================
// RTTI: .?AVC_AIBrain@xgenaimodule@wh@@ ; vtable 0x1821a4a88 (36 slots) ; ctor sub_180279134.
// Held by C_IntelligentObject at +0x118 (C_IntelligentObject::m_pBrain). Abstract; the concrete
// objects are C_AIBrainSingleSubb (0x128) and C_AIBrainMultiSubb (0x1A0), both built on this base
// (selected by C_BrainMaker from the brain config). The variable container is an EMBEDDED
// C_VariableIndex subobject at +0xF0 (NOT a pointer) -- GetVarContainer (vtbl[0x50]) returns &m_varIndex.
// Size 0x118.
class C_AIBrain : public I_Intellect {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AIBrain;
    // --- 11 virtuals introduced by C_AIBrain (after I_Intellect's 25) ---
    virtual void  _vf19_finalize() = 0;                                 // [25] 0xC8  (subbrain finalize; pure in base)
    virtual void  SetName(void* nameHash) = 0;                          // [26] 0xD0
    virtual void* GetName() = 0;                                        // [27] 0xD8  -> &m_name
    virtual bool  AddVariable(C_Variable* var) = 0;                     // [28] 0xE0  (pure in base; subbrain impl)
    virtual void  _vf1D() = 0;                                          // [29] 0xE8
    virtual void  _vf1E() = 0;                                          // [30] 0xF0
    virtual void  _vf1F() = 0;                                          // [31] 0xF8
    virtual void  _vf20() = 0;                                          // [32] 0x100
    virtual void  _vf21() = 0;                                          // [33] 0x108
    virtual void  _vf22() = 0;                                          // [34] 0x110
    virtual bool  CheckRelationship(int64_t a2, void* a3) = 0;          // [35] 0x118 (non-pure in base)

    // --- fields ---
    C_IntelligentObject* m_owner;          // +0x08  owning AI object (back-ptr; this brain sits at owner+0x118)
    uint64_t             m_name;           // +0x10  wh::framework::StringHash (interned brain-name handle)
    uint16_t             m_flags;          // +0x18  bit0 = active; bits1-4 = GetFlagBit1..4
    uint8_t              _pad1A[6];        // +0x1A
    // m_signal: a richer C_Signal<bool, E_MessageImportanceLevel::Type> variant (embedded connection
    // map + vectors). Sized + 8-aligned; internals NOT RE'd (distinct from wh::shared::C_Signal 0x30).
    uint64_t             m_signal[21];     // +0x20  (0xA8) [opaque -- signal internals out of scope]
    void*                m_primaryRecord;  // +0xC8  pooled record (pushed into m_records) [type UNVERIFIED]
    std::vector<void*>   m_records;        // +0xD0  (0x18) pooled records (CryEngine allocator) [elem UNVERIFIED]
    uint32_t             m_fieldE8;        // +0xE8  init 0 [purpose UNVERIFIED]
    uint8_t              _padEC[4];        // +0xEC
    C_VariableIndex      m_varIndex;       // +0xF0  (0x28) embedded brain-variable container
};
static_assert(sizeof(C_AIBrain) == 0x118);

}  // namespace wh::xgenaimodule
