#include "guimodule/C_UIEHud.h"
#include "Offsets/Offsets.h"

namespace wh::guimodule::uielement {

// The global qword_183785948 holds the heap C_UIEHud* (set by the ctor
// sub_1811123AC, cleared by the dtor). Persists across save loads.
C_UIEHud* C_UIEHud::GetInstance() {
    static REL::Relocation<C_UIEHud**> p{ REL::ID(879) };
    return *p;
}

}  // namespace wh::guimodule::uielement
