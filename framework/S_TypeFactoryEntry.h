#pragma once
#include <cstdint>
#include <string>

// -----------------------------------------------
// S_TypeFactoryEntry — engine-wide type registry entry
// -----------------------------------------------
// Used by multiple modules to register creatable types in a global hash map:
//   "wh.rpgmodule.buff.Constant"       (buff system)
//   "wh.entitymodule.C_ItemSlot"       (entity module)
//   "NULL"                             (root entry)
//
// Each entry is a persistent global (.bss) populated at static init time via
// RegisterType (sub_180712B68). Entries form a tree: each entry lists its parent
// entries and gets appended as a child of those parents via sub_180DA84C8.
//
// FNV-1a hash: sub_180449CD4 (basis=0xCBF29CE484222325, prime=0x100000001B3)
//
// Factory lookup (sub_18044ACA0) traverses the tree:
//   1. Compare search key against entry's key
//   2. On mismatch, recurse into m_pChildren
//   3. On match, call m_creator -> allocates + constructs the object
//   4. Pass result through m_cast(matchIndex, createdInstance)
//      Default (sub_18044B450) returns the instance unchanged.
//      Non-default may offset the pointer to a specific base class.

namespace wh::shared {

// Allocates and constructs a typed object. Receives the registration data pointer.
// Returns the new instance pointer (or nullptr on failure).
using TypeCreatorFn = void* (__fastcall*)(void* pRegistrationData);

// Adjusts the returned pointer for the matched inheritance level.
// Default (sub_18044B450): identity, returns pInstance unchanged.
// Non-default may offset the pointer to a specific base class (e.g., instance + 0x30).
using TypeCastFn = void* (__fastcall*)(int32_t nMatchIndex, void* pInstance);

struct S_TypeFactoryEntry {
    std::string             m_key;              // +0x00  key like "wh.rpgmodule.buff.Constant"
    uint64_t                m_hash;             // +0x20  FNV-1a hash of key string
    S_TypeFactoryEntry**    m_pParents;         // +0x28  null-terminated array of parent entries
                                                //        this entry is appended as a child of each parent
    int32_t                 m_nChildCount;      // +0x30  number of children registered under this entry
    int32_t                 _pad34;             // +0x34
    S_TypeFactoryEntry**    m_pChildren;        // +0x38  array of child entry pointers (grown dynamically)
    TypeCreatorFn           m_creator;          // +0x40  allocates + constructs the typed object
    TypeCastFn              m_cast;             // +0x48  default: identity (sub_18044B450)
};
static_assert(sizeof(S_TypeFactoryEntry) == 0x50);

// -----------------------------------------------
// RegisterType — registers an entry in the global type factory
// -----------------------------------------------
// sub_180712B68
// Called during static init to register a creatable type.
// Populates pEntry, builds parent-child links, inserts into the global C_HashMap.
//
// pEntry:     persistent storage (must be a global — lifetime must exceed the factory)
// pKey:       fully qualified key (e.g., "wh.rpgmodule.buff.Constant")
// pParents:   null-terminated array of parent entries (pass {nullptr} if none)
// fnCast:     pointer adjustment function (pass identity sub_18044B450 for most cases)
// fnCreator:  allocates + constructs the typed object
//
// RVA: 0x712B68
using RegisterTypeFn = void (__fastcall*)(
    S_TypeFactoryEntry*     pEntry,
    const char*             pKey,
    S_TypeFactoryEntry**    pParents,
    TypeCastFn              fnCast,
    TypeCreatorFn           fnCreator
);

// Identity cast function — returns pInstance unchanged.
// RVA: 0x44B450
inline constexpr uintptr_t kIdentityCastRVA = 0x44B450;

}  // namespace wh::shared
