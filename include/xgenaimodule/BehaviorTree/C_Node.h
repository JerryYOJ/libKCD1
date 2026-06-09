#pragma once

#include <cstdint>
#include "I_Node.h"
#include "I_DebugNode.h"

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// C_Node — base class for leaf BT nodes (no children).
//
// RTTI: .?AVC_Node@BehaviorTree@xgenaimodule@wh@@
// Size: 0x28 bytes
//
// C_Node is the concrete leaf base: in the binary it supplies the shared I_Node
// implementations (status FSM, runtime-data acquire/release, node-data/creator
// accessors — all documented per-slot in I_Node.h). A leaf has no children, so
// [6] GetNodeCategory / [9] GetChildCount stay pure (concrete nodes provide
// them), [10] IsComposite is false, and the child-management hooks ([49]
// StartChild, [53] ResetChildren, …) are nops. We model only the VERIFIED data
// layout + the verified IsComposite override here, rather than re-declaring every
// shared slot with a guessed name (their per-slot identities are catalogued in
// I_Node.h with confidence tags).
// ---------------------------------------------------------------------------
class C_Node : public I_Node, public I_DebugNode {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Node;
    bool IsComposite() const override { return false; }   // [10] VERIFIED base = false (leaf)

    // ---- Data members (VERIFIED from node ctors) ----
    void*       m_pNodeData;    // +0x10  [32]/[33] GetNodeData, [34] SetNodeData
    uint32_t    m_nodeId;       // +0x18  [7] GetNodeId, [8] SetNodeId
    uint32_t    _pad1C;         // +0x1C
    void*       m_pCreator;     // +0x20  lazily-cached creator/owning-context ([35] GetCreator)
};
static_assert(sizeof(C_Node) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
