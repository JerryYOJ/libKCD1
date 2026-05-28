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
// Leaf node — [6] GetNodeCategory and [9] GetChildCount are purecall.
// Child lifecycle callbacks [47]-[52] are guard_nop (no children to manage).
// Child control [53]-[56] are guard_nop.
// ---------------------------------------------------------------------------
class C_Node : public I_Node, public I_DebugNode {
public:
    // ---- I_Node overrides ----
    void Terminate() override {}                                    // [2]  nop
    bool IsAction() const override { return false; }                // [10]
    bool IsValid() const override { return true; }                  // [29]
    bool IsLeaf() const override { return false; }                  // [31]
    bool unk_44() const override { return false; }                  // [44]

    // [6]  GetNodeCategory — purecall (leaf has no category string)
    // [9]  GetChildCount   — purecall (leaf has no children)

    // Child lifecycle callbacks — nop in leaf (no children)
    void OnChildInitialized() override {}                           // [47]
    void OnFirstUpdate(void*) override {}                           // [48]
    void OnUpdate(void*) override {}                                // [49]
    void OnRunning(void*) override {}                               // [50]
    void OnSuspended(void*) override {}                             // [51]
    void OnCompleted() override {}                                  // [52]

    // Child control — nop in leaf
    void TerminateChildren() override {}                            // [53]
    void unk_55() override {}                                       // [55]
    void unk_56() override {}                                       // [56]

    // Suspend/Abort callbacks — nop in leaf
    void OnResume() override {}                                     // [58]
    void OnAbort() override {}                                      // [59]

    // ---- Data members ----
    void*       m_pNodeData;    // +0x10  set by SetNodeData [34]
    uint32_t    m_nodeId;       // +0x18  set by SetNodeId [8], read by GetNodeId [7]
    uint32_t    _pad1C;         // +0x1C
    void*       m_pCreator;     // +0x20  INodeCreator*, lazy-loaded by GetNodeAttributes [35]
};
static_assert(sizeof(C_Node) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
