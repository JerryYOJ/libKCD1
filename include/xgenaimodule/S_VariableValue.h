#pragma once

#include <cstdint>

namespace wh::xgenaimodule {

// Storage kind of an S_VariableValue cell (its m_tag @+0x00). VERIFIED from writer sub_18028F2A0
// + reader sub_1803B3A08 -- the payload at +0x08 is read per this tag.
enum class E_VariableValueType : uint32_t {
    None   = 0,
    Float  = 1,   // float  @+0x08
    Int    = 2,   // int32  @+0x08
    String = 3,   // CryStringT<char> data ptr @+0x08
    Bool   = 4,   // bool   @+0x08
    Handle = 5,   // int64  @+0x08
    Object = 6,   // ref-counted script object ptr @+0x08
};

// -----------------------------------------------
// S_VariableValue -- the 0x10 storage element of an AI/brain variable's value vector.
// -----------------------------------------------
// The variable system's OWN tagged value ("Variant16"), distinct from CryEngine's ScriptAnyValue
// (0x18). Both C_SingleVariable::m_value and C_AssociativeArrayTreeVariable's per-member holders
// store these. Use the typed accessors below rather than touching the union directly.
struct S_VariableValue {
    uint32_t m_tag;      // +0x00  E_VariableValueType
    uint32_t _pad04;     // +0x04
    union {              // +0x08
        float    m_float;    // Float
        int32_t  m_int32;    // Int
        void*    m_string;   // String  (CryStringT<char> data ptr)
        bool     m_bool;     // Bool
        int64_t  m_int64;    // Handle
        void*    m_object;   // Object  (ref-counted script object)
    };

    E_VariableValueType Type() const { return static_cast<E_VariableValueType>(m_tag); }
    bool IsNumber() const { return m_tag == 1 || m_tag == 2; }   // Float or Int
    bool IsInt()    const { return m_tag == 2; }
    bool IsFloat()  const { return m_tag == 1; }
    bool IsBool()   const { return m_tag == 4; }
    bool IsString() const { return m_tag == 3; }

    // Integer view of a number cell (Int as-is, Float truncated); returns `def` for any other tag.
    int32_t GetInt(int32_t def = 0) const {
        if (m_tag == 2) return m_int32;
        if (m_tag == 1) return static_cast<int32_t>(m_float);
        return def;
    }
    float GetFloat(float def = 0.0f) const {
        if (m_tag == 1) return m_float;
        if (m_tag == 2) return static_cast<float>(m_int32);
        return def;
    }
    bool    GetBool(bool def = false)  const { return m_tag == 4 ? m_bool  : def; }
    int64_t GetHandle(int64_t def = 0) const { return m_tag == 5 ? m_int64 : def; }
};
static_assert(sizeof(S_VariableValue) == 0x10);

}  // namespace wh::xgenaimodule
