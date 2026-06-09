#pragma once
#include <cstdint>
#include "../../CryEngine/CryCommon/CryExtension/CryGUID.h"
#include "../../framework/C_Signal.h"

// -----------------------------------------------
// C_BuffManager — singleton managing all active buff instances
// -----------------------------------------------
// RTTI: .?AVC_BuffManager@rpgmodule@wh@@
// vtable: 0x1822EECF8 (12 vfunc slots)
// Constructor: sub_181159BF0
// Singleton: qword_183500F10  (lazy-init, guarded by mutex at unk_1836E3C40)
// Size: 0x80
//
// Owns the global registry of all active buff instances.
// NOT a member of C_Soul — this is a standalone singleton.
// C_Soul stores the applied modifier lists; C_BuffManager tracks buff instance lifetimes.
//
// Factory mechanism (separate singleton at qword_1835F0228):
//   Registration entries are stored in a FNV-1a hash map.
//   Each entry maps "wh.rpgmodule.buff.<Name>" to a creator function.
//   The XML "Cpp:" prefix is stripped at load time; the remaining name is used
//   with the "wh.rpgmodule.buff." prefix for factory lookup.
//
//   Factory accessor:     sub_180449C0C
//   Factory register:     sub_180712B68
//   FNV-1a hash:          sub_180449CD4 (basis=0xCBF29CE484222325, prime=0x100000001B3)
//   Core buff creation:   sub_1804490A8
//   AttachBuff:            sub_180449188 (stores soul, calls ProcessModifiers/UpdateSoul)

namespace wh::rpgmodule {

class C_BuffInstanceBase;
class C_Soul;

class C_BuffManager {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_BuffManager;
    static C_BuffManager* GetInstance();

    virtual C_BuffInstanceBase* AddBuff(C_Soul* pSoul, const CryGUID* pBuffGuid, void* pParams);    // [0] 0x18056998C
    virtual C_BuffInstanceBase* AddBuffByWUID(uint64_t wuid);                                        // [1] 0x180569938
    virtual void RemoveBuff(C_BuffInstanceBase* pBuff);                                              // [2] 0x1806C4D64
    virtual void RemoveBuffWithSignal(C_BuffInstanceBase* pBuff, void* pContext);                     // [3] 0x1806F08F8
    virtual C_BuffInstanceBase* FindBuff(const CryGUID* pBuffGuid);                                   // [4] 0x1806D6790
    virtual C_BuffInstanceBase* FindBuffOnSoul(C_Soul* pSoul, const CryGUID* pBuffGuid);              // [5] 0x18115EE58
    virtual C_BuffInstanceBase* LookupByKey(void* pKey);                                              // [6] 0x180210130
    virtual void* GetBuffDefinition(const CryGUID* pGuid1, const CryGUID* pGuid2);                    // [7] 0x1804E008C
    virtual void* GetBuffDefByKey(void* pKey);                                                        // [8] 0x1805B7F2C
    virtual void ConnectOnBuffAdded(void* pCallback);                                                 // [9] 0x180F50D64
    virtual void ConnectOnBuffRemoved(void* pCallback);                                               // [10] 0x180F51CB4
    virtual ~C_BuffManager();                                                                         // [11] 0x181159F80

    // ====== Data members (verified from constructor sub_181159BF0) ======

    // Signal fired when buffs are added/removed.
    // Carries references to old and new buff instances.
    wh::shared::C_Signal<C_BuffInstanceBase&, C_BuffInstanceBase&>  m_onBuffChanged;    // +0x08  (0x30 bytes)

    uint8_t             m_flags;                // +0x38  init 0
    uint8_t             _pad39[3];              // +0x39
    float               m_effectScale;          // +0x3C  init 1.0f (global buff effect multiplier)

    // Active buff instance registry (std::list<C_BuffInstanceBase*>).
    // Sentinel node created by sub_18024B0E8. Instances inserted by sub_180617DC4.
    void*               m_pInstanceListHead;    // +0x40  std::list sentinel node
    int64_t             m_nInstanceCount;       // +0x48  number of active buff instances

    // Hash map for fast buff lookup by key.
    // Initialized by sub_18071265C with 8 buckets.
    void*               m_pBuckets;             // +0x50  bucket array begin
    void*               m_pBucketsEnd;          // +0x58  bucket array end
    void*               m_pBucketsCap;          // +0x60  bucket array capacity
    uint64_t            m_nBucketMask;          // +0x68  bucket_count - 1 (init 7)
    uint64_t            m_nBucketCount;         // +0x70  number of buckets (init 8)
    uint64_t            m_unk78;                // +0x78  init 0
};
static_assert(sizeof(C_BuffManager) == 0x80);

}  // namespace wh::rpgmodule
