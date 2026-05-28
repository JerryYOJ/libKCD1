#pragma once
#include <cstdint>

// Generic vtable call helper for interfuscated CryEngine interfaces.
// Usage: Offsets::vcall<RetType>(pInterface, binaryVtableByteOffset, args...)

namespace Offsets {

template<typename Ret = void, typename This, typename... Args>
Ret vcall(This* obj, uint32_t byteOffset, Args... args) {
    auto vtable = *reinterpret_cast<uintptr_t**>(obj);
    auto fn = reinterpret_cast<Ret(__fastcall*)(This*, Args...)>(vtable[byteOffset / 8]);
    return fn(obj, args...);
}

}  // namespace Offsets
