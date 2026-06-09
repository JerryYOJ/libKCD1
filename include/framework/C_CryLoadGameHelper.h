#pragma once

#include <cstdint>
#include "../CryEngine/CryCommon/CryString.h"

namespace wh::framework {

// -----------------------------------------------
// C_CryLoadGameHelper — bridges CryEngine ILoadGame to WH deserialization
// -----------------------------------------------
// RTTI: .?AVC_CryLoadGameHelper@framework@wh@@
// Vtable: 0x1826a2fd0 (10 entries)   Constructor: sub_180F0CBF4   Size: 0x40
//
// Allocated by C_SaveGameManager ctor, stored at C_SaveGameManager+0x1A0
// and also as global qword_1837879B0.
//
// On load, the game opens a .whs file, creates an I_WHSerializer input stream,
// and this helper walks the chunks — dispatching each to the matching module
// deserializer via ReadChunk / FindChunk.

class C_CryLoadGameHelper {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CryLoadGameHelper;
    virtual ~C_CryLoadGameHelper() = default;                       // [0]
    virtual bool        SetLoadPath(const char* path);              // [1]  copies path into m_loadPath
    virtual void        _vf2();                                     // [2]  ret 0
    virtual bool        GetNestedSaveId(int32_t* pOutId);           // [3]  reads from internal state
    virtual void*       GetChunkData();                             // [4]  returns chunk payload ptr (or null)
    virtual bool        HasChunk();                                 // [5]  returns true if current chunk valid
    virtual void*       FindChunk(void** ppOut, int64_t chunkTag);  // [6]  locate chunk by tag, alloc wrapper
    virtual bool        HasChunkByTag(int64_t chunkTag);            // [7]  returns true if chunk with tag exists
    virtual void        _vf8();                                     // [8]  stubbed
    virtual void*       GetSomething();                             // [9]  returns actor ptr from context

    CryStringT<char>    m_loadPath;         // +0x08  load file path
    void*               m_pStream;          // +0x10  active I_WHSerializer input stream
    void*               m_18;               // +0x18
    void*               m_20;               // +0x20
    void*               m_28;               // +0x28
    void*               m_30;               // +0x30
    void*               m_38;               // +0x38
};
static_assert(sizeof(C_CryLoadGameHelper) == 0x40);

}  // namespace wh::framework
