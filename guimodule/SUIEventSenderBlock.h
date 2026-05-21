#pragma once

#include <cstdint>

// -----------------------------------------------
// SUIEventSenderBlock — CryEngine Flash UI event dispatch block
// -----------------------------------------------
// Constructor: sub_18103D7C4
// Size: 0x40

namespace wh::guimodule {

struct SUIEventSenderBlock {
    uint64_t    _unk00;         // +0x00
    uint64_t    _unk08;         // +0x08
    uint8_t     m_bEnabled;     // +0x10
    char        _pad11[0x7];    // +0x11
    void*       m_pListHead;    // +0x18  self-referential sentinel
    void*       m_pListTail;    // +0x20  self-referential sentinel
    void*       m_ptr28;        // +0x28
    void*       m_ptr30;        // +0x30
    void*       m_ptr38;        // +0x38
};
static_assert(sizeof(SUIEventSenderBlock) == 0x40);

}  // namespace wh::guimodule
