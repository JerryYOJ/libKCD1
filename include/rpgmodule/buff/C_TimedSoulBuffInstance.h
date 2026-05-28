#pragma once
#include "C_SoulBuffInstance.h"

// -----------------------------------------------
// C_TimedSoulBuffInstance — buff with duration that expires over time
// -----------------------------------------------
// RTTI: .?AVC_TimedSoulBuffInstance@rpgmodule@wh@@
// vtable: 0x1821cdce0
// Factory key: "wh.rpgmodule.buff.BasicTimed"  (XML: implementation="Cpp:BasicTimed")
// Constructor: sub_18061779C (allocates 0xE0 bytes)
// Size: 0xE0
//
// Adds duration tracking. Init reads duration from the buff definition.
// Update accumulates elapsed time; when elapsed >= duration the buff expires.
// Duration < 0 means infinite (never expires via timer).
//
// GetProgress returns the remaining fraction (1.0 = full, 0.0 = expired).

namespace wh::rpgmodule {

class C_TimedSoulBuffInstance : public C_SoulBuffInstance {
public:
    // Reads duration from buff definition at buffData+0x28.
    // Sets m_elapsedTime = 0.
    bool Init(void* pBuffData, I_BuffInitParams* pInitParams) override;                // [0] 0x1806D7AD4

    // Accumulates delta time. Returns false (0) when expired.
    // If duration < 0, never expires (returns 2 = active).
    // Clamps elapsed to duration on expiry.
    bool Update() override;                                                            // [1] 0x18060AA04

    // Returns remaining fraction of duration:
    //   progress = clamp((duration - elapsed) / duration, 0, 1)
    // If duration <= 0 (infinite), returns 1.0.
    // UNVERIFIED: exact return struct layout
    void* GetProgress(void* pOutResult);                                               // [9] 0x18116A0C0

    // Returns "timed" type name string (UNVERIFIED: might be "BasicTimed").
    void* GetTypeName(void* pOutStr) override;                                         // [13]

    C_BuffInstanceBase* CastTo(const void* pTypeName) override;                        // [14]
    C_BuffInstanceBase* CastToConst(const void* pTypeName) override;                   // [15]

    // ====== Data members ======
    double              m_duration;             // +0xD0  from buffDef->duration (float widened to double)
    double              m_elapsedTime;          // +0xD8  accumulated time, compared against m_duration
};
static_assert(sizeof(C_TimedSoulBuffInstance) == 0xE0);

}  // namespace wh::rpgmodule
