#include "crysystem/SSystemGlobalEnvironment.h"
#include "Offsets/Offsets.h"

SSystemGlobalEnvironment* SSystemGlobalEnvironment::GetInstance() {
    return reinterpret_cast<SSystemGlobalEnvironment*>(REL::ID(64).address());  // gEnv
}
