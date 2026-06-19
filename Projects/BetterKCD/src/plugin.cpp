// BetterKCD — a KCSE plugin.
//
// 
//
#include "KCSE/KCSEAPI.h"
#include "crysystem/SSystemGlobalEnvironment.h"

KCSE_PLUGIN_INFO("BetterKCD", "RE", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    kcse->GetMessagingInterface()->RegisterListener([](KCSE::Message* msg) {
        if (msg->type != KCSE::IMessagingInterface::kMessage_DataLoaded) return;
        SSystemGlobalEnvironment::GetInstance()->pLog->LogAlways("[BetterKCD] loaded");
    });
    return true;
}
