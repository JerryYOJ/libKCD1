#pragma once

#include <cstdint>
#include <vector>

// ===========================================================================
// wh::xgenaimodule::XGenPublic::I_SmartEntity  -  the public subbrain-query interface.
// ===========================================================================
// RTTI: .?AVI_SmartEntity@XGenPublic@xgenaimodule@wh@@ (TD 0x182b1e4a0). An MI base of C_SmartEntity
// at +0x180; vtable 0x1827039d0 (6 slots). PURE interface (sizeof 0x08). NOT interfuscated. Slots
// operate on C_SmartEntity's subbrain members (m_pSubbrainContainer @+0x190, m_subbrainStates @+0x1A0,
// m_subbrainMap @+0x1B8). VERIFIED by decompile; gameplay names inferred.
// ===========================================================================

namespace wh::xgenaimodule::XGenPublic {

class I_SmartEntity {
public:
    virtual uint8_t  GetSubbrainState(uint32_t idx) = 0;                  // [0] +0x00 sub_1802CAE24 (2 if OOB)
    virtual void*    GetSubbrainPtr(uint32_t idx) = 0;                    // [1] +0x08 sub_180706BD0
    virtual uint32_t FindSubbrainIndex(const void* key) = 0;             // [2] +0x10 sub_1802CF054 (0xFFFFFFFF on miss)
    virtual void     GetAllSubbrainIndices(std::vector<uint32_t>& out) = 0;      // [3] +0x18 sub_18167A318
    virtual void     GetFilteredSubbrainIndices(std::vector<uint32_t>& out) = 0; // [4] +0x20 sub_18167A2F4
    virtual void*    GetSubbrainMap() = 0;                               // [5] +0x28 sub_1806FF680 (-> &m_subbrainMap)
};
static_assert(sizeof(I_SmartEntity) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::xgenaimodule::XGenPublic
