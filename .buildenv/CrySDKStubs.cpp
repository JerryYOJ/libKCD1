#include <Windows.h>
#include <cstdlib>

// Stubs for CryEngine SDK symbols referenced by CryCommon inline code.
// Linked into kcd_re so all downstream targets (KCSE, plugins) get them automatically.

void CryCreateCriticalSectionInplace(void* p) { InitializeCriticalSection(static_cast<CRITICAL_SECTION*>(p)); }
void CryDeleteCriticalSectionInplace(void* p) { DeleteCriticalSection(static_cast<CRITICAL_SECTION*>(p)); }

struct IMemoryManager;
IMemoryManager* CryGetIMemoryManager() { return nullptr; }
void CryGetIMemoryManagerInterface(void** p) { if (p) *p = nullptr; }

__declspec(dllexport) void* CryModuleMalloc(size_t size) throw() { return malloc(size); }
__declspec(dllexport) void* CryModuleCalloc(size_t count, size_t size) { return calloc(count, size); }
__declspec(dllexport) void  CryModuleFree(void* p) throw() { free(p); }
