#pragma once
#include "guimodule/SUITypes.h"
#include "IUIElementEventListener.h"

// -----------------------------------------------
// IUIElement — Binary vtable order (NOT interfuscated)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashUI.h:1047 (UNIQUE_IFACE struct IUIElement).
// No <interfuscator:shuffle> tags -> slot order == C++ declaration order.
//
// Implementation: CFlashUIElement (size 0x228, ctor sub_1818644BC, newed by
// CFlashUI::LoadElementsFromFile). Primary vtable @ 0x1823aa9f0 (101 slots,
// this_off 0). RTTI: .?AVCFlashUIElement@@ : IUIElement (+0),
// IFSCommandHandler (+0x08, vtbl 0x1823aad20), IVirtualKeyboardEvents
// (+0x10, vtbl 0x1823aad38).
//
// Layout notes (verified against WHGame.dll):
// - Slot [18] RequestUnload(bool) is an EXTRA virtual vs our SDK header copy
//   (present in later CryEngine: declared right after IsInit). Impl
//   sub_180708FD0 sets this+0x4A=1 (request flag), this+0x4B=bAllInstances.
//   Every slot from [19] on is therefore +1 vs the SDK header declaration.
// - MSVC emits adjacent overloads in REVERSE declaration order. All
//   Get*Desc / CallFunction / GetMovieClip / CreateMovieClip / RemoveMovieClip
//   / Set+Get+CreateVariable / Set+Get+CreateArray / LoadTexIntoMc /
//   UnloadTexFromMc groups below are in binary (reversed) order.
//   PROVEN: CallFunction(const char*) [65] resolves the name via
//   GetFunctionDesc(const char*) [56] (+0x1C0) and the template via
//   GetMovieClipDesc(const char*) [47] (+0x178), then tail-calls
//   CallFunction(const SUIEventDesc*) [64] (+0x200).
// - [23]/[24] Render/RenderLockless share one COMDAT-folded impl.
// - CFlashUIElement members recovered: +0x28 m_sName, +0x30 m_sGroupName,
//   +0x38 m_sFlashFile (CryStringT getters [9]/[11]/[13]), +0x4A/+0x4B unload
//   request flags, +0x50 IFlashPlayer*, +0xB8 base-element ptr (instances
//   delegate ReloadBootStrapper to it), +0xC0 uint m_iInstanceID,
//   +0xC8..0xD8 instances vector (walked by CUIElementIterator).
// - Anchor: sub_18111FD4C calls vtbl+0x208 ("fc_showInfoText", args, 0, 0)
//   -> CallFunction(const char*, ...) [65]. GetFlashPlayer is [40] = +0x140.

namespace Offsets {

struct IUIElementIterator;
struct IFlashPlayer;
struct IFlashVariableObject;

struct IUIElement {
    // SDK nested type (CryCommon/IFlashUI.h:1049) — POD replicated verbatim:
    struct SUIConstraints {
        enum EPositionType  { ePT_Fixed, ePT_Fullscreen, ePT_Dynamic, ePT_FixedDynTexSize };
        enum EPositionAlign { ePA_Lower, ePA_Mid, ePA_Upper };
        EPositionType  eType;
        int            iLeft;
        int            iTop;
        int            iWidth;
        int            iHeight;
        EPositionAlign eHAlign;
        EPositionAlign eVAlign;
        bool           bScale;
        bool           bMax;
    };

    virtual void Dtor(char flags) = 0;                                              // [0]   0x000  sub_181868F90 (scalar deleting dtor)
    virtual void AddRef() = 0;                                                      // [1]   0x008  sub_1806F90C0  (decl-mapped)
    virtual void Release() = 0;                                                     // [2]   0x010  sub_1806E71E4  (decl-mapped)

    // instances
    virtual unsigned int GetInstanceID() const = 0;                                 // [3]   0x018  0x180708e20  VERIFIED: returns dword this+0xC0 (logged as "(%i)" by CallFunction)
    virtual IUIElement* GetInstance(unsigned int instanceID) = 0;                   // [4]   0x020  sub_1805558C4  (decl-mapped)
    virtual void* GetInstances(void* sret) const = 0;                               // [5]   0x028  sub_180503560  SDK: IUIElementIteratorPtr by value -> hidden sret param (creates CUIElementIterator)
    virtual bool DestroyInstance(unsigned int instanceID) = 0;                      // [6]   0x030  sub_181872430  (decl-mapped)
    virtual bool DestroyThis() = 0;                                                 // [7]   0x038  sub_1818725FC  (decl-mapped)

