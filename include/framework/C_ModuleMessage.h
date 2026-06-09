#pragma once

#include <cstdint>

namespace wh::framework {

// C_ModuleMessage — base class for inter-module messages dispatched by C_ModulesManager.
//
// RTTI: .?AVC_ModuleMessage@framework@wh@@
// Vtable: 0x1821a8ab0 (5 entries)
// Size: 0x18 bytes (from scalar delete in dtor sub_180F00784)
//
// Dispatched through C_ModulesManager::ProcessMessage (sub_1803D9BB8):
//   1. Manager's internal handler processes the message by type
//   2. Iterates I_ModuleMessageListener vector, calls OnModuleMessage on each
//   3. Calls message->OnProcessed()
//
// Derived types: C_NewGamePrepareMessage, C_ModuleMessageSaveGameRequest,
//   C_ModuleMessageSaveToChunk, C_ModuleMessageLoadFromChunk,
//   C_ModuleMessageSerializer, C_ModuleMessagePatch, C_ModuleMessageSoul

class C_ModuleMessage {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ModuleMessage;
    virtual ~C_ModuleMessage() = default;           // [0] 0x00
    virtual void OnProcessed() {}                   // [1] 0x08  called after dispatch, nop in base
    virtual void _vf2() {}                          // [2] 0x10  nop in base
    virtual void _vf3() {}                          // [3] 0x18  nop in base
    virtual bool IsExtended() const {               // [4] 0x20  returns m_type > 0x3F
        return m_type > 0x3F;
    }

    enum : int32_t {
        kType_Init                  = 0x00,
        kType_RegisterSerializers   = 0x01,
        kType_SaveGameRequest       = 0x04,
        kType_SaveToChunk           = 0x06, // 0x06-0x09 depending on version/dirty flags
        kType_SaveToChunkEnd        = 0x09,
        kType_LoadDatabases         = 0x0C,
        kType_Reset                 = 0x1C,
        kType_PreLoad               = 0x22,
        kType_Deserialize           = 0x23,
        kType_PostLoad              = 0x24,
        kType_Cleanup               = 0x26,
        kType_TimeOfDay             = 0x2D,
        kType_NewGamePrepare        = 0x33,
        kType_LoadComplete          = 0x3C, // fires once after all chunks deserialized from save
    };

    int32_t     m_type;     // +0x08
    int32_t     m_param;    // +0x0C  (usually 0xFFFFFFFF)
    uint8_t     m_flag;     // +0x10
    uint8_t     _pad11[7];  // +0x11
};
static_assert(sizeof(C_ModuleMessage) == 0x18);

}  // namespace wh::framework
