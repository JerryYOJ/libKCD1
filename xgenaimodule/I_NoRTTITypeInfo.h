#pragma once

namespace wh::xgenaimodule {

// ---------------------------------------------------------------------------
// I_NoRTTITypeInfo — root interface for WH xgenai type system.
// RTTI: .?AVI_NoRTTITypeInfo@xgenaimodule@wh@@
// Base of I_CastableIface → I_Node chain.
// ---------------------------------------------------------------------------
class I_NoRTTITypeInfo {
public:
    virtual ~I_NoRTTITypeInfo() = default;
};

// ---------------------------------------------------------------------------
// I_CastableIface — interface for runtime type casting.
// RTTI: .?AVI_CastableIface@xgenaimodule@wh@@
// Inherits I_NoRTTITypeInfo, base of I_Node.
// ---------------------------------------------------------------------------
class I_CastableIface : public I_NoRTTITypeInfo {
};

}  // namespace wh::xgenaimodule
