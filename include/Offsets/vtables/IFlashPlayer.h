#pragma once
#include <cstdint>
#include "IFlashVariableObject.h"
#include "CryEngine/CryCommon/SFlashVarValue.h"   // global SFlashVarValue (NOT the SDK IFlashPlayer.h — Cry_Math swamp)

// -----------------------------------------------
// IFlashPlayer — Binary vtable order (INTERFUSCATED)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashPlayer.h (<interfuscator:shuffle> block lines 86-181
//      => binary slot order != SDK declaration order; this replica is BINARY order).
// RTTI: .?AUIFlashPlayer@@ (global namespace, struct)
// Impl: CFlashPlayer (.?AVCFlashPlayer@@), sizeof == 0x198
//   - primary base (+0x00) IFlashPlayer            -> vtable 0x1821bc500 (this replica, 63 slots)
//   - second  base (+0x08) IFlashPlayer_RenderProxy -> vtable 0x1821bc4d8 (see IFlashPlayer_RenderProxy.h)
//   (base offsets verified via RTTI BaseClassArray pmd of COL @ both vtables)
//
// CFlashPlayer is the thread-safe CryEngine wrapper around statically linked
// Scaleform GFx 3.x: nearly every slot takes the CRITICAL_SECTION at this+0xF8
// and forwards to GFxMovieView* at this+0xB8 (movie-def queries use GFxMovieDef*
// at this+0xB0). Slot identification is behavioral: the GFxMovie/GFxMovieView
// vfunc offsets called by each wrapper line up exactly with the GFx 3.x Player.h
// declaration order (GetCurrentFrame +0x10, HasLooped +0x18, GotoFrame +0x20,
// GotoLabeledFrame +0x28, SetVisible +0x40, IsVisible +0x48, IsAvailable +0x50,
// CreateString +0x58 ... Invoke +0xB8, SetViewport +0xC8 ... Restart +0x120,
// Advance +0x128, SetPause +0x140, IsPaused +0x148, SetBackgroundColor +0x150,
// SetBackgroundAlpha +0x158, GetBackgroundAlpha +0x160, HandleEvent +0x168).
//
// Construction (see analysis/ui_infra/flashplayer.md):
//   CFlashPlayer::Ctor_180557760, allocation size 0x198 at both creation sites:
//   - CSystem::CreateFlashPlayer_180E6CCEC      (CSystem vtable 0x18268a6a8, slot 149)
//   - CFlashPlayer::CreateAndLoad_1805571E8(path, options, cat) — called by
//     CFlashPlayerBootStrapper::CreatePlayerInstance_1805569E0 (vtable 0x182685c98 slot [2])
//
// UNVERIFIED (flagged inline): slots [19][20][21] are three bool setters writing
// bit2/bit3 of +0x20 and bit5 of +0x21 (forwarded to renderer flags +0x48/+0x49/+0x4A
// by the render proxy). They are AvoidStencilClear / EnableMaskedRendering /
// ExtendCanvasToViewport, but the 1:1 assignment among the three rests only on
// member-declaration-order correlation with the SDK. Slot [36] is a true no-op.
// Slot [56]/[62] names are CE-version guesses for behavior not in our SDK copy.

struct SFlashCursorEvent;
struct SFlashKeyEvent;
struct SFlashCharEvent;
struct IFSCommandHandler;
struct IExternalInterfaceHandler;
struct IActionScriptFunction;
struct ITexture;
template<typename T> struct Color_tpl;
typedef Color_tpl<unsigned char> ColorB;   // matches CryCommon Cry_Color.h typedef

namespace Offsets {

struct IFlashPlayer {
    enum EScaleModeType { eSM_NoScale, eSM_ShowAll, eSM_ExactFit, eSM_NoBorder };
    enum EAlignType {
        eAT_Center, eAT_TopCenter, eAT_BottomCenter, eAT_CenterLeft, eAT_CenterRight,
        eAT_TopLeft, eAT_TopRight, eAT_BottomLeft, eAT_BottomRight
    };
    enum EFlashVariableArrayType { FVAT_Int, FVAT_Double, FVAT_Float, FVAT_ConstStrPtr, FVAT_ConstWstrPtr };

