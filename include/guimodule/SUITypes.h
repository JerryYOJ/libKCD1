#pragma once

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <new>
#include "framework/DynArray.h"   // wh::DynArray — single-pointer, binary-exact

// ---------------------------------------------------------------------------
// FlashUI value types — fully usable, binary-layout-matched to WHGame.dll.
//
// These are the argument/descriptor types the FlashUI event system marshals
// between game code and ActionScript. A plugin can build SUIArguments, add
// typed values, read them back, and register typed event handlers. Layouts and
// type tags were verified in IDA: SUIArguments ctor sub_18020DF40, element
// copy sub_18020D30C (SUIData stride 0x20), insert sub_18020D168, grow
// sub_18020D434, RegisterEvent clone sub_181891D40 (SUIEventDesc 0x68).
// ---------------------------------------------------------------------------

typedef uint32_t EntityId;
// Vec3 / Vec2 / Matrix34 come from the real SDK Cry_Math.h (included by kcd.h).

// Type tags = index into the variant's type list {int, float, EntityId, Vec3,
// string, wstring, bool}. eUIDT_Any (-1) means "untyped / any".
enum EUIDataTypes {
    eUIDT_Any      = -1,
    eUIDT_Int      =  0,
    eUIDT_Float    =  1,
    eUIDT_EntityId =  2,
    eUIDT_Vec3     =  3,
    eUIDT_String   =  4,
    eUIDT_WString  =  5,
    eUIDT_Bool     =  6,
};

// ===========================================================================
// TUIData — tagged union (0x18). CryEngine's CConfigurableVariant compiles
// down to {int tag; pad; 16-byte inline value} in this build. Strings are
// stored as CryStringT (refcounted, 8-byte handle) inside the value buffer.
// ===========================================================================
struct TUIData
{
    int32_t  m_type;        // EUIDataTypes (the variant's own type tag)
    int32_t  _pad04;
    union {
        int32_t   m_int;
        float     m_float;
        EntityId  m_entityId;
        Vec3      m_vec3;
        uint8_t   m_bool;
        char      m_buffer[16];     // CryStringT<char> / CryStringT<wchar_t> live here
        void*     _align8;          // forces 8-byte alignment for the string handle
    };

    TUIData()                  : m_type(eUIDT_Int), _pad04(0) { m_int = 0; }
    TUIData(int v)             : m_type(eUIDT_Int), _pad04(0) { m_int = v; }
    TUIData(float v)           : m_type(eUIDT_Float), _pad04(0) { m_float = v; }
    TUIData(bool v)            : m_type(eUIDT_Bool), _pad04(0) { m_bool = v ? 1 : 0; }
    TUIData(const Vec3& v)     : m_type(eUIDT_Vec3), _pad04(0) { m_vec3 = v; }
    TUIData(const char* s)     : m_type(eUIDT_String), _pad04(0) { new (m_buffer) CryStringT<char>(s); }
    TUIData(const CryStringT<char>& s)    : m_type(eUIDT_String), _pad04(0) { new (m_buffer) CryStringT<char>(s); }
    TUIData(const CryStringT<wchar_t>& s) : m_type(eUIDT_WString), _pad04(0) { new (m_buffer) CryStringT<wchar_t>(s); }

    TUIData(const TUIData& o) : m_type(o.m_type), _pad04(0)
    {
        if (o.m_type == eUIDT_String)       new (m_buffer) CryStringT<char>(o.str());
        else if (o.m_type == eUIDT_WString) new (m_buffer) CryStringT<wchar_t>(o.wstr());
        else                                memcpy(m_buffer, o.m_buffer, sizeof(m_buffer));
    }
    TUIData& operator=(const TUIData& o)
    {
        if (this != &o) { this->~TUIData(); new (this) TUIData(o); }
        return *this;
    }
    ~TUIData()
    {
        if (m_type == eUIDT_String)       str().~CryStringT();
        else if (m_type == eUIDT_WString) wstr().~CryStringT();
    }

