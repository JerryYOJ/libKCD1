#pragma once

#include <cstdint>
#include "IActionListener.h"

// -----------------------------------------------
// IGameObject — Binary vtable order (interfuscated)
// -----------------------------------------------
// CGameObject RTTI: .?AVCGameObject@@
// IGameObject sub-object vtable: 0x1821A5950 (at CGameObject+0x28)
// IGameObject is a secondary base of CGameObject, NOT the primary vtable.
// C_Actor stores IGameObject* at IActor+0x28 (m_pGameObject).
//
// Inherits IActionListener as base (slots 0-2).
// Total: 63 slots (0x00-0x1F0)
//
// CGameObject layout (key offsets from IGameObject sub-object base):
//   +0x08  EntityId m_entityId          +0x10  IMovementController*
//   +0x18  IEntity* m_pEntity           +0x20  IActionListener* m_pActionDelegate
//   +0x28  IGameObjectView* m_pViewDelegate
//   +0x30  IGameObjectProfileManager* m_pProfileManager
//   +0x38  uint8_t m_profiles[32]       +0x58  void* (WH-specific field)
//   +0x80  uint16_t m_channelId         +0x84  uint32_t m_enabledAspects
//   +0x88  uint32_t m_delegatableAspects
//   +0x8C  uint8_t m_flags (bit 0x04=justExchanging, 0x40=noSyncPhysics)
//   +0x90  uint8_t m_aiPhysFlags (bits 3-4=aiMode, 5-6=physDisable)
//   +0xB8  uint32_t m_enabledPhysicsEvents
//   +0xBC  int32_t m_forceUpdate        +0xC0  uint32_t m_predictionHandle
//   +0xC4  uint32_t m_prePhysicsUpdateRule
//   +0xD4  EntityId m_networkParentId

struct IEntity;

