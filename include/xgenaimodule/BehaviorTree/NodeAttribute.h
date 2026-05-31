#pragma once

#include <cstdint>

// ===========================================================================
// NodeAttribute.h  -  Typed XML-attribute binding for BT nodes.
//
// Reverse-engineered from WHGame.dll (KCD1 retail).  Namespace
// wh::xgenaimodule::BehaviorTree.
//
// A NodeAttribute<T> binds one named attribute from a behavior-tree XML node to
// a typed C++ value with a default.  Action / decorator / barrier nodes own a
// set of these so they can read tuning values (loop counts, durations, enum
// modes, etc.) declared in the tree XML.
//
// EVIDENCE  (resolved name-string -> signature-validated COL [signature==1 AND
//            typeDescriptor-RVA match] -> vtable; RTTI ClassHierarchyDescriptor
//            base-class arrays parsed)
// --------------------------------------------------------------------------
//   NodeAttributeBase  name@0x182a87c80  COL@0x1824527e8  primaryVT@0x1821A8048
//       base-class array = [ NodeAttributeBase ]   (root, 1 entry)
//       primaryVT slot1 == _purecall (abstract base).
//       => NodeAttributeBase = { vtable@+0x00, void* @+0x08 }, size 0x10
//          (the +0x08 member is asserted from layout; the ctor inlines into
//           every NodeAttribute<T> ctor so it was not isolated standalone).
//
//   VERIFIED template instantiations (each base-class array == [self,
//   NodeAttributeBase], i.e. DIRECT single inheritance):
//       NodeAttribute<int>            .?AV?$NodeAttribute@H@...   primaryVT@0x1821A2D40
//       NodeAttribute<float>          .?AV?$NodeAttribute@M@...   primaryVT@0x1821A1E58
//       NodeAttribute<bool>           .?AV?$NodeAttribute@_N@...  primaryVT@0x1821A80A0
//       NodeAttribute<CryStringT<char>> .?AV?$NodeAttribute@V?$CryStringT@D@@@...
//                                                                 primaryVT@0x1821A80F8
//       NodeAttribute<unsigned int>   .?AV?$NodeAttribute@I@...   (name@0x182a9a800)
//       EnumNodeAttribute<int>        .?AV?$EnumNodeAttribute@H@... primaryVT@0x1821A1B70
//       EnumNodeAttribute<E_SubtreeRunLogic::Type>
//             .?AV?$EnumNodeAttribute@W4Type@E_SubtreeRunLogic@xgenaimodule@wh@@@...
//                                                                 primaryVT@0x1821A2570
//       (~40 further EnumNodeAttribute<...> enum specialisations exist - e.g.
//        E_DestinationType, E_GameMode, E_MovementSpeed, E_CombatGuardTypes -
//        each a VERIFIED direct subclass of NodeAttributeBase.)
//
// IMPORTANT CORRECTIONS vs an earlier draft:
//   * The string instantiation binds CryEngine's CryStringT<char>, NOT
//     std::string (verified from the mangled name V?$CryStringT@D@@).
//   * EnumNodeAttribute takes ONE template parameter (the enum type), not two:
//     EnumNodeAttribute<int> and EnumNodeAttribute<E_SubtreeRunLogic::Type>
//     both have exactly that single parameter in their mangled names.
//
// LAYOUT
// ------
//     +0x00 vtable
//     +0x08 void*  m_pName        (single base member)
//     +0x10 T      m_value        (typed default / parsed value)
// [UNVERIFIED] the +0x08 member's semantics (attribute name string vs interned
// id vs parser hook) - it is one pointer-sized field; "name" is inferred from
// the XML-attribute role.  [UNVERIFIED] exact size of NodeAttributeBase and per-
// T tail: the base ctor is inlined into every derived ctor and was not isolated
// to read a standalone MemAlloc size, so the 0x10 base size and +0x10 value
// offset are layout-consistent estimates, not a directly-read allocation size.
// ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// NodeAttributeBase
//
// RTTI: .?AVNodeAttributeBase@BehaviorTree@xgenaimodule@wh@@
// primary vtable: 0x1821A8048 (slot1 == _purecall -> abstract base)
// Size: 0x10  [UNVERIFIED - layout estimate, see note above]
//
// Polymorphic base for all typed attributes.  The vtable exposes the
// type-erased operations used by the attribute-registration / XML-load pass.
// [UNVERIFIED] exact vtable slot order (CryEngine interfuscator shuffles vfunc
// order); only the DATA layout is estimated here, so virtuals are declared
// generically and must be index-validated before any direct call.
// ---------------------------------------------------------------------------
class NodeAttributeBase {
public:
    virtual ~NodeAttributeBase() = default;   // [UNVERIFIED slot index]
    // Further type-erased ops (GetDefaultValue / GetName / ParseFromXml) exist
    // in the vtable but their slot order is interfuscator-shuffled and was not
    // index-validated; intentionally not declared to avoid asserting a wrong
    // order. [UNVERIFIED]

