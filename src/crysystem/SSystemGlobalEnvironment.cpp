#include "crysystem/SSystemGlobalEnvironment.h"
#include "Offsets/Offsets.h"

SSystemGlobalEnvironment* SSystemGlobalEnvironment::GetInstance() {
    return reinterpret_cast<SSystemGlobalEnvironment*>(Offsets::GetBase() + Offsets::kGEnvOffset);
}
