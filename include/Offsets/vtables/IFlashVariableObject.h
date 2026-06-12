#pragma once
#include <cstdint>

// -----------------------------------------------
// IFlashVariableObject — Binary vtable order (INTERFUSCATED)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashPlayer.h (<interfuscator:shuffle> block lines 233-293
//      => binary slot order != SDK declaration order; this replica is BINARY order).
// RTTI: .?AUIFlashVariableObject@@ (global namespace, struct)
// Impl: CFlashVariableObject (.?AVCFlashVariableObject@@), single base at +0x00,
//       vtable 0x1821a30d0 (46 slots == exact SDK method count incl. dtor),
//       sizeof == 0x70 (operator new(0x70) at every creation site:
//       CFlashPlayer::GetVariable/Create*/..., Clone, GetMember, GetElement, ...).
//   Ctor: CFlashVariableObject::Ctor_18020C17C(this, GFxValue* src,
//         sharedFilePath* (player+0xD0), sharedLock* (player+0xF8))
//
// Layout (from ctor + method bodies):
//   +0x00 vfptr                     +0x08 GFxValue m_value { ObjectInterface*@+0x08,
//   type@+0x10, value@+0x18 }       +0x20/+0x28 shared filepath ptr + refholder
//   +0x30 returned-string cache     +0x48/+0x50 CRITICAL_SECTION* + refholder
//   +0x58 global-list node (qword_18300B910) +0x68 owner backptr
//
// GFxValue runtime types observed: 4=string 5=wstring 6=object 7=array 8=displayobject;
// type guards: IsObject (t&0x8F)-6<=2, IsArray ==7, IsDisplayObject ==8. Object ops
// forward to GFxValue::ObjectInterface helpers (movie root, this+0x08) passing the
// raw AS object (this+0x18) and an isDisplayObject flag.

struct SFlashVarValue;
struct SFlashCxform;
struct SFlashDisplayInfo;
template<typename F> struct Matrix33_tpl;
template<typename F> struct Matrix44_tpl;
typedef Matrix33_tpl<float> Matrix33;   // matches CryCommon Cry_Math typedef (f32 == float)
typedef Matrix44_tpl<float> Matrix44;

namespace Offsets {

struct IFlashVariableObject {
    struct ObjectVisitor {            // declared OUTSIDE the SDK shuffle block — order trusted
        virtual void Visit(const char* pName) = 0;       // [0]
    protected:
        virtual ~ObjectVisitor() {}                      // [1]
    };

