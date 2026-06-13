#include "KCSE/KCSEAPI.h"
#include "crysystem/SSystemGlobalEnvironment.h"
#include "Offsets/vtables/IInput.h"
#include "game/S_GameContext.h"
#include "playermodule/C_PlayerModule.h"
#include "playermodule/C_FastTravel.h"

static wh::playermodule::C_FastTravel* GetFastTravel()
{
    auto* ctx = wh::game::S_GameContext::GetInstance();
    if (!ctx || !ctx->m_pPlayerModule) return nullptr;
    return ctx->m_pPlayerModule->m_pFastTravel;
}

class FastTravelCancel : public Offsets::IInputEventListener {
    void Dtor(char) override {}
    bool OnInputEventUI(const void*) override { return false; }
    int  GetPriority() const override { return 0x100; }
    bool OnInputEvent(const Offsets::SInputEvent& event) override {
        if (event.keyId != Offsets::eKI_Escape || !(event.state & Offsets::eIS_Pressed))
            return false;
        auto* ft = GetFastTravel();
        if (ft && ft->IsFastTravelling() && !ft->m_pPendingEventPrompt) {
            ft->Stop();
            return true;
        }
        return false;
    }
} g_CancelListener;

KCSE_PLUGIN_INFO("Fast Travel Cancel", "elaine", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    KCSE::GetMessagingInterface()->RegisterListener([](KCSE::Message* msg) {
        if (msg->type == KCSE::IMessagingInterface::kMessage_DataLoaded)
            SSystemGlobalEnvironment::GetInstance()->pInput->AddEventListener(&g_CancelListener);
    });
    return true;
}
