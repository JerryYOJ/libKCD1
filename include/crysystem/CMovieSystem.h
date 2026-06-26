#pragma once

#include <cstddef>
#include <cstdint>

#include "Offsets/Offsets_VTABLE.h"
#include "Offsets/vtables/IMovieSystem.h"
#include "Offsets/vtables/IMovieUser.h"
#include "crysystem/SCameraParams.h"

// -----------------------------------------------
// CMovieSystem - stock CryEngine movie/TrackView system.
// -----------------------------------------------
// RTTI: .?AVCMovieSystem@@
// Hierarchy (RTTI): CMovieSystem : IMovieSystem, with IMovieSystem at +0x00.
// Primary vtable: WHGame+0x279FD10, 92 verified function slots.

struct CMovieSystem : public Offsets::IMovieSystem {
    inline static constexpr auto VTABLE = Offsets::VTABLE_CMovieSystem;

    uint8_t _pad08[0x70 - 0x08];       // +0x08
    Offsets::IMovieUser* m_pUser;      // +0x70 notified by SetCameraParams
    void* m_pCallback;                 // +0x78 callback object; exact interface not recovered
    uint8_t _pad80[0xE4 - 0x80];       // +0x80
    SCameraParams m_cameraParams;      // +0xE4 copied by SetCameraParams
};

static_assert(offsetof(CMovieSystem, m_pUser) == 0x70);
static_assert(offsetof(CMovieSystem, m_pCallback) == 0x78);
static_assert(offsetof(CMovieSystem, m_cameraParams) == 0xE4);
