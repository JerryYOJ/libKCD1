#pragma once

#include <cstdint>
#include "IInputEventListener.h"
#include "SInputEvent.h"

// -----------------------------------------------
// IInput — raw input system (concrete impl CDXInput)
// -----------------------------------------------
// Lives at gEnv+0x48 (the IDA/SDK gEnv label "pStatoscope" is WRONG — KCD
// reorders gEnv; gEnv+0x38 "pInput" is actually the view/renderer). The runtime
// object is CDXInput (vtable 0x182797de8), which inherits CBaseInput; the IInput
// interface is UNIQUE_IFACE/shuffled in the SDK, so this is the FULL binary
// vtable order de-shuffled against the concrete impl. All slots verified from
// decompilation unless marked.
//
// Two slots are genuinely unrecoverable and left as opaque placeholders:
//   [16] +0x80  /OPT:ICF folded the slot onto the CRT _isctype_l — a KCD-specific
//               virtual whose body is shared with unrelated code; identity lost.
//   [50] +0x190 an empty `return false` stub (sub_180434C90), no call site found.

namespace Offsets {

struct ITouchEventListener;   // opaque
struct IInputDevice;          // opaque
struct IKinectInput;          // opaque
struct INaturalPointInput;    // opaque
struct IEyeTrackerInput;      // opaque
enum   EInputDeviceType : int;

struct IInput {
    virtual void  Dtor(char flags) = 0;                                                       // [0]  +0x00  ~CDXInput
    virtual void  AddConsoleEventListener(IInputEventListener* p) = 0;                         // [1]  +0x08
    virtual void  RemoveConsoleEventListener(IInputEventListener* p) = 0;                      // [2]  +0x10
    virtual void  AddEventListener(IInputEventListener* p) = 0;                                // [3]  +0x18  ◄ register here
    virtual void  RemoveEventListener(IInputEventListener* p) = 0;                             // [4]  +0x20  ◄ unregister here
    virtual bool  AddTouchEventListener(ITouchEventListener* p, const char* name) = 0;         // [5]  +0x28
    virtual void  RemoveTouchEventListener(ITouchEventListener* p) = 0;                        // [6]  +0x30
    virtual void  SetExclusiveListener(IInputEventListener* p) = 0;                            // [7]  +0x38
    virtual IInputEventListener* GetExclusiveListener() = 0;                                   // [8]  +0x40
    virtual bool  AddInputDevice(IInputDevice* pDevice) = 0;                                   // [9]  +0x48
    virtual void  EnableEventPosting(bool bEnable) = 0;                                        // [10] +0x50
    virtual bool  IsEventPostingEnabled() const = 0;                                           // [11] +0x58
    virtual void  PostInputEvent(const SInputEvent& event, bool bForce = false) = 0;           // [12] +0x60
    virtual void  PostTouchEvent(const void* touchEvent, bool bForce = false) = 0;             // [13] +0x68  const STouchEvent&
    virtual void  PostUnicodeEvent(const void* unicodeEvent, bool bForce = false) = 0;         // [14] +0x70  const SUnicodeEvent&
    virtual void  ForceFeedbackEvent(const void* ffEvent) = 0;                                 // [15] +0x78  const SFFOutputEvent& (likely; empty on PC)
    virtual void  _vf16() = 0;                                                                 // [16] +0x80  UNIDENTIFIED (ICF-folded onto CRT)
    virtual void  ForceFeedbackSetDeviceIndex(int index) = 0;                                  // [17] +0x88  (likely)
    virtual bool  Init() = 0;                                                                  // [18] +0x90
    virtual void  PostInit() = 0;                                                              // [19] +0x98
    virtual void  Update(bool bFocus) = 0;                                                     // [20] +0xA0
    virtual void  ShutDown() = 0;                                                              // [21] +0xA8
    virtual void  SetExclusiveMode(EDeviceId deviceId, bool exclusive, void* hwnd = nullptr) = 0; // [22] +0xB0
    virtual bool  InputState(const char* key, EInputState state) = 0;                          // [23] +0xB8  key = TKeyName
    virtual const char*    GetKeyName(EKeyId keyId) const = 0;                                 // [24] +0xC0
    virtual const char*    GetKeyName(const SInputEvent& event) const = 0;                     // [25] +0xC8
    virtual char           GetInputCharAscii(const SInputEvent& event) = 0;                    // [26] +0xD0
    virtual SInputSymbol*  LookupSymbol(EDeviceId deviceId, int deviceIndex, EKeyId keyId) = 0;// [27] +0xD8
    virtual const SInputSymbol* GetSymbolByName(const char* name) const = 0;                   // [28] +0xE0
    virtual const wchar_t* GetOSKeyName(const SInputEvent& event) = 0;                         // [29] +0xE8
    virtual void  ClearKeyState() = 0;                                                         // [30] +0xF0
    virtual void  ClearAnalogKeyState() = 0;                                                   // [31] +0xF8
    virtual void  RetriggerKeyState() = 0;                                                     // [32] +0x100
    virtual bool  Retriggering() = 0;                                                          // [33] +0x108
    virtual bool  HasInputDeviceOfType(EInputDeviceType type) = 0;                             // [34] +0x110
    virtual int   GetModifiers() const = 0;                                                    // [35] +0x118
    virtual void  EnableDevice(EDeviceId deviceId, bool enable) = 0;                           // [36] +0x120
    virtual void  SetDeadZone(float fThreshold) = 0;                                           // [37] +0x128
    virtual void  RestoreDefaultDeadZone() = 0;                                                // [38] +0x130
    virtual IInputDevice*  GetDevice(uint16_t deviceIndex, EInputDeviceType type) = 0;         // [39] +0x138  (likely)
    virtual uint32_t       GetPlatformFlags() const = 0;                                       // [40] +0x140  (likely)
    virtual bool  SetBlockingInput(const void* blockData) = 0;                                 // [41] +0x148  const SInputBlockData&
    virtual bool  RemoveBlockingInput(const void* blockData) = 0;                              // [42] +0x150  const SInputBlockData&
    virtual bool  HasBlockingInput(const void* blockData) const = 0;                           // [43] +0x158  const SInputBlockData&
    virtual int   GetNumBlockingInputs() const = 0;                                            // [44] +0x160
    virtual void  ClearBlockingInputs() = 0;                                                   // [45] +0x168
    virtual bool  ShouldBlockInputEventPosting(EKeyId keyId, EDeviceId deviceId, uint8_t deviceIndex) const = 0; // [46] +0x170
    virtual IKinectInput*       GetKinectInput() = 0;                                          // [47] +0x178
    virtual INaturalPointInput* GetNaturalPointInput() = 0;                                    // [48] +0x180
    virtual IEyeTrackerInput*   GetEyeTrackerInput() = 0;                                       // [49] +0x188  (likely; Warhorse Tobii)
    virtual bool  _vf50() = 0;                                                                 // [50] +0x190  UNIDENTIFIED stub (returns false)
    virtual const char* GetKeyNameLocalized(const SInputEvent& event) = 0;                     // [51] +0x198  (Warhorse; name unverified)
    virtual void  FlushBufferedInputs() = 0;                                                   // [52] +0x1A0  (Warhorse)
};

}  // namespace Offsets
