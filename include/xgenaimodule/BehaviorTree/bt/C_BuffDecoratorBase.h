#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"

// C_BuffDecoratorBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_BuffDecoratorBase : public C_WrapperDecorator   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_BuffDecoratorBase : public C_WrapperDecorator {};

}  // namespace wh::xgenaimodule::BehaviorTree
