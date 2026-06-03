#pragma once

#include <cstdint>
#include <vector>
#include "../framework/C_Signal.h"
#include "../entitymodule/I_ItemAttachmentListener.h"
#include "../Offsets/vtables/IEntityEventListener.h"
#include "../Offsets/vtables/IEntity.h"
#include "C_CombatModule.h"
#include "I_CombatActor.h"
#include "C_CombatActorObject.h"
#include "I_CombatActorAction.h"
#include "C_CombatComboManager.h"
#include "S_CombatActorState.h"
#include "I_CombatTarget.h"
#include "C_CombatActorHuntAttack.h"

namespace wh::entitymodule {
enum E_HandSlot : int32_t;
}  // namespace wh::entitymodule

namespace wh::combatmodule {

// Forward declarations
class C_CombatScene;
class I_CombatActorAction;
class C_CombatActorActionManager;
class C_CombatActorHorsePullDown;
class C_CombatActorMercyKill;
class C_CombatActorHuntAttack;
struct S_HitInfo;
struct S_MeleeHitDetails;

// ---------------------------------------------------------------------------
// E_CombatActorStateId -- combat actor state identifiers.
// Referenced in C_Signal template parameters at +0x18 and +0x48.
// Used in signals: C_Signal<I_CombatActor&, I_CombatActor&,
//                           E_CombatActorStateId, E_CombatActorStateId>
// Enum values NOT recovered: no enum-to-string converter function found
// in binary. Only RTTI template parameter names confirm its existence.
// Forward-declared; define values when a converter function is located.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// E_CombatZoneId -- directional combat zones.
//
// VERIFIED: from combat_zone.xml in Tables.pak.
// Each zone corresponds to a guard/attack direction in the star combat system.
// Zone 2 (upper_right) is the default zone (default_zone="True").
// ---------------------------------------------------------------------------
enum class E_CombatZoneId : int32_t {
    Undefined  = -1,
    Head       = 0,   // "head"        — top stab
    UpperLeft  = 1,   // "upper_left"  — angles 135°-205°
    UpperRight = 2,   // "upper_right" — angles 325°-45° (DEFAULT)
    LowerLeft  = 3,   // "lower_left"  — angles 205°-270°
    LowerRight = 4,   // "lower_right" — angles 270°-325°
    Center     = 5,   // "center"      — radius 0 (thrust/stab)
};

enum class E_CombatActorStateId : int32_t;

// ---------------------------------------------------------------------------
// E_CounterActionType -- event types for DispatchCounterAction (sub_18069536C).
//
// Used as a3 in sub_1805633D0. Internally mapped to a "trigger type" v14
// which selects the factory path and action type.
// VERIFIED: switch chain in sub_1805633D0. Values 1 and 2 are invalid
// (fall through all checks, return null).
// ---------------------------------------------------------------------------
enum class E_CounterActionType : int32_t {
    PerfectBlock     = 0,   // v14=4  → PerfectBlockFactory, g_actionType_perfectBlock
    // 1 — invalid (unused)
    // 2 — invalid (unused)
    SyncDodge        = 3,   // v14=6  → PerfectBlockFactory, g_actionType_syncDodge
    SyncRiposte      = 4,   // v14=8  → PerfectBlockFactory, g_actionType_syncRiposte
    SyncBlock        = 5,   // v14=2  → AttackFactory, g_actionType_block (via sub_1804E10A4)
    PerfectBlockDodge = 6,  // v14=0xA → PerfectBlockFactory, g_actionType_perfectBlockDodge
    SyncPerfectBlock = 7,   // v14=0xC → PerfectBlockFactory, g_actionType_syncPerfectBlock
};

// ---------------------------------------------------------------------------
// E_SignalSource::Type -- combat signal source type.
// Referenced in multiple C_Signal template parameters.
// Confirmed via RTTI: used in Signal<..., E_SignalSource::Type, ...>
// and Signal<..., E_SignalSource::Type, E_WeaponKind::Type>.
// Also referenced by xgenaimodule::C_CombatInfo signals.
// Enum values NOT recovered: no enum-to-string converter found.
// Forward-declared; define values when usage sites reveal constants.
// ---------------------------------------------------------------------------
namespace E_SignalSource {
    enum Type : int32_t;
}

// ---------------------------------------------------------------------------
// E_WeaponKind::Type -- weapon classification type.
// Referenced in C_Signal template parameters.
// Confirmed via RTTI: used in Signal<I_CombatActor&,
//   E_SignalSource::Type, E_WeaponKind::Type> and standalone
//   Signal<E_WeaponKind::Type>. Also used by xgenaimodule.
// Enum values NOT recovered: no enum-to-string converter found.
// Forward-declared; define values when usage sites reveal constants.
// ---------------------------------------------------------------------------
namespace E_WeaponKind {
    enum Type : int32_t;
}

// ---------------------------------------------------------------------------
// C_CombatActor -- per-entity combat state object.
//
// RTTI: .?AVC_CombatActor@combatmodule@wh@@
// Primary vtable   @ 0x182228be8
// Secondary vtable @ 0x1822293f8 (I_ItemAttachmentListener, at this+0x08)
// Tertiary vtable  @ 0x182229418 (IEntityEventListener, at this+0x10)
// Constructor: sub_1804F3068(this, entity, combatScene)
// Destructor (cleanup): sub_1804F3904
// Scalar deleting dtor: sub_180602020 (frees 0x780)
// Size: 0x780 bytes
//
// Inheritance chain (from RTTI BaseClassArray & destructor):
//   C_CombatActor
//     I_CombatActor                   (wh::combatmodule, at +0x00)
//     I_ItemAttachmentListener        (wh::entitymodule, at +0x08)
//     IEntityEventListener            (CryEngine, at +0x10)
//
// The constructor takes three arguments:
//   a1 = this
//   a2 = entity pointer (stored at +0x4A0)
//   a3 = C_CombatScene pointer (stored at +0x4B0)
//
// Factory: sub_1806EDD24 allocates 0x780 bytes and calls the constructor.
//
// Subclass: C_CombatPlayer (extends C_CombatActor with extra vtable at +0x780)
//
// === Signal members (each is 0x30 bytes, C_Signal<...>) ===
//
// The signals use I_CombatActor& as the "sender" parameter in most cases.
// Signal template types are VERIFIED from constructor RTTI vtable writes.
// Signal member names are inferred from parameter types (not from symbols).
//
// === Primary vtable layout (interfuscator-shuffled) ===
//   [0]  sub_180602020  -- scalar deleting destructor (frees 0x780)
//   [1]  sub_180564390  -- reads *(entity+0xBD8) as byte (IsXxx)
//   [2]  sub_1804550E0  -- combat distance/range check
//   [3]  sub_1806FABE0  -- reads *(entity+0xCFC) as byte (IsYyy)
//   [4]  sub_1805637FC  -- (complex operation)
//   [5]  sub_180563F10  -- (operation)
//   [6]  sub_18045E1C0  -- GetEntity: returns *(this+0x4A0)
//   [7]  sub_180695320  -- GetEntityId: returns *(entity+0x30)
//   [8]  sub_1804576A8  -- reads entity subsystem via *(entity+0xCA0)
//   [9]  sub_18045883C  -- reads entity subsystem via *(entity+0xCA0)
//   [10] sub_180F49204  -- reads entity subsystem via *(entity+0xCA0), vfunc[1]
//   [11] sub_180F49224  -- reads entity subsystem via *(entity+0xCA0), vfunc[2]
//   [12] sub_180F49244  -- gets entity name string
//   [13] sub_1804936C0  -- returns *(entity+0xBEC) as uint
//   [14] sub_180493B80  -- returns *(entity+0xBE0) as uint
//   [15] sub_1804317F0  -- (complex, 0x1ad bytes)
//
// === Key data member regions ===
//   +0x498: m_pCombatSystemGlobal (set from qword_18300BF98)
//   +0x4A0: m_pEntity (CryEngine IEntity*, ctor arg2)
//   +0x4A8: unknown qword
//   +0x4B0: m_pCombatScene (ctor arg3)
//   +0x4B8: m_pState (S_CombatActorState*, 0xD08 bytes)
//   +0x518..0x524: state flags
//   +0x524: bool flag (init 0)
//   +0x528: int32 (init -1)
//   +0x52C: bool (init 1)
//   +0x52D: bool (init 0)
//   +0x52E: bool (init 0)
//   +0x530: qword
//   +0x538: flags byte (masked with 0xFC)
//   +0x53C..0x540: floats (init -1.0f, -1.0f)
//   +0x560: byte (init 4)
//   +0x561..0x567: initialized by sub_1806699C8 (7 bytes)
//   +0x568: subsystem vector 1 (begin/end/capacity, 0x18 bytes)
//   +0x580: bool -- subsystem init flag (determines which vector to add to)
//   +0x588: subsystem vector 2 (begin/end/capacity, 0x18 bytes)
//   +0x5A0..0x6F8: zeroed fields (combat state data)
//   +0x6F8: int32 (init 0)
//   +0x700..0x778: zeroed fields
//   +0x770: word (init 0x101)
//   +0x774: qword (init 0) -- extends to near end
// ---------------------------------------------------------------------------
class C_CombatActor : public I_CombatActor,
                      public wh::entitymodule::I_ItemAttachmentListener,
                      public IEntityEventListener
{
public:
    // ---- I_CombatActor overrides [0]-[15] ----
    // Warhorse classes are NOT interfuscator-shuffled — slot indices are stable.
    ~C_CombatActor() override = default;                                    // [0]
    void unk_1() override {}                                                // [1] sub_180564390
    void unk_2() override {}                                                // [2] sub_1804550E0
    void unk_3() override {}                                                // [3] sub_1806FABE0
    void unk_4() override {}                                                // [4] sub_1805637FC
    void unk_5() override {}                                                // [5] sub_180563F10
    Offsets::IEntity* GetEntity() const override { return m_pEntity; }       // [6] sub_18045E1C0
    EntityId GetEntityId() const override { return 0; }                     // [7] sub_180695320
    void unk_8() override {}                                                // [8] sub_1804576A8
    void unk_9() override {}                                                // [9] sub_18045883C
    void unk_10() override {}                                               // [10] sub_180F49204
    void unk_11() override {}                                               // [11] sub_180F49224
    void unk_12() override {}                                               // [12] sub_180F49244
    uint32_t unk_13() const override { return 0; }                          // [13] sub_1804936C0
    uint32_t unk_14() const override { return 0; }                          // [14] sub_180493B80
    void unk_15() override {}                                               // [15] sub_1804317F0

    // ---- C_CombatActor virtual methods [16]-[82] ----
    // New methods added by C_CombatActor beyond I_CombatActor's 16-slot interface.
    // vtable @ 0x182228BE8, slot indices stable (not interfuscator-shuffled).
    virtual void unk_vf16() {}      // [16]
    virtual void unk_vf17() {}      // [17]
    virtual void unk_vf18() {}      // [18]
    virtual void unk_vf19() {}      // [19]
    virtual void unk_vf20() {}      // [20]
    virtual void unk_vf21() {}      // [21]
    virtual void unk_vf22() {}      // [22]
    virtual void unk_vf23() {}      // [23]
    virtual void unk_vf24() {}      // [24]
    virtual void unk_vf25() {}      // [25]
    virtual void unk_vf26() {}      // [26]
    virtual void unk_vf27() {}      // [27]
    virtual void unk_vf28() {}      // [28]
    virtual void unk_vf29() {}      // [29]
    virtual void unk_vf30() {}      // [30]
    virtual void unk_vf31() {}      // [31]
    virtual void unk_vf32() {}      // [32]
    virtual void unk_vf33() {}      // [33]
    virtual void unk_vf34() {}      // [34]
    virtual void unk_vf35() {}      // [35]
    virtual void unk_vf36() {}      // [36]
    virtual void unk_vf37() {}      // [37]
    virtual void unk_vf38() {}      // [38]
    virtual void unk_vf39() {}      // [39]
    virtual void unk_vf40() {}      // [40]
    virtual void unk_vf41() {}      // [41]
    virtual void unk_vf42() {}      // [42]
    virtual void unk_vf43() {}      // [43]
    virtual void unk_vf44() {}      // [44]
    virtual void unk_vf45() {}      // [45]
    virtual void unk_vf46() {}      // [46]
    virtual void unk_vf47() {}      // [47]
    virtual void unk_vf48() {}      // [48]
    virtual void unk_vf49() {}      // [49]
    virtual void unk_vf50() {}      // [50]
    virtual void unk_vf51() {}      // [51]
    virtual void unk_vf52() {}      // [52]
    virtual void unk_vf53() {}      // [53]
    virtual void unk_vf54() {}      // [54]
    virtual void unk_vf55() {}      // [55]
    virtual void unk_vf56() {}      // [56]
    virtual void unk_vf57() {}      // [57]
    virtual void unk_vf58() {}      // [58]
    virtual void unk_vf59() {}      // [59]
    virtual void unk_vf60() {}      // [60]
    virtual void unk_vf61() {}      // [61]
    virtual void unk_vf62() {}      // [62]
    virtual void unk_vf63() {}      // [63]
    virtual void unk_vf64() {}      // [64]
    virtual void unk_vf65() {}      // [65]
    virtual void unk_vf66() {}      // [66]
    virtual void unk_vf67() {}      // [67]
    virtual void unk_vf68() {}      // [68]
    virtual void unk_vf69() {}      // [69]
    virtual void unk_vf70() {}      // [70]
    virtual void unk_vf71() {}      // [71]
    virtual void unk_vf72() {}      // [72]
    virtual void unk_vf73() {}      // [73]
    virtual void unk_vf74() {}      // [74]
    virtual void unk_vf75() {}      // [75]
    virtual void unk_vf76() {}      // [76]
    virtual void unk_vf77() {}      // [77]
    virtual void unk_vf78() {}      // [78]
    virtual void unk_vf79() {}      // [79]
    virtual void unk_vf80() {}      // [80]
    virtual void unk_vf81() {}      // [81]

    // [82] SetAction — dispatches an action through the slot manager at +0x4A8.
    // Validates replacement policy, stops the current action in the target slot,
    // installs the new action, and emits transition signals.
    // ppAction: pointer to smart_ptr holding the action (ownership transferred).
    // Returns true if the action was accepted, false if rejected by slot policy.
    // sub_1804619CC, vtable offset 0x290
    virtual bool SetAction(I_CombatActorActionPtr* pAction) { return false; }   // [82]

    // ---- Non-virtual methods (direct function calls) ----

    // sub_18069536C → sub_1805633D0
    // Dispatches a counter action through the appropriate factory.
    // Creates the action AND calls SetAction internally.
    // scopeIndex: animation scope index (use 0 for default/primary scope).
    //   NOT a combat zone ID — it's passed to the director subsystem's slot lookup.
    // ppOutAction receives the created action (caller must Release).
    void DispatchCounterAction(I_CombatActorActionPtr* pOutAction, E_CounterActionType type, uint32_t scopeIndex = 0);

    // ---- I_ItemAttachmentListener overrides ----
    void OnItemAttached(uint64_t entityId, unsigned int handSlot) override {}  // sub_18054A9F4
    void OnItemDetached(uint64_t entityId, unsigned int handSlot) override {}  // sub_18054A904

    // ---- Signals (each 0x30 bytes) ----
    // Signal types are VERIFIED from constructor RTTI vtable writes (sub_1804F3068).
    // Signal names are mapped from BehaviorTree node names where the type signature
    // uniquely identifies the signal. Signals with non-unique types that could not
    // be definitively mapped use offset-based names (m_signal_XXX).
    //
    // Known BT signal names (from xgenaimodule BehaviorTree nodes):
    //   OnCombatStateChange, OnCombatActionStateChange, OnCombatModeChange,
    //   OnCombatGuardTypeChange, OnCombatZoneChange, OnWeaponChange,
    //   OnCombatEvent, OnCombatMoveEvent, OnActionBase, OnHit

    // +0x18: Signal<I_CombatActor&, I_CombatActor&, E_CombatActorStateId, E_CombatActorStateId>
    // One of: OnCombatStateChange / OnCombatActionStateChange (both use this type)
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_CombatActorStateId, E_CombatActorStateId>
        m_onCombatStateChange;                                              // +0x18

    // +0x48: Signal<I_CombatActor&, I_CombatActor&, E_CombatActorStateId, E_CombatActorStateId>
    // One of: OnCombatStateChange / OnCombatActionStateChange (both use this type)
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_CombatActorStateId, E_CombatActorStateId>
        m_onCombatActionStateChange;                                        // +0x48

    // +0x78: Signal<I_CombatActor&, I_CombatActor&, bool>
    // One of: OnCombatModeChange / OnCombatZoneChange (both are actor-pair + bool)
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_onCombatModeChange;                                               // +0x78

    // +0xA8: Signal<I_CombatActor&, I_CombatActor&, bool>
    // One of: OnCombatModeChange / OnCombatZoneChange
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_onCombatZoneChange;                                               // +0xA8

    // +0xD8: Signal<I_CombatActor&, I_CombatActor&, int>
    // OnCombatGuardTypeChange (guard type is an int enum)
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, int>
        m_onCombatGuardTypeChange;                                          // +0xD8

    // +0x108: Signal<I_CombatActor&, I_CombatActor&, int>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, int>
        m_onOpponentGuardType2;                                              // +0x108  relayed from opponent via LinkTarget

    // +0x138: Signal<I_CombatActor&, I_CombatActor&, int, E_HandSlot>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, int, wh::entitymodule::E_HandSlot>
        m_onOpponentHandSlot;                                                // +0x138  relayed from opponent via LinkTarget

    // +0x168: Signal<I_CombatActor&, bool>
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onOpponentPBWindow;                                               // +0x168  relayed from opponent state+0x5D0 via LinkTarget

    // +0x198: Signal<I_CombatActor&, bool>
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_198;                                                       // +0x198

    // +0x1C8: Signal<I_CombatActor&, int const&, I_CombatActorActionPtr const&, I_CombatActorActionPtr const&>
    // OnActionBase (self action changed, old+new action pair)
    wh::shared::C_Signal<I_CombatActor&, const int&, const I_CombatActorActionPtr&, const I_CombatActorActionPtr&>
        m_onActionBase;                                                     // +0x1C8


    // +0x1F8: Signal<I_CombatActor&, int const&, I_CombatActorActionPtr const&, I_CombatActorActionPtr const&>
    wh::shared::C_Signal<I_CombatActor&, const int&, const I_CombatActorActionPtr&, const I_CombatActorActionPtr&>
        m_signal_1F8;                                                       // +0x1F8

    // +0x228: Signal<I_CombatActor&, I_CombatActor&, int const&, I_CombatActorActionPtr const&, I_CombatActorActionPtr const&>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, const int&, const I_CombatActorActionPtr&, const I_CombatActorActionPtr&>
        m_signal_228;                                                       // +0x228

    // +0x258: Signal<I_CombatActor&, I_CombatActor&, int const&, I_CombatActorActionPtr const&, I_CombatActorActionPtr const&>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, const int&, const I_CombatActorActionPtr&, const I_CombatActorActionPtr&>
        m_onOpponentActionChanged;                                           // +0x258  relayed from opponent via LinkTarget

    // +0x288: Signal<> (no arguments)
    // OnCombatEvent (unique: only parameterless signal)
    wh::shared::C_Signal<>
        m_onCombatEvent;                                                    // +0x288

    // +0x2B8: Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
        m_signal_2B8;                                                       // +0x2B8

    // +0x2E8: Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
        m_signal_2E8;                                                       // +0x2E8

    // +0x318: Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type>
        m_signal_318;                                                       // +0x318

    // +0x348: Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
        m_signal_348;                                                       // +0x348

    // +0x378: Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type, bool>
        m_signal_378;                                                       // +0x378

    // +0x3A8: Signal<I_CombatActor&, E_SignalSource::Type, E_WeaponKind::Type>
    // OnWeaponChange (unique type: only signal with E_WeaponKind::Type)
    wh::shared::C_Signal<I_CombatActor&, E_SignalSource::Type, E_WeaponKind::Type>
        m_onWeaponChange;                                                   // +0x3A8

    // +0x3D8: Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, E_SignalSource::Type>
        m_signal_3D8;                                                       // +0x3D8

    // +0x408: Signal<I_CombatActor&>
    wh::shared::C_Signal<I_CombatActor&>
        m_signal_408;                                                       // +0x408

    // +0x438: Signal<I_CombatActor&, I_CombatActor*, S_HitInfo&, S_MeleeHitDetails&>
    // OnHit (unique type: only signals with S_HitInfo/S_MeleeHitDetails)
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor*, void*, void*>
        m_onHit;                                                            // +0x438
    // NOTE: void* stands in for S_HitInfo& and S_MeleeHitDetails&. Full types not yet recovered.

    // +0x468: Signal<I_CombatActor&, I_CombatActor*, S_HitInfo&, S_MeleeHitDetails&>
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor*, void*, void*>
        m_signal_468;                                                       // +0x468

    // ---- End of signals, start of data fields ----

    // +0x498: global pointer (set from qword_18300BF98 in sub_1805FCBC0)
    // VERIFIED: set in sub_1805FCBC0 which is called from the constructor.
    // Points to a static global; likely a combat system singleton or settings.
    void*                   m_pCombatSystemGlobal;  // +0x498

    // +0x4A0: entity pointer (ctor arg2)
    Offsets::IEntity*       m_pEntity;              // +0x4A0

    // +0x4A8: C_CombatActorDirector (0xD8 bytes)
    // VERIFIED RTTI: sub_1805FD214 writes C_CombatActorDirector vftable at +0x00
    //   AND at +0xB0 (MI — C_CombatActorObject embedded at +0xB0).
    // Used by action system: C_Action constructor stores this as owner ptr.
    void*                   m_pDirector;            // +0x4A8  C_CombatActorDirector

    // +0x4B0: C_CombatScene pointer (ctor arg3)
    C_CombatScene*          m_pCombatScene;         // +0x4B0

    // +0x4B8: Combat runtime state — 64+ signals + opponent/action state.
    // See S_CombatActorState.h for full layout (0xD08 bytes).
    S_CombatActorState*     m_pState;               // +0x4B8

    // +0x4C0: C_CombatActorCollisions (0x2B8 bytes)
    // VERIFIED RTTI: sub_1805FCC30 writes C_CombatActorCollisions vftable.
    void*                   m_pCollisions;          // +0x4C0  C_CombatActorCollisions

    // +0x4C8: C_CombatActorAnimCollisions (0x50 bytes)
    // VERIFIED RTTI: sub_1805FCE60 writes C_CombatActorAnimCollisions vftable.
    void*                   m_pAnimCollisions;      // +0x4C8  C_CombatActorAnimCollisions

    // +0x4D0: Per-actor data block (0x30 bytes, back-ptr + 5 zeroed qwords)
    // VERIFIED: inline alloc in sub_1805FDC88.
    void*                   m_pCombatData4D0;       // +0x4D0

    // +0x4D8: C_CombatEffects (0x20 bytes)
    // VERIFIED RTTI: sub_1805FD4A8 writes C_CombatEffects vftable.
    void*                   m_pEffects;             // +0x4D8  C_CombatEffects

    // +0x4E0: C_CombatActorRestriction (0x50 bytes)
    // VERIFIED RTTI: sub_1805FD578 writes C_CombatActorRestriction vftable.
    void*                   m_pRestriction;         // +0x4E0  C_CombatActorRestriction

    // +0x4E8: C_CombatEnvironmentManager (0x70 bytes)
    // VERIFIED RTTI: sub_1805FD5F4 writes C_CombatEnvironmentManager vftable.
    void*                   m_pEnvironmentManager;  // +0x4E8  C_CombatEnvironmentManager

    // +0x4F0: (UNVERIFIED purpose, zeroed in constructor)
    uint64_t                m_unknown4F0;           // +0x4F0

    // +0x4F8: C_CombatAlignmentManager (0x10 bytes)
    // VERIFIED RTTI: sub_1805FD2B4 writes C_CombatAlignmentManager vftable.
    void*                   m_pAlignmentManager;    // +0x4F8  C_CombatAlignmentManager

    // +0x500: C_CombatActorVirtualWeapon (0x28 bytes)
    // VERIFIED RTTI: sub_1805FD954 writes C_CombatActorVirtualWeapon vftable.
    void*                   m_pVirtualWeapon;       // +0x500  C_CombatActorVirtualWeapon

    // +0x508: C_CombatModifierAim (0x20 bytes)
    // VERIFIED RTTI: sub_1805FD2FC writes C_CombatModifierAim vftable.
    void*                   m_pModifierAim;         // +0x508  C_CombatModifierAim

    // +0x510: C_CombatModifierLookEnemy (0x20 bytes)
    // VERIFIED RTTI: sub_1805FD34C writes C_CombatModifierLookEnemy vftable.
    void*                   m_pModifierLookEnemy;   // +0x510  C_CombatModifierLookEnemy

    // +0x518: state/flag region
    uint16_t                m_stateFlags518;        // +0x518  (init 0)
    uint16_t                _pad51A;                // +0x51A
    uint32_t                m_stateFlags51C;        // +0x51C  (init 0)
    uint32_t                _pad520;                // +0x520
    bool                    m_isActive;             // +0x524  (init 0)
    uint8_t                 _pad525[3];             // +0x525
    int32_t                 m_combatStateIndex;     // +0x528  (init -1)
    bool                    m_isInitialized;        // +0x52C  (init 1)
    bool                    m_flag52D;              // +0x52D  (init 0)
    bool                    m_flag52E;              // +0x52E  (init 0)
    uint8_t                 _pad52F;                // +0x52F
    uint64_t                m_unknown530;           // +0x530  (init 0)
    uint8_t                 m_stateFlags538;        // +0x538  (masked with 0xFC in init)
    uint8_t                 _pad539[3];             // +0x539
    float                   m_timerA;               // +0x53C  (init -1.0f)
    float                   m_timerB;               // +0x540  (init -1.0f)
    uint8_t                 _pad544[0x1C];          // +0x544

    uint8_t                 m_updateMode;           // +0x560  (init 4)
    uint8_t                 m_subsystemFlags[7];    // +0x561  (init by sub_1806699C8)

    // +0x568: subsystem object vector 1 (used when !m_subsystemsInited)
    struct S_SubsystemEntry {
        C_CombatActorObject*    pObject;    // +0x00
        // VERIFIED from constructor (sub_180431258): entry is 0x10 bytes.
        // Byte at +0x08 is set to 1 (bool m_enabled), remaining 7 bytes are padding.
        bool                    m_enabled;  // +0x08
        uint8_t                 _pad09[7];  // +0x09
    };
    std::vector<S_SubsystemEntry> m_subsystemEntries1;  // +0x568

    bool                    m_subsystemsInited;     // +0x580  (init 0)
    uint8_t                 _pad581[7];             // +0x581

    // +0x588: subsystem object vector 2 (used when m_subsystemsInited)
    std::vector<S_SubsystemEntry> m_subsystemEntries2;  // +0x588

    // +0x5A0..0x6FC: Combat target tracking arrays.
    // VERIFIED layout from destructor (sub_1804F3904): 13 vectors freed via
    // sub_1805B72C0, 4 bool flags, 1 int32 counter. Elements are POD pointers
    // (no per-element destructors called).
    //
    // Organized as 4 S_TargetSlot blocks (opponent tracking slots) plus a
    // trailing pair of vectors. Each slot has 2-3 target lists and an active flag.
    // The opponent manager (C_CombatActorOpponentManager at +0x750) reads/writes
    // the current target from S_CombatActorState (+0xC98/+0xCA0/+0xCA8) and
    // likely populates these slot vectors during target evaluation.
    //
    // Exact per-vector purpose NOT confirmed — reader functions access them
    // through computed pointers that resist static search. Names below are
    // structural (slot + index), not semantic.

    struct S_TargetSlot2 {
        std::vector<I_CombatTarget*> targets;       // primary target list
        std::vector<I_CombatTarget*> candidates;    // candidate/fallback list
        bool                         active;        // slot in use
        uint8_t                      _pad[7];
    };
    static_assert(sizeof(S_TargetSlot2) == 0x38);

    struct S_TargetSlot3 {
        std::vector<I_CombatTarget*> targets;       // primary target list
        std::vector<I_CombatTarget*> secondary;     // secondary list
        std::vector<I_CombatTarget*> tertiary;      // tertiary/history list
        bool                         active;        // slot in use
        uint8_t                      _pad[7];
    };
    static_assert(sizeof(S_TargetSlot3) == 0x50);

    S_TargetSlot2               m_targetSlot0;      // +0x5A0  (2 vectors + bool)
    S_TargetSlot3               m_targetSlot1;      // +0x5D8  (3 vectors + bool)
    S_TargetSlot3               m_targetSlot2;      // +0x628  (3 vectors + bool)
    S_TargetSlot3               m_targetSlot3;      // +0x678  (3 vectors + bool)

    std::vector<I_CombatTarget*> m_targetOverflow0; // +0x6C8
    std::vector<I_CombatTarget*> m_targetOverflow1; // +0x6E0

    int32_t                 m_targetSlotCounter;    // +0x6F8  (init 0)
    uint8_t                 _pad6FC[4];             // +0x6FC

    // +0x700: C_CombatRPG (0x60 bytes)
    // VERIFIED RTTI: sub_1805FCF10 writes C_CombatRPG vftable.
    // Holds RPG tuning curve (skill levels 2/3/4 -> 0.0/0.5/1.0) used by
    // hunt-attack / action probability checks.
    void*                   m_pCombatRPG;           // +0x700  C_CombatRPG

    // +0x708: Action distance check data (0x10 bytes)
    // VERIFIED: alloc 0x10 in sub_1805FDC88, stores {actor_ptr, float 0.3f}
    // then looks up entity bone hash at entity+0x728.
    void*                   m_pActionDistData;      // +0x708

    // +0x710: C_CombatHumanPhysics subsystem (0x18 bytes)
    // VERIFIED: alloc 0x18 in sub_1805FDC88, vtable = C_CombatHumanPhysics.
    void*                   m_pHumanPhysics;        // +0x710  C_CombatHumanPhysics

    // +0x718: Combat state-signal listener (0x20 bytes, NON-polymorphic)
    // VERIFIED: sub_1805FCEBC writes NO vtable — stores {actor, sub-object, 0}
    // and connects callback sub_18054C73C to state signal (state+0x4B8).
    void*                   m_pStateListener718;    // +0x718  (sub_1805FCEBC, 0x20 bytes)

    // +0x720: C_CombatActorActionManager (0x60 bytes)
    // VERIFIED: created in sub_1805FDC88 via sub_1805FD39C.
    // This is the ACTION MANAGER that owns attack + perfect block factories.
    // The chain *(*(actor+0x720)+0x50) resolves to m_pAttackFactory.
    // Constructor is the C_CombatActorActionManager ctor (sub_1805FD39C).
    class C_CombatActorActionManager* m_pActionManager; // +0x720  (sub_1805FD39C, 0x60 bytes)

    // +0x728: C_CombatComboManager (0x230 bytes)
    // VERIFIED: created in sub_1805FDC88 via sub_1804F1300.
    // RTTI vtable: wh::combatmodule::C_CombatComboManager
    // Manages combo slots, combo state machine, AND action transitions.
    // Contains 7 signals (+0x18..+0x168), transition rules at +0x1B0
    // (via sub_1806024EC), and connects to 7 state signals + 1 actor signal.
    // Subsystem ID: COMBAT_SUB_COMBO_MANAGER (0x10)
    C_CombatComboManager*   m_pComboManager;        // +0x728  (0x230 bytes)

    // +0x730: C_CombatActorOpponentManager (0x40 bytes)
    // VERIFIED RTTI: sub_1805FD660 writes C_CombatActorOpponentManager vftable.
    void*                   m_pOpponentManager;     // +0x730  C_CombatActorOpponentManager

    // +0x738: C_CombatActorTimeCop (0x78 bytes)
    // VERIFIED RTTI: sub_1805FD6D4 writes C_CombatActorTimeCop vftable.
    void*                   m_pTimeCop;             // +0x738  C_CombatActorTimeCop

    // +0x740: C_CombatActorTimewarp (0x40 bytes)
    // VERIFIED RTTI: sub_1805FD784 writes C_CombatActorTimewarp vftable.
    void*                   m_pTimewarp;            // +0x740  C_CombatActorTimewarp

    // +0x748: C_CombatActorNextGuardSelector (0x20 bytes)
    // VERIFIED RTTI: sub_1805FD9C8 writes C_CombatActorNextGuardSelector vftable.
    void*                   m_pNextGuardSelector;   // +0x748  C_CombatActorNextGuardSelector

    // +0x750: C_CombatActorStealth (0x80 bytes)
    // VERIFIED RTTI: sub_1805FD7C8 writes C_CombatActorStealth vftable.
    void*                   m_pStealth;             // +0x750  C_CombatActorStealth

    // +0x758: C_CombatActorHorsePullDown (0x20 bytes, subsystem 0x1B "HORSE_PULLDOWN")
    // VERIFIED RTTI: sub_1805FD884 writes C_CombatActorHorsePullDown vftable
    //   (primary 0x1821CB328, secondary I_CombatActorHorsePullDown 0x1821CB360).
    C_CombatActorHorsePullDown* m_pHorsePullDown;   // +0x758

    // +0x760: C_CombatActorMercyKill (0x20 bytes, subsystem 0x1D "MERCY_KILL")
    // VERIFIED RTTI: sub_1805FD8B8 writes C_CombatActorMercyKill vftable.
    //   primary 0x1821CB3D8, secondary 0x1821CB410 (I_CombatActorMercyKill):
    //   [0] dtor [1] CanMercyKill [2] RequestMercyKill
    C_CombatActorMercyKill*     m_pMercyKillSubsystem; // +0x760

    // +0x768: Combat hunt attack subsystem (0x20 bytes)
    // VERIFIED: created in sub_1805FDC88 via sub_1805FD924, alloc 0x20.
    // VERIFIED vtable 0x1821CB3B8 (I_CombatActorHuntAttack):
    //   [0] dtor  [1] TryHuntAttack (sub_180639804)  [2] Request (sub_18063A428)
    C_CombatActorHuntAttack* m_pHuntAttackSubsystem; // +0x768  C_CombatActorHuntAttack

    uint16_t                m_flags770;             // +0x770  (init 0x101)
    uint8_t                 _pad772[2];             // +0x772
    uint32_t                m_unknown774;           // +0x774  (init 0)
    uint64_t                m_unknown778;           // +0x778  (init 0)
};
static_assert(sizeof(C_CombatActor) == 0x780, "C_CombatActor must be 0x780 bytes");

}  // namespace wh::combatmodule
