#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// E_CombatInputClass — combat input-class id.
//
// VERIFIED from combat_input_class.xml (Tables.pak): fixed table ids. Stored in
// C_CombatInputClassData.combat_input_class_id (+0x00) and C_CombatComboStepData.m_inputClassId
// (+0x10), and matched by TryGetComboAction against CreateAndDispatch's a3.
// NOTE: S_CombatActorState+0xC00 is NOT this enum -- it is the committed attack ZONE
// (E_CombatZoneId m_committedAttackZone); the old "m_inputClassId" label there was a mislabel.
//
// The runtime globals (Offsets::InputClassId) hold these SAME values, not a
// re-numbered/sequential set: C_CombatInputClassDatabase::Init (sub_18071EA94)
// sets each id global to -1, then registers a per-row onLoad callback that
// resolves the id FROM the loaded data row (looked up by name, in fixed XML-name
// order). So global == data-row combat_input_class_id == XML id. (The id globals
// are members of the DB singleton at 0x18359C2F0..0x18359C30C; the static IDB
// shows the -1 pre-load sentinel because resolution happens at table-load.)
// ---------------------------------------------------------------------------
enum class E_CombatInputClass : int32_t {
    None          = -1,   // "none"
    AttackLight   = 0,    // "attack_light"
    AttackHeavy   = 1,    // "attack_heavy"
    AttackSpecial = 2,    // "attack_special"
    MoveLeft      = 3,    // "move_left"
    MoveRight     = 4,    // "move_right"
    MoveBack      = 5,    // "move_back"
    MoveForward   = 6,    // "move_forward"
    Block         = 7,    // "block"
};

}  // namespace wh::combatmodule
