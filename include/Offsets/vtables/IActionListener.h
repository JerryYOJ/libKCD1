#pragma once

#include "ActionId.h"

// -----------------------------------------------
// IActionListener — action-map callback (register via AddExtraActionListener
//                   or be a map's SetActionListener entity)
// -----------------------------------------------
// SDK: CryEngine CryAction/IActionMapManager.h:133. Interface vtable
// ??_7IActionListener@@ @ 0x1821acb30 (NOT shuffled). C_UIMap implements it:
//   [0] sub_180B1AF34  dtor thunk (this -= 0x10)
//   [1] 0x1801FF728    OnAction(const ActionId&, int activationMode, float value)
//   [2] 0x1802004AC    AfterAction()  (default no-op)
//
// activationMode = EActionActivationMode (eAAM_OnPress/OnRelease/OnHold/...).
// value = analog axis value (0/1 for digital). The action's name:
//   actionId.c_str().

namespace Offsets {

struct IActionListener {
    virtual void Dtor(char flags) = 0;                                            // [0] +0x00
    virtual void OnAction(const ActionId& action, int activationMode, float value) = 0; // [1] +0x08
    virtual void AfterAction() = 0;                                               // [2] +0x10
};

}  // namespace Offsets
