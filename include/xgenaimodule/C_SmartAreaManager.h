#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include "I_SmartAreaManager.h"                       // +0x00 primary base
#include "C_IntelligentObjectManager.h"               // +0x10 base I_DebugDraw (defined there; shared AI iface)
#include "../framework/I_WUIDMappingProvider.h"       // +0x18 base
#include "../Offsets/vtables/IEntitySystemSink.h"     // +0x08 base (Offsets::IEntitySystemSink)

// ===========================================================================
// wh::xgenaimodule::C_SmartAreaManager  (size 0x4B0)  RTTI .?AVC_SmartAreaManager@xgenaimodule@wh@@
// ===========================================================================
// The WUID(type 7 = SmartArea) registry + per-frame area updater. Singleton = *qword_183785A20
// (getter sub_180705E80; created by sub_1815E993C via operator new(0x4B0) + ctor sub_1815E4414;
// destroyed on AI shutdown sub_181607EDC). Registered as an entity-system sink in its ctor.
//
// NOTE: the spatial POINT QUERY (I_SmartAreaManager slot[5]) does NOT use a member grid -- it
// delegates to the PROCESS-GLOBAL wh::shared::C_RegularGrid (holder qword_1835012A8, getter
// sub_180498DE8). The manager only owns the WUID->area registry (+0xA0). 4 bases (RTTI base array):
//   I_SmartAreaManager @+0x00, IEntitySystemSink @+0x08, I_DebugDraw @+0x10, I_WUIDMappingProvider @+0x18.
// Layout VERIFIED from ctor sub_1815E4414 + cross-verified; only +0xA0 is disasm-confirmed by usage,
// the other maps' element types are UNVERIFIED (placeholdered as <uint64,void*>; all 0x40 MSVC _Hash).
namespace wh::xgenaimodule {

class C_SmartArea;

class C_SmartAreaManager
    : public I_SmartAreaManager                  // +0x00
    , public Offsets::IEntitySystemSink          // +0x08  (AddSink'd in ctor, flags 0x14)
    , public I_DebugDraw                         // +0x10
    , public wh::framework::I_WUIDMappingProvider // +0x18
{
public:
    // +0x20  std::unordered_map (0x40 _Hash). Secondary index; key/value UNVERIFIED.
    std::unordered_map<uint64_t, void*>        m_index20;
    // +0x60  std::unordered_map (0x40). UNVERIFIED (likely observer/registration index).
    std::unordered_map<uint64_t, void*>        m_index60;
    // +0xA0  WUID -> C_SmartArea*  [VERIFIED by ResolveWuid disasm]. node {next,prev, key u64 @+0x10, value @+0x18}.
    std::unordered_map<uint64_t, C_SmartArea*> m_areasByWuid;
    // +0xE0  std::unordered_map (0x40). UNVERIFIED.
    std::unordered_map<uint64_t, void*>        m_indexE0;

    uint8_t   m_flag120;            // +0x120  zeroed in ctor [purpose UNVERIFIED]
    uint8_t   _pad121[7];           // +0x121
    std::vector<void*> m_vec128;    // +0x128  {begin,end,cap}; linked to m_sub140 via sub_1815D9270

    // +0x140 (0x50)  sub-object (ctor sub_1815CC32C; bound to m_vec128) -- type UNVERIFIED (opaque).
    uint8_t   m_sub140[0x50];
    // +0x190 (0x2D0) per-area UPDATE scheduler (ctor sub_1815E4668; driven by Update/slot0 via
    //                sub_18039D024). NOT the spatial grid. Type UNVERIFIED (opaque).
    uint8_t   m_updateScheduler[0x2D0];
    // +0x460 (0x48)  C_Signal<C_SmartArea&, CryStringT<char> const&, bool> (connection storage
    //                +0x460..+0x478, signal vtable @+0x480, internals +0x488..+0x4A8). Opaque.
    uint8_t   m_areaSignal[0x48];

    int32_t   m_unk4A8;             // +0x4A8  ctor = -1 (reserved id?) [UNVERIFIED]
    int32_t   m_unk4AC;             // +0x4AC  ctor = -1 (reserved id?) [UNVERIFIED]

    // *qword_183785A20 (getter sub_180705E80). Null before the AI module is up. Impl in C_SmartAreaManager.cpp.
    static C_SmartAreaManager* GetInstance();
};
static_assert(sizeof(C_SmartAreaManager) == 0x4B0, "C_SmartAreaManager (operator new 0x4B0; ctor sub_1815E4414)");

}  // namespace wh::xgenaimodule
