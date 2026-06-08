#pragma once

#include <cstdint>
#include "C_MessageCapableObject.h"
#include "../framework/C_HashMap.h"
#include "../framework/WUID.h"
#include "../Offsets/vtables/IScriptTable.h"   // Offsets::IScriptTable — m_scriptTable is a SmartScriptTable handle to it

// ===========================================================================
// wh::xgenaimodule::C_IntelligentObject : C_MessageCapableObject
// ===========================================================================
// Ctor:    sub_180278388(this, ...)
// vtable:  0x1821A4528 (24 slots) — overrides 0/1/2/16, adds 17..23.
// Registers into qword_183799950 (std::unordered_map<WUID, C_IntelligentObject*>;
// the registry the Information *multi*-holder query paths resolve through).
//
// THIS IS THE INFORMATION HOLDER: C_InformationManager (qword_183501790) keys
// m_holders by a C_IntelligentObject* (its GetCapabilityFlags() returns 0x63,
// so &0x40 "can hold information" is set). For humans the concrete class is
// C_NPC; world objects use C_SmartEntity.
//
// Subscribes to brain mailbox "bWH_ReceiveEmittedInformation" (flag @+0x128).
// size 0x178.
// ===========================================================================

namespace wh::xgenaimodule {

class C_IntelligentObject : public C_MessageCapableObject {
public:
    // --- primary-vtable additions (slots 17..23); slot 16 is overridden here ---
    int64_t  vf16_MessageHook() override;   // [16] +0x80  sub_1803A95C8: state update via m_pBrain
    virtual void* GetScriptTable();    // [17] +0x88  if m_pBrain -> brain->vtbl[+0x30](); else build @ m_scriptTable
    virtual void  SetBrain(void* brain); // [18] +0x90  release old (brain->vtbl[+0x10]), store @+0x118, back-link (brain->vtbl[+0x08](this))
    virtual bool  HasBrain();           // [19] +0x98  -> (m_pBrain != nullptr)
    virtual bool  vf20_BrainState();    // [20] +0xA0  -> m_pBrain && m_pBrain->vtbl[+0xB8]() == 0  [name UNVERIFIED]
    virtual void  vf21_Hook();          // [21] +0xA8  empty hook
    virtual int64_t vf22();             // [22] +0xB0  uses m_pBrain + slot 23  [name UNVERIFIED]
    virtual void  SetFlag170(char v);   // [23] +0xB8  m_flag170 = v

    // --- fields (ctor sub_180278388) ---
    // m_pBrain: the AI brain/controller (the b_* brain-variable store where crime data lives:
    // b_informationData / b_informations / b_crimeSystemRole). NOT the soul. Set via SetBrain (slot 18).
    // Used through its vtable: +0x08 attach(this), +0x10 detach/release, +0x18 bool (mode select),
    // +0x30 GetScriptTable, +0x50 GetVarContainer()->+0x10(nameHash) = variable-by-name, +0xB8 bool.
    // CONCRETE CLASS UNVERIFIED (SetBrain's caller / brain ctor not yet traced) — kept void* until RE'd.
    void*          m_pBrain;       // +0x118  (set via SetBrain / vtable slot 18)
    Offsets::IScriptTable* m_scriptTable;  // +0x120  SmartScriptTable: refcounted Offsets::IScriptTable* handle. VERIFIED:
                                   //         assign sub_1803B97E4 = AddRef new (IScriptTable[3] vtbl+0x18) /
                                   //         Release old ([4] vtbl+0x20). Holds the entity's (or brain's, slot 17) Lua table.
    bool    m_recvInfoFlag;    // +0x128  init 1 ("bWH_ReceiveEmittedInformation" subscription)
    char    _pad129[7];        // +0x129
    wh::shared::C_HashMap<wh::framework::WUID, void*> m_knowledgeMap;  // +0x130 (0x40) brain-variable / knowledge map [key/value UNVERIFIED]
    bool    m_flag170;         // +0x170  init 0
    bool    m_flag171;         // +0x171  init 0
    char    _pad172[6];        // +0x172
};
static_assert(sizeof(C_IntelligentObject) == 0x178);

// Concrete subclasses (not yet fully RE'd):
//   C_NPC        : C_IntelligentObject  (ctor sub_1805609A8; humans; >0x1978 bytes;
//                  adds C_Signal bases @+0x178/+0x1A8, movement, status)
//   C_SmartEntity: C_IntelligentObject  (ctor sub_181676814; world smart objects)
class C_NPC;
class C_SmartEntity;

}  // namespace wh::xgenaimodule