    // common
    virtual void SetName(const char* name) = 0;                                     // [8]   0x040  sub_1811A43C0  VERIFIED: called by LoadElementsFromFile with xml "name" attr
    virtual const char* GetName() const = 0;                                        // [9]   0x048  0x1806f7f70  VERIFIED: returns this+0x28; used for "%s" in CallFunction logs
    virtual void SetGroupName(const char* groupName) = 0;                           // [10]  0x050  sub_181895410  VERIFIED: called by LoadElementsFromFile with file-level name
    virtual const char* GetGroupName() const = 0;                                   // [11]  0x058  0x1806f94a0  VERIFIED shape: returns this+0x30
    virtual void SetFlashFile(const char* flashFile) = 0;                           // [12]  0x060  sub_181895320  (decl-mapped)
    virtual const char* GetFlashFile() const = 0;                                   // [13]  0x068  0x1806f8c30  VERIFIED shape: returns this+0x38 (ICF-shared body)

    virtual bool Init(bool bLoadAsset) = 0;                                         // [14]  0x070  sub_1805560CC  VERIFIED: CFlashUI::PostInit calls (false); ReloadBootStrapper re-Inits
    virtual void Unload(bool bAllInstances) = 0;                                    // [15]  0x078  sub_1806A6748  (decl-mapped)
    virtual void Reload(bool bAllInstances) = 0;                                    // [16]  0x080  sub_1818928B0  (decl-mapped)
    virtual bool IsInit() const = 0;                                                // [17]  0x088  sub_180303DD8  VERIFIED: queried by ReloadBootStrapper before unload
    // KCD/later-CryEngine ADDED slot (absent from our SDK header copy; CE V
    // declares RequestUnload(bool bAllInstances=false) exactly here).
    virtual void RequestUnload(bool bAllInstances) = 0;                             // [18]  0x090  sub_180708FD0  VERIFIED behavior: this+0x4A=1, this+0x4B=bAllInstances
    virtual bool IsValid() const = 0;                                               // [19]  0x098  sub_180556AD8  (decl-mapped)

    virtual void UnloadBootStrapper() = 0;                                          // [20]  0x0A0  sub_181897DE8  VERIFIED: called per-instance by ReloadBootStrapper
    virtual void ReloadBootStrapper() = 0;                                          // [21]  0x0A8  sub_181892E0C  VERIFIED: saves IsInit/IsVisible, UnloadBootStrapper, re-Init + SetVisible
    virtual void Update(float fDeltaTime) = 0;                                      // [22]  0x0B0  sub_1803E0C74  VERIFIED: called from CFlashUI::Update loop
    virtual void Render() = 0;                                                      // [23]  0x0B8  sub_1803E0B08  VERIFIED: called from CFlashUI::Update render path
    virtual void RenderLockless() = 0;                                              // [24]  0x0C0  sub_1803E0B08  (same impl as [23] — COMDAT folded)

    // visibility
    virtual void RequestHide() = 0;                                                 // [25]  0x0C8  sub_181893404  (decl-mapped)
    virtual bool IsHiding() const = 0;                                              // [26]  0x0D0  sub_180500580  (decl-mapped)
    virtual void SetVisible(bool bVisible) = 0;                                     // [27]  0x0D8  sub_180500A4C  VERIFIED: ReloadBootStrapper restores saved visibility via +0xD8
    virtual bool IsVisible() const = 0;                                             // [28]  0x0E0  sub_180708F10  VERIFIED: queried by ReloadBootStrapper via +0xE0
    virtual void SetFlag(int flag, bool bSet) = 0;                                  // [29]  0x0E8  sub_180555D54  EFlashUIFlags (decl-mapped)
    virtual bool HasFlag(int flag) const = 0;                                       // [30]  0x0F0  sub_1803E0D24  VERIFIED: CFlashUI::Update tests eFUI_LAZY_UPDATE(0x2000-style masks) via +0xF0
    virtual float GetAlpha() const = 0;                                             // [31]  0x0F8  sub_1806FF880  (decl-mapped)
    virtual void SetAlpha(float fAlpha) = 0;                                        // [32]  0x100  sub_180555E28  (decl-mapped)
    virtual int GetLayer() const = 0;                                               // [33]  0x108  sub_1806F8610  (decl-mapped)
    virtual void SetLayer(int iLayer) = 0;                                          // [34]  0x110  sub_180555DEC  (decl-mapped)
    virtual void SetConstraints(const SUIConstraints& newConstraints) = 0;          // [35]  0x118  sub_181895270  (decl-mapped)
    virtual const SUIConstraints& GetConstraints() const = 0;                       // [36]  0x120  sub_180708C20  (decl-mapped)

