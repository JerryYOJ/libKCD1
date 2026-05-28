#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// C_ScriptBindHuman — entity script binding for humans
// -----------------------------------------------
// RTTI: .?AVC_ScriptBindHuman@entitymodule@wh@@
// vtable: 0x1826c5ed8
// Constructor: sub_1810B96C4
// Size: 0x78
//
// Entity binding — separate from C_ScriptBindActor (NOT a subclass).
// Created as an independent object by C_EntityModule (stored at module+0x90).

namespace wh::entitymodule {

class C_ScriptBindHuman : public CScriptableBase {
public:
    Offsets::IScriptTable*  m_pEntityTable;     // +0x60
    void*                   m_pGameFramework;   // +0x68  IGameFramework*
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x70

    // -- Constants --
    enum EPickDiscard {
        EP_DISCARD = 0,
        EP_FOLD    = 1,
    };

    enum EWeaponSet {
        WS_PRIMARY   = 0,
        WS_SECONDARY = 1,
    };

    enum EHandSide {
        HS_RIGHT = 0,
        HS_LEFT  = 1,
    };

    enum EPrepareFoodType {
        PFT_COOK  = 0,
        PFT_SMOKE = 1,
        PFT_DRY   = 2,
    };

    // -- Lua methods (35+) --
    int CanTalk(IFunctionHandler* pH);                                              // 0x180B1AC14
    int CanInteractWith(IFunctionHandler* pH, EntityId entityId);                   // 0x180B1AC1C
    int IsInDialog(IFunctionHandler* pH);                                           // 0x180B1AC24
    int RequestDialog(IFunctionHandler* pH);                                        // 0x180B1AB4C
    int ReadyForDialog(IFunctionHandler* pH);                                       // 0x180B1AC2C
    int ReadyForDialogWithTwins(IFunctionHandler* pH);                              // 0x180B1AC34
    int PrepareForDialog(IFunctionHandler* pH);                                     // 0x180B1AD1C
    int InterruptDialog(IFunctionHandler* pH);                                      // 0x180B1AC3C
    int GetDialogRequestSourceName(IFunctionHandler* pH);                           // 0x180B1AC44
    int ToggleWeapon(IFunctionHandler* pH);                                         // 0x180B1AC5C
    int DrawWeapon(IFunctionHandler* pH);                                           // 0x180B1AC68
    int HolsterWeapon(IFunctionHandler* pH);                                        // 0x180B1AC80
    int IsWeaponDrawn(IFunctionHandler* pH);                                        // 0x180B1ACA4
    int ToggleWeaponSet(IFunctionHandler* pH, int set);                             // 0x180B1AC74
    int AttachEntityToHand(IFunctionHandler* pH, EntityId id, int hand);            // 0x180B1AC8C
    int DetachFromHand(IFunctionHandler* pH, int hand);                             // 0x180B1AC98
    int DrawFromInventory(IFunctionHandler* pH, EntityId itemId, int hand, bool bAnimate); // 0x180B1ACB0
    int HolsterToInventory(IFunctionHandler* pH, int hand, bool bAnimate);          // 0x180B1ACBC
    int GrabOnLadder(IFunctionHandler* pH, EntityId ladderId);                      // 0x180B1ACC8
    int IsOnLadder(IFunctionHandler* pH);                                           // 0x180B1ACD4
    int CanUseLadder(IFunctionHandler* pH, EntityId ladderId, float ladderHeight, bool useOnlyFromFront); // 0x180B1ACE0
    int Mount(IFunctionHandler* pH, EntityId horseId);                              // 0x180B1ACEC
    int Dismount(IFunctionHandler* pH);                                             // 0x180B1ACF8
    int GetHorseMountPoint(IFunctionHandler* pH, EntityId horseId);                 // 0x180B1AD04
    int ForceMount(IFunctionHandler* pH, EntityId horseId);                         // 0x180B1AD10
    int ForceDismount(IFunctionHandler* pH);                                        // 0x180B1A948
    int StartReading(IFunctionHandler* pH, EntityId bookId);                        // 0x180B1A954
    int StartBookTranscription(IFunctionHandler* pH, EntityId bookId);              // 0x180B1A96C
    int GetItemInHand(IFunctionHandler* pH, int handId);                            // 0x180B1A978
    int PlayAnim(IFunctionHandler* pH, const char* fragment, const char* tag);      // 0x180B1A984
    int StopAnim(IFunctionHandler* pH);                                             // 0x180B1A990
    int SetAnimMotionParam(IFunctionHandler* pH, int paramId, float value);         // 0x180B1A57C
    int GetHorse(IFunctionHandler* pH);                                             // 0x180B1A594
    int IsMounted(IFunctionHandler* pH);                                            // 0x180B1A588
    int PickUpItem(IFunctionHandler* pH, EntityId itemId, int toHand);              // 0x180B1AC4C
    int PlaceItem(IFunctionHandler* pH, EntityId itemId, EntityId entity, int fromHand); // 0x180B1AC54
    int PrepareFood(IFunctionHandler* pH, EntityId itemId, int type);               // 0x180B1A9C0
    int RequestPickpocketing(IFunctionHandler* pH, EntityId victimEntityId, int mode); // 0x180B1A99C
    int CanBeRobbed(IFunctionHandler* pH, EntityId victimEntityId);                 // 0x180B1A9A8
    int IsPickpocketing(IFunctionHandler* pH);                                      // 0x180B1A9B4
    int StartBuilding(IFunctionHandler* pH, EntityId bookId);                       // 0x180B1A960
};
static_assert(sizeof(C_ScriptBindHuman) == 0x78);

} // namespace wh::entitymodule
