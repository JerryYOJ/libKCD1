#include "xgenaimodule/C_SmartAreaManager.h"
#include "Offsets/Offsets.h"

// C_SmartAreaManager singleton accessor. The manager pointer lives at the global qword_183785A20
// (WUID type 7 = SmartArea registry; getter sub_180705E80). Read it directly -- null before the AI
// module is up. (The spatial point query delegates to the SEPARATE process-global C_RegularGrid.)

namespace wh { namespace xgenaimodule {

C_SmartAreaManager* C_SmartAreaManager::GetInstance()
{
    static REL::Relocation<C_SmartAreaManager**> p{ REL::ID(880) };
    return *p;
}

}}  // namespace wh::xgenaimodule
