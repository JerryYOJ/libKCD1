#pragma once
#include <cstdint>
#include "S_CombatQueryData.h"

namespace wh::combatmodule {

class C_CombatActor;

// ---------------------------------------------------------------------------
// S_CombatActionAttackQueryData -- the 0xC0-byte query that drives attack-candidate
// enumeration. Built from the attacker's (and opponent's) live combat state, handed
// to S_AttackCandidateResultHolder::Enumerate. [V] workflow wf_05aec32f + RTTI walk.
//
// Hierarchy (RTTI-confirmed): derives from the CRTP base
// S_CombatQueryData<S_CombatActionAttackQueryData> at offset 0 (which owns the
// vtable: [0] GetTypeNameHash, [1] GetCacheKey). The vptr lives at +0x00 via that
// base; the query's own fields start at +0x08.
//
// RAII: the C++ ctor runs the engine ctor (sub_1804600BC); the dtor runs the manual
// teardown (sub_1802185C4 + MemFree of the +0xA8 list node). Usage:
//   S_CombatActionAttackQueryData q;            // ctor builds the empty query
//   factory->BuildAttackQuery(inputClassId, &q);
//   holder.Enumerate(&q);                       // q destroyed at scope end
// ---------------------------------------------------------------------------
struct S_CombatActionAttackQueryData : S_CombatQueryData<S_CombatActionAttackQueryData> {
    // +0x00 vtable (from the S_CombatQueryData base)
    C_CombatActor* m_pAttackerActor; // +0x08  = factory->m_pOwnerActor
    C_CombatActor* m_pOpponentActor; // +0x10  = attacker state+0xCA8 (0 if none)
    int32_t  m_attackerZoneKeyA;   // +0x18  <- attacker state+0xC80 (may be refined by sub_180F49060)
    int32_t  m_attackerZoneKeyB;   // +0x1C  <- attacker state+0xC84
    int32_t  _reserved20;          // +0x20
    int32_t  _reserved24;          // +0x24
    int32_t  m_opponentZoneKeyA;   // +0x28  <- opponent state+0xC80
    int32_t  m_opponentZoneKeyB;   // +0x2C  <- opponent state+0xC84
    int32_t  _reserved30;          // +0x30
    int32_t  _reserved34;          // +0x34
    int32_t  m_attackerStateBE0;   // +0x38  <- attacker state+0xBE0 (combat state category)
    int32_t  m_attackerStateBE8;   // +0x3C  <- attacker state+0xBE8 (attack zone)
    int32_t  m_opponentStateBE8;   // +0x40  <- opponent state+0xBE8
    int32_t  m_attackerStateBEC;   // +0x44  <- attacker state+0xBEC (action type)
    int32_t  m_defaultAttackId;    // +0x48  set to dword_18359B410 in the no-combo branch
    int32_t  _field4C;             // +0x4C  not written by ctor (gap)
    int32_t  _reserved50;          // +0x50
    int32_t  _reserved54;          // +0x54
    uint32_t m_input;              // +0x58  THE input class id (E_CombatInputClass) set by BuildAttackQuery
    int32_t  m_attackerSubId;      // +0x5C
    int32_t  m_opponentSubId;      // +0x60
    int32_t  _reserved64;          // +0x64
    int32_t  _reserved68;          // +0x68
    int32_t  _reserved6C;          // +0x6C
    void*    _field70;             // +0x70  ctor=0
    void*    _field78;             // +0x78  ctor=0
    void*    _field80;             // +0x80  ctor=0
    void*    _field88;             // +0x88  ctor=0
    void*    _field90;             // +0x90  ctor=0
    int32_t  _field98;             // +0x98  ctor=-1
    int32_t  m_attackerWeaponId;   // +0x9C  attacker weapon-class id (sub_18021B1FC)
    int32_t  m_opponentWeaponId;   // +0xA0  opponent weapon-class id
    int32_t  _fieldA4;             // +0xA4  not written by ctor (gap)
    // +0xA8: a std::set/std::map (MSVC red-black tree). Modeled as the raw _Tree fields:
    // the ctor (sub_1804600BC -> _Buyhead sub_180208FD8) allocates the 0x30 sentinel node
    // (self-linked, _Color/_Isnil = 0x0101; element = 0x10), the dtor clears it (_Tree::clear
    // sub_1802185C4) then frees the sentinel. EMPTY on the attack-query path (no inserts here;
    // other query consumers populate it). We never touch it, so it stays raw, not a literal
    // std::set<> member (key type unknown without an insert site).
    void*    m_pTreeHead;          // +0xA8  std::_Tree _Myhead (RB-tree sentinel ptr)
    uint64_t m_treeSize;           // +0xB0  std::_Tree _Mysize
    uint8_t  m_attackerFlagB8;     // +0xB8  sub_18021C7A4(attacker)
    uint8_t  m_opponentFlagB9;     // +0xB9  sub_18021C7A4(opponent)
    uint8_t  m_flagBA;             // +0xBA  (attacker state+0xD00 & 0x400) != 0
    uint8_t  _padBB[5];            // +0xBB

    // vtable overrides (engine fns; the engine ctor installs the real vptr, so live
    // dispatch hits these directly -- the bodies trampoline to the same engine code).
    void* GetTypeNameHash(void* outStringHash) override;  // vtable[0] sub_180F49280
    uint64_t GetCacheKey() override;                      // vtable[1] sub_180219730

    S_CombatActionAttackQueryData();   // engine ctor sub_1804600BC
    ~S_CombatActionAttackQueryData();  // manual teardown (sub_1802185C4 + MemFree)
};
static_assert(sizeof(S_CombatActionAttackQueryData) == 0xC0, "S_CombatActionAttackQueryData must be 0xC0");
// (field offsets verified by layout-dump: polymorphic type, so no offsetof asserts.)

}  // namespace wh::combatmodule
