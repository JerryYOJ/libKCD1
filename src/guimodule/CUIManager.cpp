#include "guimodule/CUIManager.h"
#include "Offsets/Offsets.h"

wh::guimodule::CUIManager* wh::guimodule::CUIManager::GetInstance() {
    return *reinterpret_cast<CUIManager**>(Offsets::GetBase() + Offsets::kCUIManagerOffset);
}
