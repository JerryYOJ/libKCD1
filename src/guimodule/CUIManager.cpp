#include "guimodule/CUIManager.h"
#include "Offsets/Offsets.h"

wh::guimodule::CUIManager* wh::guimodule::CUIManager::GetInstance() {
    static REL::Relocation<CUIManager**> p{ REL::ID(869) };
    return *p;
}