    void* m_pName;      // +0x08  attribute identity (name / interned id);
                        //        semantics [UNVERIFIED]
};
// [UNVERIFIED] size - not static_assert'd (base ctor inlined; size not
// directly read). Layout estimate: 0x10.

// ---------------------------------------------------------------------------
// NodeAttribute<T>
//
// RTTI: .?AV?$NodeAttribute@<mangled T>@BehaviorTree@xgenaimodule@wh@@
// Base: NodeAttributeBase   (VERIFIED direct single inheritance for H/M/_N/
//                            I/CryStringT<char>; primaryVTs int=0x1821A2D40
//                            float=0x1821A1E58 bool=0x1821A80A0
//                            CryStringT=0x1821A80F8)
//
// Stores the parsed/default value inline at +0x10.
// Size: 0x10 + sizeof(T) (rounded to T's alignment).  [UNVERIFIED] per-T tail.
// ---------------------------------------------------------------------------
template<typename T>
class NodeAttribute : public NodeAttributeBase {
public:
    T m_value;          // +0x10  parsed value (XML attribute or default)
};

// Convenience aliases for the verified instantiations.
using NodeAttributeInt    = NodeAttribute<int32_t>;       // NodeAttribute@H
using NodeAttributeUInt   = NodeAttribute<uint32_t>;      // NodeAttribute@I
using NodeAttributeFloat  = NodeAttribute<float>;         // NodeAttribute@M
using NodeAttributeBool   = NodeAttribute<bool>;          // NodeAttribute@_N
// NodeAttribute<CryStringT<char>> - CryStringT not redefined here; the engine's
// CryStringT<char> is the value type. Alias omitted to avoid a forward type.

// ---------------------------------------------------------------------------
// EnumNodeAttribute<TEnum>
//
// RTTI: .?AV?$EnumNodeAttribute@<mangled TEnum>@BehaviorTree@xgenaimodule@wh@@
// Base: NodeAttributeBase   (VERIFIED direct single inheritance; 1 template
//                            parameter - e.g. EnumNodeAttribute<int>
//                            primaryVT@0x1821A1B70 and
//                            EnumNodeAttribute<E_SubtreeRunLogic::Type>
//                            primaryVT@0x1821A2570)
//
// Binds an XML attribute whose string value names one of a scoped enum's
// members; parses string -> enum at load.  Stores the value inline at +0x10.
// [UNVERIFIED] whether it additionally caches the enum<->string table pointer
// (would push sizeof beyond 0x10 + sizeof(TEnum)).
// ---------------------------------------------------------------------------
template<typename TEnum>
class EnumNodeAttribute : public NodeAttributeBase {
public:
    TEnum m_value;      // +0x10  parsed enum value
};

}  // namespace wh::xgenaimodule::BehaviorTree
