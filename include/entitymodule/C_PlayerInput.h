#pragma once

#include <cstdint>
#include <map>
#include <set>
#include "../Offsets/vtables/IActionListener.h"        // Offsets::IActionListener, Offsets::ActionId
#include "../Offsets/vtables/ISystemEventListener.h"

// -----------------------------------------------
// C_PlayerInput — the local player's action-map listener / input state
// -----------------------------------------------
// RTTI: .?AVC_PlayerInput@entitymodule@wh@@
// Constructor: 0x1810976FC  (placement-init over a 0x340 alloc)
// Allocated by: C_Player::Init @ 0x1810A18B8 (size 0x340), stored at C_Player+0xA90
// Destructor:  0x181098B40 (member teardown) / 0x1810991F0 (scalar-deleting)
//
// vtable (IActionListener):      0x1822E2F50  (+0x00)  [0]dtor [1]OnAction [2]AfterAction
// vtable (ISystemEventListener): 0x1822E2F30  (+0x08, mdisp=8)  [0]dtor-thunk [1]OnSystemEventAnyThread(empty) [2]OnSystemEvent
// Bases (RTTI): C_PlayerInput, IActionListener (off 0), ISystemEventListener (off 8)
// Total size: 0x340
//
// OnAction (vtable[1], 0x1801FF740) snapshots m_inputFlags -> m_prevInputFlags,
// inserts/erases the action in m_heldActionIds, then dispatches through
// m_actionHandlers (+0x2B8) keyed by ActionId. Horse gait handlers (map entries,
// NOT vtable slots):
//   "horse_sprint"     -> 0x1810A2AB4  (C_EntityActions+0x6B8)
//   "horse_toggle_run" -> 0x1810A31A0  (C_EntityActions+0x6C8)
// Movement keys -> sub_1806D4B24 (writes m_moveVec + the x3 run-scaled mirror).
//
// Gaits are THREE distinct fields: trot = m_toggleRun (byte toggle); canter =
// m_inputFlags ePIF_Canter (set sub_1810A9E6C / cleared sub_1810AA114); dash =
// m_dashRequested via 2nd sprint press within wh_player_DashMaxInterval.
//
// COVERAGE: fields are recovered from the ctor, dtor, OnAction, OnSystemEvent and
// the movement/jump/sprint/toggle handlers. Regions still marked _unkXX are
// genuinely unmapped (rotate/aim handlers, per-frame Update, script-call path —
// not yet traced), sized to keep named offsets exact (/d1reportSingleClassLayout).
// ============================================================================

