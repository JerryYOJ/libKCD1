#include <Windows.h>
#include <cstddef>
#include "Offsets/Offsets.h"

void CryCreateCriticalSectionInplace(void* p) { InitializeCriticalSection(static_cast<CRITICAL_SECTION*>(p)); }
void CryDeleteCriticalSectionInplace(void* p) { DeleteCriticalSection(static_cast<CRITICAL_SECTION*>(p)); }

struct IMemoryManager;
IMemoryManager* CryGetIMemoryManager() { return nullptr; }
void CryGetIMemoryManagerInterface(void** p) { if (p) *p = nullptr; }

namespace {
inline uintptr_t game_fn(uintptr_t rva) { return Offsets::GetBase() + rva; }
}

__declspec(dllexport) void* CryModuleMalloc(size_t size) throw()
{
    return reinterpret_cast<void* (__cdecl*)(size_t)>(game_fn(Offsets::kGameMallocOffset))(size);
}
__declspec(dllexport) void* CryModuleCalloc(size_t count, size_t size)
{
    return reinterpret_cast<void* (__cdecl*)(size_t, size_t)>(game_fn(Offsets::kGameCallocOffset))(count, size);
}
__declspec(dllexport) void* CryModuleRealloc(void* p, size_t size) throw()
{
    return reinterpret_cast<void* (__cdecl*)(void*, size_t)>(game_fn(Offsets::kGameReallocOffset))(p, size);
}
__declspec(dllexport) void CryModuleFree(void* p) throw()
{
    reinterpret_cast<void (__cdecl*)(void*)>(game_fn(Offsets::kGameFreeOffset))(p);
}
