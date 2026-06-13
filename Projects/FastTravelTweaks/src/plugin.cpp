#include "KCSE/KCSEAPI.h"
#include "crysystem/SSystemGlobalEnvironment.h"
#include "Offsets/Offsets.h"
#include "Offsets/vtables/IInput.h"
#include "game/S_GameContext.h"
#include "playermodule/C_PlayerModule.h"
#include "playermodule/C_FastTravel.h"
#include "guimodule/C_UIMap.h"

static wh::playermodule::C_FastTravel* GetFastTravel()
{
    auto* ctx = wh::game::S_GameContext::GetInstance();
    if (!ctx || !ctx->m_pPlayerModule) return nullptr;
    return ctx->m_pPlayerModule->m_pFastTravel;
}

static constexpr double kNearMapSq = 10.0 * 10.0;
static wh::guimodule::C_CompassMark* MapMarker(Offsets::IFlashPlayer*& fp,
                                               wh::playermodule::C_FastTravel*& ft, bool& isNear)
{
    fp = nullptr; ft = nullptr; isNear = false;
    auto* el = SSystemGlobalEnvironment::GetInstance()->pFlashUI->GetUIElement("Inventory");
    if (!el || !el->IsVisible()) return nullptr;
    fp = el->GetFlashPlayer();
    ft = GetFastTravel();
    if (!ft || !ft->m_pUIMap) return nullptr;
    SFlashVarValue full; fp->GetVariable("_root.m_MapFullscreen", full);
    if (!full.GetBool()) return nullptr;
    auto* mark = ft->m_pUIMap->m_pCheckpoint.get();
    if (!mark) return nullptr;

    auto num  = [&](const char* p) { SFlashVarValue v; fp->GetVariable(p, v); return v.GetDouble(); };
    auto conv = [&](const char* fn, double a, double b) {
        SFlashVarValue ar[2] = { a, b }, r; fp->Invoke(fn, ar, 2, &r); return r.GetDouble(); };
    double dx = num("_root.path.mc_map._xmouse") - conv("coordFromGameWorldToMapX", mark->m_fPosX, 8192.0);
    double dy = num("_root.path.mc_map._ymouse") - conv("coordFromGameWorldToMapY", mark->m_fPosY, 8192.0);
    isNear = (dx * dx + dy * dy <= kNearMapSq);
    return mark;
}

//static void UpdateMarkerPrompt()
//{
//    static bool shown = false;
//    Offsets::IFlashPlayer* fp; wh::playermodule::C_FastTravel* ft; bool isNear;
//    MapMarker(fp, ft, isNear);
//    if (isNear == shown) return;
//    shown = isNear;
//    if (!fp) return;
//    if (isNear) {
//        SFlashVarValue a[2] = { "$ui_confirm; @ui_maplegend_fasttravel", "$ui_back; @ui_invhint_exit" };
//        fp->Invoke("HelpBarSet", a, 2);
//    } else {
//        fp->Invoke("HelpBarSetItem", nullptr, 0);   // let the game restore its own prompts
//    }
//}

class FastTravelTweaks : public Offsets::IInputEventListener {
    void Dtor(char) override {}
    bool OnInputEventUI(const void*) override { return false; }
    int  GetPriority() const override { return 0x0; }
    bool OnInputEvent(const Offsets::SInputEvent& event) override {
        //UpdateMarkerPrompt();
        
        if (!(event.state & Offsets::eIS_Pressed)) return false;

        if (event.keyId == Offsets::eKI_Escape) {
            auto* ft = GetFastTravel();
            if (ft && ft->IsFastTravelling() && !ft->m_pPendingEventPrompt) {
                ft->Stop();
                return true;
            }
        }
        else if (event.keyId == Offsets::eKI_E) {
            Offsets::IFlashPlayer* fp; wh::playermodule::C_FastTravel* ft; bool isNear;
            auto* mark = MapMarker(fp, ft, isNear);
            if (!mark || !isNear) return false;

            bool armed = ft->m_path.size() >= 2
                && ft->m_destination.x == mark->m_fPosX
                && ft->m_destination.y == mark->m_fPosY;

            if (!armed) {
                float gz = Offsets::Get3DEngine()->GetTerrainElevation(mark->m_fPosX, mark->m_fPosY);
                Vec3 dest = { mark->m_fPosX, mark->m_fPosY, gz };
                ft->SetDestination(dest, false);
                return true;
            }

            fp->Invoke("RemoveCheckpoint", nullptr, 0);
            Offsets::FlashVarPtr cb;
            fp->GetVariable("_root.FastTravelDialogSubmit", cb.put());
            fp->SetVariable("_root.m_FastTravelName", SFlashVarValue("ft"));
            SFlashVarValue dlg[3] = { "@ui_dlg_fasttravel_confirm", "question", SFlashVarValue() };
            fp->Invoke("ShowInfoDialog", dlg, 3);
            fp->SetVariable("_root.m_OnInfoDialogSubmit", cb.get());
            return true;
        }
        return false;
    }
} g_Listener;

//static void Tick() {
//    auto* ft = GetFastTravel();
//    bool showEsc = ft && ft->IsFastTravelling() && !ft->m_pPendingEventPrompt;
//
//    static bool shown = false;
//    if (showEsc != shown) {                       
//        shown = showEsc;
//        auto* el = SSystemGlobalEnvironment::GetInstance()->pFlashUI->GetUIElement("Inventory");
//        auto* fp = (el && el->IsVisible()) ? el->GetFlashPlayer() : nullptr;
//        if (fp) {
//            if (showEsc) {                        // show [ESC] Cancel on the right
//                SFlashVarValue a[2] = { "", "$ui_back; @ui_invhint_cancel" };
//                fp->Invoke("HelpBarSet", a, 2);
//            } else {                              
//                fp->Invoke("HelpBarSetItem", nullptr, 0);
//            }
//        }
//    }
//
//    KCSE::GetTaskInterface()->AddTask(Tick);
//}

KCSE_PLUGIN_INFO("Fast Travel Tweaks", "JerryYOJ", 1);
KCSE_PLUGIN_LOAD(kcse)
{
    KCSE::GetMessagingInterface()->RegisterListener([](KCSE::Message* msg) {
        if (msg->type == KCSE::IMessagingInterface::kMessage_DataLoaded) {
            SSystemGlobalEnvironment::GetInstance()->pInput->AddEventListener(&g_Listener);
            //KCSE::GetTaskInterface()->AddTask(Tick);
        } 
    });
    return true;
}
