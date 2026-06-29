// HorseControls — a KCSE plugin (MinHook).
//
// Reimplements the horse_sprint action handler (sub_1810A2AB4) to remap the gaits:
//   tap shift  -> toggle CANTER on/off (persistent)
//   hold shift -> GALLOP while held, settling back to canter on release
//
// Stateless: m_dashRequested (C_PlayerInput+0xF0) doubles as the gallop signal AND the
// "this press became a hold" marker, so the plugin keeps no state of its own — the horse
// reads m_inputFlags (ePIF_Canter) and m_dashRequested to drive its gait.
//
// Requires horse_sprint to emit hold events (XML: onHold="1" holdTriggerDelay="0.25").
// RE: entitymodule/C_PlayerInput.h, sub_1810A2AB4.
#include <MinHook.h>

#include "KCSE/KCSEAPI.h"
#include "Offsets/Offsets.h"
#include "entitymodule/C_PlayerInput.h"        // pulls in Offsets::eAAM_* + ePIF_* via IActionListener.h

namespace em = wh::entitymodule;

namespace {

constexpr std::uint64_t kHorseSprintId = 145556;   // sub_1810A2AB4 (steam rva 0x10A2AB4)
bool __fastcall Hook_HorseSprint(em::C_PlayerInput* self, EntityId,
                                 const Offsets::ActionId&, Offsets::EActionActivationMode activationMode, float)
{
    if (activationMode & Offsets::eAAM_OnHold) {
        self->m_inputFlags |= em::ePIF_Canter;     // forward drive during gallop
        self->m_dashRequested = 1;                 // gallop; also marks "this press became a hold"
    }
    else if (activationMode & Offsets::eAAM_OnRelease) {
        if (self->m_dashRequested) {
            // hold-end -> stop gallop, stay cantering
            self->m_dashRequested = 0;
            self->m_inputFlags &= ~em::ePIF_Canter;
        }
        else                                       // tap -> toggle canter
            self->m_inputFlags ^= em::ePIF_Canter;
    }
    return 0;
}

}  // namespace

KCSE_PLUGIN_INFO("HorseControls", "RE", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    if (MH_Initialize() != MH_OK)
        return false;

    void* target = reinterpret_cast<void*>(REL::ID(kHorseSprintId).address());
    if (MH_CreateHook(target, reinterpret_cast<void*>(&Hook_HorseSprint),
                      nullptr) != MH_OK)
        return false;

    return MH_EnableHook(target) == MH_OK;
}
