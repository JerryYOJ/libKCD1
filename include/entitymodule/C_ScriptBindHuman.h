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
// Created by C_EntityModule (stored at module+0x90).

namespace wh::entitymodule {

class C_ScriptBindHuman : public CScriptableBase {
public:
    Offsets::IScriptTable*  m_pEntityTable;     // +0x60
    void*                   m_pGameFramework;   // +0x68
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x70

    enum EPickDiscard { EP_DISCARD = 0, EP_FOLD = 1 };
    enum EWeaponSet { WS_PRIMARY = 0, WS_SECONDARY = 1 };
    enum EHandSide { HS_RIGHT = 0, HS_LEFT = 1 };
    enum EPrepareFoodType { PFT_COOK = 0, PFT_SMOKE = 1, PFT_DRY = 2 };

    virtual int RequestDialog(IFunctionHandler* pH);              // 0x1810E1650
    virtual int CanTalk(IFunctionHandler* pH);                    // 0x1810C05D8
    virtual int CanInteractWith(IFunctionHandler* pH);            // 0x1810C0154
    virtual int IsInDialog(IFunctionHandler* pH);                 // 0x1810D29BC
    virtual int ReadyForDialog(IFunctionHandler* pH);             // 0x1810DD920
    virtual int ReadyForDialogWithTwins(IFunctionHandler* pH);    // 0x1810DD990
    virtual int PrepareForDialog(IFunctionHandler* pH);           // 0x1810DB658
    virtual int InterruptDialog(IFunctionHandler* pH);            // 0x1810D2650
    virtual int GetDialogRequestSourceName(IFunctionHandler* pH); // 0x1810C87E4
    virtual int ToggleWeapon(IFunctionHandler* pH);               // 0x1810E9698
    virtual int DrawWeapon(IFunctionHandler* pH);                 // 0x1810C49A8
    virtual int HolsterWeapon(IFunctionHandler* pH);              // 0x1810CD980
    virtual int IsWeaponDrawn(IFunctionHandler* pH);              // 0x1810D3598
    virtual int ToggleWeaponSet(IFunctionHandler* pH);            // 0x1810E9708
    virtual int AttachEntityToHand(IFunctionHandler* pH);         // 0x1810BEE10
    virtual int DetachFromHand(IFunctionHandler* pH);             // 0x1810C2D60
    virtual int DrawFromInventory(IFunctionHandler* pH);          // 0x1810C494C
    virtual int HolsterToInventory(IFunctionHandler* pH);         // 0x1810CD934
    virtual int GrabOnLadder(IFunctionHandler* pH);               // 0x1810CCB6C
    virtual int IsOnLadder(IFunctionHandler* pH);                 // 0x1810D2EEC
    virtual int CanUseLadder(IFunctionHandler* pH);               // 0x1810C07B0
    virtual int Mount(IFunctionHandler* pH);                      // 0x1810D5920
    virtual int Dismount(IFunctionHandler* pH);                   // 0x1810C2E70
    virtual int GetHorseMountPoint(IFunctionHandler* pH);         // 0x1810C96A4
    virtual int ForceMount(IFunctionHandler* pH);                 // 0x1810C696C
    virtual int ForceDismount(IFunctionHandler* pH);              // 0x1810C6920
    virtual int StartReading(IFunctionHandler* pH);               // 0x1810E8E6C
    virtual int StartBookTranscription(IFunctionHandler* pH);     // 0x1810E89A4
    virtual int GetItemInHand(IFunctionHandler* pH);              // 0x1810C9BF4
    virtual int PlayAnim(IFunctionHandler* pH);                   // 0x1810DA760
    virtual int StopAnim(IFunctionHandler* pH);                   // 0x1810E90C4
    virtual int SetAnimMotionParam(IFunctionHandler* pH);         // 0x1810E52B0
    virtual int GetHorse(IFunctionHandler* pH);                   // 0x1810C95D4
    virtual int IsMounted(IFunctionHandler* pH);                  // 0x1810D2D64
    virtual int PickUpItem(IFunctionHandler* pH);                 // 0x1810DA174
    virtual int PlaceItem(IFunctionHandler* pH);                  // 0x1810DA224
    virtual int PrepareFood(IFunctionHandler* pH);                // 0x1810DB5EC
    virtual int RequestPickpocketing(IFunctionHandler* pH);       // 0x1810E1AA4
    virtual int CanBeRobbed(IFunctionHandler* pH);                // 0x1810BFDB8
    virtual int IsPickpocketing(IFunctionHandler* pH);            // 0x1810D2FCC
    virtual int StartBuilding(IFunctionHandler* pH);              // 0x1810E89F8
};
static_assert(sizeof(C_ScriptBindHuman) == 0x78);

} // namespace wh::entitymodule
