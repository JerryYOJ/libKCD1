#pragma once

#include <cstdint>
#include "IActionListener.h"

// -----------------------------------------------
// IActionMapManager — binary vtable replica (concrete CActionMapManager)
// -----------------------------------------------
// SDK: CryEngine CryAction/IActionMapManager.h (UNIQUE_IFACE → shuffled, plus
// KCD added several methods). Concrete vtable @ 0x182733200 (56 slots), de-
// shuffled against the impl. Obtained via IGameFramework::GetIActionMapManager()
// (CCryAction vtable [28] +0xE0). Lua surface: global table "ActionMapManager".
//
// All slots identified from log strings + decompilation (most are "verified";
// a few list-management mirrors are "likely"; slots 29/55 are best-effort).
// Smart-pointer-by-value returns (iterators) are simplified to void* — fine for
// laying out the vtable; just don't call those two through this replica.

namespace Offsets {

struct IActionMap;                 // opaque
struct IActionFilter;              // opaque
struct IActionMapPopulateCallBack; // opaque
struct IActionMapEventListener;    // opaque
struct SActionInput;               // opaque
struct SActionInputDeviceData;     // opaque
enum   EActionFilterType : int;
enum   EActionInputDevice : int;
using  EntityId = unsigned int;

struct IActionMapManager {
    virtual void Dtor(char flags) = 0;                                                         // [0]  +0x000  ~CActionMapManager
    virtual void Update() = 0;                                                                 // [1]  +0x008
    virtual void Reset() = 0;                                                                  // [2]  +0x010
    virtual void Clear() = 0;                                                                  // [3]  +0x018
    virtual bool InitActionMaps(const char* szFilename) = 0;                                   // [4]  +0x020  (KCD-added)
    virtual void SetLoadFromXMLPath(const char* szPath) = 0;                                   // [5]  +0x028
    virtual const char* GetLoadFromXMLPath() const = 0;                                        // [6]  +0x030
    virtual bool LoadFromXML(const void* node) = 0;                                            // [7]  +0x038  const XmlNodeRef&
    virtual bool LoadRebindDataFromXML(const void* node) = 0;                                  // [8]  +0x040
    virtual bool SaveRebindDataToXML(void* node) = 0;                                          // [9]  +0x048
    virtual void AddExtraActionListener(IActionListener* l, const char* actionMap = nullptr) = 0;    // [10] +0x050  ◄ global if actionMap null
    virtual void RemoveExtraActionListener(IActionListener* l, const char* actionMap = nullptr) = 0; // [11] +0x058
    virtual const void* GetExtraActionListeners() const = 0;                                   // [12] +0x060  const TActionListeners&
    virtual void AddAlwaysActionListener(void* blockingListener) = 0;                          // [13] +0x068  TBlockingActionListener (boost::shared_ptr)
    virtual void RemoveAlwaysActionListener(void* blockingListener) = 0;                       // [14] +0x070
    virtual void RemoveAllAlwaysActionListeners() = 0;                                         // [15] +0x078
    virtual IActionMap* CreateActionMap(const char* name) = 0;                                 // [16] +0x080
    virtual bool RemoveActionMap(const char* name) = 0;                                        // [17] +0x088
    virtual void RemoveAllActionMaps() = 0;                                                    // [18] +0x090
    virtual IActionMap* GetActionMap(const char* name) = 0;                                    // [19] +0x098
    virtual IActionFilter* CreateActionFilter(const char* name, EActionFilterType type) = 0;   // [20] +0x0A0
    virtual IActionFilter* GetActionFilter(const char* name) = 0;                              // [21] +0x0A8
    virtual void* CreateActionMapIterator() = 0;                                               // [22] +0x0B0  IActionMapIteratorPtr (by value)
    virtual void* CreateActionFilterIterator() = 0;                                            // [23] +0x0B8  IActionFilterIteratorPtr (by value)
    virtual const SActionInput* GetActionInput(const ActionId& actionId, EActionInputDevice device, int iByDeviceIndex) const = 0;                       // [24] +0x0C0  (KCD: searches all maps)
    virtual const SActionInput* GetActionInput(const char* actionMapName, const ActionId& actionId, EActionInputDevice device, int iByDeviceIndex) const = 0; // [25] +0x0C8
    virtual void Enable(bool enable, bool resetStateOnDisable = false) = 0;                    // [26] +0x0D0
    virtual void EnableActionMap(const char* name, bool enable) = 0;                           // [27] +0x0D8  (empty name = all maps)
    virtual void EnableFilter(const char* name, bool enable) = 0;                              // [28] +0x0E0  (empty name = all filters)
    virtual void FilterAction(const char* filterName, uint32_t actionCRC, bool bFiltered) = 0; // [29] +0x0E8  (KCD-inserted; name best-effort)
    virtual bool IsFilterEnabled(const char* name) = 0;                                        // [30] +0x0F0
    virtual void ReleaseFilteredActions() = 0;                                                 // [31] +0x0F8
    virtual void ClearStoredCurrentInputData() = 0;                                            // [32] +0x100
    virtual bool ReBindActionInput(const char* actionMapName, const ActionId& actionId, const char* szCurrentInput, const char* szNewInput) = 0; // [33] +0x108
    virtual int  GetVersion() const = 0;                                                       // [34] +0x110
    virtual void SetVersion(int version) = 0;                                                  // [35] +0x118
    virtual void EnumerateActions(IActionMapPopulateCallBack* pCallBack) const = 0;            // [36] +0x120
    virtual int  GetActionsCount() const = 0;                                                  // [37] +0x128
    virtual int  GetActionMapsCount() const = 0;                                               // [38] +0x130
    virtual bool AddInputDeviceMapping(EActionInputDevice deviceType, const char* szDeviceTypeStr) = 0; // [39] +0x138
    virtual bool RemoveInputDeviceMapping(EActionInputDevice deviceType) = 0;                  // [40] +0x140
    virtual void ClearInputDevicesMappings() = 0;                                              // [41] +0x148
    virtual int  GetNumInputDeviceData() const = 0;                                            // [42] +0x150
    virtual const SActionInputDeviceData* GetInputDeviceDataByIndex(int iIndex) = 0;           // [43] +0x158
    virtual const SActionInputDeviceData* GetInputDeviceDataByType(const char* szDeviceType) = 0;     // [44] +0x160  (overloads swapped vs SDK)
    virtual const SActionInputDeviceData* GetInputDeviceDataByType(EActionInputDevice deviceType) = 0; // [45] +0x168
    virtual void RemoveAllRefireData() = 0;                                                    // [46] +0x170
    virtual bool LoadControllerLayoutFile(const char* szLayoutKeyName) = 0;                    // [47] +0x178  (KCD-added)
    virtual EntityId GetDefaultActionEntity() const = 0;                                       // [48] +0x180
    virtual void SetDefaultActionEntity(EntityId id, bool bUpdateAll = true) = 0;              // [49] +0x188
    virtual void RegisterActionMapEventListener(IActionMapEventListener* l) = 0;               // [50] +0x190
    virtual void UnregisterActionMapEventListener(IActionMapEventListener* l) = 0;             // [51] +0x198
    virtual bool ActionFiltered(const ActionId& action) = 0;                                   // [52] +0x1A0  (any enabled filter blocks it?)
    virtual const IActionMap* GetActionMap(const char* name) const = 0;                        // [53] +0x1A8  (const overload)
    virtual void RemoveAllActionFilters() = 0;                                                 // [54] +0x1B0  (KCD-added)
    virtual void RemoveAllInputBlockData() = 0;                                                // [55] +0x1B8  (name best-effort)
};

}  // namespace Offsets
