#include "xgenaimodule/C_InformationManager.h"
#include "xgenaimodule/C_IntelligentObject.h"
#include "Offsets/Offsets.h"

// C_InformationManager engine-function forwarders. Singleton = *qword_183501790.
// The crime-erase chain: FindInformationId({wuid,label}) -> DestroyInformationById.
// Some engine fns take a SUBOBJECT pointer (m_holders @+0x08 / m_records @+0x88),
// not `this` -- passed explicitly below. See Offsets.h for the RVAs.

namespace wh { namespace xgenaimodule {

C_InformationManager* C_InformationManager::GetInstance()
{
    return *reinterpret_cast<C_InformationManager**>(
        Offsets::GetBase() + Offsets::kInformationManagerOffset);
}

const std::vector<S_InformationRecord*>*
C_InformationManager::GetHolderRecords(C_IntelligentObject* holder) const
{
    // m_holders is a stock std::unordered_map<C_IntelligentObject*, vector<S_InformationRecord*>*>
    // (pointer key -> std::hash<ptr>), so just query it natively -- no engine call. (The engine's
    // own sub_1805127EC is exactly this find; it returns a static empty vector on miss, we return null.)
    // NOTE: this is the holder's OWN records only. A guard that *confronts* about a crime is usually
    // NOT the holder (the witness holds it; the guard learns it via the info-sharing network), so this
    // returns empty for such a guard -- query the holder/witness, the location's guard GROUP, or m_byId.
    auto it = m_holders.find(holder);
    return it != m_holders.end() ? it->second : nullptr;
}

bool C_InformationManager::FindInformationId(const wh::framework::WUID& perceivedEntity,
                                             const CryStringT<char>& label, uint32_t* outId) const
{
    // sub_1815D3FEC(&m_records, &wuid, &label, &outId) -> bool found.
    using Fn = char (__fastcall*)(const void*, const wh::framework::WUID*,
                                  const CryStringT<char>*, uint32_t*);
    return reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kInfoFindInformationIdOffset)(
        &m_records, &perceivedEntity, &label, outId) != 0;
}

void C_InformationManager::DestroyInformationById(uint32_t informationId)
{
    // sub_1815DB7C0(this, id): remove from every holder + global finalize.
    using Fn = void (__fastcall*)(C_InformationManager*, uint32_t);
    reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kInfoDestroyByIdOffset)(this, informationId);
}

bool C_InformationManager::RemoveInformationFromHolder(uint32_t informationId, C_IntelligentObject* holder,
                                                       bool createResolution, bool finalizeIfLast)
{
    // sub_1815DB81C(this, id, holder, createResolution, finalizeIfLast) -> true iff it finalized.
    using Fn = char (__fastcall*)(C_InformationManager*, uint32_t, C_IntelligentObject*, char, int);
    return reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kInfoRemoveFromHolderOffset)(
        this, informationId, holder, createResolution, finalizeIfLast) != 0;
}

void C_InformationManager::RemoveHolder(C_IntelligentObject* holder)
{
    // sub_180513938(this, holder): wipe ALL of one holder's records.
    using Fn = void (__fastcall*)(C_InformationManager*, C_IntelligentObject*);
    reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kInfoRemoveHolderOffset)(this, holder);
}

}} // namespace wh::xgenaimodule
