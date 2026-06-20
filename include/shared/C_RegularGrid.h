#pragma once

#include <cstdint>
#include <functional>   // the four std::function functors (0x40 each in MSVC, signature-independent)
#include <vector>       // cell vector + deferred vector
// Vec2_tpl<float>/Vec3 come from the PCH prelude (Cry_Math.h).

// ===========================================================================
// wh::shared::C_RegularGrid<T>  -  a flat 2D regular-grid spatial index (size 0x178).
// ===========================================================================
// RTTI: .?AV?$C_RegularGrid@PEAVC_RegularGridCellDummy@shared@wh@@@shared@wh@@ (TD 0x182a8af70);
// vtable 0x18231afb8 (3 slots). Polymorphic single-root (primary COL offset 0). NOT interfuscated.
// The layout is uniform across all instantiations (SmartArea, AIObject, PathNode, PerceptibleVolume,
// TriggerArea, ...): cells store an 8-byte element T (a pointer). For SmartAreas the stored object is a
// C_RegularGridObjectWrapper<C_SmartArea, C_RegularGridCellDummy>* that the query unwraps.
//
// Bins objects into a numCellsX x numCellsY grid with implicit origin (0,0): a world XY is divided by
// (cellSizeX,cellSizeY) -> (cellX,cellY); cellIndex = cellX + cellY*numCellsX. Each object stores its own
// {cellX,cellY} (read/written via the F_getObjectCellCoords functor) so Remove is O(1)-ish. cells/cellSizes
// are NOT allocated by the ctor -- SetBounds (sub_1815B1980) sizes the grid from world extents.
//
// SmartArea instance: the process-global holder qword_1835012A8 (lazy getter sub_180498DE8; alloc 0xF0
// holder + this 0x178 grid via sub_1812EA998); grid = *(holder+0x00); dims 128x128. The C_SmartAreaManager
// point query (its vtbl+0x28) reaches it through sub_180498DE8 -> sub_1803756D8(holder, pt, out) -- the
// manager holds NO pointer to the grid. VERIFIED: ctor sub_1812EAEC4; operator new(0x178) at 3 creators.
// ===========================================================================

namespace wh::shared {

class C_RegularGrid {
public:
    // Cell = std::vector<T> (0x18). The grid is a std::vector<Cell> sized numCellsX*numCellsY.
    using Element = void*;                 // T -- an 8-byte object pointer (wrapper / cell-dummy ptr)
    using Cell    = std::vector<Element>;

    // --- vtable 0x18231afb8 (3 slots; wh::shared -> canonical order) ---
    virtual ~C_RegularGrid();                       // [0] 0x00  teardown sub_1812ED454 (+ op delete)
    virtual void Insert(Element obj) = 0;           // [1] 0x08  sub_180214CB4: F_pos -> cell, push, store coords, ++count
    virtual void Remove(Element obj) = 0;           // [2] 0x10  sub_180214BF4: read stored coords, erase from cell, --count

    // --- fields (VERIFIED from ctor sub_1812EAEC4 + Insert/Remove/SetBounds) ---
    // m_getObjectPos: object -> world Vec2(float) (used before binning). m_getObjectCellCoords: object ->
    // its stored Vec2(int) {cellX,cellY} (read & written; {-1,-1} == not yet placed). m_tolerance1/2 are
    // two hard-coded tolerance functors installed by the ctor. (Each std::function is 0x40 in MSVC.)
    std::function<void()> m_getObjectPos;          // +0x08  F_getObjectPos      (Vec2_tpl<float>(T))
    std::function<void()> m_tolerance1;            // +0x48  hard-coded tolerance functor
    std::function<void()> m_tolerance2;            // +0x88  hard-coded tolerance functor (sub_180ABA420)
    std::function<void()> m_getObjectCellCoords;   // +0xC8  F_getObjectCellCoords (Vec2_tpl<int>&(T))

    std::vector<Cell>     m_cells;                  // +0x108 the numCellsX*numCellsY cells (empty until SetBounds)
    float                 m_extentX;               // +0x120 world width  (origin implicit 0; coords clamped [0,extent])
    float                 m_extentY;               // +0x124 world height
    int32_t               m_numCellsX;             // +0x128 ACTIVE column count (row stride in cellIndex)
    int32_t               m_configDimX;            // +0x12C configured dimX (ctor arg; e.g. 128 for SmartAreas)
    int32_t               m_numCellsY;             // +0x130 ACTIVE row count
    int32_t               m_configDimY;            // +0x134 configured dimY (ctor arg)
    int32_t               m_totalCellCount;        // +0x138 numCellsX*numCellsY (SetBounds)
    float                 m_cellSizeX;             // +0x13C extentX/numCellsX (cellX = (int)(x/cellSizeX))
    float                 m_cellSizeY;             // +0x140 extentY/numCellsY
    uint32_t              _pad144;                 // +0x144 alignment

    std::vector<Element>  m_deferred;              // +0x148 objects added before build; re-binned + cleared by SetBounds
    bool                  m_isBuilt;               // +0x160 set 1 by SetBounds
    uint8_t               _pad161[3];              // +0x161
    int32_t               m_objectCount;           // +0x164 ++Insert / --Remove / 0 on SetBounds
    int32_t               m_unk168;                // +0x168 ctor = -1 [UNVERIFIED: cached/min cell idx]
    int32_t               m_unk16C;                // +0x16C ctor = -1 [UNVERIFIED]
    int32_t               m_unk170;                // +0x170 ctor = 0  [UNVERIFIED]
    uint32_t              _pad174;                 // +0x174 trailing pad to 0x178
};
static_assert(sizeof(C_RegularGrid) == 0x178, "C_RegularGrid (operator new 0x178; ctor sub_1812EAEC4)");

}  // namespace wh::shared