    // lazy update
    virtual void ForceLazyUpdate() = 0;                                             // [37]  0x128  sub_180708B60  (decl-mapped)
    virtual void LazyRendered() = 0;                                                // [38]  0x130  sub_180708F20  (decl-mapped)
    virtual bool NeedLazyRender() const = 0;                                        // [39]  0x138  sub_181888234  (decl-mapped)

    virtual IFlashPlayer* GetFlashPlayer() = 0;                                     // [40]  0x140  sub_1803E0ED8  VERIFIED: lazy-inits then returns IFlashPlayer* at this+0x50
    // descs (each overload pair REVERSED: (const char*) first, (int) second)
    virtual const SUIParameterDesc* GetVariableDesc(const char* varName) const = 0; // [41]  0x148  sub_18187ED48  (decl-mapped)
    virtual const SUIParameterDesc* GetVariableDesc(int index) const = 0;           // [42]  0x150  sub_18187ED28  (decl-mapped)
    virtual int GetVariableCount() const = 0;                                       // [43]  0x158  sub_180708F00  (decl-mapped)
    virtual const SUIParameterDesc* GetArrayDesc(const char* arrayName) const = 0;  // [44]  0x160  sub_1818748D8  (decl-mapped)
    virtual const SUIParameterDesc* GetArrayDesc(int index) const = 0;              // [45]  0x168  sub_1818748B8  (decl-mapped)
    virtual int GetArrayCount() const = 0;                                          // [46]  0x170  sub_180708B70  (decl-mapped)
    virtual const SUIMovieClipDesc* GetMovieClipDesc(const char* movieClipName) const = 0; // [47]  0x178  sub_18020BBD4  VERIFIED: CallFunction [65] resolves pTmplName via +0x178
    virtual const SUIMovieClipDesc* GetMovieClipDesc(int index) const = 0;          // [48]  0x180  sub_18187D684  (decl-mapped)
    virtual int GetMovieClipCount() const = 0;                                      // [49]  0x188  sub_180708E40  (decl-mapped)
    virtual const SUIMovieClipDesc* GetMovieClipTmplDesc(const char* movieClipTmplName) const = 0; // [50] 0x190  sub_18187D6C4  (decl-mapped)
    virtual const SUIMovieClipDesc* GetMovieClipTmplDesc(int index) const = 0;      // [51]  0x198  sub_18187D6A4  (decl-mapped)
    virtual int GetMovieClipTmplCount() const = 0;                                  // [52]  0x1A0  sub_180708E50  (decl-mapped)
    virtual const SUIEventDesc* GetEventDesc(const char* eventName) const = 0;      // [53]  0x1A8  sub_18187BEA0  (decl-mapped)
    virtual const SUIEventDesc* GetEventDesc(int index) const = 0;                  // [54]  0x1B0  sub_18187BE80  (decl-mapped)
    virtual int GetEventCount() const = 0;                                          // [55]  0x1B8  sub_180708C70  (decl-mapped)
    virtual const SUIEventDesc* GetFunctionDesc(const char* functionName) const = 0; // [56]  0x1C0  sub_18020DCD8  VERIFIED: CallFunction [65] resolves fctName via +0x1C0
    virtual const SUIEventDesc* GetFunctionDesc(int index) const = 0;               // [57]  0x1C8  sub_18187C0D4  (decl-mapped)
    virtual int GetFunctionCount() const = 0;                                       // [58]  0x1D0  sub_180708CA0  (decl-mapped)

    virtual void UpdateViewPort() = 0;                                              // [59]  0x1D8  sub_180556404  (decl-mapped)
    virtual void GetViewPort(int& x, int& y, int& width, int& height, float& aspectRatio) = 0; // [60] 0x1E0  sub_18187ED54  (decl-mapped)

    virtual bool Serialize(XmlNodeRef& xmlNode, bool bIsLoading) = 0;               // [61]  0x1E8  sub_18189467C  VERIFIED: LoadElementsFromFile calls (node, true) via +0x1E8

