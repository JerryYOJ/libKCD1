#pragma once

// -----------------------------------------------
// I3DEngine — Binary vtable order (INTERFUSCATED: <interfuscator:shuffle>)
// -----------------------------------------------
// SDK: CryEngine CryCommon/I3DEngine.h (struct I3DEngine : public IProcess).
// I3DEngine carries <interfuscator:shuffle> -> retail slot order is SCRAMBLED
// vs the SDK declaration order. Do NOT assume a named SDK method at index N
// in the SDK header maps to slot N here.
//
// Implementation: C3DEngine, primary vtable @ 0x1827160a8 (??_7C3DEngine@@6B@).
// RTTI: .?AVC3DEngine@@ (type descriptor 0x182b3aaf0).
//
// ACCESS: gEnv.p3DEngine (+0x08) is a DEAD SLOT in KCD (always null).
//         Use Offsets::Get3DEngine() which reads the Cry3DEngineBase static
//         C3DEngine* at qword_183785BC0 (RVA 0x3785BC0), set in the ctor.
//
// Slot identification methodology: 88 entries read from the vtable, each
// looked up in IDA (function name/size), decompiled where tractable, and
// matched to SDK I3DEngine methods by signature shape, string references,
// CScriptBind callers, and field-access patterns.
//
// Confidence tags:
//   VERIFIED  — confirmed by independent evidence (scriptbind, /FA, live test)
//   high      — strong match (string ref, unique signature shape)
//   medium    — plausible match (field offsets, param count, return type)
//   low       — weak match (similar shape but could be another method)
//   (no tag)  — unidentified; placeholder _vfNN preserved

