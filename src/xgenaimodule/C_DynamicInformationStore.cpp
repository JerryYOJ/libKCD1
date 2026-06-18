#include "xgenaimodule/C_DynamicInformationStore.h"
#include "Offsets/Offsets.h"

// C_DynamicInformationStore singleton accessor. The store pointer lives at the global
// qword_183501560 (sibling to the C_InformationManager singleton). We read it DIRECTLY
// rather than via the lazy creator sub_1814CEBBC, so inspection never allocates the store
// (null = no dynamic-info values exist yet this session).

namespace wh { namespace xgenaimodule {

C_DynamicInformationStore* C_DynamicInformationStore::GetInstance()
{
    return *reinterpret_cast<C_DynamicInformationStore**>(
        Offsets::GetBase() + Offsets::kDynInfoStoreOffset);
}

}}  // namespace wh::xgenaimodule
