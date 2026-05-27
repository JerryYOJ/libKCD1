#pragma once

#include <cstdint>
#include <functional>

// ---- Plugin handle ----

using PluginHandle = uint32_t;
constexpr PluginHandle kPluginHandle_Invalid = 0xFFFFFFFF;
constexpr PluginHandle kPluginHandle_KCSE    = 0;

// ---- Version data exported by plugins as `KCSEPlugin_Version` ----

struct KCSEPluginVersionData {
    enum { kDataVersion = 1 };

    enum {
        kVersionIndependent_None       = 0,
        kVersionIndependent_Signatures = 1 << 0,
    };

    uint32_t    dataVersion;
    uint32_t    pluginVersion;
    char        name[256];
    char        author[256];
    uint32_t    compatibleGameVersions[16];
    uint32_t    kcseVersionRequired;
    uint32_t    versionIndependence;
};

// ---- Plugin info (available after PostLoad) ----

struct KCSEPluginInfo {
    enum { kVersion = 1 };

    uint32_t    infoVersion;
    const char* name;
    uint32_t    version;
};

// ---- Message ----

struct KCSEMessage {
    const char* sender;
    uint32_t    type;
    uint32_t    dataLen;
    void*       data;
};

// ---- Task function ----

using TaskFn = std::function<void()>;

// ---- Interface IDs ----

enum : uint32_t {
    kInterface_Messaging   = 0,
    kInterface_Trampoline  = 1,
    kInterface_Task        = 2,
};

// ---- Messaging interface ----

class IMessagingInterface {
public:
    enum { kInterfaceVersion = 1 };

    enum : uint32_t {
        kMessage_AllPluginsLoaded = 0,
        kMessage_LoadGame,
        kMessage_SaveGame,
        kMessage_NewGame,
        kMessage_InputLoaded,
        kMessage_DataLoaded,
    };

    using EventCallback = void(*)(KCSEMessage* msg);

    virtual uint32_t GetInterfaceVersion() const = 0;
    virtual bool RegisterListener(PluginHandle listener, const char* sender, EventCallback handler) = 0;
    virtual bool Dispatch(PluginHandle sender, uint32_t messageType, void* data, uint32_t dataLen, const char* receiver) = 0;
};

// ---- Trampoline interface ----

class Trampoline; // forward decl — plugins include BranchTrampoline.h for full type

class ITrampolineInterface {
public:
    enum { kInterfaceVersion = 3 };

    virtual uint32_t GetInterfaceVersion() const = 0;
    virtual Trampoline* CreateTrampoline(PluginHandle plugin, size_t size) = 0;
    virtual Trampoline* GetTrampoline(PluginHandle plugin) = 0;
    virtual void DestroyTrampoline(PluginHandle plugin) = 0;
};

// ---- Task interface ----

class ITaskInterface {
public:
    enum { kInterfaceVersion = 1 };

    virtual uint32_t GetInterfaceVersion() const = 0;
    virtual void AddTask(TaskFn task) = 0;
};

// ---- Root interface passed to KCSEPlugin_Load ----

class IKCSEInterface {
public:
    enum { kVersion = 1 };

    virtual uint32_t GetKCSEVersion() const = 0;
    virtual uint32_t GetGameVersion() const = 0;
    virtual uint32_t GetReleaseIndex() const = 0;
    virtual PluginHandle GetPluginHandle() const = 0;
    virtual const KCSEPluginInfo* GetPluginInfo(const char* name) const = 0;
    virtual void* QueryInterface(uint32_t id) const = 0;

    IMessagingInterface*  GetMessagingInterface() const  { return static_cast<IMessagingInterface*>(QueryInterface(kInterface_Messaging)); }
    ITrampolineInterface* GetTrampolineInterface() const { return static_cast<ITrampolineInterface*>(QueryInterface(kInterface_Trampoline)); }
    ITaskInterface*       GetTaskInterface() const       { return static_cast<ITaskInterface*>(QueryInterface(kInterface_Task)); }
};

// ---- Plugin entry points ----

using KCSEPlugin_LoadFn = bool(*)(const IKCSEInterface* kcse);

// ---- Global accessors (call KCSE::Init in KCSEPlugin_Load) ----

namespace KCSE {

inline const IKCSEInterface*  g_kcse       = nullptr;
inline PluginHandle           g_handle     = kPluginHandle_Invalid;
inline IMessagingInterface*   g_messaging  = nullptr;
inline ITrampolineInterface*  g_trampoline = nullptr;
inline ITaskInterface*        g_task       = nullptr;

inline void Init(const IKCSEInterface* kcse) {
    g_kcse       = kcse;
    g_handle     = kcse->GetPluginHandle();
    g_messaging  = kcse->GetMessagingInterface();
    g_trampoline = kcse->GetTrampolineInterface();
    g_task       = kcse->GetTaskInterface();
}

inline PluginHandle           GetPluginHandle()       { return g_handle; }
inline const IKCSEInterface*  GetInterface()          { return g_kcse; }
inline IMessagingInterface*   GetMessagingInterface()  { return g_messaging; }
inline ITrampolineInterface*  GetTrampolineInterface() { return g_trampoline; }
inline ITaskInterface*        GetTaskInterface()       { return g_task; }

}  // namespace KCSE
