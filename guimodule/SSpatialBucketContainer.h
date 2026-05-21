#pragma once

#include <cstdint>

// -----------------------------------------------
// SSpatialBucketContainer — spatial hash / event bucket
// -----------------------------------------------
// Constructors: sub_180F993F0 / sub_1811247E0 / sub_181023FC4
// Size: 0x30

namespace wh::guimodule {

struct SSpatialBucketContainer {
    float       m_fGridScale;   // +0x00  init 1.0f
    char        _pad04[0x4];    // +0x04
    void*       m_pBuckets;     // +0x08  bucket array
    uint64_t    m_unk10;        // +0x10
    void*       m_ptr18;        // +0x18
    void*       m_ptr20;        // +0x20
    void*       m_ptr28;        // +0x28
};
static_assert(sizeof(SSpatialBucketContainer) == 0x30);

}  // namespace wh::guimodule
