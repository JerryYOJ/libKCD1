#pragma once

#include <cstdint>
#include <functional>            // ForEach collector
#include <vector>               // point-query out vector
#include "../framework/WUID.h"  // ResolveWuid key
// Vec3 comes from the PCH prelude (Cry_Math.h).

// ===========================================================================
// wh::xgenaimodule::I_SmartAreaManager  -  C_SmartAreaManager primary interface.
// ===========================================================================
// RTTI: .?AVC_SmartAreaManager@xgenaimodule@wh@@ family. Primary base of C_SmartAreaManager (+0x00).
// Vtable 0x1827045e8, 16 slots (bounded by the next base COL). PURE interface (sizeof 0x08). NOT
// interfuscated (wh:: type -> canonical order). All 16 slots VERIFIED by decompile (byte-read vtable).
//
// The manager is the WUID(type 7 = SmartArea) registry (its +0xA0 unordered_map<uint64,C_SmartArea*>).
// Its spatial point query (slot 5) does NOT own a grid -- it delegates to the PROCESS-GLOBAL
// wh::shared::C_RegularGrid (holder qword_1835012A8, getter sub_180498DE8). Singleton instance =
// *qword_183785A20 (getter sub_180705E80). See C_SmartAreaManager.h for the concrete data layout.
// ===========================================================================

namespace wh::xgenaimodule {

class C_SmartArea;

class I_SmartAreaManager {
public:
    // [0]  0x00  per-frame update; logs "SmartArea::Update"; drives the +0x190 scheduler (sub_18039D948)
    virtual void Update(float dt, char a3, char a4) = 0;
    // [1]  0x08  single best C_SmartArea at a point via the GLOBAL grid (sub_180498bac -> sub_180375964)
    virtual C_SmartArea* QueryBestAreaAtPoint(const Vec3& pt) = 0;
    // [2]  0x10  resolve a SmartArea WUID -> C_SmartArea* via the +0xA0 registry (sub_180498a38)
    virtual C_SmartArea* ResolveWuid(const wh::framework::WUID& key) = 0;
    // [3]  0x18  single best area at a point (variant) via the GLOBAL grid (sub_180498b50 -> sub_180498CA8)
    virtual C_SmartArea* QueryBestAreaAtPoint2(const Vec3& pt) = 0;
    // [4]  0x20  ResolveWuid (thunk -> slot[2] impl sub_180498a38) (sub_180498a30)
    virtual C_SmartArea* ResolveWuid2(const wh::framework::WUID& key) = 0;
    // [5]  0x28  POINT QUERY: all C_SmartArea(s) containing `pt`, via the GLOBAL grid (sub_180208bd4 ->
    //            sub_180498DE8 then sub_1803756D8). THIS backs C_RPGLocationManager's "where am I".
    virtual void EnumerateAreasAtPoint(const Vec3& pt, std::vector<C_SmartArea*>& out) = 0;
    // [6]  0x30  collect all registered SmartAreas (walks the +0xA0 map) (sub_1815e9174)
    virtual void GetAllSmartAreas(std::vector<C_SmartArea*>& out) = 0;
    // [7]  0x38  invoke `fn` for each SmartArea (its I_Area sub-object) (sub_1815e8d24)
    virtual void ForEach(std::function<void(C_SmartArea*)>& fn) = 0;
    // [8]  0x40  find-by-name helper (re-fetches singleton; strcmp name) (sub_1815e9644) [INFERRED]
    virtual C_SmartArea* FindByName(const char* name) = 0;
    virtual void _vf9()  = 0;   // [9]  0x48  sub_180705df0 (8-byte stub) [UNVERIFIED]
    // [10] 0x50  pause/resume the +0x190 update scheduler (sub_18039d8f0 -> sub_18039A57C / sub_18039CE6C)
    virtual void SetUpdatePaused(bool paused) = 0;
    // [11] 0x58  connect/add a listener delegate to the area-changed C_Signal @+0x480 (sub_180427278 ->
    //            sub_1804272A4: dedup + append {invoke,instance} to the delegate vector @+0x490)
    virtual void ConnectAreaChanged(void* delegate) = 0;
    virtual void _vf12() = 0;   // [12] 0x60  area-changed C_Signal op (sub_18042724c) -- likely disconnect [UNVERIFIED]
    // [13] 0x68  EMIT/broadcast the area-changed signal (sub_18067c918 -> sub_18067C924: walks the delegate
    //            vector @+0x490, invokes each, using the reentrancy slots @+0x4A8/+0x4AC). C_SmartArea calls
    //            this (via mgr vtbl+0x68) on a tag change to notify all listeners.
    virtual void NotifyAreaChanged(C_SmartArea& area, CryStringT<char> const& tag, bool added) = 0;
    // [14] 0x70  reset all areas (iterates the +0xA0 map twice: sub_1815DD4A0 + sub_1815E9AA0) (sub_1815eb070)
    virtual void ResetAllAreas() = 0;
    virtual void _vf15() = 0;   // [15] 0x78  sub_180706370 (7-byte stub) [UNVERIFIED]
};
static_assert(sizeof(I_SmartAreaManager) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::xgenaimodule
