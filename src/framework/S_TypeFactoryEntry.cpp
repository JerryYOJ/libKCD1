#include "framework/S_TypeFactoryEntry.h"
#include "Offsets/Offsets.h"

void wh::shared::S_TypeFactoryEntry::Init(
    const char* pKey, S_TypeFactoryEntry** pParents, TypeCastFn fnCast, TypeCreatorFn fnCreator)
{
    using Fn = void(__fastcall*)(S_TypeFactoryEntry*, const char*, S_TypeFactoryEntry**, TypeCastFn, TypeCreatorFn);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kTypeFactoryEntryInitOffset);
    fn(this, pKey, pParents, fnCast, fnCreator);
}
