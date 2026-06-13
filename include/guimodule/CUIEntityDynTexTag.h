#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include <vector>
#include "Offsets/vtables/IUIGameEventSystem.h"
// (individual UI includes consolidated into IFlashUI.h)
#include "Offsets/vtables/IEntityEventListener.h"
// (individual UI includes consolidated into IFlashUI.h)

// -----------------------------------------------
// CUIEntityDynTexTag 鈥?3D entity-attached dynamic-texture UI tags
// -----------------------------------------------
// RTTI: .?AVCUIEntityDynTexTag@guimodule@wh@@   (GameSDK-derived class; the
// CryEngine GameSDK original renders UIElements onto dynamic textures
// attached to world entities)
// Constructor:     sub_181119344  (factory memsets 0x68 first)
// Factory:         sub_18111A8D4  (SAutoRegUIEventSystem<CUIEntityDynTexTag>
//                  vtable 0x1822e7580; allocates 0x68, returns this+0)
// GetName:         sub_1806FE760  -> "UIEntityDynTexTag"
// InitEventSystem: sub_18111B884  (IUIGameEventSystem slot [2])
// UnloadEventSystem: sub_1811205CC (slot [3]: ClearAllTags sub_18111A6BC +
//                  pFlashUI->UnregisterModule(this+8) via vtbl+0xB0)
// OnUpdate:        sub_1805F38B4  (slot [5], (this, float fDeltaTime) 鈥?//                  per-frame tag transform/lerp update)
// Size:            0x68
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] IUIGameEventSystem (: IUIPseudoRTTI)  (vtable 0x1826cf528)
//   [+0x08] IUIModule                              (vtable 0x1826cf4e0)
//   [+0x10] IUIElementEventListener                (vtable 0x1826cf440)
//   [+0x18] IEntityEventListener                   (vtable 0x1826cf428)
//
// InitEventSystem (sub_18111B884) creates the UI->system IUIEventSystem
// "UIEntityTagsDynTex" (direction 0), registers the receiver dispatcher as
// listener "UIEntityDynTexTag" with 4 functions (registration order):
//   [0] "AddEntityTag"      "Adds a 3D entity Tag"            handler sub_18111DC70
//         EntityID(Int "Entity ID of tagged entity"),
//         uiElements_UIElement(String "UIElement that is used for this tag
//           (Instance with EntityId as instanceId will be created)"),
//         EntityClass(String "EntityClass of the spawned entity"),
//         Material(String "Material template that is used for the dyn texture"),
//         Offset(Vec3 "Offset in camera space relative to entity pos"),
//         TagIDX(String "Custom IDX to identify entity tag.")
//   [1] "UpdateEntityTag"   "Updates a 3D entity Tag"         handler sub_18111E6F4
//         EntityID(Int), TagIDX(String), Offset(Vec3),
//         LerpSpeed(Float "Define speed of lerp between old and new offset, 0=instant")
//   [2] "RemoveEntityTag"   "Removes a 3D entity Tag"         handler sub_18111E59C
//         EntityID(Int), TagIDX(String)
//   [3] "RemoveAllEntityTag" "Removes all 3D entity Tags for given entity"
//         EntityID(Int)                                       handler sub_18111E594
// then registers itself as a UI module: pFlashUI->RegisterModule(this+8,
// "CUIEntityDynTexTag") (vtbl+0xA8).
//
// Handler signatures cross-checked against the SUIEventDispatchFctImpl RTTI
// instantiations at 0x1822e7458 (Fct6: uint,char*,char*,char*,Vec3&,char*),
// 0x1822e74d0 (Fct4: uint,CryStringT&,Vec3&,float), 0x1822e74e8 (Fct2:
// uint,CryStringT&), 0x1822e74a0 (Fct1: uint).
//
// IEntityEventListener::OnEntityEvent (sub_18111E2CC) -> RemoveAllEntityTags
// for the entity (sub_18111EA90). IUIElementEventListener slot [6]
// (sub_18111E534) = OnInstanceDestroyed: walks m_Tags zeroing the matching
// pInstance.

namespace wh::guimodule {

class CUIEntityDynTexTag
    : public Offsets::IUIGameEventSystem        // +0x00  (: IUIPseudoRTTI)
    , public Offsets::IUIModule                 // +0x08
    , public Offsets::IUIElementEventListener   // +0x10
    , public Offsets::IEntityEventListener      // +0x18
{
public:
    // Per-tag record, 0x38 bytes (stride proven by the OnInstanceDestroyed
    // loop sub_18111E534: iterates [m_Tags.begin, m_Tags.end) in 0x38 steps).
    // Only +0x28 is identified; the rest mirrors the GameSDK STagInfo
    // (ownerId/entityId/idx/offset/...) but is UNVERIFIED here.
    struct STagInfo {
        char  _unk00[0x28];      // +0x00  UNVERIFIED fields (ids, idx string, offsets)
        void* pInstance;         // +0x28  IUIElement* tag instance (zeroed on instance destroy)
        char  _unk30[0x8];       // +0x30
    };
    static_assert(sizeof(STagInfo) == 0x38);

    // Embedded dispatcher (0x28: vtable 0x1826cf570, mFunctionMap @+0x28,
    // m_pEventSystem @+0x38 = UI->system "UIEntityTagsDynTex", m_pThis @+0x40).
    SUIEventReceiverDispatcher<CUIEntityDynTexTag>
                              m_eventDispatcher;   // +0x20 .. 0x48
    Offsets::IUIEventSystem*  m_pUIFunctions;      // +0x48  same "UIEntityTagsDynTex" event system

    std::vector<STagInfo>     m_Tags;              // +0x50  active tags (0x18: begin/end/cap)

    // Overrides (vtables inherited, not re-declared):
    //   IUIGameEventSystem::GetName           -> sub_1806FE760 ("UIEntityDynTexTag")
    //   IUIGameEventSystem::InitEventSystem   -> sub_18111B884
    //   IUIGameEventSystem::UnloadEventSystem -> sub_1811205CC (slot [3])
    //   IUIGameEventSystem::Update            -> sub_1805F38B4 (slot [5], float dt)
    //   IUIModule::Reload/Reset               -> sub_18111EA38 / sub_18111EC88 (tag clearing)
    //   IUIElementEventListener::OnInstanceDestroyed -> sub_18111E534 (slot [6])
    //   IEntityEventListener::OnEntityEvent   -> sub_18111E2CC
};
static_assert(sizeof(CUIEntityDynTexTag) == 0x68);

}  // namespace wh::guimodule
