#pragma once
#include <cstdint>
#include "C_BuffInstanceBase.h"
#include "S_ModifierNode.h"

// -----------------------------------------------
// C_BuffInstance<T> — template adding owner-type-specific virtuals
// -----------------------------------------------
// RTTI: .?AV?$C_BuffInstance@VC_Soul@rpgmodule@wh@@@rpgmodule@wh@@
// vtable: 0x1821ce118  (22 vfunc slots)
// Size: 0x90
//
// Adds 6 new virtual slots for owner-type-specific behavior.
// The only known instantiation is C_BuffInstance<C_Soul>.
//
// -----------------------------------------------
// C_SoulBuffInstance — soul-specific buff instance base
// -----------------------------------------------
// RTTI: .?AVC_SoulBuffInstance@rpgmodule@wh@@
// vtable: 0x1821ce040  (26 vfunc slots)
// Constructor: sub_180617B58
// Size: 0xD0
//
// Implements the full buff lifecycle for soul-attached buffs:
//   - Maintains 7 modifier staging lists (one per stat category)
//   - Handles material effect attachment via flowgraph
//   - Fires "rpgModule:buffTagChanged" signals
//   - Supports Lua script binding (via HasLuaScript/ApplyMaterialEffect)
//
// This is the base class for ALL concrete C++ buff implementations.
// To create a custom buff, inherit from this and override Update() at minimum.

namespace wh::rpgmodule {

class C_Soul;

// -----------------------------------------------
// C_BuffInstance<C_Soul> — template instantiation
// -----------------------------------------------
// We fold C_BuffInstance<C_Soul> into C_SoulBuffInstance's inheritance since
// C_BuffInstance is only instantiated for C_Soul in the binary.

class C_SoulBuffInstance : public C_BuffInstanceBase {
public:
    // ====== Overrides from C_BuffInstanceBase ======

    // Stores pBuffData at m_pBuffData, calls InitModifiers to parse
    // the buff definition's params string into modifier nodes.
    bool Init(void* pBuffData, I_BuffInitParams* pInitParams) override;                // [0] 0x180448828

    // Update remains pure virtual — concrete subclasses must implement.
    // bool Update() override = 0;                                                     // [1] _purecall

    // Calls base Terminate (clears initialized flag), then walks all 7 modifier
    // staging lists deactivating each node via SetModifierActive.
    void Terminate() override;                                                         // [2] 0x180448CC8

    // Moves nodes from staging lists (m_statMods..m_soulLevelMods) into
    // the soul's sorted active lists at C_Soul+0x98..+0xC8.
    // Sorted by E_ModifierOp (ascending) for correct application order.
    bool CommitModifiers() override;                                                   // [3] 0x1804496C8

    // Deep-copies all 7 modifier lists field-by-field from another instance.
    void CopyFrom(C_BuffInstanceBase* pSrc, void* pArchive) override;                  // [4] 0x18115A848

    // Extended serialization — writes base chunk + soul-specific modifier data.
    void Save(void* pArchive) override;                                                // [7] 0x18115F120
    void Load(void* pArchive) override;                                                // [8] 0x18115DCA0

    ~C_SoulBuffInstance() override;                                                    // [10] 0x180617144

    // Fires "rpgModule:buffTagChanged" signal with "tagId(%i),add(%s)" payload.
    void NotifyTagChanged(uint32_t nTagId, bool bAdded) override;                      // [11] 0x180448FB4

    // Returns "wh.rpgmodule.buff.SoulBuffInstance" type string.
    void* GetTypeName(void* pOutStr) override;                                         // [13] 0x1806FEBC0

    // Checks both "SoulBuffInstance" and "BuffInstanceBase" type strings.
    C_BuffInstanceBase* CastTo(const void* pTypeName) override;                        // [14] 0x18115EC04
    C_BuffInstanceBase* CastToConst(const void* pTypeName) override;                   // [15] 0x18115EC04

    // ====== New virtuals from C_BuffInstance<C_Soul> layer ======

    // Re-registers this buff in the soul's active buff list,
    // re-applies all modifiers, checks for Lua script object.
    virtual void UpdateSoul();                                                         // [16] 0x1804491CC

    // Sets up the buff: gets Lua script object, removes self from soul's
    // buff registry, unapplies all modifiers.
    virtual void Activate();                                                           // [17] 0x180448F00

    // Dispatches modifiers to the soul based on buff class:
    //   case 1 → skill/stat modifiers (sub_180A8C4D0)
    //   case 3 → derived stat modifiers (sub_180A8C5F0)
    //   case 4 → perception modifiers (sub_180A8C570)
    virtual void ProcessModifiers();                                                   // [18] 0x18044921C

    virtual void OnMaterialEffectStart() {}                                            // [19] nop
    virtual void OnMaterialEffectEnd() {}                                              // [20] nop

    // Returns buff_ai_tag_id from the buff definition data.
    virtual uint32_t GetBuffClassFromDef();                                            // [21] 0x18044909C

    // ====== New virtuals from C_SoulBuffInstance layer ======

    // Applies flowgraph-based material/visual effect from buffDef->visual_effect.
    // Stores effect handle in m_materialEffectHandle.
    virtual int16_t ApplyMaterialEffect(C_Soul* pSoul);                                // [22] 0x1804A5DEC

    // Removes active material effect if m_materialEffectHandle is nonzero.
    virtual void RemoveMaterialEffect(C_Soul* pSoul);                                  // [23] 0x1806B2FA4

    // Whether this buff has an associated Lua script. Base returns false.
    virtual bool HasLuaScript() { return false; }                                      // [24] 0x180434C90

    virtual void OnModifierRegistered() {}                                             // [25] nop

    // ====== Data members ======

    C_Soul*             m_pSoul;                // +0x88  owner soul, set by AttachBuff (sub_180449188)

    // 7 modifier staging linked lists, one per category.
    // During Init, modifier nodes are parsed from the buff params string
    // and placed here. CommitModifiers moves them to the soul's main lists.
    S_ModifierNode*     m_statMods;             // +0x90  category 0: base stats (E_SoulStat, 10 entries)
    S_ModifierNode*     m_skillMods;            // +0x98  category 1: skills (33 entries)
    S_ModifierNode*     m_derivedStatMods;      // +0xA0  category 2: derived stats (39 entries)
    S_ModifierNode*     m_detailMods;           // +0xA8  category 3: detail/extended (110 entries)
    S_ModifierNode*     m_movementMods;         // +0xB0  category 4: perk/movement (E_MovementType, 6 entries)
    S_ModifierNode*     m_specialMods;          // +0xB8  category 5: special/manual
    S_ModifierNode*     m_soulLevelMods;        // +0xC0  category 6: soul-level (E_SoulLevel, 6 entries)

    uint16_t            m_materialEffectHandle; // +0xC8  flowgraph effect handle from ApplyMaterialEffect
    uint8_t             _padCA[6];              // +0xCA
};
static_assert(sizeof(C_SoulBuffInstance) == 0xD0);

}  // namespace wh::rpgmodule