    virtual void AddEventListener(IUIElementEventListener* pListener, const char* name) = 0; // [62]  0x1F0  sub_180502430  (decl-mapped)
    virtual void RemoveEventListener(IUIElementEventListener* pListener) = 0;       // [63]  0x1F8  sub_1805023B4  (decl-mapped)

    // functions. const char* overload declared FIRST so MSVC's overload-reversal
    // lands it at the higher binary slot +0x208; declaring SUIEventDesc* first
    // sends CallFunction("name", ...) to +0x200 -> wrong handler. pDataRes =
    // TUIData* (CryVariant typedef — not forward-declarable, kept void*).
    virtual bool CallFunction(const char* fctName, const SUIArguments& args, void* pDataRes, const char* pTmplName) = 0;  // [65] 0x208  sub_18020DC54  VERIFIED ANCHOR: sub_18111FD4C ("fc_showInfoText", args, 0, 0); creates "Dynamic Created Fct" desc, tail-calls [64]
    virtual bool CallFunction(const SUIEventDesc* pFctDesc, const SUIArguments& args, void* pDataRes, const SUIMovieClipDesc* pTmplDesc) = 0; // [64] 0x200  sub_18020C9D8  VERIFIED: "Function invoked: %s (%s)" GFx Invoke

    virtual IFlashVariableObject* GetMovieClip(const SUIMovieClipDesc* pMovieClipDesc, const SUIMovieClipDesc* pTmplDesc) = 0; // [66] 0x210  sub_18020BB50  (decl-mapped)
    virtual IFlashVariableObject* GetMovieClip(const char* movieClipName, const char* pTmplName) = 0;                          // [67] 0x218  sub_18020BB08  (decl-mapped)
    virtual IFlashVariableObject* CreateMovieClip(const SUIMovieClipDesc*& pNewInstanceDesc, const SUIMovieClipDesc* pMovieClipTemplateDesc, const SUIMovieClipDesc* pParentMC, const char* mcInstanceName) = 0; // [68] 0x220  sub_1818707D0  (decl-mapped)
    virtual IFlashVariableObject* CreateMovieClip(const SUIMovieClipDesc*& pNewInstanceDesc, const char* movieClipTemplate, const char* mcParentName, const char* mcInstanceName) = 0;   // [69] 0x228  sub_181870764  (decl-mapped)
    // RemoveMovieClip triple REVERSED: (IFlashVariableObject*), (SUIParameterDesc*), (const char*)
    virtual void RemoveMovieClip(IFlashVariableObject* pVarObject) = 0;             // [70]  0x230  sub_1818931E8  (decl-mapped)
    virtual void RemoveMovieClip(const SUIParameterDesc* pMovieClipDesc) = 0;       // [71]  0x238  sub_1818932A8  (decl-mapped)
    virtual void RemoveMovieClip(const char* movieClipName) = 0;                    // [72]  0x240  sub_181893278  (decl-mapped)

    // variables (pairs REVERSED: desc-version first, name-version second).
    // value/valueOut = TUIData (CryVariant typedef — not forward-declarable,
    // kept void*).
    virtual bool SetVariable(const SUIParameterDesc* pVarDesc, const void* value, const SUIMovieClipDesc* pTmplDesc) = 0;        // [73] 0x248  sub_181895868  (decl-mapped)
    virtual bool SetVariable(const char* varName, const void* value, const char* pTmplName) = 0;         // [74] 0x250  sub_181895800  (decl-mapped)
    virtual bool GetVariable(const SUIParameterDesc* pVarDesc, void* valueOut, const SUIMovieClipDesc* pTmplDesc) = 0;           // [75] 0x258  sub_18187E974  (decl-mapped)
    virtual bool GetVariable(const char* varName, void* valueOut, const char* pTmplName) = 0;            // [76] 0x260  sub_18187E908  (decl-mapped)
    virtual bool CreateVariable(const SUIParameterDesc*& pNewDesc, const char* varName, const void* value, const SUIMovieClipDesc* pTmplDesc) = 0; // [77] 0x268  sub_181871B6C  (decl-mapped)
    virtual bool CreateVariable(const SUIParameterDesc*& pNewDesc, const char* varName, const void* value, const char* pTmplName) = 0; // [78] 0x270  sub_181871AFC  (decl-mapped)

