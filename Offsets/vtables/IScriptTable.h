#pragma once
#include <cstdint>

// -----------------------------------------------
// IScriptTable — Binary vtable order (interfuscated)
// -----------------------------------------------
// Cracked by tracing __ThisWUID read/write paths:
//   Read:  sub_1803B92D0 → GetValueAny at vtable+0x40
//   Write: sub_1802B8BCC → SetValueAny at vtable+0x38
//   Entity→Table: sub_1803B9A0C → IEntity::GetProxy(2) → IEntityScriptProxy::GetScriptTable()
//
// Uses ScriptAnyValue (see IScriptSystem.h) for type-discriminated get/set.

struct IScriptTable;  // forward decl for self-referential methods

namespace Offsets {

struct IScriptTable {
    virtual void _vf0() = 0;                                                           // [0]  0x00
    virtual void _vf1() = 0;                                                           // [1]  0x08
    virtual IScriptTable* Clone() = 0;                                                  // [2]  0x10  shallow clone, result AddRef'd by caller
    virtual void AddRef() = 0;                                                          // [3]  0x18  confirmed from SmartScriptTable pattern
    virtual void Release() = 0;                                                         // [4]  0x20  confirmed from type-6 cleanup in sub_1803B9E68
    virtual void SetDelegate(IScriptTable* pDelegate) = 0;                              // [5]  0x28  links soul table to entity
    virtual void _vf6() = 0;                                                           // [6]  0x30
    virtual void SetValueAny(const char* key, void* pScriptAnyValue, bool forceLocal = false) = 0; // [7]  0x38  confirmed: 4 independent wrapper functions
    virtual bool GetValueAny(const char* key, void* pScriptAnyValue, bool forceLocal = false) = 0; // [8]  0x40  confirmed: sub_1803B92D0 reads __ThisWUID
    virtual void _vf9() = 0;                                                           // [9]  0x48
    virtual void _vf10() = 0;                                                          // [10] 0x50
    virtual int  GetCount() = 0;                                                        // [11] 0x58  returns int, no key arg
    virtual IScriptTable* CloneDeep(bool bDeep, int cloneType) = 0;                     // [12] 0x60  3-arg clone factory
    virtual void _vf13() = 0;                                                          // [13] 0x68
    virtual void _vf14() = 0;                                                          // [14] 0x70
    virtual void BeginIteration(void* pIterator, bool bReverse = false) = 0;            // [15] 0x78  inits iterator state
    virtual bool MoveNext(void* pIterator) = 0;                                         // [16] 0x80  advances iterator, returns false at end
    virtual void EndIteration(void* pIterator) = 0;                                     // [17] 0x88  cleans up iterator
};

}  // namespace Offsets