namespace Offsets {

struct IGameObjectExtension;
struct IGameObjectView;
struct IGameObjectProfileManager;

struct IGameObject : IActionListener {
    // === IGameObject (slots 3-62, interfuscated) ===
    virtual bool BindToNetwork(int mode) = 0;                                  // [3]  0x018  0x1805DB1B8  calls [4] with parentId=0
    virtual bool BindToNetworkWithParent(int mode, uint32_t parentId) = 0;     // [4]  0x020  0x1805DB1C4
    virtual void ChangedNetworkState(uint32_t aspects) = 0;                    // [5]  0x028  0x1819AA728
    virtual void EnableAspect(uint32_t aspects, bool enable) = 0;              // [6]  0x030  0x1819B037C  m_enabledAspects at +0x84
    virtual void EnableDelegatableAspect(uint32_t aspects, bool enable) = 0;   // [7]  0x038  0x1819B03D0  m_delegatableAspects at +0x88
    virtual void DontSyncPhysics() = 0;                                        // [8]  0x040  0x1807092D0  sets +0x8C |= 0x40
    virtual IGameObjectExtension* QueryExtension(const char* name) = 0;        // [9]  0x048  0x180600030
    virtual IGameObjectExtension* _vf10() = 0;                                 // [10] 0x050  0x1805FFFFC  internal QueryExtensionByNewId
    virtual void SetExtensionParams(const char* ext, void* pTable) = 0;        // [11] 0x058  0x1819C7BF8
    virtual void GetExtensionParams(const char* ext, void* pTable) = 0;        // [12] 0x060  0x1819B5278
    virtual void SendEvent(const void* pEvent) = 0;                            // [13] 0x068  0x1803B9824  SGameObjectEvent&
    virtual void ForceUpdate(bool force) = 0;                                  // [14] 0x070  0x1819B113C  m_forceUpdate at +0xBC
    virtual void ForceUpdateExtension(IGameObjectExtension* ext, int slot) = 0; // [15] 0x078  0x1819B1150
    virtual uint16_t GetChannelId() const = 0;                                 // [16] 0x080  0x1803713F0  *(uint16*)(+0x80)
    virtual void SetChannelId(uint16_t id) = 0;                                // [17] 0x088  0x1819C7AF4
    virtual void* GetNetChannel() const = 0;                                   // [18] 0x090  0x1819B6FE8  INetChannel*
    virtual void FullSerialize(void* ser) = 0;                                 // [19] 0x098  0x1819B1188  TSerialize
    virtual void NetSerialize(void* ser, uint32_t aspect, uint8_t profile, int flags) = 0; // [20] 0x0A0  0x1819BC8A4
    virtual void PostSerialize() = 0;                                          // [21] 0x0A8  0x1819BF420
    virtual bool IsProbablyVisible() = 0;                                      // [22] 0x0B0  0x1819B9974
    virtual bool IsProbablyDistant() = 0;                                      // [23] 0x0B8  0x1819B98F4
    virtual bool SetAspectProfile(uint32_t aspect, uint8_t profile, bool fromNetwork) = 0; // [24] 0x0C0  0x1805DD244
    virtual uint8_t GetAspectProfile(uint32_t aspect) = 0;                     // [25] 0x0C8  0x1819B2820  m_profiles at +0x38
    virtual IGameObjectExtension* GetExtensionWithRMIBase(const void* pBase) = 0; // [26] 0x0D0  0x1819B54C8
    virtual void EnablePrePhysicsUpdate(int rule) = 0;                         // [27] 0x0D8  0x180437FE4  m_prePhysicsUpdateRule at +0xC4
    virtual void SetNetworkParent(uint32_t parentId) = 0;                      // [28] 0x0E0  0x1819C7E54  m_networkParentId at +0xD4
    virtual void Pulse(uint32_t pulse) = 0;                                    // [29] 0x0E8  0x1819C12DC
    virtual void RegisterAsPredicted() = 0;                                    // [30] 0x0F0  0x1819C2424
    virtual void RegisterAsValidated(IGameObject* pObj, int predictionHandle) = 0; // [31] 0x0F8  0x1819C2498
    virtual uint32_t GetPredictionHandle() = 0;                                // [32] 0x100  0x180708E20  m_predictionHandle at +0xC0
    virtual void RegisterExtForEvents(IGameObjectExtension* ext, const int* events, int count) = 0; // [33] 0x108  0x180561B60
    virtual void UnRegisterExtForEvents(IGameObjectExtension* ext, const int* events, int count) = 0; // [34] 0x110  0x180561BB4
    virtual void EnablePhysicsEvent(bool enable, int events) = 0;              // [35] 0x118  0x180561134  m_enabledPhysicsEvents at +0xB8
    virtual bool WantsPhysicsEvent(int events) = 0;                            // [36] 0x120  0x1803765B8
    virtual void AttachDistanceChecker() = 0;                                  // [37] 0x128  0x1819A9CD4
    virtual void SetAIActivation(int mode) = 0;                               // [38] 0x130  0x1805395C0  bits 3-4 of +0x90
    virtual void SetAutoDisablePhysicsMode(int mode) = 0;                      // [39] 0x138  0x1806089AC  bits 5-6 of +0x90
    virtual bool ShouldUpdate() = 0;                                           // [40] 0x140  0x1819C8C58
    virtual void RequestRemoteUpdate(uint32_t aspects) = 0;                    // [41] 0x148  0x1805DE17C
    virtual void CaptureView(IGameObjectView* pView) = 0;                     // [42] 0x150  0x1805FF444  m_pViewDelegate at +0x28
    virtual void ReleaseView(IGameObjectView* pView) = 0;                     // [43] 0x158  0x1804EFACC
    virtual void CaptureActions(void* pListener) = 0;                          // [44] 0x160  0x1819AA4B4  m_pActionDelegate at +0x20
    virtual void ReleaseActions(void* pListener) = 0;                          // [45] 0x168  0x180E2ABEC
    virtual void CaptureProfileManager(IGameObjectProfileManager* pm) = 0;    // [46] 0x170  0x1802BDFB0  m_pProfileManager at +0x30
    virtual void ReleaseProfileManager(IGameObjectProfileManager* pm) = 0;    // [47] 0x178  0x180438F10
    virtual void EnableUpdateSlot(IGameObjectExtension* ext, int slot) = 0;   // [48] 0x180  0x180438F1C
    virtual void DisableUpdateSlot(IGameObjectExtension* ext, int slot) = 0;  // [49] 0x188  0x180437FF4
    virtual uint8_t GetUpdateSlotEnables(IGameObjectExtension* ext, int slot) = 0; // [50] 0x190  0x1819B770C
    virtual void EnablePostUpdates(IGameObjectExtension* ext) = 0;            // [51] 0x198  0x180437F28
    virtual void DisablePostUpdates(IGameObjectExtension* ext) = 0;           // [52] 0x1A0  0x180438034
    virtual void SetUpdateSlotEnableCondition(IGameObjectExtension* ext, int slot, int cond) = 0; // [53] 0x1A8  0x1802BBEDC
    virtual void PostUpdate(float dt) = 0;                                     // [54] 0x1B0  0x18057CB84
    virtual void* GetWorldQuery() = 0;                                         // [55] 0x1B8  0x1819B7900  IWorldQuery*
    virtual bool IsJustExchanging() = 0;                                       // [56] 0x1C0  0x1807094F0  (+0x8C & 4) != 0
    virtual void* GetMovementController() = 0;                                 // [57] 0x1C8  0x18036D7CC  IMovementController*
    virtual void GetMemoryUsage(void* pSizer) = 0;                            // [58] 0x1D0  0x180B1D018  thunk
    virtual void* _vf59() = 0;                                                // [59] 0x1D8  0x1806FD7E0  WH getter: *(QWORD*)(+0x58)
    virtual void _vf60(void* p) = 0;                                          // [60] 0x1E0  0x180703EF0  WH setter: *(QWORD*)(+0x58) = p
    virtual void* ChangeExtension(const char* name, int changeType) = 0;      // [61] 0x1E8  0x1802BC6E0
    virtual void DoInvokeRMI(void* pBody, unsigned int where, int channel) = 0; // [62] 0x1F0  0x1819AFACC
};

} // namespace Offsets