namespace wh::entitymodule {

class C_Player;

// m_inputFlags bits. VERIFIED writers only — bit 0x2 and bits >=0x20 are not yet
// traced, so this is a PARTIAL decode of the dword, not the complete set.
enum E_PlayerInputFlag : uint32_t {
    ePIF_JumpRequested = 0x01,   // bit0  set by jump handler (sub_1810A2DB4)
    ePIF_Canter        = 0x04,   // bit2  run/canter active (set sub_1810A9E6C, cleared sub_1810AA114)
    ePIF_CtorBit3      = 0x08,   // bit3  set at construction; purpose unconfirmed
    ePIF_Moving        = 0x10,   // bit4  a movement key is held (sub_1806D4B24)
};

class C_PlayerInput : public Offsets::IActionListener,        // +0x00 vtable
                      public Offsets::ISystemEventListener     // +0x08 vtable
{
public:
    // Action-map callback: a bound member handler. Under C_PlayerInput's multiple
    // inheritance the MFP is 16 bytes {pfn, this-adjust}, matching the map value.
    using TOnActionHandler = bool (C_PlayerInput::*)(unsigned int entityId,
                                                     const Offsets::ActionId& action,
                                                     int activationMode, float value);

    // ===================================================================
    // Data members
    // ===================================================================
    C_Player*   m_pPlayer;              // +0x10  owning player (ctor arg)

    uint32_t    m_inputFlags;           // +0x18  E_PlayerInputFlag bitset (init ePIF_CtorBit3)
    uint32_t    m_prevInputFlags;       // +0x1C  snapshot of m_inputFlags each OnAction

    // Currently-held action IDs: inserted on press, erased on release (OnAction).
    std::set<Offsets::ActionId> m_heldActionIds;   // +0x20 (0x10; _Myhead/_Mysize, 0x28 RB nodes)

    // Held-action ring (+0x30..+0x58): NOT STL and NOT boost — a hand-rolled power-of-2
    // ring of pointer-nodes (sub_1810AC68C; (cap-1)&(head+i) indexing, 0x10 nodes). Does
    // not match boost::container::vector / unordered / circular_buffer or any std container.
    // Drained on level-unload (OnSystemEvent ev 0x36), replaying each entry as a release.
    void*       m_ringRecent;           // +0x30  0x10 node (ctor self-links to +0x30)
    void**      m_ringSlots;            // +0x38  slot array (m_ringCapacity entries, 0x10 nodes)
    uint64_t    m_ringCapacity;         // +0x40  power-of-2 capacity
    uint64_t    m_ringHeadIdx;          // +0x48  ring base index
    uint64_t    m_ringCount;            // +0x50  live count

    float       m_moveStrafe;           // +0x58  moveleft/right analog (1x)
    float       m_moveForward;          // +0x5C  moveforward/back analog (1x)
    uint32_t    m_unk60;                // +0x60  cleared on dismount (OnAction)
    uint8_t     _unk64[0xC];            // +0x64
    float       m_turnResidual[3];      // +0x70  movement/turn residual vec; must settle to clear ePIF_Moving (sub_1810AC288)

    uint8_t     m_toggleRun;            // +0x7C  TROT auto-run toggle byte (ctor init 1; gait handlers)
    uint8_t     _unk7D[0x17];           // +0x7D

    float       m_viewYawComputed;      // +0x94  smoothed view-yaw (sub_1810A284C); zeroed when canter stops
    uint8_t     _unk98[0x8];            // +0x98
    float       m_yawInput;             // +0xA0  raw rotate input (= -value)
    uint8_t     _unkA4[0x24];           // +0xA4
    uint8_t     m_moveSettleLatch;      // +0xC8  set once moving, cleared when m_turnResidual settles (sub_1810AC288)
    uint8_t     _unkC9[3];              // +0xC9

    uint32_t    m_heldMoveKeys;         // +0xCC  bitmask of currently-held movement keys (sub_1806D4B24)
    uint8_t     _unkD0[0x18];           // +0xD0

    float       m_lastSprintPressTime;  // +0xE8  GetCurrTime() of last sprint press (dash double-tap timing)
    float       m_canterReleaseTimer;   // +0xEC  canter grace timer (sub_1810A9E6C / sub_1810AA114)
    uint8_t     m_dashRequested;        // +0xF0  set when a double-tap dash fires (init 0)
    uint8_t     _unkF1[0xBF];           // +0xF1  aim/camera/lock state (unmapped)

    Offsets::CCryName m_actionName;     // +0x1B0 interned action/filter name (ctor: sub_18028D060; dtor refcount cleanup)
    uint8_t     _unk1B8[0x28];          // +0x1B8
    void*       m_pRefCounted1E0;       // +0x1E0 refcounted object (released in dtor via sub_180222688)
    uint8_t     _unk1E8[0xAC];          // +0x1E8 (unmapped)

    float       m_moveStrafeRun;        // +0x294 m_moveStrafe x3 (run-scaled mirror)
    float       m_moveForwardRun;       // +0x298 m_moveForward x3 (run-scaled mirror)
    uint8_t     _unk29C[0xC];           // +0x29C

    uint8_t     m_jumpHeld;             // +0x2A8 jump-held latch (jump handler)
    uint8_t     _unk2A9[7];             // +0x2A9
    uint8_t     m_latch2B0;             // +0x2B0 press latch (set on press, acts on release)
    uint8_t     _unk2B1[7];             // +0x2B1

    // CryEngine TActionHandler<C_PlayerInput>: action name -> bound member handler.
    // (entries registered via sub_180FA20FC; horse_sprint/horse_toggle_run live here.)
    std::map<Offsets::ActionId, TOnActionHandler> m_actionHandlers;  // +0x2B8 (0x10)

    uint8_t     _unk2C8[0x20];          // +0x2C8
    uint8_t     m_holdActionHelper[0x38]; // +0x2E8 embedded hold/repeat-action helper (sub_180FD6970 teardown)
    uint8_t     _unk320[0x18];          // +0x320

    uint8_t     m_registeringHandlers;  // +0x338 ctor guard: 1 during handler registration, 0 after
    uint8_t     _unk339[7];             // +0x339
};
static_assert(sizeof(C_PlayerInput) == 0x340);

} // namespace wh::entitymodule
