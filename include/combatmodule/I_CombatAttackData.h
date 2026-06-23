#pragma once

namespace wh::combatmodule {

class C_CombatZoneMappingData;

// ---------------------------------------------------------------------------
// I_CombatAttackData -- the single-slot interface base of C_CombatActionAttackData.
//
// RTTI: .?AVI_CombatAttackData@combatmodule@wh@@ (typedesc 0x182a08b98).
// The derived class owns the only vtable slot (0x1826b0628[0] = sub_1806fbe30,
// "mov rax,[rcx+0xE0]; ret") -- i.e. GetAimZoneMapping returns the +0xE0
// C_CombatZoneMappingData*. There is NO virtual GetExecutedZone; the executed
// zone is read by a direct field deref (+0xE8). [V] workflow wf_05aec32f.
// ---------------------------------------------------------------------------
class I_CombatAttackData {
public:
    // vtable[0]: returns the AIM zone-mapping (the +0xE0 FK). NOTE: this is the
    // AIM zone (-> state+0xC10), NOT the executed/visible zone (+0xE8).
    virtual C_CombatZoneMappingData* GetAimZoneMapping() = 0;
};

}  // namespace wh::combatmodule
