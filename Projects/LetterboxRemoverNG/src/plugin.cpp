// Letterbox Remover NG — a KCSE plugin.
//
// Removes the dialogue/cutscene letterbox while keeping the cinematic camera:
//   1. Render-side base bars  — hook C_DialogCameraManager::FillViewParams and
//      rewrite the forced 2.35 aspect to the live screen aspect (+ open-matte
//      FOV so framing/size are preserved), and clear the constrain flag.
//   2. HUD "RatioStrips" bars  — pin the C_UIEHud element-hide refcount so the
//      growing Flash bars can never become visible.
#include "KCSE/KCSEAPI.h"
#include "crysystem/CMovieSystem.h"
#include "crysystem/SSystemGlobalEnvironment.h"
#include "vtable_hook.h"

#include <Windows.h>
#include <cstdint>
#include <cmath>

namespace {

namespace uieh = wh::guimodule::uielement;
namespace dlg  = wh::dialogmodule;

[[nodiscard]] float GetScreenAspect()
{
    auto* env = SSystemGlobalEnvironment::GetInstance();
    auto* con = env ? env->pConsole : nullptr;
    if (con) {
        auto* w = con->GetCVar("r_Width");
        auto* h = con->GetCVar("r_Height");
        if (w && h) {
            const float fw = w->GetFVal();
            const float fh = h->GetFVal();
            if (fw > 0.0f && fh > 0.0f)
                return fw / fh;
        }
    }

    const int sw = GetSystemMetrics(SM_CXSCREEN);
    const int sh = GetSystemMetrics(SM_CYSCREEN);
    if (sw > 0 && sh > 0)
        return static_cast<float>(sw) / static_cast<float>(sh);

    return 16.0f / 9.0f;
}

// --- Render-side dialogue letterbox (the base bars) ------------------------
// C_DialogCameraManager::FillViewParams forces a 2.35 aspect + constrain flag
// into the view params. Rewrite to normal params
using FillViewFn = int64_t(__fastcall*)(dlg::C_DialogCameraManager*, dlg::S_ViewParams*);
FillViewFn g_origFillView = nullptr;
int64_t __fastcall Hook_FillViewParams(dlg::C_DialogCameraManager* self, dlg::S_ViewParams* vp)
{
    const int64_t r = g_origFillView(self, vp);
    if (!vp)
        return r;

    const float origAspect = vp->m_aspect;       // forced 2.35f
    const float scrAspect  = GetScreenAspect();
    const float fov        = vp->m_fov;          // vertical FOV (radians)

    // Open-matte: tan(newFov/2) = (origAspect / scrAspect) * tan(fov/2).
    if (origAspect > 0.01f && scrAspect > 0.01f && fov > 0.05f && fov < 3.2f)
        vp->m_fov = 2.0f * atanf((origAspect / scrAspect) * tanf(fov * 0.5f));
    vp->m_aspect          = scrAspect;   // undistort
    vp->m_constrainAspect = 0;           // no bars
    return r;
}

void InstallBaseBarHook()
{
    g_origFillView = VtableHook::SwapByOffset(
        Offsets::GetBase(), dlg::C_DialogCameraManager::VTABLE[0], 2, &Hook_FillViewParams);
}

// --- Render-side CUTSCENE letterbox (in-engine `sequence` cutscenes) --------
using SetCamParamsFn = void(__fastcall*)(CMovieSystem* self, SCameraParams* params);
SetCamParamsFn g_origSetCameraParams = nullptr;

void __fastcall Hook_SetCameraParams(CMovieSystem* self, SCameraParams* params)
{
    if (params && params->bCustomAspect) {
        float& fov    = params->fFOV;
        float& aspect = params->fAspectRatio;

        const float origAspect = aspect;
        const float scrAspect  = GetScreenAspect();

        // Open-matte: widen the vertical FOV to keep horizontal framing.
        if (origAspect > 0.01f && scrAspect > 0.01f && fov > 0.05f && fov < 3.2f)
            fov = 2.0f * atanf((origAspect / scrAspect) * tanf(fov * 0.5f));

        aspect = scrAspect;            // undistort
        params->bCustomAspect = false; // no constrain -> no bars
    }
    g_origSetCameraParams(self, params);
}

void InstallCutsceneHook()
{
    g_origSetCameraParams = VtableHook::SwapByOffset(
        Offsets::GetBase(), CMovieSystem::VTABLE[0], 58, &Hook_SetCameraParams);
}

// --- HUD "RatioStrips" letterbox -------------------------------------------
// The bars are HUD element bit 20 (a per-element HIDE refcount; 0 == visible).
// Keeping refcount[20] >= 1 means a dialogue's single decrement can never reach
// 0, so they never show.
void HideRatioStrips()
{
    uieh::C_UIEHud::GetInstance()->m_elementHideRefcount[uieh::HUDELEMENT_RatioStrips]++;
}

}  // namespace

KCSE_PLUGIN_INFO("Letterbox Remover NG", "RE", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    InstallBaseBarHook();
    InstallCutsceneHook();

    kcse->GetMessagingInterface()->RegisterListener([](KCSE::Message* msg) {
        if (msg->type == KCSE::IMessagingInterface::kMessage_DataLoaded) {
            auto* log = SSystemGlobalEnvironment::GetInstance()->pLog;
            log->LogAlways("[Letterbox Remover NG] Hiding hud ratioStrips");
            HideRatioStrips();
        }
    });
    return true;
}