    // arrays (pairs REVERSED)
    virtual bool SetArray(const SUIParameterDesc* pArrayDesc, const SUIArguments& values, const SUIMovieClipDesc* pTmplDesc) = 0;        // [79] 0x278  sub_181894EE0  (decl-mapped)
    virtual bool SetArray(const char* arrayName, const SUIArguments& values, const char* pTmplName) = 0;         // [80] 0x280  sub_181894E78  (decl-mapped)
    virtual bool GetArray(const SUIParameterDesc* pArrayDesc, SUIArguments& valuesOut, const SUIMovieClipDesc* pTmplDesc) = 0;           // [81] 0x288  sub_181874540  (decl-mapped)
    virtual bool GetArray(const char* arrayName, SUIArguments& valuesOut, const char* pTmplName) = 0;            // [82] 0x290  sub_1818744D8  (decl-mapped)
    virtual bool CreateArray(const SUIParameterDesc*& pNewDesc, const char* arrayName, const SUIArguments& values, const SUIMovieClipDesc* pTmplDesc) = 0; // [83] 0x298  sub_18186FB08  (decl-mapped)
    virtual bool CreateArray(const SUIParameterDesc*& pNewDesc, const char* arrayName, const SUIArguments& values, const char* pTmplName) = 0; // [84] 0x2A0  sub_18186FA98  (decl-mapped)

    // textures (pairs REVERSED)
    virtual void LoadTexIntoMc(const SUIParameterDesc* pMovieClipDesc, ITexture* pTexture, const SUIMovieClipDesc* pTmplDesc) = 0;   // [85] 0x2A8  sub_181887080  (decl-mapped)
    virtual void LoadTexIntoMc(const char* movieClip, ITexture* pTexture, const char* pTmplName) = 0;        // [86] 0x2B0  sub_181887018  (decl-mapped)
    virtual void UnloadTexFromMc(const SUIParameterDesc* pMovieClipDesc, ITexture* pTexture, const SUIMovieClipDesc* pTmplDesc) = 0; // [87] 0x2B8  sub_181897EAC  (decl-mapped)
    virtual void UnloadTexFromMc(const char* movieClip, ITexture* pTexture, const char* pTmplName) = 0;      // [88] 0x2C0  sub_181897E44  (decl-mapped)

    virtual void ScreenToFlash(const float& px, const float& py, float& rx, float& ry, bool bStageScaleMode) const = 0; // [89] 0x2C8  sub_181894158  (decl-mapped)
    virtual void WorldToFlash(const ::Matrix34& camMat, const ::Vec3& worldpos, ::Vec3& flashpos, ::Vec2& borders, float& scale, bool bStageScaleMode) const = 0; // [90] 0x2D0  sub_181899F00  (decl-mapped)

    // dyn textures
    virtual void AddTexture(IDynTextureSource* pDynTexture) = 0;                    // [91]  0x2D8  sub_18186A608  (decl-mapped)
    virtual void RemoveTexture(IDynTextureSource* pDynTexture) = 0;                 // [92]  0x2E0  sub_181893390  (decl-mapped)
    virtual int GetNumExtTextures() const = 0;                                      // [93]  0x2E8  sub_18187D820  (decl-mapped)
    virtual bool GetDynTexSize(int& width, int& height) const = 0;                  // [94]  0x2F0  sub_18187BC90  (decl-mapped)

    // input events
    virtual void SendCursorEvent(int evt, int iX, int iY, int iButton, float fWheel) = 0; // [95] 0x2F8  sub_1805004A8  SFlashCursorEvent::ECursorState (decl-mapped)
    virtual void SendKeyEvent(const SFlashKeyEvent& evt) = 0;                       // [96]  0x300  sub_1806AAB10  (decl-mapped)
    virtual void SendCharEvent(const SFlashCharEvent& charEvent) = 0;               // [97]  0x308  sub_1804FEE54  (decl-mapped)
    virtual void SendControllerEvent(int event, int state) = 0;                     // [98]  0x310  sub_1805007DC  EControllerInputEvent/State (decl-mapped)

    virtual void GetMemoryUsage(ICrySizer* s) const = 0;                            // [99]  0x318  sub_18187CFC0  (decl-mapped)
    virtual void RemoveFlashVarObj(const SUIParameterDesc* pDesc) = 0;              // [100] 0x320  sub_18020CC44  VERIFIED: CallFunction [64] calls via +0x320 after invoke
};

}  // namespace Offsets
