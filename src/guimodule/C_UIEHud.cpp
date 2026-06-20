#include "guimodule/C_UIEHud.h"
#include "Offsets/Offsets.h"

namespace wh::guimodule::uielement {

// The global qword_183785948 holds the heap C_UIEHud* (set by the ctor
// sub_1811123AC, cleared by the dtor). Persists across save loads.
C_UIEHud* C_UIEHud::GetInstance() {
    return *reinterpret_cast<C_UIEHud**>(Offsets::GetBase() + Offsets::kUIEHudOffset);
}

}  // namespace wh::guimodule::uielement
