#pragma once

#include <cstdint>

// ===========================================================================
// wh::guimodule::I_UIMenuEventsListener  -  receives UI (inventory) menu events.
// ===========================================================================
// RTTI: .?AVI_UIMenuEventsListener@guimodule@wh@@ (TD img 0x2A42850). A 3-slot interface
// (dtor + 2 event callbacks). Implemented as a SECONDARY base by script-bind classes that
// expose inventory menu hooks to Lua (e.g. C_ScriptBindActor @ +0x60). PURE interface (0x08).
// Method names are derived from the C_ScriptBindActor override behavior (the only implementor
// examined): each forwards to the entity's Lua table callback of the same name.
// ===========================================================================

namespace wh::guimodule {

class I_UIMenuEventsListener {
public:
    virtual ~I_UIMenuEventsListener() = default;               // [0]
    // [1] sub_1810D8208: on inventory/menu close -- unregisters the entity and fires the entity's
    //     Lua "OnInventoryClosed" callback (arg = the close flag).
    virtual void OnInventoryClosed(bool closed) = 0;
    // [2] sub_1810D8170: on inventory item used -- fires the entity's Lua "OnInventoryItemUsed"
    //     callback (arg = the used item handle).
    virtual void OnInventoryItemUsed(int64_t item) = 0;
};
static_assert(sizeof(I_UIMenuEventsListener) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::guimodule
