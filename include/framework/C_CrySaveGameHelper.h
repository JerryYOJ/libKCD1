#pragma once

#include <cstdint>
#include <vector>
#include "../CryEngine/CryCommon/CryString.h"

namespace wh::framework {

class C_CryOutputSerializer;

// -----------------------------------------------
// C_CrySaveGameHelper — bridges WH save system to CryEngine ISaveGame
// -----------------------------------------------
// RTTI: .?AVC_CrySaveGameHelper@framework@wh@@
// Vtable: 0x1826a2dd8 (11 entries)   Constructor: sub_180F0CC38   Size: 0x38
//
// Allocated by C_SaveGameManager ctor, stored at C_SaveGameManager+0x198
// and also as global qword_1837879A8.
//
// The save chain calls CreateSerializer to allocate a C_CryOutputSerializer per
// module chunk, then FlushSerializers to write all of them into the .whs file.

class C_CrySaveGameHelper {
public:
    virtual ~C_CrySaveGameHelper() = default;                                   // [0]
    virtual bool        SetSavePath(const char* path);                          // [1]  copies path into m_savePath
    virtual void        WriteChunkHeader(const char* chunkName, int32_t tag);   // [2]  writes name+tag to active stream (tag 0x20A8)
    virtual void        WriteFilenamePair(const char* name, const char* path);  // [3]  writes two strings to stream (tag 0x20A7)
    virtual C_CryOutputSerializer* CreateSerializer(void** ppOut, const char* chunkName); // [4] alloc serializer, push to m_serializers
    virtual void        _vf5();                                                 // [5]  ret 0
    virtual void        _vf6();                                                 // [6]  ret 0
    virtual bool        FlushSerializers(bool commit);                          // [7]  iterates m_serializers → writes each to stream, clears
    virtual void        _vf8();                                                 // [8]  stubbed
    virtual void        SetVersion(int32_t ver);                                // [9]  m_version = ver
    virtual int32_t     GetVersion();                                           // [10] return m_version

    int32_t             m_version;          // +0x08  init 3, set via SetVersion
    char                _pad0C[0x04];       // +0x0C
    CryStringT<char>    m_savePath;         // +0x10  save file path
    void*               m_pStream;          // +0x18  active I_WHSerializer stream (sub_180F332E8)
    std::vector<C_CryOutputSerializer*> m_serializers; // +0x20  pending serializer list
};
static_assert(sizeof(C_CrySaveGameHelper) == 0x38);

}  // namespace wh::framework
