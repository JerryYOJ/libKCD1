#pragma once

#include <cstdint>
#include <vector>

namespace wh::framework {

namespace internal {

// S_Job — base unit of the framework task graph.
// RTTI: .?AUS_Job@internal@framework@wh@@
// vtable @ 0x1822c1ee0 (approx)
// Destructor: sub_180F18294
class S_Job {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_S_Job;
    virtual ~S_Job() = default;

    uint16_t m_flags;           // +0x08  (init 0)
    uint16_t m_moduleId;        // +0x0A  assigned module enum id (from global counter)
    uint32_t _pad0C;            // +0x0C
};
static_assert(offsetof(S_Job, m_moduleId) == 0x0A);

// S_Graph — task graph node with dependency/successor vectors.
// RTTI: .?AUS_Graph@internal@framework@wh@@
// Destructor (sub_180F18294) frees four vectors at +0x18..+0x70.
// Size: 0x78 bytes (S_Job 0x10 + own 0x68).
class S_Graph : public S_Job {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_S_Graph;
    uint64_t m_graphData;                   // +0x10

    std::vector<uint64_t> m_predecessors;   // +0x18
    std::vector<uint64_t> m_successors;     // +0x30
    std::vector<uint64_t> m_inputs;         // +0x48
    std::vector<uint64_t> m_outputs;        // +0x60
};
static_assert(sizeof(S_Graph) == 0x78);

}  // namespace internal

// I_ModuleMessageListener — interface for receiving framework messages.
// RTTI: .?AVI_ModuleMessageListener@framework@wh@@
// Secondary vtable in C_BaseModule at offset +0x78.
class I_ModuleMessageListener {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_ModuleMessageListener;
    virtual ~I_ModuleMessageListener() = default;                   // [0]
    virtual void OnModuleMessage(void* msg) = 0;                    // [1]
};

// C_Graph — graph node with full task scheduling.
// RTTI: .?AVC_Graph@framework@wh@@
// Inherits S_Graph, adds nothing visible in layout.
class C_Graph : public internal::S_Graph {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Graph;
};

// C_BaseModule — base class for all Warhorse engine modules.
// Provides module lifecycle integration (Init, Shutdown, Update).
// Inherited by C_DatabaseModule, C_CombatModule, C_EntityModule, etc.
//
// RTTI: .?AVC_BaseModule@framework@wh@@
// Primary vtable @ 0x1822C1D30
// Secondary vtable (I_ModuleMessageListener) @ 0x1822C1D80, at this+0x78
// Constructor: sub_180F364AC
// Destructor (scalar deleting): sub_180F36BF4
// Size: 0x88 bytes
//
// Inheritance: C_BaseModule : C_Graph : S_Graph : S_Job
//                           : I_ModuleMessageListener (at +0x78)
//
// Primary vtable layout (WARNING: interfuscator shuffled):
//   [0] scalar deleting destructor
//   [1] GetModuleId() -> returns *(uint16_t*)(this+0xA)    (sub_1806F9E00)
//   [2] _guard_check_icall_nop
//   [3] _guard_check_icall_nop
//   [4] purecall — Init()
//   [5] purecall — PostInit() / Shutdown()
//   [6] _guard_check_icall_nop
//   [7] purecall — GetSubsystemCount() or similar
//   [8] purecall — GetModuleName()
class C_BaseModule : public C_Graph, public I_ModuleMessageListener {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_BaseModule;
    // +0x00: primary vtable (C_BaseModule)
    // +0x08: S_Job::m_flags, +0x0A: S_Job::m_moduleId
    // +0x10: S_Graph::m_graphData
    // +0x18..0x70: S_Graph vectors (4 vectors, graph topology)
    // +0x78: secondary vtable (I_ModuleMessageListener)
    // +0x80:
    virtual ~C_BaseModule() = default;                               // [0]
    virtual uint16_t GetModuleId() const { return m_moduleId; }     // [1]
    virtual void _guard_2() {}                                      // [2] _guard_check_icall_nop
    virtual void _guard_3() {}                                      // [3] _guard_check_icall_nop
    virtual bool Init() = 0;                                        // [4]
    virtual void PostInit() = 0;                                    // [5]
    virtual void _guard_6() {}                                      // [6] _guard_check_icall_nop
    virtual int GetSubsystemCount() const = 0;                      // [7]
    virtual const char* GetModuleName() const = 0;                  // [8]

    uint32_t m_state;           // +0x80  module state (init 0)
    uint32_t _pad84;            // +0x84
};
static_assert(sizeof(C_BaseModule) == 0x88, "C_BaseModule must be 0x88 bytes");

}  // namespace wh::framework
