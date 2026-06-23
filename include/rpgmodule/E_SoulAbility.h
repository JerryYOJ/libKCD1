#pragma once
#include <cstdint>

namespace wh::rpgmodule {

// ---------------------------------------------------------------------------
// E_SoulAbility -- soul ability ids (rpg/soul_ability.xml). Granted to a soul by
// perks (perk_soul_ability.xml), stored in C_Soul::m_soulAbilities (+0x180), and
// queried by C_Soul::HasSoulAbility (I_Soul vtable slot +0x1A8, sub_18023B6BC).
//
// Ids 0/1/2 (Dodge/PerfectBlock/Riposte) GATE the matching defensive reaction in
// C_CombatAutomationDefense: sub_180432CF4 maps a reaction to its ability id and
// calls HasSoulAbility before the reaction is allowed. Finticka(3) is the feint
// ability; ChainStrike(50) backs the Chain-strike perk buff. A few ids are
// COMPUTED at query time instead of stored -- SteakTartare(17) and TwoHanded(61)
// have dedicated branches in HasSoulAbility (TwoHanded from the equipped weapon).
// ---------------------------------------------------------------------------
enum class E_SoulAbility : int32_t {
    Dodge              = 0,    // gates the dodge reaction
    PerfectBlock       = 1,    // gates the perfect-block reaction
    Riposte            = 2,    // gates the riposte / master-strike reaction
    Finticka           = 3,    // feint
    StealthKnockOut    = 4,
    StealthKill        = 5,
    HorsePullDown      = 6,
    Bumper             = 7,
    Comrade            = 10,
    EasyWayOut         = 12,
    Reading_ArtAdmirer = 14,
    Reading_AvidReader = 15,
    SteakTartare       = 17,   // COMPUTED at query time (not stored)
    TrialAndError      = 18,
    EasyDrunk          = 19,
    TrueSlav           = 21,
    Bacchus            = 22,
    AlchemyRoutine1    = 23,
    AlchemyRoutine2    = 24,
    WineBibber         = 25,
    BeerBibber         = 26,
    LiquorBibber       = 27,
    LooseTongue        = 28,
    BundleAlchemist    = 29,
    HumanDustbin       = 30,
    SaltAndSmoke       = 31,
    Witcher            = 33,
    EutuBrutus         = 35,
    Reading_Wanderer   = 36,
    Butcher            = 37,
    Antlers            = 38,
    Tusks              = 39,
    Tanner             = 40,
    Salty              = 41,
    WaterOfLife        = 42,
    Taunt              = 43,
    HuntAttack         = 44,
    MercyKill          = 45,
    FirstAid           = 46,
    Empathic           = 47,
    Serration          = 48,
    HeavyTip           = 49,
    ChainStrike        = 50,   // backs the "Chain strike" (连击) perk buff
    SevenLeague        = 51,
    Letailleur         = 52,
    Padding            = 53,
    Blacksmithsson     = 54,
    HuntingPermit      = 55,
    Attack             = 56,
    Alarm              = 57,
    Distract           = 58,
    Hunt               = 59,
    Search             = 60,
    TwoHanded          = 61,   // COMPUTED at query time (not stored) -- from equipped weapon
};

}  // namespace wh::rpgmodule