    EUIDataTypes GetType() const { return (EUIDataTypes)m_type; }

    CryStringT<char>&          str()        { return *reinterpret_cast<CryStringT<char>*>(m_buffer); }
    const CryStringT<char>&    str()  const { return *reinterpret_cast<const CryStringT<char>*>(m_buffer); }
    CryStringT<wchar_t>&       wstr()       { return *reinterpret_cast<CryStringT<wchar_t>*>(m_buffer); }
    const CryStringT<wchar_t>& wstr() const { return *reinterpret_cast<const CryStringT<wchar_t>*>(m_buffer); }

    // --- numeric read with coercion (matches the SDK conversion rules) ---
    float AsFloat() const
    {
        switch (m_type) {
            case eUIDT_Int:      return (float)m_int;
            case eUIDT_Float:    return m_float;
            case eUIDT_EntityId: return (float)m_entityId;
            case eUIDT_Bool:     return m_bool ? 1.f : 0.f;
            case eUIDT_Vec3:     return m_vec3.x;
            case eUIDT_String:   return (float)atof(str().c_str());
            default:             return 0.f;
        }
    }
    int      AsInt()      const { return (m_type == eUIDT_Int)   ? m_int      : (int)AsFloat(); }
    EntityId AsEntityId() const { return (m_type == eUIDT_EntityId) ? m_entityId : (EntityId)AsFloat(); }
    bool     AsBool()     const { return (m_type == eUIDT_Bool)  ? (m_bool != 0) : (AsFloat() != 0.f); }
    Vec3     AsVec3()     const { if (m_type == eUIDT_Vec3) return m_vec3; float f = AsFloat(); return Vec3{ f, f, f }; }
    CryStringT<char> AsString() const
    {
        if (m_type == eUIDT_String) return str();
        char tmp[64];
        switch (m_type) {
            case eUIDT_Int:      snprintf(tmp, sizeof(tmp), "%d", m_int); break;
            case eUIDT_Float:    snprintf(tmp, sizeof(tmp), "%f", m_float); break;
            case eUIDT_EntityId: snprintf(tmp, sizeof(tmp), "%u", m_entityId); break;
            case eUIDT_Bool:     snprintf(tmp, sizeof(tmp), "%d", m_bool); break;
            case eUIDT_Vec3:     snprintf(tmp, sizeof(tmp), "%f,%f,%f", m_vec3.x, m_vec3.y, m_vec3.z); break;
            default:             tmp[0] = 0; break;
        }
        return CryStringT<char>(tmp);
    }

    // Generic typed read used by the event dispatchers (deref_t pattern).
    bool GetValueWithConversion(int& v)      const { v = AsInt(); return true; }
    bool GetValueWithConversion(float& v)    const { v = AsFloat(); return true; }
    bool GetValueWithConversion(bool& v)     const { v = AsBool(); return true; }
    bool GetValueWithConversion(EntityId& v) const { v = AsEntityId(); return true; }
    bool GetValueWithConversion(Vec3& v)     const { v = AsVec3(); return true; }
    bool GetValueWithConversion(CryStringT<char>& v)    const { v = AsString(); return true; }
    bool GetValueWithConversion(CryStringT<wchar_t>& v) const { if (m_type == eUIDT_WString) { v = wstr(); return true; } return false; }
};
static_assert(sizeof(TUIData) == 0x18);

// SUIData — one {type, value} element of SUIArguments::m_ArgList (stride 0x20).
struct SUIData
{
    EUIDataTypes m_eType;   // duplicate of value.m_type (matches binary layout)
    int32_t      _pad04;
    TUIData      m_value;   // +0x08

    SUIData() : m_eType(eUIDT_Int), _pad04(0) {}
    SUIData(EUIDataTypes t, const TUIData& v) : m_eType(t), _pad04(0), m_value(v) {}
};
static_assert(sizeof(SUIData) == 0x20);

