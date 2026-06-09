#pragma once
#include "../crysystem/CScriptableBase.h"

// C_ScriptBindSmartObject — entity script binding for smart objects
// RTTI: .?AVC_ScriptBindSmartObject@xgenaimodule@wh@@  vtable: 0x18239d928
// Constructor: sub_18166BE98  Registration: sub_181672498  Size: 0x70

namespace wh::xgenaimodule {
class C_ScriptBindSmartObject : public CScriptableBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ScriptBindSmartObject;
    void*                   m_pGameFramework;   // +0x60
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x68
    // int GetHelpers(IFunctionHandler* pH);                                                       // 0x18166ECF4
    // int GetHelpersCategory(IFunctionHandler* pH, const char* categoryName);                     // 0x18166ED90
    // int GetHelperLinks(IFunctionHandler* pH, const char* helperName);                           // 0x18166EB34
    // int GetHelperLinkTarget(IFunctionHandler* pH, const char* helperName, const char* linkName); // 0x18166EA38
    // int GetHelperUserData(IFunctionHandler* pH, const char* helperName, const char* userDataKey); // 0x18166EC0C
};
static_assert(sizeof(C_ScriptBindSmartObject) == 0x70);
} // namespace wh::xgenaimodule
