#pragma once
#include <cstdint>

// -----------------------------------------------
// C_BuffInstanceBase — abstract base for all buff instances
// -----------------------------------------------
// RTTI: .?AVC_BuffInstanceBase@rpgmodule@wh@@
// vtable: 0x1821ce1d0  (16 vfunc slots)
// Constructor: sub_180617BBC
// Size: 0x88
//
// The root of the buff instance hierarchy. Defines the interface that all buffs must implement.
// Concrete buff types inherit through C_BuffInstance<T> -> C_SoulBuffInstance -> derived.
//
// Creation flow:
//   1. Factory allocates + constructs via registered creator function
//   2. Constructor sets vtable, zeroes fields, sets up intrusive list node
//   3. sub_180617DC4 stores buff ID at +0x08, registers with C_BuffManager singleton
//   4. Init() is called with buff data + init params
//   5. AttachBuff (sub_180449188) stores owner (soul) at +0x88, calls ProcessModifiers/UpdateSoul
//
// Dynamic type checking uses string comparison against "wh.rpgmodule.buff.<Type>" names,
// NOT C++ RTTI. See CastTo / GetTypeName.

namespace wh::rpgmodule {

class C_Soul;
class I_BuffInitParams;
struct S_ModifierNode;

class C_BuffInstanceBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_BuffInstanceBase;
    // --- Pure virtuals (must be overridden by concrete buffs) ---

    // Initialize the buff instance with definition data and optional params.
    // Stores pBuffData at m_pBuffData (+0x10). Parses modifier definitions.
    // Returns true on success.
    // UNVERIFIED: exact arg types — pBuffData may be C_BuffData* (FK resolver layer);
    //   pInitParams is I_BuffInitParams* (default: C_BuffInitParamsDefault)
    virtual bool Init(void* pBuffData, I_BuffInitParams* pInitParams) = 0;            // [0] 0x180448828

    // Tick update. Return true to stay active, false to expire the buff.
    // C_ConstantSoulBuffInstance returns true always.
    // C_TimedSoulBuffInstance accumulates deltaTime and returns false when elapsed >= duration.
    virtual bool Update() = 0;                                                         // [1] _purecall

    // Cleanup on removal. Deactivates all modifier nodes and unlinks from soul.
    virtual void Terminate() = 0;                                                      // [2] 0x180448EC0

    // Move staged modifier nodes into the soul's sorted active modifier lists.
    // Nodes are sorted ascending by E_ModifierOp for correct application order.
    virtual bool CommitModifiers() = 0;                                                // [3] 0x1804496C8

    // --- Virtual methods with default implementations ---

    // Deep-copy modifier state from another buff instance (for save/load).
    virtual void CopyFrom(C_BuffInstanceBase* pSrc, void* pArchive) {}                 // [4] nop

    virtual void unk_05() {}                                                           // [5] nop

    // Returns the buff's current strength as a float.
    // Wraps IsActive(): returns 1.0f if active, 0.0f if not.
    virtual float GetStatus(void* pOutResult, int a3);                                 // [6] 0x180631E74

    // Serialization. Writes/reads buff state with chunk hash 0x94E7.
    virtual void Save(void* pArchive);                                                 // [7] 0x18115EEDC
    virtual void Load(void* pArchive);                                                 // [8] 0x18115DA10

    // Add a new modifier from script/table data (e.g., from BasicBuff.lua's AddNewModifier).
    virtual void AddNewModifier(void* pModifierDef) = 0;                               // [9] _purecall

    virtual ~C_BuffInstanceBase();                                                     // [10] 0x181159F4C

    // Notification when a buff tag modifier changes. C_SoulBuffInstance fires
    // "rpgModule:buffTagChanged" signal through this.
    virtual void NotifyTagChanged(uint32_t nTagId, bool bAdded) {}                     // [11] nop

    // Whether this buff is currently active. Base returns true.
    virtual bool IsActive() { return true; }                                           // [12] 0x1806F8140

    // Returns the type name string (e.g., "constant", "timed").
    // Used for dynamic type checking, NOT the same as C++ typeid.
    virtual void* GetTypeName(void* pOutStr);                                          // [13] 0x1806FE9E0

    // String-based dynamic type check. Returns this if typeName matches, nullptr otherwise.
    // Each derived class checks its own type string and chains to parent.
    virtual C_BuffInstanceBase* CastTo(const void* pTypeName);                         // [14] 0x18115E458
    virtual C_BuffInstanceBase* CastToConst(const void* pTypeName);                    // [15] 0x18115E458

    // --- Data members ---

    uint64_t                m_buffKey;          // +0x08  buff identifier key, set by sub_180617DC4
    void*                   m_pBuffData;        // +0x10  buff definition data ptr, set in Init
                                                //        provides buff_class, params, ai_tag, etc.
    uint64_t                m_unk18;            // +0x18
    uint64_t                m_unk20;            // +0x20
    uint64_t                m_unk28;            // +0x28
    uint64_t                m_unk30;            // +0x30
    uint64_t                m_unk38;            // +0x38
    uint64_t                m_unk40;            // +0x40
    uint64_t                m_unk48;            // +0x48

    // Intrusive list node for C_BuffManager tracking
    // Self-referential on construction: m_listFwd = &m_listNode
    uint64_t                m_listNode;         // +0x50
    uint8_t                 m_listFlag;         // +0x58
    uint8_t                 _pad59[7];          // +0x59
    void*                   m_listFwd;          // +0x60  initially points to &m_listNode
    void*                   m_listHead;         // +0x68  initially points to &m_listNode
    uint64_t                m_unk70;            // +0x70
    uint64_t                m_unk78;            // +0x78
    uint64_t                m_unk80;            // +0x80
};
static_assert(sizeof(C_BuffInstanceBase) == 0x88);

}  // namespace wh::rpgmodule