// ===========================================================================
// SUIArguments — typed argument list for FlashUI events (0x30).
// ===========================================================================
struct SFlashVarValue;   // Scaleform value (IFlashPlayer.h); only the lazy cache uses it

struct SUIArguments
{
    enum EBufferDirtyFlag {
        eBDF_None      = 0x00,
        eBDF_String    = 0x01,
        eBDF_WString   = 0x02,
        eBDF_FlashVar  = 0x04,
        eBDF_Delimiter = 0x08,
        eBDF_ALL       = 0xFF,
    };

    SUIArguments() : m_cDelimiter("|"), m_pFlashValueCache(nullptr), m_Dirty(eBDF_Delimiter) {}

    // --- build ---
    void AddArgument(int v)            { push(eUIDT_Int,      TUIData(v)); }
    void AddArgument(float v)          { push(eUIDT_Float,    TUIData(v)); }
    void AddArgument(bool v)           { push(eUIDT_Bool,     TUIData(v)); }
    void AddArgument(const Vec3& v)    { push(eUIDT_Vec3,     TUIData(v)); }
    void AddArgument(const char* v)    { push(eUIDT_String,   TUIData(v)); }
    void AddArgument(const CryStringT<char>& v)    { push(eUIDT_String,  TUIData(v)); }
    void AddArgument(const CryStringT<wchar_t>& v) { push(eUIDT_WString, TUIData(v)); }
    void AddArgumentEntityId(EntityId v) { TUIData d; d.m_type = eUIDT_EntityId; d.m_entityId = v; push(eUIDT_EntityId, d); }

    template <class T>
    static SUIArguments Create(const T& arg) { SUIArguments a; a.AddArgument(arg); return a; }

    void Clear() { m_ArgList.clear(); m_Dirty = eBDF_ALL; }

    // --- read ---
    int          GetArgCount() const { return m_ArgList.size(); }
    EUIDataTypes GetArgType(int i) const { return m_ArgList[i].m_eType; }
    const TUIData& GetArg(int i) const { return m_ArgList[i].m_value; }

    template <class T>
    bool GetArg(int index, T& val) const
    {
        if (index < 0 || index >= m_ArgList.size()) return false;
        return m_ArgList[index].m_value.GetValueWithConversion(val);
    }

private:
    void push(EUIDataTypes t, const TUIData& d) { m_ArgList.push_back(SUIData(t, d)); m_Dirty = eBDF_ALL; }

    wh::DynArray<SUIData> m_ArgList;          // +0x00
    CryStringT<char>    m_sArgStringBuffer;   // +0x08  lazy GetAsString() cache
    CryStringT<wchar_t> m_sArgWStringBuffer;  // +0x10  lazy GetAsWString() cache
    void*               m_pFlashValueCache;   // +0x18  lazy DynArray<SFlashVarValue> for GetAsList() (unmanaged here)
    CryStringT<char>    m_cDelimiter;         // +0x20  default "|"
    uint32_t            m_Dirty;              // +0x28  EBufferDirtyFlag mask
};
static_assert(sizeof(SUIArguments) == 0x30);

// SUIArgumentsRet — returned by value from OnEvent/SendEvent (hidden sret in
// the binary ABI).
using SUIArgumentsRet = SUIArguments;

// ===========================================================================
// SUIParameterDesc / SUIEventDesc — function & event descriptors.
// ===========================================================================
struct SUIParameterDesc
{
    enum EUIParameterType {
        eUIPT_Any, eUIPT_Bool, eUIPT_Int, eUIPT_Float, eUIPT_Vec3, eUIPT_String, eUIPT_WString
    };

    const char*             sName;
    const char*             sDisplayName;
    const char*             sDesc;
    const SUIParameterDesc* pParent;
    EUIParameterType        eType;