namespace Offsets {

struct I3DEngine {
    virtual void Dtor(unsigned int flags) = 0;                                   // [0]  0x000  sub_1816B91E8  VERIFIED: scalar deleting dtor
    virtual void _vf01() = 0;                                                    // [1]  0x008  sub_1816C3704
    virtual void _vf02() = 0;                                                    // [2]  0x010  sub_1803836B4
    virtual void _vf03() = 0;                                                    // [3]  0x018  sub_1803E3CE8
    virtual void _vf04() = 0;                                                    // [4]  0x020  sub_1816D540C
    virtual void SetFlags(int flags) = 0;                                        // [5]  0x028  sub_1807053B0  high: IProcess::SetFlags — stores flags
    virtual int  GetFlags() = 0;                                                 // [6]  0x030  sub_1806F99E0  high: IProcess::GetFlags — returns flags
    virtual void SetLevelPath(const char* szFolderName) = 0;                     // [7]  0x038  sub_1816D3A40  high: string path copy into engine
    virtual void _vf08() = 0;                                                    // [8]  0x040  sub_180645394  low: SetCamera candidate (CCamera&)
    virtual void _vf09() = 0;                                                    // [9]  0x048  sub_180651484
    virtual void _vf10() = 0;                                                    // [10] 0x050  sub_1816C8210
    virtual void _vf11() = 0;                                                    // [11] 0x058  sub_1816C39D8
    virtual void _vf12() = 0;                                                    // [12] 0x060  sub_1803DB80C
    virtual void _vf13() = 0;                                                    // [13] 0x068  sub_1816CBFD8
    virtual void _vf14() = 0;                                                    // [14] 0x070  sub_1816CC134
    virtual void _vf15() = 0;                                                    // [15] 0x078  sub_1816D5C28
    virtual void* _vf16() = 0;                                                   // [16] 0x080  sub_1806FF460  returns this+0x690
    virtual float _vf17() = 0;                                                   // [17] 0x088  sub_180706F50  returns *(float*)(this+0x680)
    virtual float _vf18() = 0;                                                   // [18] 0x090  sub_180706F70  returns (float)*(uint8*)(this+0x688)
    virtual bool  _vf19() = 0;                                                   // [19] 0x098  sub_1806CF380  returns *(uint8*)(global+0x2A1)
    virtual unsigned __int64 _vf20() = 0;                                        // [20] 0x0A0  sub_1803838FC
    virtual void _vf21() = 0;                                                    // [21] 0x0A8  sub_1816D72BC
    virtual void FreeRenderNodeState(void* pRenderNode) = 0;                     // [22] 0x0B0  sub_1816CEA98  low: frees render-node state
    virtual void _vf23() = 0;                                                    // [23] 0x0B8  sub_1803E3878
    virtual void _vf24() = 0;                                                    // [24] 0x0C0  sub_1803E3F4C
    virtual void _vf25() = 0;                                                    // [25] 0x0C8  sub_1816CA030
    virtual void _vf26() = 0;                                                    // [26] 0x0D0  sub_180401240
    virtual void _vf27(void* a2) = 0;                                            // [27] 0x0D8  sub_1816CF88C  forwards to sub_1803A5DB4(this+0xF20, a2)
    virtual void* _vf28(const char* a2) = 0;                                     // [28] 0x0E0  sub_1816BEC50  string arg, checks non-empty
    virtual void _vf29() = 0;                                                    // [29] 0x0E8  sub_1802A28E0  zeros this+0x2E0..0x2E1
    virtual int  GetLoadedObjectCount() = 0;                                     // [30] 0x0F0  sub_1816C19E0  low: returns this+0x40 + CharMgr stats
    virtual void _vf31(void* a2, unsigned int* a3) = 0;                          // [31] 0x0F8  sub_1816C1A40  outputs to *a3
    virtual void _vf32(void* outStruct) = 0;                                     // [32] 0x100  sub_1816C2974  fills 0x1C-byte output struct
    virtual void _vf33(int type, void* a3) = 0;                                  // [33] 0x108  sub_1816C3168  type==1 -> renderer vtable call
    virtual void _vf34(int a2, int a3) = 0;                                      // [34] 0x110  sub_180374A38  CritSec@+0x12028, calls sub_180374B20
    virtual void RegisterEntity(void* pRenderNode) = 0;                          // [35] 0x118  sub_1816CE8B4  medium: sets flags 0x100/0x80000000, calls [34]
    virtual void SelectEntity(void* pRenderNode) = 0;                            // [36] 0x120  sub_1806C6F0C  low: timer-based flag 0x200 swap
    virtual void _vf37() = 0;                                                    // [37] 0x128  sub_180472E00
    virtual void UnRegisterEntityDirect(void* pRenderNode) = 0;                  // [38] 0x130  sub_1804BF66C  low: direct call to sub_180374B20
    virtual void _vf39() = 0;                                                    // [39] 0x138  sub_1816C5224
    virtual void _vf40(char a2) = 0;                                             // [40] 0x140  sub_1816D49B0  indexes gEnv._unk170 by this+0x10
    virtual bool _vf41() = 0;                                                    // [41] 0x148  sub_1803D14A0  returns byte at this+0xD50
    virtual int  _vf42() = 0;                                                    // [42] 0x150  sub_180706E70  returns global dword_182B7C1A8
    virtual void _vf43(void* a2, void* a3) = 0;                                  // [43] 0x158  sub_1816C10B4  forwards to self vtable[45]
    virtual float GetBottomLevel(const Vec3& pos, float maxDepth) = 0;           // [44] 0x160  sub_1816C10CC  medium: 2-arg water bottom level
    virtual float GetBottomLevel3(const Vec3& pos, float maxDepth, int objTypes) = 0; // [45] 0x168  sub_1816C10DC  medium: 3-arg overload
    virtual void _vf46() = 0;                                                    // [46] 0x170  sub_180312D9C
    virtual float GetWaterLevel() = 0;                                           // [47] 0x178  sub_180375D7C  high: water level getter
    virtual void _vf48() = 0;                                                    // [48] 0x180  sub_1816C0D30
    virtual void _vf49() = 0;                                                    // [49] 0x188  sub_1803D2AE0  Vec3 getter from this+0x29C/0x2A0/0x2A8
    virtual void _vf50() = 0;                                                    // [50] 0x190  sub_18068C3D0  Vec4 getter from this+0x2AC..0x2B4
    virtual void _vf51() = 0;                                                    // [51] 0x198  sub_1802A0E8C
    virtual void _vf52() = 0;                                                    // [52] 0x1A0  sub_18029F4DC
    virtual void _vf53() = 0;                                                    // [53] 0x1A8  sub_1816CF96C
    virtual void _vf54() = 0;                                                    // [54] 0x1B0  sub_1804D3EAC
    virtual void _vf55() = 0;                                                    // [55] 0x1B8  sub_1816BDC1C  checks qword_183785C48, calls sub_1816DE53C
    virtual void _vf56(const Vec3& pos) = 0;                                     // [56] 0x1C0  sub_1816D4D14  terrain dispatch via gEnv._unk170
    virtual void _vf57() = 0;                                                    // [57] 0x1C8  sub_18046A9EC
    virtual void _vf58(float value) = 0;                                         // [58] 0x1D0  sub_18046AA3C  terrain dispatch with float
    virtual float _vf59() = 0;                                                   // [59] 0x1D8  sub_180706F00  returns *(float*)(qword_182F97AD8+0x98)
    virtual void* _vf60(void* a2) = 0;                                           // [60] 0x1E0  sub_1802AF154  creates 280-byte stack obj
    virtual void _vf61() = 0;                                                    // [61] 0x1E8  sub_18037F5A8
    virtual void _vf62(const void* floats5) = 0;                                 // [62] 0x1F0  sub_1816D3AEC  terrain dispatch with 5 floats
    virtual bool _vf63(void* outData) = 0;                                       // [63] 0x1F8  sub_1803D1B58  reads 16 bytes from qword_182F97AD8+0x1F4
    virtual void* _vf64() = 0;                                                   // [64] 0x200  sub_1816C19CC  delegates to renderer vtable[0x518/8]
    virtual void _vf65(const Vec3& pos, float a3, float a4, float a5, float a6) = 0; // [65] 0x208  sub_1816D4DE4  terrain dispatch
    virtual bool GetSkyLightParameters(Vec3& sunColor, float& Km, float* moonR, float* moonG, float* moonB) = 0; // [66] 0x210  sub_18037F754  medium
    virtual void _vf67(int type, float f1, float f2, float f3, float f4, float f5, float f6) = 0; // [67] 0x218  sub_1816D4D70  terrain call
    virtual bool _vf68(float* out7floats) = 0;                                   // [68] 0x220  sub_18037F7D0  reads terrain+0x1D8..0x1F4
    virtual void _vf69(float value) = 0;                                         // [69] 0x228  sub_180707010  sets this+0x58 = value
    virtual float GetMaxViewDistance(bool bScaled = true) = 0;                   // [70] 0x230  sub_1802F4508  medium: complex distance/fog calc
    virtual void _vf71() = 0;                                                    // [71] 0x238  sub_1816C13BC
    virtual void* _vf72() = 0;                                                   // [72] 0x240  sub_1803FD540  returns ptr to this+0xE48
    virtual void _vf73(const Vec3& pos) = 0;                                     // [73] 0x248  sub_180382F38  compares pos vs this+0xE4C/0xE50
    virtual void _vf74() = 0;                                                    // [74] 0x250  sub_18046AAAC
    virtual Vec3 GetSunDir() const = 0;                                          // [75] 0x258  sub_1803D1DE0  medium: returns Vec3 from this+0xA0..0xA8
    virtual void _vf76() = 0;                                                    // [76] 0x260  sub_1816C2D0C
    virtual void _vf77() = 0;                                                    // [77] 0x268  sub_18046AAFC
    virtual float _vf78() = 0;                                                   // [78] 0x270  sub_180706E30  returns *(float*)(this+0x900)
    virtual bool _vf79(void* pNode, void* pInfo, bool bFullUpdate) = 0;          // [79] 0x278  sub_180333EA8  visibility/LOD check
    virtual void _vf80(int type, const Vec3& pos, void* pMat) = 0;              // [80] 0x280  sub_1816D4B00  AABB query + set material; "Game changed render node material"
    virtual void SetWind(const Vec3& wind) = 0;                                  // [81] 0x288  sub_1816CB4C0  medium: copies Vec3 into terrain+0x380
    virtual void _vf82(void* outBuf, const Vec3& boxMin, const Vec3& boxMax, int f1, int f2) = 0; // [82] 0x290  sub_1816B9EB8
    virtual void _vf83(int param) = 0;                                           // [83] 0x298  sub_1816BBE20  terrain dispatch
    virtual void* _vf84() = 0;                                                   // [84] 0x2A0  sub_1816BBD88  terrain dispatch
    virtual void GetTerrainSize(int* pnSizeX, int* pnSizeY) = 0;                // [85] 0x2A8  sub_1816C2AD8  low: reads two global DWORDs from terrain obj
    virtual int  _vf86(int a1, int a2, int a3) = 0;                              // [86] 0x2B0  sub_1804CD5D4  forwards 3 args to sub_1804CD5E8

    // VERIFIED also via CScriptBind_System::GetTerrainElevation (sub_182131A5C).
    // Impl 0x180404DF0: if (g_pTerrain==0) return 0.0f; else bilinear heightmap interp.
    // RETURNS 0.0f when no terrain loaded OR (x,y) off heightmap — NOT a sentinel.
    virtual float GetTerrainElevation(float x, float y, int nSID = 0) = 0;       // [87] 0x2B8
};

}  // namespace Offsets
