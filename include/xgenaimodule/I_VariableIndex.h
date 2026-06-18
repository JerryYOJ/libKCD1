#pragma once

#include <cstdint>
#include <vector>

namespace wh::xgenaimodule {

class C_Variable;

// ===========================================================================
// I_VariableIndex -- base of the AI/brain variable container.
// ===========================================================================
// RTTI: .?AVI_VariableIndex@xgenaimodule@wh@@ ; vtable 0x1821A3900 (21 slots). Root of the chain
// (C_VariableIndex derives). NOT data-less: it owns m_parent (+0x08) and provides concrete
// Set/Clear/GetParent; most other slots are purecall (implemented by C_VariableIndex). Size 0x10.
// m_parent is the hierarchical fallback (a local index falls back to the global index when a name
// is absent). wh:: type -> vtable slot order == declaration order.
//
// Methods are declared non-pure (empty bodies) so the concrete C_VariableIndex -- which is embedded
// BY VALUE inside C_AIBrain -- is not abstract (matches the I_CombatSoul convention). The bodies are
// never executed: we only ever reinterpret_cast live game objects, which carry the engine vtable.
class I_VariableIndex {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_VariableIndex;
    virtual ~I_VariableIndex() = default;                                                          // [0]  0x00
    virtual C_Variable* GetVariableById(uint16_t id, bool fallbackToParent) { return nullptr; }    // [1]  0x08  sub_1803B1698
    virtual C_Variable* GetVariableByName(const CryStringT<char>& name, bool fallbackToParent) { return nullptr; } // [2] 0x10  sub_180253F00
    virtual bool        AddVariable(void* out, const CryStringT<char>& name, void* factoryCtx) { return false; }   // [3] 0x18
    virtual bool        HasVariable(const CryStringT<char>& name) { return false; }                // [4]  0x20
    virtual bool        RemoveVariableByName(const CryStringT<char>& name) { return false; }       // [5]  0x28
    virtual void        SetParent(I_VariableIndex* parent) {}                                      // [6]  0x30
    virtual void        ClearParent() {}                                                           // [7]  0x38
    virtual void        GetAllVariables(std::vector<C_Variable*>& out, bool includeParent) {}      // [8]  0x40
    virtual void        GetAllVariableNames(std::vector<CryStringT<char>>& out, bool includeParent) {} // [9] 0x48
    virtual I_VariableIndex* GetParent() { return nullptr; }                                       // [10] 0x50
    virtual void        _vf11_resetAll() {}                                                        // [11] 0x58  calls C_Variable[0xE8] on each
    virtual void        Clear() {}                                                                 // [12] 0x60
    virtual bool        _vf13_serializeWrite(void* s, int64_t, void* ctx) { return false; }        // [13] 0x68
    virtual bool        _vf14_serializeRead(void* s, void* ctx, void* ctx2) { return false; }      // [14] 0x70
    virtual bool        _vf15_serializeWrite2(void* s, int64_t, void* ctx) { return false; }       // [15] 0x78
    virtual bool        _vf16_serializeRead2(void* s, void* ctx) { return false; }                 // [16] 0x80
    virtual int64_t     _vf17_serializeSupport(void* ctx) { return 0; }                            // [17] 0x88
    virtual void*       _vf18_resolveToRoot(void* out) { return nullptr; }                         // [18] 0x90
    virtual void*       GetVariableName(void* outStr, C_Variable* var) { return nullptr; }         // [19] 0x98
    virtual void        _vf20() {}                                                                 // [20] 0xA0  (no-op stub)

    I_VariableIndex* m_parent;   // +0x08  hierarchical fallback index (non-owning); default = global index
};
static_assert(sizeof(I_VariableIndex) == 0x10);

}  // namespace wh::xgenaimodule