    SUIParameterDesc() : sName("undefined"), sDisplayName("undefined"), sDesc("undefined"), pParent(nullptr), eType(eUIPT_Any) {}
    SUIParameterDesc(const char* name, const char* displ, const char* desc, EUIParameterType type = eUIPT_Any, const SUIParameterDesc* parent = nullptr)
        : sName(name), sDisplayName(displ), sDesc(desc), pParent(parent), eType(type) {}
};
static_assert(sizeof(SUIParameterDesc) == 0x28);

struct SUIEventDesc : public SUIParameterDesc
{
    // Input/output parameter group: a dynamic-array flag + the typed params.
    struct SEvtParams
    {
        bool                     IsDynamic;
        const char*              sDynamicName;
        const char*              sDynamicDesc;
        wh::DynArray<SUIParameterDesc> Params;

        SEvtParams(bool isDyn = false, const char* dynName = "Array", const char* dynDesc = "")
            : IsDynamic(isDyn), sDynamicName(dynName), sDynamicDesc(dynDesc) {}

        void SetDynamic(const char* name, const char* desc) { IsDynamic = true; sDynamicName = name; sDynamicDesc = desc; }

        template <SUIParameterDesc::EUIParameterType T>
        void AddParam(const char* name, const char* desc) { Params.push_back(SUIParameterDesc(name, name, desc, T)); }
        template <SUIParameterDesc::EUIParameterType T>
        void AddParam(const char* name, const char* displ, const char* desc) { Params.push_back(SUIParameterDesc(name, displ, desc, T)); }
    };

    SEvtParams InputParams;     // +0x28
    SEvtParams OutputParams;    // +0x48

    SUIEventDesc() {}
    SUIEventDesc(const char* name, const char* desc) : SUIParameterDesc(name, name, desc) {}
    SUIEventDesc(const char* name, const char* displ, const char* desc, SEvtParams inputs = SEvtParams(), SEvtParams outputs = SEvtParams(), const SUIParameterDesc* parent = nullptr)
        : SUIParameterDesc(name, displ, desc, eUIPT_Any, parent), InputParams(inputs), OutputParams(outputs) {}

    void SetDynamic(const char* name, const char* desc) { InputParams.SetDynamic(name, desc); }
    template <SUIParameterDesc::EUIParameterType T>
    void AddParam(const char* name, const char* desc) { InputParams.AddParam<T>(name, desc); }
    template <SUIParameterDesc::EUIParameterType T>
    void AddParam(const char* name, const char* displ, const char* desc) { InputParams.AddParam<T>(name, displ, desc); }
};
static_assert(sizeof(SUIEventDesc) == 0x68);

// SUIMovieClipDesc — descriptor with lookup tables; used only by pointer in the
// interface replicas, so it stays an opaque forward declaration.
struct SUIMovieClipDesc;

// SUIEvent — { event id, args } delivered to event listeners.
struct SUIEvent
{
    unsigned int event;
    char         _pad4[4];
    SUIArguments args;

    SUIEvent() : event(0) {}
    SUIEvent(unsigned int id) : event(id) {}
    SUIEvent(unsigned int id, const SUIArguments& a) : event(id), args(a) {}
};
static_assert(sizeof(SUIEvent) == 0x38);

// IUIEventDispatchFct — abstract base of the dispatch functors. Fully defined
// in guimodule/SUIEventReceiverDispatcher.h; forward-declared for pointer use.
struct IUIEventDispatchFct;

// --- Forward declarations (pointer/ref use only in the interface replicas) ---
// Vec2 / Matrix34 are real SDK types from Cry_Math.h (kcd.h).
struct ITexture;
struct IDynTextureSource;
struct ICrySizer;
struct ICryFactory;
struct SFlashKeyEvent;
struct SFlashCharEvent;
struct SFlashCursorEvent;
struct IFSCommandHandler;
struct IExternalInterfaceHandler;
struct IActionScriptFunction;
struct IUIAction;
struct IUIActionManager;
struct IPlayerProfile;
class  CFlashUIActionEvents;
class  XmlNodeRef;
