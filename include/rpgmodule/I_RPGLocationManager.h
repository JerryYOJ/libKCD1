#pragma once

#include <cstdint>
#include <functional>            // std::function collector (EnumerateLocationsAtPoint)
#include <vector>                // std::vector<I_Location*> collectors (GetAll*/FindPOIs*)

#include "../framework/WUID.h"   // wh::framework::WUID (GetOrCreateLocationByKey)
// Vec3 is provided by the PCH prelude (Cry_Math.h), as in I_Location.h.

// ===========================================================================
// wh::rpgmodule::I_RPGLocationManager  -  C_RPGLocationManager primary interface.
// ===========================================================================
// RTTI: .?AVI_RPGLocationManager@rpgmodule@wh@@   (TD 0x182a62030 / img 0x2A62030)
// Primary base of C_RPGLocationManager (+0x00). PURE interface (sizeof 0x08).
// Primary vtable: 0x1826d3c30. Slot 0 is the (scalar-deleting) destructor.
// All 40 slots verified by decompile (a location + POI registry); a few leaf semantics [INFERRED]. NOT interfuscated
// (wh:: type -> canonical order). Vtable extends beyond slot [39].
// ===========================================================================

namespace wh::rpgmodule {

class I_Location;          // returned by GetOrCreateLocationByKey
// (slot[3] takes a Vec3 point + a std::function collector -- there is no S_LocationArea type.)

class I_RPGLocationManager {
public:
    virtual ~I_RPGLocationManager() = 0;   // [0]  0x00  dtor (sub_1811A2DEC)
    virtual void SetStateFlag(uint8_t mask, bool set) = 0;  // [1]  0x08  m_state(+0x10) |= mask / &= ~mask (sub_1811938DC)
    virtual bool IsSuspended() = 0;                         // [2]  0x10  C_FastTravel::IsFastTravelling || m_state!=0 (sub_1803DBDF0)
    // [3]  0x18  EnumerateLocationsAtPoint: invoke `outCollector` for every I_Location whose SmartArea
    //      contains `point`. VERIFIED sub_1802088F4: asks the SmartArea manager (qword_183785A20, WUID
    //      type 7 = SmartArea) for the C_SmartArea(s) at `point` (its regular-grid query, vtbl+0x28), then
    //      maps each area's key -> location via the +0x138 (area-key -> guid) map + GetOrCreateLocationByKey[8].
    //      THIS is the engine's "which location(s) am I in" query (wh_rpg_getLocation, no -radius arg).
    virtual void EnumerateLocationsAtPoint(const Vec3& point,
                                           std::function<void(I_Location*)>& outCollector) = 0;
    // [4]  0x20  EnumerateLocationsById: collect locations by int id via the id-index (mgr+0x1F8) into a
    //      std::function collector (sub_181197DE4). The wh_rpg_getLocation -radius path. [arg shape INFERRED]
    virtual void EnumerateLocationsById(const int32_t* id, int count,
                                        std::function<void(I_Location*)>& outCollector) = 0;
    virtual void GetAllLocations(std::vector<I_Location*>& out) = 0;    // [5] 0x28  walk m_locationsByGuid (sub_181197D58)
    virtual I_Location* GetOrCreateLocationForKey(const void* key) = 0; // [6] 0x30  build guid (sub_1806D130C) -> [8] (sub_181197C10)
    virtual I_Location* FindLocationByName(const char* name) = 0;       // [7] 0x38  case-insensitive name scan (sub_181197C5C)
    // [8]  0x40  get-or-create the C_RPGLocation for a WUID key, return its I_Location* [CONFIRMED sub_180208C40 -> sub_180208CA8]
    virtual I_Location* GetOrCreateLocationByKey(const wh::framework::WUID& key) = 0;
    virtual I_Location* CreatePOIVariant(const void* guid, int, int, int, int) = 0; // [9]  0x48  -> sub_1811934B4 [INFERRED POI create]
    virtual I_Location* GetOrCreatePOIByGuid(const void* guid, int kind) = 0;        // [10] 0x50  -> sub_181193694 (sub_181193844)
    virtual bool        RemovePOIByGuid(const void* guid) = 0;                       // [11] 0x58  erase m_poisByGuid + spatial (sub_1811A2C48)
    virtual I_Location* FindPOIByGuid(const void* guid) = 0;                         // [12] 0x60  lookup m_poisByGuid (sub_1811989AC)
    virtual bool        HasLocationForKey(const void* guid) = 0;                     // [13] 0x68  slot[41] resolve + sub_181199BF8 (sub_181199BAC) [INFERRED]
    virtual int         _vf14_poiGuidSetOp() = 0;                                    // [14] 0x70  op over m_poiGuidSet(+0xB0) (sub_18116FEEC) [INFERRED count/clear]
    virtual float       GetDefaultPOIRadius() = 0;                                   // [15] 0x78  returns const 20.0f (sub_1806FF200)
    virtual int         FindPOIsInSphere(const Vec3& c, float r, std::vector<I_Location*>& out) = 0; // [16] 0x80 spatial +0x58 (sub_181198AD4)
    virtual int         FindPOIsAtPoint(const Vec3& c, std::vector<I_Location*>& out) = 0;           // [17] 0x88 spatial +0x58, vtbl+0xC8 filter (sub_18069FB90)
    virtual int         GetAllPOIs(std::vector<I_Location*>& out) = 0;               // [18] 0x90  walk m_poisByGuid (sub_181198A5C)
    virtual int         ForEachPOIInSphere(const Vec3& c, float r, void* cb, void* ctx) = 0;         // [19] 0x98 (sub_1806F3298)
    virtual int         FindPOIsWhere(std::vector<I_Location*>& out, const void* pred) = 0;          // [20] 0xA0 filter sub_18069F9A0 (sub_1811994C4)
    virtual void        VisitSpatialPOIs() = 0;                                      // [21] 0xA8  over +0x58 (sub_181198C9C) [INFERRED]
    virtual void        ForEachPOIInSphere2(const Vec3& c, float r, void* cb) = 0;   // [22] 0xB0 (sub_181198CD0)
    virtual int         CountLocationsWhere() = 0;                                   // [23] 0xB8  loc vtbl+0x68 predicate (sub_1811977BC)
    virtual int         GetPOIsWithFlag(std::vector<I_Location*>& out) = 0;          // [24] 0xC0  poi flags&2 via vtbl+0x60 (sub_1811979D4)
    virtual int         CountMapMarkers() = 0;                                       // [25] 0xC8  flags&2 && discovered && !0x20 (sub_181197748)
    virtual int         ForEachPOI(const void* pred) = 0;                            // [26] 0xD0  std::function<bool(I_POI&)> -> sub_1811A29A0 (sub_1811907E0) [INFERRED]
    virtual int         QueryPOIsRegion(const void* query, void* out) = 0;           // [27] 0xD8  spatial sub_18069FD54 (sub_18119E128)
    virtual bool        GetLocationPosition(const void* guid, Vec3& out) = 0;        // [28] 0xE0  location GetPosition by guid (sub_181197CC8)
    virtual I_Location* SetLocationDiscovered(const void* guid, int, bool) = 0;      // [29] 0xE8  get-or-create + SmartArea listener notify (sub_181193CE8) [INFERRED]
    virtual void        SetPOIFlags(const void* guid, char a, char b) = 0;          // [30] 0xF0  -> sub_18069F924 (sub_181193F58)
    virtual void        SetPOIGroup(const void* guid, const void* group) = 0;        // [31] 0xF8  update m_poisByGroup(+0x70) (sub_1811A43CC)
    virtual I_Location* AddPOI(const void* guid, const void* a3, const Vec3& pos, float radius, int type, const void* group) = 0; // [32] 0x100 alloc 0x90 C_POI + spatial + group (sub_1811A60D0)
    virtual bool        RegisterLocationKey(const wh::framework::WUID& key, int64_t guid) = 0; // [33] 0x108 m_idToGuid/m_guidToId insert; dirty +0x268 (sub_181192FA8)
    virtual void        UnregisterLocationKey(const wh::framework::WUID& key) = 0;   // [34] 0x110 erase from id-maps; dirty (sub_1811938F0)
    virtual I_Location* GetSpecialLocationA() = 0;                                   // [35] 0x118 get-or-create guid @manager+0x248 (sub_181197660)
    virtual I_Location* GetSpecialLocationB() = 0;                                   // [36] 0x120 get-or-create guid @manager+0x258 (sub_1811976AC)
    virtual void        AddListener(void* listener) = 0;                            // [37] 0x128 push to m_listeners(+0x270); I_LocationListener (sub_1806CB684)
    // [38] 0x130  remove a listener from the change-notify vector (+0x270) [CONFIRMED sub_1806BD5F8]
    virtual void RemoveListener(void* listener) = 0;
    virtual void _vf39() = 0;   // [39] 0x138 -> sub_1811A434C(arg, true) (sub_18119C448); POI/location op [INFERRED]
};
static_assert(sizeof(I_RPGLocationManager) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::rpgmodule
