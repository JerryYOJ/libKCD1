#pragma once

#include <cstdint>

#include "E_CrimeIconLevel.h"
#include "../framework/WUID.h"     // wh::framework::WUID (GetKey return)
// Vec3 is provided by the PCH prelude (CryEngine/CryCommon/Cry_Math.h, included by kcd.h/PCH.h).

// ===========================================================================
// wh::rpgmodule::I_Location  -  the crime/RPG "location" interface.
// ===========================================================================
// RTTI: .?AVI_Location@rpgmodule@wh@@  (TD img 0x2A672B0)
// Second base of C_RPGLocation (at C_RPGLocation+0x10). PURE interface: it owns NO
// data of its own (sizeof 0x08, vtable only) -- the concrete fields live in
// C_RPGLocation (see C_RPGLocation.h). The runtime "location" object handed out by
// C_RPGLocationManager (slot[8]/+0x40) is this I_Location subobject.
//
// Vtable (C_RPGLocation I_Location subobject): 0x182307180 (COL 0x182307178),
// 28 slots (0x00..0xD8; next COL at +0xE0). NOT interfuscated (wh:: type ->
// canonical declaration order, slots trustworthy). There is NO virtual dtor in this
// vtable -- slot 0 is GetKey; destruction is handled by the _reference_target primary
// base (C_RPGLocation+0x00).  Member methods reach the C_RPGLocation fields via
// `this` = I_Location* = C_RPGLocation+0x10 (e.g. GetOwnWantedLevel reads this+0x20
// = C_RPGLocation+0x30).
// ===========================================================================

namespace wh::rpgmodule {

class I_Location {
public:
    // [0]  0x00  this location's key/WUID (delegates to C_RPGLocation::m_pIdentitySource->slot0) [CONFIRMED sub_1804989B8]
    virtual wh::framework::WUID GetKey() = 0;
    virtual void _vf1()  = 0;   // [1]  0x08  sub_1804ACC24 (= C_CombatTarget::GetEntityId; likely GetEntityId) [UNVERIFIED]
    virtual void _vf2()  = 0;   // [2]  0x10  sub_1804ACC18 [UNVERIFIED]
    virtual void _vf3()  = 0;   // [3]  0x18  sub_1811C0B9C [UNVERIFIED]
    virtual void _vf4()  = 0;   // [4]  0x20  sub_18067D234 [UNVERIFIED]
    virtual void _vf5()  = 0;   // [5]  0x28  sub_18024DE04 [UNVERIFIED]
    virtual void _vf6()  = 0;   // [6]  0x30  sub_180641B30 [UNVERIFIED]
    virtual void _vf7()  = 0;   // [7]  0x38  sub_1805BD320 [UNVERIFIED]
    virtual void _vf8()  = 0;   // [8]  0x40  sub_1811BFBC0 [UNVERIFIED]
    virtual void _vf9()  = 0;   // [9]  0x48  sub_1811C2AE4 [UNVERIFIED]
    virtual void _vf10() = 0;   // [10] 0x50  sub_1806F8F70 [UNVERIFIED]
    virtual void _vf11() = 0;   // [11] 0x58  sub_1806FF630 [UNVERIFIED]
    virtual void _vf12() = 0;   // [12] 0x60  sub_1811C5DFC [UNVERIFIED]
    virtual void _vf13() = 0;   // [13] 0x68  sub_1811C5974 [UNVERIFIED]
    // [14] 0x70  parent location: resolve self via manager, walk parent-chain @node+0x238 [CONFIRMED sub_18049889C]
    virtual I_Location* GetParent() = 0;
    virtual void _vf15() = 0;   // [15] 0x78  sub_1811C59FC [UNVERIFIED]
    // [16] 0x80  world position: override Vec3 if non-zero, else center of node AABB [CONFIRMED sub_1811C3238]
    virtual Vec3 GetPosition() = 0;
    virtual void _vf17() = 0;   // [17] 0x88  sub_1806FF620 [UNVERIFIED]
    // [18] 0x90  reputation = average over the member factions [CONFIRMED sub_1811C36BC]
    virtual float GetReputation() = 0;
    // [19] 0x98  aggregate "wanted by any member faction" predicate [INFERRED sub_1811C45F4]
    virtual bool GetFactionWanted() = 0;
    virtual void _vf20() = 0;   // [20] 0xA0  sub_1811C4168 [UNVERIFIED]
    // [21] 0xA8  effective wanted level = max(own, parent->GetWantedLevel) [CONFIRMED sub_180498864]
    virtual E_CrimeIconLevel GetWantedLevel() = 0;
    // [22] 0xB0  own wanted level = *(this+0x20) (C_RPGLocation::m_selfWantedLevel) [CONFIRMED sub_1806F8600]
    virtual E_CrimeIconLevel GetOwnWantedLevel() = 0;
    // [23] 0xB8  set own wanted level; on change, notify C_RPGLocationManager listeners [CONFIRMED sub_18027CFC4]
    virtual void SetWantedLevel(E_CrimeIconLevel level) = 0;
    virtual void _vf24() = 0;   // [24] 0xC0  sub_1806D15BC [UNVERIFIED]
    virtual void _vf25() = 0;   // [25] 0xC8  sub_1806FF5E0 [UNVERIFIED]
    virtual void _vf26() = 0;   // [26] 0xD0  sub_1811CE1F8 [UNVERIFIED]
    virtual void _vf27() = 0;   // [27] 0xD8  sub_1811CE920 [UNVERIFIED]
};
static_assert(sizeof(I_Location) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::rpgmodule
