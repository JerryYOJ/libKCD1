#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include "I_SmartAreaManager.h"                       // +0x00 primary base
#include "C_IntelligentObjectManager.h"               // +0x10 base I_DebugDraw (defined there; shared AI iface)
#include "../framework/I_WUIDMappingProvider.h"       // +0x18 base
#include "../framework/WUID.h"                         // WUID key/value type
#include "../framework/C_Signal.h"                     // wh::shared::C_Signal (+0x480 area-changed signal, 0x30)
#include "S_AIUpdateScheduler.h"                       // +0x190 update scheduler (0x2D0)
#include "../Offsets/vtables/IEntitySystemSink.h"     // +0x08 base (Offsets::IEntitySystemSink)
// std::hash<wh::framework::WUID> comes from PCH.h (used by the WUID-keyed maps below).

// ===========================================================================
// wh::xgenaimodule::C_SmartAreaManager  (size 0x4B0)  RTTI .?AVC_SmartAreaManager@xgenaimodule@wh@@
// ===========================================================================
// The WUID(type 7 = SmartArea) registry + per-frame area updater. Singleton = *qword_183785A20
// (getter sub_180705E80; created by sub_1815E993C via operator new(0x4B0) + ctor sub_1815E4414;
// dtor sub_1815E4F98, destroyed on AI shutdown sub_181607EDC). Registers itself as an entity-system
// sink (ctor: gEnv.pEntitySystem->AddSink(this+8, 0x14)) and registers its I_WUIDMappingProvider
// (this+0x18) with the GameContext WUID system.
//
// 4 bases (RTTI base array, COL-offset verified): I_SmartAreaManager @+0x00, IEntitySystemSink @+0x08,
// I_DebugDraw @+0x10, I_WUIDMappingProvider @+0x18.
//
// The spatial POINT QUERY (I_SmartAreaManager slot[5]) does NOT use a member grid -- it delegates to
// the PROCESS-GLOBAL wh::shared::C_RegularGrid (holder qword_1835012A8, getter sub_180498DE8). The
// manager only owns the WUID->area registry (+0xA0) and the entity<->area indices.
//
// Layout VERIFIED from ctor sub_1815E4414, member-dtor sub_1815E4F98 (per-member destructor calls),
// ResolveWuid sub_180498A38, GetWuidForEntity sub_1815EA628, the entity-sink OnRemove sub_1806AF92C
// (which links entity->WUID->area->record), and the template builder sub_1815D9270.
// ===========================================================================