    // Binary vtable 0x1821bc500 (63 slots)
    virtual void AddRef() = 0;                                              // [0]  0x000 sub_1806F8A30  InterlockedIncrement(this+0x10)
    virtual void Release() = 0;                                             // [1]  0x008 sub_1803E8C2C  InterlockedExchangeAdd(this+0x10,-1); on 1 -> vcall [61] (scalar dtor)
    virtual bool Load(const char* pFilePath, unsigned int options = 0x1C,
                      unsigned int cat = 0) = 0;                            // [2]  0x010 sub_180E70FA4  strings ".usm", "Error: GFxLoader failed to open '%s'", "Trying to load non-stripped flash movie..."; GFxLoader::CreateMovie sub_180843020
    virtual void SetBackgroundColor(const ColorB& color) = 0;               // [3]  0x018 sub_180E752F0  repacks 4 colour bytes, GFxMovieView vf+0x150
    virtual void SetBackgroundAlpha(float alpha) = 0;                       // [4]  0x020 sub_180555E9C  GFxMovieView vf+0x158 (float stays in xmm1)
    virtual float GetBackgroundAlpha() const = 0;                           // [5]  0x028 sub_180E6EEFC  GFxMovieView vf+0x160 (double->float), 1.0f when no movie
    virtual void SetViewport(int x0, int y0, int width, int height,
                             float aspectRatio = 1.0f) = 0;                 // [6]  0x030 sub_1805566A8  builds GViewport, aspect<=0 -> 1.0f, GFxMovieView vf+0xC8
    virtual void GetViewport(int& x0, int& y0, int& width, int& height,
                             float& aspectRatio) const = 0;                 // [7]  0x038 sub_180E6FF80  GFxMovieView vf+0xD0
    virtual void SetViewScaleMode(EScaleModeType scaleMode) = 0;            // [8]  0x040 sub_180556800  enum remap 0..3, GFxMovieView vf+0xD8
    virtual EScaleModeType GetViewScaleMode() const = 0;                    // [9]  0x048 sub_180E6FF04  GFxMovieView vf+0xE0 (inverse remap)
    virtual void SetViewAlignment(EAlignType viewAlignment) = 0;            // [10] 0x050 sub_180556764  enum remap 0..8, GFxMovieView vf+0xE8
    virtual EAlignType GetViewAlignment() const = 0;                        // [11] 0x058 sub_180E6FE4C  GFxMovieView vf+0xF0
    virtual void SetScissorRect(int x0, int y0, int width, int height) = 0; // [12] 0x060 sub_180E75C54  GetViewport vf+0xD0, OR flag 0x4 (scissor), SetViewport vf+0xC8
    virtual void GetScissorRect(int& x0, int& y0, int& width,
                                int& height) const = 0;                     // [13] 0x068 sub_180E6F868  vf+0xD0, checks scissor flag bit (0x4 of viewport flags)
    virtual void Advance(float deltaTime) = 0;                              // [14] 0x070 sub_1803E0CB8  GFxMovieView vf+0x128 = GFxMovie::Advance(deltaTime, catchUp cvar dword_1829DC734)
    virtual void Render(bool stereo = false) = 0;                           // [15] 0x078 sub_1803E0B50  AddRef(this); renderer(*(this+0xC8)+0x38) vf+0x350(this+8 /*RenderProxy*/, stereo)
    virtual void SetCompositingDepth(float depth) = 0;                      // [16] 0x080 sub_1806F9010  this+0x18 = depth; ctor default 0.0f; RenderCallback: depth > 0 -> renderer vf+0xE8
    virtual void StereoEnforceFixedProjectionDepth(bool enforce) = 0;       // [17] 0x088 sub_1805007A0  bit1 of this+0x20; RenderCallback copies it to renderer+0x350, adjacent to stereo-frame flags +0x351/+0x352
    virtual void StereoSetCustomMaxParallax(float maxParallax = -1.0f) = 0; // [18] 0x090 sub_1806F9060  this+0x1C = v; ctor default 0xBF800000 = -1.0f == SDK default; -> renderer+0x344
    virtual void AvoidStencilClear(bool avoid) = 0;                         // [19] 0x098 sub_1806F8E00  bit2 of this+0x20 -> renderer+0x48   [UNVERIFIED name: one of the 3 bool render flags, see banner]
    virtual void EnableMaskedRendering(bool enable) = 0;                    // [20] 0x0A0 sub_1806F8E50  bit3 of this+0x20 -> renderer+0x49   [UNVERIFIED name: one of the 3 bool render flags, see banner]
    virtual void ExtendCanvasToViewport(bool extend) = 0;                   // [21] 0x0A8 sub_1806F8E60  bit5 of this+0x21 -> renderer+0x4A   [UNVERIFIED name: one of the 3 bool render flags, see banner]
    virtual void Restart() = 0;                                             // [22] 0x0B0 sub_180E74008  GFxMovieView vf+0x120 (slot directly before Advance +0x128 == GFx 3.x decl order)
    virtual bool IsPaused() const = 0;                                      // [23] 0x0B8 sub_180E70F3C  GFxMovieView vf+0x148
    virtual void Pause(bool pause) = 0;                                     // [24] 0x0C0 sub_180E72984  GFxMovieView vf+0x140 (SetPause)
    virtual void GotoFrame(unsigned int frameNumber) = 0;                   // [25] 0x0C8 sub_180E70190  GFxMovie vf+0x20
    virtual bool GotoLabeledFrame(const char* pLabel, int offset = 0) = 0;  // [26] 0x0D0 sub_180E701E4  GFxMovie vf+0x28, null label rejected
    virtual unsigned int GetCurrentFrame() const = 0;                       // [27] 0x0D8 sub_180E6F134  GFxMovie vf+0x10
    virtual bool HasLooped() const = 0;                                     // [28] 0x0E0 sub_180E704DC  GFxMovie vf+0x18
    virtual void SetFSCommandHandler(IFSCommandHandler* pHandler,
                                     void* pUserData = 0) = 0;              // [29] 0x0E8 sub_1805569D0  stores this+0x90 / this+0x98
    virtual void SetExternalInterfaceHandler(IExternalInterfaceHandler* pHandler,
                                             void* pUserData = 0) = 0;      // [30] 0x0F0 sub_1806F9020  stores this+0xA0 / this+0xA8
    virtual void SendCursorEvent(const SFlashCursorEvent& cursorEvent) = 0; // [31] 0x0F8 sub_180500588  state {0..3}->GFxEvent{1..4} (MouseMove/Down/Up/Wheel), reads m_cursorX@+4 m_cursorY@+8 m_button@+0xC m_wheelScrollVal@+0x10; vf+0x168 HandleEvent
    virtual void SendKeyEvent(const SFlashKeyEvent& keyEvent) = 0;          // [32] 0x100 sub_1806AAB54  state 0/1 -> GFxEvent 5/6 (KeyDown/KeyUp), remaps m_specialKeyState bits, m_keyCode@+4 m_asciiCode@+9 m_wcharCode@+0xC
    virtual void SendCharEvent(const SFlashCharEvent& charEvent) = 0;       // [33] 0x108 sub_1804FED58  GFxEvent type 0xD (CharEvent), m_wCharCode@+0 m_keyboardIndex@+4
    virtual void SetVisible(bool visible) = 0;                              // [34] 0x110 sub_180E76260  GFxMovie vf+0x40
    virtual bool GetVisible() const = 0;                                    // [35] 0x118 sub_180E70060  GFxMovie vf+0x48 (IsVisible)
    virtual void _vf36() = 0;                                               // [36] 0x120 sub_180E75664  NO-OP (Enter/LeaveCriticalSection only). UNVERIFIED: likely the stubbed RenderRecordLockless or RenderPlaybackLockless
    // SetVariable/GetVariable overload pairs: SFlashVarValue& declared FIRST so
    // MSVC's overload-reversal lands it at the HIGHER slot (+0x130 / +0x140) that
    // the binary uses. Declaring the IFlashVariableObject overload first sends the
    // SFlashVarValue& call to the lower slot -> wrong handler -> garbage value.
    virtual bool SetVariable(const char* pPathToVar,
                             const SFlashVarValue& value) = 0;              // [38] 0x130 sub_180E7602C  SFlashVarValue->GFxValue (sub_18020C590); GFxMovie vf+0x80
    virtual bool SetVariable(const char* pPathToVar,
                             const IFlashVariableObject* pVarObj) = 0;      // [37] 0x128 sub_180E760C4  GFxValue copied from pVarObj+8 (sub_18020C558), nullptr -> undefined; GFxMovie vf+0x80
    virtual bool GetVariable(const char* pPathToVar,
                             SFlashVarValue& value) const = 0;              // [40] 0x140 sub_180E6FC48  vf+0x88; GFxValue->SFlashVarValue sub_18020CE4C; (w)string results cached at this+0x108
    virtual bool GetVariable(const char* pPathToVar,
                             IFlashVariableObject*& pVarObj) const = 0;     // [39] 0x138 sub_180556878  GFxMovie vf+0x88; wraps result: operator new(0x70) + CFlashVariableObject::Ctor_18020C17C
    virtual bool IsAvailable(const char* pPathToVar) const = 0;             // [41] 0x148 sub_180500C20  GFxMovie vf+0x50 (VariableExists)
    virtual bool SetVariableArray(EFlashVariableArrayType type, const char* pPathToVar,
                                  unsigned int index, const void* pData,
                                  unsigned int count) = 0;                  // [42] 0x150 sub_180E76198  type remap sub_180E6EEB8; GFxMovie vf+0x90 (..., setType=1)
    virtual unsigned int GetVariableArraySize(const char* pPathToVar) const = 0; // [43] 0x158 sub_180E6FDE4  GFxMovie vf+0xA0
    virtual bool GetVariableArray(EFlashVariableArrayType type, const char* pPathToVar,
                                  unsigned int index, void* pData,
                                  unsigned int count) const = 0;            // [44] 0x160 sub_180E6FD3C  GFxMovie vf+0xA8; pData==null rejected
    virtual bool Invoke(const char* pMethodName, const SFlashVarValue* pArgs,
                        unsigned int numArgs, SFlashVarValue* pResult = 0) = 0; // [45] 0x168 sub_1805008B8  alloca GFxValue[numArgs] from 0x10-stride SFlashVarValue array (sub_18020C590); GFxMovie vf+0xB8; result via sub_18020CE4C
    virtual bool CreateString(const char* pString,
                              IFlashVariableObject*& pVarObj) = 0;          // [46] 0x170 sub_180E6E000  GFxMovieView vf+0x58; checks GFxValue type==4 (string); new(0x70) CFlashVariableObject
    virtual bool CreateStringW(const wchar_t* pString,
                               IFlashVariableObject*& pVarObj) = 0;         // [47] 0x178 sub_180E6E1D8  GFxMovieView vf+0x60; type==5 (wstring)
    virtual bool CreateObject(const char* pClassName, const SFlashVarValue* pArgs,
                              unsigned int numArgs,
                              IFlashVariableObject*& pVarObj) = 0;          // [48] 0x180 sub_180E6DC2C  GFxMovieView vf+0x68; arg array conversion as Invoke; type 6..8 (object/array/dispobj)
    virtual bool CreateArray(IFlashVariableObject*& pVarObj) = 0;           // [49] 0x188 sub_180E6C720  GFxMovieView vf+0x70; type==7 (array)
    virtual bool CreateFunction(IFlashVariableObject*& pFuncVarObj, IActionScriptFunction* pFunc,
                                void* pUserData = 0) = 0;                   // [50] 0x190 sub_180E6D9E4  builds FunctionHandlerAdaptor (vftable string) holding pFunc+player; GFxMovieView vf+0x78
    virtual unsigned int GetFrameCount() const = 0;                         // [51] 0x198 sub_1806F8EB0  returns dword this+0x80 (IDA-misnamed "UMSThreadProxy::GetId")
    virtual float GetFrameRate() const = 0;                                 // [52] 0x1A0 sub_1806F8EC0  returns float this+0x84
    virtual int GetWidth() const = 0;                                       // [53] 0x1A8 sub_1806F8FA0  returns dword this+0x88 (Load writes video width here for .usm)
    virtual int GetHeight() const = 0;                                      // [54] 0x1B0 sub_1806F8EE0  returns dword this+0x8C
    virtual size_t GetMetadata(char* pBuff, unsigned int buffSize) const = 0; // [55] 0x1B8 sub_180E6F7FC  GFxMovieDef(this+0xB0) vf+0x80; rdx/r8 passthrough verified in disasm; [56] calls this slot twice (size probe + fill)
    virtual bool HasMetadata(const char* pTag) const = 0;                   // [56] 0x1C0 sub_180E705B0  UNVERIFIED NAME: GetMetadata into temp buffer, then case-insensitive substring search sub_180414F88(buffer, pTag) != 0. Not present in our SDK header copy.
    virtual const char* GetFilePath() const = 0;                            // [57] 0x1C8 sub_1806F8E80  returns **(this+0xD0) (shared filepath cell, also handed to each CFlashVariableObject)
    virtual void ResetDirtyFlags() = 0;                                     // [58] 0x1D0 sub_1803E0EC4  fetches CryGFxTranslator singleton (off_1829D1A78, lazy-init w/ atexit) and clears its dirty byte at +0x28
    virtual void ScreenToClient(int& x, int& y) const = 0;                  // [59] 0x1D8 sub_180500650  GetViewport vf+0xD0; x -= x0, y -= y0
    virtual void ClientToScreen(int& x, int& y) const = 0;                  // [60] 0x1E0 sub_180E6A5C0  GetViewport vf+0xD0; x += x0, y += y0
    virtual ~IFlashPlayer() {}                                              // [61] 0x1E8 sub_1805573E4  scalar deleting dtor -> ~CFlashPlayer sub_180557418 (+free if flags&1); Release vcalls this slot
    virtual bool SetOverrideTexture(const char* pResourceName, ITexture* pTexture,
                                    bool resize = true) = 0;                // [62] 0x1F0 sub_180E75870  UNVERIFIED NAME: GFxMovieDef vf+0xD8 GetResource(name), resource-type check (vf+0x10()&0xFF00)==0x100 (image), wraps texture in 0x38-byte GImageInfo-like object (sub_180E7D050 / sub_180E7D0F8 w/ original dims when resize), swaps into resource+0x18. Not present in our SDK header copy.
};

}  // namespace Offsets