    // Binary vtable 0x1821a30d0 (46 slots)
    virtual void Release() = 0;                                             // [0]  0x000 sub_18020C22C  vcall self vf+0x168 == slot [45] scalar dtor(1)
    virtual IFlashVariableObject* Clone() const = 0;                        // [1]  0x008 sub_180E6BEFC  operator new(0x70) + copy-ctor sub_180E651D0(new, this)
    virtual bool IsObject() const = 0;                                      // [2]  0x010 sub_180E70F28  (type&0x8F)-6 <= 2  (object/array/displayobject)
    virtual bool IsArray() const = 0;                                       // [3]  0x018 sub_180E70DA8  (type&0x8F) == 7
    virtual bool IsDisplayObject() const = 0;                               // [4]  0x020 sub_18020BC48  (type&0x8F) == 8
    virtual SFlashVarValue ToVarValue() const = 0;                          // [5]  0x028 sub_180E768D8  GFxValue(this+8) -> SFlashVarValue via sub_18020CE4C
    virtual bool HasMember(const char* pMemberName) const = 0;              // [6]  0x030 sub_180E70534  ObjectInterface::HasMember sub_18083C600
    virtual bool SetMember(const char* pMemberName,
                           const IFlashVariableObject* pVarObj) = 0;        // [7]  0x038 sub_180E75794  GFxValue copy from pVarObj+8 (sub_18020C558), nullptr -> undefined; ObjectInterface::SetMember sub_18083C930
    virtual bool SetMember(const char* pMemberName,
                           const SFlashVarValue& value) = 0;                // [8]  0x040 sub_180E756EC  SFlashVarValue -> GFxValue (sub_18020C590); sub_18083C930
    virtual bool GetMember(const char* pMemberName,
                           IFlashVariableObject*& pVarObj) const = 0;       // [9]  0x048 sub_18020AD84  ObjectInterface::GetMember sub_18083C740 + new(0x70) Ctor_18020C17C
    virtual bool GetMember(const char* pMemberName,
                           SFlashVarValue& value) const = 0;                // [10] 0x050 sub_180E6F59C  sub_18083C740 + sub_18020CE4C; (w)string results cached at this+0x30
    virtual void VisitMembers(ObjectVisitor* pVisitor) const = 0;           // [11] 0x058 sub_180E780B8  wraps pVisitor in local adaptor — `CFlashVariableObject::VisitMembers'::VisitorAdaptor::`vftable'; sub_18083CDF0
    virtual bool DeleteMember(const char* pMemberName) = 0;                 // [12] 0x060 sub_180E6E5B4  ObjectInterface::DeleteMember sub_18083CCE0
    virtual bool Invoke(const char* pMethodName, const SFlashVarValue* pArgs,
                        unsigned int numArgs, SFlashVarValue* pResult = 0) = 0; // [13] 0x068 sub_18020C27C  alloca GFxValue[numArgs] from 0x10-stride SFlashVarValue array; ObjectInterface::Invoke sub_18083CA60 (IDA-misnamed "_store_winword")
    virtual unsigned int GetArraySize() const = 0;                          // [14] 0x070 sub_180E6EE60  type==7; ObjectInterface::GetArraySize sub_18083CEF0
    virtual bool SetArraySize(unsigned int size) = 0;                       // [15] 0x078 sub_180E75284  sub_18083CF50
    virtual bool SetElement(unsigned int idx,
                            const IFlashVariableObject* pVarObj) = 0;       // [16] 0x080 sub_180E7558C  sub_18020C558 (null -> undefined); ObjectInterface::SetElement sub_18083D0A0
    virtual bool SetElement(unsigned int idx, const SFlashVarValue& value) = 0; // [17] 0x088 sub_180E754F8  sub_18020C590; sub_18083D0A0
    virtual bool GetElement(unsigned int idx,
                            IFlashVariableObject*& pVarObj) const = 0;      // [18] 0x090 sub_180E6F238  ObjectInterface::GetElement sub_18083CFC0 + new(0x70)
    virtual bool GetElement(unsigned int idx, SFlashVarValue& value) const = 0; // [19] 0x098 sub_180E6F3C0  sub_18083CFC0 + sub_18020CE4C (+string cache)
    virtual bool PushBack(const IFlashVariableObject* pVarObj) = 0;         // [20] 0x0A0 sub_180E73648  sub_18020C558 (null -> undefined); ObjectInterface::PushBack sub_18083D3C0
    virtual bool PushBack(const SFlashVarValue& value) = 0;                 // [21] 0x0A8 sub_180E735C4  sub_18020C590; sub_18083D3C0
    virtual bool PopBack() = 0;                                             // [22] 0x0B0 sub_180E729DC  ObjectInterface::PopBack sub_18083D460(..., 0)
    virtual bool RemoveElements(unsigned int idx, int count = -1) = 0;      // [23] 0x0B8 sub_180E73C7C  ObjectInterface::RemoveElements sub_18083D540(idx, count)
    virtual bool SetDisplayInfo(const SFlashDisplayInfo& info) = 0;         // [24] 0x0C0 sub_18020B0E8  reads exact SFlashDisplayInfo layout (x@0 y@4 z@8 ... alpha@0x24 visible@0x28 m_varsSet@0x2A), remaps FDIF_* bits, ObjectInterface::SetDisplayInfo sub_18083D930
    virtual bool GetDisplayInfo(SFlashDisplayInfo& info) const = 0;         // [25] 0x0C8 sub_18020B32C  ObjectInterface::GetDisplayInfo sub_18083D650, inverse bit/field mapping
    virtual bool SetDisplayMatrix(const Matrix33& mat) = 0;                 // [26] 0x0D0 sub_180E75454  copies 6 floats (2x3 affine) -> GMatrix2D; ObjectInterface::SetDisplayMatrix sub_18083E4A0
    virtual bool GetDisplayMatrix(Matrix33& mat) const = 0;                 // [27] 0x0D8 sub_180E6F188  sub_18083E3D0; reconstitutes 3x3 (third row 0,0,1)
    virtual bool Set3DMatrix(const Matrix44& mat) = 0;                      // [28] 0x0E0 sub_180E750E0  16 floats transposed; ObjectInterface::SetMatrix3D sub_18083E760
    virtual bool Get3DMatrix(Matrix44& mat) const = 0;                      // [29] 0x0E8 sub_180E6ED28  sub_18083E670, transposed back
    virtual bool SetColorTransform(const SFlashCxform& cx) = 0;             // [30] 0x0F0 sub_180E7536C  8 floats {ColorF mul, ColorF add} interleaved -> GRenderer::Cxform; sub_18083EA00
    virtual bool GetColorTransform(SFlashCxform& cx) const = 0;             // [31] 0x0F8 sub_180E6F054  sub_18083E970, inverse interleave
    virtual bool SetVisible(bool visible) = 0;                              // [32] 0x100 sub_18061B798  builds GFx DisplayInfo with only Visible flag (0x40) set; sub_18083D930
    virtual bool SetText(const wchar_t* pText) = 0;                         // [33] 0x108 sub_180E75D88  sub_18083ECE0(...,html=0): direct TextField SetText if AS type==4, else SetMember("text", GFxValue type 5 = WSTRING)
    virtual bool SetText(const char* pText) = 0;                            // [34] 0x110 sub_180E75D1C  sub_18083EBE0(...,html=0): fallback GFxValue type 4 = STRING
    virtual bool SetTextHTML(const wchar_t* pHtml) = 0;                     // [35] 0x118 sub_180E75E60  sub_18083ECE0(...,html=1): member name "htmlText"
    virtual bool SetTextHTML(const char* pHtml) = 0;                        // [36] 0x120 sub_180E75DF4  sub_18083EBE0(...,html=1)
    virtual bool GetText(SFlashVarValue& text) const = 0;                   // [37] 0x128 sub_180E6F97C  sub_18083EAA0(...,html=0) + sub_18020CE4C (+string cache)
    virtual bool GetTextHTML(SFlashVarValue& html) const = 0;               // [38] 0x130 sub_180E6FA5C  sub_18083EAA0(...,html=1)
    virtual bool CreateEmptyMovieClip(IFlashVariableObject*& pVarObjMC, const char* pInstanceName,
                                      int depth = -1) = 0;                  // [39] 0x138 sub_180E6C9F4  ObjectInterface::CreateEmptyMovieClip sub_18083EDE0 + new(0x70)
    virtual bool AttachMovie(IFlashVariableObject*& pVarObjMC, const char* pSymbolName,
                             const char* pInstanceName, int depth = -1,
                             const IFlashVariableObject* pInitObj = 0) = 0; // [40] 0x140 sub_180E69E54  ObjectInterface::AttachMovie sub_18083F020; pInitObj's GFxValue at +8 (null-safe) + new(0x70)
    virtual bool GotoAndPlay(unsigned int frame) = 0;                       // [41] 0x148 sub_180E700B8  sub_18083F4D0(frame, stop=0): sprite GotoFrame(frame-1) then SetPlayState(Playing)
    virtual bool GotoAndPlay(const char* pFrame) = 0;                       // [42] 0x150 sub_180E70124  sub_18083F3F0(label, stop=0)
    virtual bool GotoAndStop(unsigned int frame) = 0;                       // [43] 0x158 sub_18020B6E4  sub_18083F4D0(frame, stop=1)
    virtual bool GotoAndStop(const char* pFrame) = 0;                       // [44] 0x160 sub_18020ACC0  sub_18083F3F0(label, stop=1)
    virtual ~IFlashVariableObject() {}                                      // [45] 0x168 sub_18020C248  scalar deleting dtor -> ~CFlashVariableObject sub_18020C448 (+free if flags&1); Release vcalls this slot
};

}  // namespace Offsets
