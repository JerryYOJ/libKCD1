#include "framework/C_SaveGameManager.h"
#include "framework/C_PlayerProfileWHManager.h"
#include "Offsets/Offsets.h"

// Thin forwarders into the retail save chain. Each calls the original WHGame.dll
// routine in place (no reimplementation) so behaviour exactly matches the game.

void wh::framework::C_PlayerProfileWHManager::ExecuteSave()
{
    using Fn = void(__fastcall*)(C_PlayerProfileWHManager*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kExecuteSaveOffset);
    fn(this);
}

bool wh::framework::C_SaveGameManager::SaveGameToSlot(E_SaveType type, int32_t param, const char* saveName)
{
    using Fn = char(__fastcall*)(C_SaveGameManager*, uint32_t, int32_t, const char*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kSaveGameToSlotOffset);
    return fn(this, static_cast<uint32_t>(type), param, saveName) != 0;
}

bool wh::framework::C_SaveGameManager::WriteSaveFile(void* saveBuffer, void* saveDescriptor, uint32_t replaceSlotIndex)
{
    using Fn = bool(__fastcall*)(C_SaveGameManager*, void*, void*, uint32_t);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kWriteSaveFileOffset);
    return fn(this, saveBuffer, saveDescriptor, replaceSlotIndex);
}
