#pragma once

#include <cstdint>


// Forward declarations for template POLICY/TAG parameters (filters, anim-action tags, filter-op traits). These are used only as template arguments; their full layout is [UNVERIFIED] and not needed to instantiate the bases that take them.

namespace wh::xgenaimodule::BehaviorTree {

class C_HolsterItemAnimAction;
class C_ItemAIAnimAction;
class C_PickUpItemAnimAction;
class C_PlaceItemAnimAction;
class C_PutItemAnimAction;
class C_PutItemInHandAnimAction;
class I_LinkSorter;
struct S_AndByRandom;
struct S_IntersectionTrait;
struct S_OrByRandom;
struct S_UnionTrait;

// MI mixin interfaces (inherited by link/filter families) - modeled as
// minimal complete types [layout UNVERIFIED] so they can be base classes.
class I_LinkFilter {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_LinkFilter;
};

}  // namespace wh::xgenaimodule::BehaviorTree
