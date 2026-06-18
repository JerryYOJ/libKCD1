#pragma once

#include <cstdint>
#include "Callbacks/C_PlainCallbackExtension.h"
#include "BehaviorTree/Expressions/C_ExpressionRef.h"

// ScriptAnyValue is the CryEngine variant carried by variable get/set (full def in IScriptSystem.h).
struct ScriptAnyValue;

namespace wh::xgenaimodule {

class I_VariableIndex;   // owning container back-pointer (C_Variable+0x28)

// ===========================================================================
// C_Variable -- abstract base for all AI/brain variables (the b_*/t_* values).
// ===========================================================================
// RTTI: .?AVC_Variable@xgenaimodule@wh@@ (type desc 0x182B37F08); vtable 0x1821A3B28 (34 slots).
// Ctor sub_180253B98(name, typeDesc, owner, str); dtor sub_1805B3DEC.
// Single-inherits the callback mixin spine (C_PlainCallbackExtension, [0x00,0x18)); its own fields
// begin at +0x18. Identity is the interned name id @+0x18 (resolved to/from a string via the global
// brain-variable name registry sub_180253FE8 / sub_180544770). Concrete forms (factory sub_18024A498
// type byte): C_SingleVariable (scalar), C_AssociativeArrayTreeVariable / C_IndexedArrayTreeVariable /
// C_CustomAssociativeTreeVariable (composites). Size 0x48.
//
// vtable note: this is a wh:: type (NOT interfuscator-shuffled) -- slot order == declaration order.
// Pure slots are purecall in the base (0x180A2CA89); concrete forms override the value-bearing ones.
class C_Variable : public Callbacks::C_PlainCallbackExtension {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Variable;
    ~C_Variable() override = default;                                        // [0] 0x00  dtor (sub_181685AA0)

    virtual uint8_t           GetForm() = 0;                                 // [1] 0x08  variable-kind tag (E_VariableForm)
    virtual void*             ToString(void* outStr) = 0;                    // [2] 0x10  debug "Form: .. | Type: .."
    virtual C_Variable*       Clone() = 0;                                   // [3] 0x18
    virtual ScriptAnyValue*   GetValue(ScriptAnyValue& out) = 0;            // [4] 0x20  read current value
    virtual bool              SetValue(const ScriptAnyValue& in) = 0;       // [5] 0x28  write value (+ notify)
    virtual bool              _vf06_setFromExprA(void* exprVal) = 0;        // [6] 0x30  type-dispatch setter A
    virtual bool              _vf07_setStringA(void* s) = 0;                // [7] 0x38
    virtual bool              _vf08_setIntA(uint32_t i) = 0;                // [8] 0x40
    virtual bool              _vf09_setFromExprB(void* exprVal) = 0;        // [9] 0x48  type-dispatch setter B
    virtual bool              _vf0A_setStringB(void* s) = 0;               // [10] 0x50
    virtual bool              _vf0B_setIntB(uint32_t i) = 0;               // [11] 0x58
    virtual bool              _vf0C_setFromExprC(void* exprVal) = 0;       // [12] 0x60  type-dispatch setter C
    virtual void              _vf0D_variantCString(void* s) = 0;          // [13] 0x68
    virtual void              _vf0E_variantCInt(uint32_t i) = 0;          // [14] 0x70
    virtual void              _vf0F_refreshFromType() = 0;                // [15] 0x78  resize-then-validate (0xD8 then 0xC8)
    virtual bool              _vf10_testY(void* exprVal) = 0;             // [16] 0x80  equals/test dispatcher
    virtual bool              _vf11_testX(void* exprVal) = 0;             // [17] 0x88
    virtual bool              _vf12_testString(void* s) = 0;             // [18] 0x90
    virtual bool              _vf13_testInt(uint32_t i) = 0;             // [19] 0x98
    virtual bool              _vf14_setFromExprFlagged(void* v, char useB) = 0; // [20] 0xA0
    virtual bool              IsSupportedValueType(uint64_t typeToken) = 0;// [21] 0xA8
    virtual int32_t           GetElementCount() = 0;                      // [22] 0xB0
    virtual void              _vf17() = 0;                                // [23] 0xB8  (base no-op)
    virtual bool              SetValueChecked(void* value, int64_t a3) = 0;// [24] 0xC0
    virtual bool              ValidateValue() = 0;                        // [25] 0xC8
    virtual void*             _vf1A() = 0;                                // [26] 0xD0
    virtual void*             ResizeStorageFromType() = 0;               // [27] 0xD8
    virtual void*             _vf1C(void* a2) = 0;                        // [28] 0xE0
    virtual void*             _vf1D() = 0;                                // [29] 0xE8  (same impl as 0x78)
    virtual void*             GetName(void* outStr) = 0;                 // [30] 0xF0  resolve m_nameId -> CryString
    virtual void*             SerializeRead(void* ar) = 0;              // [31] 0xF8
    virtual void*             SerializeWrite(void* ar, int64_t a3) = 0; // [32] 0x100
    virtual bool              FillReference(void* outRec) = 0;          // [33] 0x108 build S_VariableReference

    // --- fields (own; begin after the 0x18 callback base) ---
    uint16_t          m_nameId;            // +0x18  interned name id (global registry sub_180253FE8)
    uint8_t           m_flags;             // +0x1A  bit0 set at ctor; bit1 surfaced by FillReference
    uint8_t           _pad1B[5];           // +0x1B
    void*             m_pTypeDescriptor;   // +0x20  value-type schema (C_VariableType*, non-owning) [INFERRED type]
    I_VariableIndex*  m_pOwner;            // +0x28  owning variable container (back-ptr, non-owning)
    CryStringT<char>  m_string;            // +0x30  owned string (empty in the table factory) [role UNVERIFIED]
    BehaviorTree::Expressions::C_ExpressionRef m_boundExpression;  // +0x38  (0x10) optional bound expression
};
static_assert(sizeof(C_Variable) == 0x48);

}  // namespace wh::xgenaimodule