namespace wh::xgenaimodule {

class C_SmartArea;
struct S_SmartAreaTemplate;   // 0xA8 area template (built from the AI data tables); defined elsewhere

class C_SmartAreaManager
    : public I_SmartAreaManager                   // +0x00
    , public Offsets::IEntitySystemSink           // +0x08  (AddSink'd in ctor, event flags 0x14)
    , public I_DebugDraw                          // +0x10
    , public wh::framework::I_WUIDMappingProvider // +0x18
{
public:
    // ---- manager-private layout helpers (nested: implementation detail of this class) ----

    // +0x140 (0x50)  the AI data-table handles the manager reads SmartArea config from -- registered
    // then fetched in ctor sub_1815CC32C from the GameContext table system (vtbl+0x48 / vtbl+0x60).
    struct S_TableHandles {
        void* m_hSmartArea;        // +0x00  "sa_smart_area"
        void* m_hBehaviourTag;     // +0x08  "sa_behaviour_tag"
        void* m_hSmartArea2Tag;    // +0x10  "sa_smart_area2sa_behaviour_tag"
        void* m_hTag2Mailbox;      // +0x18  "sa_behaviour_tag2mailbox"
        void* m_hTagParent;        // +0x20  "sa_behaviour_tag_parent"
        void* m_hBehaviourAction;  // +0x28  "sa_behaviour_action"
        void* m_hBrain;            // +0x30  "brain"
        std::vector<void*> m_all;  // +0x38  the 7 handles above, in push order
    };
    static_assert(sizeof(S_TableHandles) == 0x50);

    // value type of m_areaRecords (+0x20): a 0x18 per-area record keyed by the area WUID.
    struct S_AreaRecord {
        uint64_t _unk00;        // +0x00  [UNVERIFIED]
        uint64_t _unk08;        // +0x08  [UNVERIFIED]
        void*    m_entityLink;  // +0x10  cleared when the bound entity is removed (sink OnRemove sub_1806AF92C)
    };
    static_assert(sizeof(S_AreaRecord) == 0x18);

    // +0x460 (0x20)  the manager's OWN owned subscription/connection records for the area-changed signal:
    // a std::vector of heap objects (each a rich record -- nested CryStringT vectors + a name; element-dtor
    // sub_1815E5C80 -> sub_1815E54F0) + one trailing POD qword. This is NOT the signal's internals: the
    // signal's reentrancy is its own two int slots inside its 0x30 (verified -- emit sub_18067C924 uses
    // +0x4A8/+0x4AC; the C_Signal dtor sub_1815E579C frees only its delegate vector, never this list).
    // LAYOUT-DUMP CERTIFIED as a separate member before the C_Signal: making the store a base would force
    // the vtable to +0x460 (MSVC promotes polymorphic bases to offset 0 -- empirically tested); the binary
    // has the vtable at +0x480, which only composition (store member, then C_Signal member) reproduces.
    struct S_SignalConnRecords {
        std::vector<void*> m_records;   // +0x00 (0x18)  owned connection-record objects (ptr elems; dtor sub_1815E5C80)
        uint64_t           _unk18;      // +0x18  POD; zeroed at ctor, never freed [UNVERIFIED]
    };
    static_assert(sizeof(S_SignalConnRecords) == 0x20);

    // ---- fields ----
    std::unordered_map<wh::framework::WUID, S_AreaRecord> m_areaRecords;   // +0x20  area WUID -> per-area record (node 0x30)
    std::unordered_map<uint64_t, void*>                   m_index60;       // +0x60  secondary index; never observed read/written
                                                                          //        in the examined methods [semantics UNVERIFIED]
    std::unordered_map<wh::framework::WUID, C_SmartArea*> m_areasByWuid;   // +0xA0  WUID -> area [VERIFIED: ResolveWuid sub_180498A38]
    std::unordered_map<uint64_t, wh::framework::WUID>     m_entityToWuid;  // +0xE0  entity key -> area WUID
                                                                          //        [VERIFIED: GetWuidForEntity sub_1815EA628]

    uint8_t            m_flag120;             // +0x120  zeroed in ctor [purpose UNVERIFIED]
    uint8_t            _pad121[7];            // +0x121
    std::vector<S_SmartAreaTemplate*> m_templates;  // +0x128  area templates (OWNED; built from m_tableHandles by
                                                    //         sub_1815D9270, deleted on dtor); looked up by sub_1815E8CEC
    S_TableHandles     m_tableHandles;       // +0x140  (0x50)
    S_AIUpdateScheduler m_updateScheduler;   // +0x190  (0x2D0)  the "SmartAreaUpdate" update scheduler
    S_SignalConnRecords m_areaChangedConns;  // +0x460  (0x20)  manager-owned subscription records (see above)
    // +0x480 (0x30)  area-changed signal: emits (C_SmartArea&, tag name, bool) on a tag-set change.
    // A plain, self-contained wh::shared::C_Signal (same 0x30 as every other consumer -- reused, not
    // modified): delegate list @+0x490, reentrancy int slots @+0x4A8/+0x4AC. Add a listener via slot[11]
    // (sub_1804272A4); broadcast via slot[13] (sub_18067C924), which C_SmartArea calls on tag change.
    wh::shared::C_Signal<C_SmartArea&, CryStringT<char> const&, bool> m_areaChangedSignal;

    // *qword_183785A20 (getter sub_180705E80). Null before the AI module is up. Impl in C_SmartAreaManager.cpp.
    static C_SmartAreaManager* GetInstance();
};
static_assert(sizeof(C_SmartAreaManager) == 0x4B0, "C_SmartAreaManager (operator new 0x4B0; ctor sub_1815E4414)");

}  // namespace wh::xgenaimodule
