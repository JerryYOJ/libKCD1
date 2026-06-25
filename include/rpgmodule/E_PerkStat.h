#pragma once
#include <cstdint>

namespace wh::rpgmodule {

// ---------------------------------------------------------------------------
// E_PerkStat -- the perk-MODIFIABLE stat namespace (modifier category 2,
// C_Soul m_perkStatMods @ soul+0xA8). Built by the global ctor sub_1801282A0;
// code->id lookup is C_RPGUtils vtable +0x88 (not-found sentinel 0x27 = 39).
//
// This is every stat a perk/buff can MODIFY via AccumulatePerkStat (sub_180229980).
// It is NOT combat-only -- it spans melee (wat/asp/pbs/dsl/osb/dee), metabolism
// (dig/exh/srg/sra), lockpicking (lpd/lpn/lpb), stealth (skp), fast-travel (eep/ors),
// mounted combat (ahm/pdp), first-aid (fae), bleeding (ain/hin), etc. (Was named
// E_CombatStat -- renamed because the data showed the set is far broader than combat.)
// Distinct namespace from E_DerivedStat (category 3, the 110 computed character stats):
// here Pbs(8) is the perfect-block stat, not Hlt.
//
// Full names verified by: localized perk/buff descriptions (Localization/English_xml.pak
// resolving buff_desc/perk_ui_desc text keys) + binary readers of AccumulatePerkStat
// + the in-reader clamp ranges (sub_180229980): ids {7,8,9,0x15,0x16,0x18,0x21} clamp
// [0,1] (probabilities), id 0x25 is signed/unclamped, the rest clamp [0,+inf).
// Confidence tags:  [V] verified (localized desc names it, or prior RE ground truth)
//                   [S] strong (single-code perk/buff name implies it + consistent clamp)
//                   [I] inferred (suggestive, not pinned)
//                   [?] UNKNOWN (no naming-grade evidence -- do not trust a guess)
// ---------------------------------------------------------------------------
enum class E_PerkStat : int32_t {
    Ade = 0x00,   // "ade"  [?] UNKNOWN -- only dev buff test_turtle_skin (ade*1.2); maybe damage-resist, unpinned
    Uat = 0x01,   // "uat"  Unarmed attack power (melee damage)            [S] paired w/ wat; berserk potion "armed or unarmed damage increased"
    Wat = 0x02,   // "wat"  Weapon attack power (melee DAMAGE)             [V] greater_attack wat*2, furious "stronger attacks", huntsman "more damage" (NOT attack-time)
    Wac = 0x03,   // "wac"  Weapon-attack STAMINA COST                     [S] heavy_swing "+10% stamina", fast_striker "-30% stamina", god_mode wac=0
    Ahm = 0x04,   // "ahm"  Mounted (horseback) attack damage              [V] perk_knight "+15% damage in mounted combat, melee & ranged"
    Rtm = 0x05,   // "rtm"  [?] UNKNOWN -- single-code perk_warhorse (rtm*0.5); mount-themed, no desc resolved
    Act = 0x06,   // "act"  [?] UNKNOWN -- 0 buff usages; reader builds a perception/sense value
    Asp = 0x07,   // "asp"  Attack SUCCESS probability (skill-diff factor)  [S] clamp[0,1] geom-mean success chance (NOT attack speed; "debuffSpeed" name is misleading)
    Pbs = 0x08,   // "pbs"  Perfect-block / master-strike chance           [V] clamp[0,1] SHARED base; built from Defense skill (0xF). item_shield pbs+0.3
    Cli = 0x09,   // "cli"  Clinch (overpower) chance                      [V] clamp[0,1] perk_clinch_master "+40% chance to overpower in a clinch"
    Hlh = 0x0A,   // "hlh"  Incoming HEALTH damage taken (mult)            [V] aqua_vitalis "wound 50% less", tough_guy hlh*0.13, god_mode hlh=0 (lower = take less)
    Slh = 0x0B,   // "slh"  Incoming STAMINA damage taken (mult)           [S] stamina counterpart of hlh; always paired & symmetric (god_mode slh=0)
    Sls = 0x0C,   // "sls"  Shield-block STAMINA cost                      [V] perk_stronghold "block w/ shield costs 30% less stamina"
    Dig = 0x0D,   // "dig"  Digestion / hunger rate                        [V] HC Tapeworm "get hungry faster", good_appetite dig*3, ascetic dig*0.7
    Exh = 0x0E,   // "exh"  Exhaustion / energy-drain rate                 [V] perk_insomniac "Energy falls 25% more slowly", good_appetite exh*2
    Psp = 0x0F,   // "psp"  [?] UNKNOWN -- only hardcore_mode (psp*0.5); reader adds to a capped meter (+0xD8)
    Lcs = 0x10,   // "lcs"  Aim sway / hand-shake magnitude                [S] perk_steady_hand lcs=0; HC Shakes "bad for archery/lockpicking/pickpocketing"
    Srg = 0x11,   // "srg"  Stamina REGENERATION rate                      [V] perk_berserk "stamina regen 4x faster"; night_rider day/night
    Sco = 0x12,   // "sco"  [?] UNKNOWN -- only god_mode/imba (sco=0 with src=0); maybe an action-cost stat
    Srb = 0x13,   // "srb"  [?] UNKNOWN -- 0 buff usages; reader uses it as a per-state upper cap
    Sra = 0x14,   // "sra"  In-combat / backswing stamina regen           [S] perk_tight_grip "regen won't slow in combat, even on backswing" (distinct from srg)
    Skp = 0x15,   // "skp"  Stealth-kill probability                       [S] clamp[0,1] test_stealth_kill_success skp=1 / _fail skp=0
    Rst = 0x16,   // "rst"  Max-stamina cap factor (health-derived)        [S] clamp[0,1] overeat "max Stamina lowered"; sets HUD stamina-bar extent
    Pdp = 0x17,   // "pdp"  Unhorse resistance (stay-in-saddle chance)     [V] perk_strong_thighs "stay in saddle if an opponent tries to unhorse you"
    Eep = 0x18,   // "eep"  Fast-travel evade/escape chance                [S] clamp[0,1] Scout perks "your chances of evading are increased by 10%"
    Lpd = 0x19,   // "lpd"  Lockpick difficulty (lower = easier)           [S] luck_of_the_drunk lpd*0.5 "pick locks twice as easily" (binary reader = generic prob; loc pins lockpicking)
    Lpn = 0x1A,   // "lpn"  Lockpicking noise                              [S] luck_of_the_drunk lpn*1.3 "30% more noise"; silent_fiddler lpn*0.1
    Ain = 0x1B,   // "ain"  Bleed-INFLICTION chance (cause bleeding)       [V] bloodletter "greater chance to draw blood"; serration "+15% bleed chance"
    Hin = 0x1C,   // "hin"  Incoming bleed chance (bleed susceptibility)   [V] thickblooded "chance a foe makes you bleed reduced"; receive-side of ain
    Fae = 0x1D,   // "fae"  First-aid effectiveness                        [S] perk_first_aid_2 fae*2 / first_aid_3 fae*3 (rank-keyed mnemonic)
    Dee = 0x1E,   // "dee"  Armour-condition damage dealt (degrade armour) [V] perk_heavy_tip "+15% damage to opponent's armour"; reader = per-hit durability loss
    Osb = 0x1F,   // "osb"  Opponent stamina cost to block your strikes    [V] perk_firm_hand/Firm Grip "blocking your strikes costs an opponent +15% stamina"
    Dsl = 0x20,   // "dsl"  Dodge (combat dodge chance/weight)             [V] perk_light_armor "50% easier to dodge"; read by C_RPGCombat weight calc (sub_1802AE65C)
    Cos = 0x21,   // "cos"  [?] UNKNOWN -- clamp[0,1] zeroed with dodge in limited_combat (dsl=0,cos=0,pbs*2); a defensive reaction lever
    Pac = 0x22,   // "pac"  Poison-apply chance                            [S] q_..poisonApplyMaster pac*10; rusty_edge "chance of poisoning him +50%" (reader's "soiling" label is a weak guess; loc decisive)
    Lpb = 0x23,   // "lpb"  Lockpick break/snap noise (likely)             [I] silent_fiddler "noise a snapping lockpick makes reduced 90%" (paired w/ lpn; not firmly isolated)
    Res = 0x24,   // "res"  [?] UNKNOWN -- only fasttravel (res*3 alongside ors); no desc
    Ors = 0x25,   // "ors"  AI detectability / observability               [S] SIGNED (unclamped) test_invisible & dog_person set ors=-1 = undetectable; fasttravel ors*3
    Ptp = 0x26,   // "ptp"  [?] UNKNOWN -- HC Shakes ptp*1.6 (tremor); reader uses (1.0-ptp) to reduce a directional combat prob
    None = 0x27,  // "---"  not-found sentinel (== count of real ids: 0x00..0x26 = 39)
};

}  // namespace wh::rpgmodule
