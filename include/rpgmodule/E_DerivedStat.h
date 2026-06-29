#pragma once

#include <cstdint>

// ===========================================================================
// wh::rpgmodule::E_DerivedStat
// ===========================================================================
// The `index` argument of C_Soul::GetDerivedStat / GetDerivedStatFull
// (I_Soul vtable slots 48/49 = sub_180339650 / sub_180339980). It is dispatched
// by a ~110-case switch in sub_180339980.
//
// There is NO `derived_stat` game table in the paks. The authoritative id<->code
// map is a BINARY registry built by the rpgmodule global ctor sub_180128740: a
// 16-byte-stride table at .data 0x1835ABB00..0x1835AC1E0 of {const char* code; int id}.
// The enumerator names below are those verbatim 3-letter codes (binary-VERIFIED
// from the .rdata string literals) — the same codes Lua and the Flash UI use as
// string keys, e.g. player.soul:GetDerivedStat("mst").
//   code -> id converter : C_RPGUtils vtable slot 11 (sub_1802ADE84), returns 0x6E
//                          ("---" / None) when a code is not found.
//   Lua scriptbind       : GetDerivedStat handler sub_1811AF7E0 (reg sub_1811CCC44).
//
// Full names resolved by cross-referencing four sources (workflow verify-derivedstat-codes):
//   (1) the GetDerivedStat switch sub_180339980 -- what each case actually computes;
//   (2) Flash UI enums inventoryEnums.as (E_DER_*_NAME / E_STATE_*_NAME) -> @ui_derivstat_* keys;
//   (3) buff.xml params + perk localized _desc (single-code buffs);
//   (4) localized UI strings (English_xml.pak).
// Confidence tags:  [V] verified (Flash enum + localized name, or switch unambiguously computes it)
//                   [S] strong (single-code buff/perk whose localized desc names the effect)
//                   [I] inferred (suggestive code + context, not pinned)
//                   [?] UNKNOWN (switch computes a value but nothing names it -- do not trust a guess)
// Tally: 20 V / 40 S / 28 I / 22 unknown.
//
// [cached]  = base value is stored in S_SoulDerivedStatCache (C_Soul+0xA94),
//             recomputed by sub_180549518. (ids 0,3,5,0x19,0x1A,0x1D,0x25,0x26,
//             0x48,0x55,0x62,0x63.)
// Engine note: sub_180339980 returns a real computed base only for the cached/
// computed/param/field-read/flag-test ids; many ids return a flat 1.0f or 0.0f
// from the switch and get their real value from the buff/perk path (sub_1803385BC)
// instead -- so a 0.0f here does NOT mean the stat is unused.
// ===========================================================================

namespace wh::rpgmodule {

enum class E_DerivedStat : int32_t {
    Cha = 0x00,   // "cha" Charisma                                    [V] Flash E_DER_CHARISMA_NAME; @ui_derivstat_charisma; [cached]
    Rch = 0x01,   // "rch" [?] UNKNOWN -- switch = cha/rpg_param[0x3B] normalized; no name (reach?)
    Vib = 0x02,   // "vib" Visibility (raw / AI-perceived)            [V] BT sa_test_perception GetDerivedStat('vib'); distinct from Evi UI%
    Evi = 0x03,   // "evi" Visibility (equipment visibility, UI %)    [V] Flash E_DER_VISIBILITY_NAME; @ui_derivstat_equipvisib="Visibility"; [cached]
    Lpv = 0x04,   // "lpv" [?] UNKNOWN -- switch = combat-only time-decaying value (sub_180633698)
    Con = 0x05,   // "con" Conspicuousness                            [V] Flash E_DER_CONSPICUOUSNESS_NAME; @ui_derivstat_conspic; [cached]
    Mst = 0x06,   // "mst" Stamina (current)                          [V] Flash E_STATE_STAMINA_NAME; switch HP-gated, scales Mhs
    Mhs = 0x07,   // "mhs" Max stamina                                [V] Flash E_STATE_STAMINA_MAX_NAME; divisor for Mst/Hlt
    Hlt = 0x08,   // "hlt" Health (fraction)                          [V] switch = Mst/Mhs = 0..1 health fraction
    Sdt = 0x09,   // "sdt" [I] stamina boost? CONFLICT: switch computes a lighting/stealth-detectability value (buff sdt+1000 vs switch)
    Src = 0x0A,   // "src" Stamina consumption/drain factor           [I] god_mode src=0 (no drain), injured_head src+1; paired w/ srg
    Fov = 0x0B,   // "fov" [?] UNKNOWN -- switch = clamped cat-5 skill; no name (field-of-view?)
    Vir = 0x0C,   // "vir" [?] UNKNOWN -- switch = combat-state curve from soul+0x4D4
    Tsr = 0x0D,   // "tsr" Sense (dog Sense stat)                     [V] Flash E_STAT_SENSE_NAME; DogStats.as
    Dtf = 0x0E,   // "dtf" Dice-game throw bonus (winning dice)       [I] perk_perfect_throw (dice perk, NOT thrown weapon)
    Dbf = 0x0F,   // "dbf" Dice-game roll bonus                       [I] perk_perfect_throw group
    Pt1 = 0x10,   // "pt1" Dice-game throw param (tier 1)             [I] perk_perfect_throw group
    Pt5 = 0x11,   // "pt5" Dice-game throw param (tier 5)             [I] perk_perfect_throw group
    Dai = 0x12,   // "dai" [?] UNKNOWN -- switch = normalized skill 0x1F
    Hac = 0x13,   // "hac" Haggling second chances                    [V] Negotiation.lua secondChances; perk_final_offer hac+1
    Lsa = 0x14,   // "lsa" Lockpicking start position                 [S] perk_lockpickers_knack "starting position closer to the end"
    Lfu = 0x15,   // "lfu" Lockpick-break instant-open chance         [S] perk_lucky_thief lfu=0.1 "10% chance of opening instantly"
    Lio = 0x16,   // "lio" Auto-unlock (easy-lock) chance             [S] perk_master_thief "unlock easier locks automatically"
    Cap = 0x17,   // "cap" Carry capacity (max inventory weight)      [V] Flash E_DER_CAPACITY_NAME; @ui_derivstat_inventorycapacity
    Alo = 0x18,   // "alo" Armour load / armour encumbrance           [S] dev buffs test_suppressArmorLoad alo=-0.2/0/0.2
    Oad = 0x19,   // "oad" [?] UNKNOWN -- cached weapon-defense aggregate (cache+0x28); [cached]
    Owa = 0x1A,   // "owa" [?] UNKNOWN -- cached max weapon stat (cache+0x30); [cached]
    Wud = 0x1B,   // "wud" [?] UNKNOWN -- switch = lerp(1.0, rpg[0x84], normSkill2)
    Lvl = 0x1C,   // "lvl" Character level (main level)               [V] Flash E_LEVEL_NAME; @ui_derivstat_mainlevel; weighted avg of 5 main stats
    Noi = 0x1D,   // "noi" Noise                                      [V] Flash E_DER_NOISE_NAME; @ui_derivstat_noise; [cached]
    Fsm = 0x1E,   // "fsm" stealth/detectability factor               [I] sa_test_stealth draws it by vib/con; crouch fsm-0.5
    Nrs = 0x1F,   // "nrs" Speed (movement/run speed)                 [V] Flash E_DER_SPEED_NAME; @ui_derivstat_speed (NOTE: speed BUFFS use Rms, not Nrs)
    Rsa = 0x20,   // "rsa" [?] UNKNOWN -- switch = signed map of cat-1 skill
    Ble = 0x21,   // "ble" Bleeding                                   [V] Scripts GetDerivedStat("ble")='Krvaceni'; buff test_bleeding ble=1
    Ibi = 0x22,   // "ibi" Bleeding rate/interval factor              [S] thickblooded ibi*2 (slower) / HC Haemophilia ibi*0.5 (faster)
    Bow = 0x23,   // "bow" Bow/ranged-weapon factor                   [I] switch scales by weapon-class; archery uses 'weapon_bow' token
    Cow = 0x24,   // "cow" Sprint-charge (bump) impact force          [S] perk_boar "deplete Health/Stamina by bumping at a sprint"
    Aco = 0x25,   // "aco" Charge/impact component                    [I] perk_boar aco*6 (paired cow); [cached]
    Caw = 0x26,   // "caw" Carry weight (current load)                [V] Flash E_DER_WEIGHT_NAME; IGM_Inventory Stat="caw"; [cached]
    Rcw = 0x27,   // "rcw" [?] UNKNOWN -- only cheat golden_egg (rcw=3); switch = availability flag
    Mor = 0x28,   // "mor" Morale                                     [V] Flash E_DER_MORALITY_NAME; sb_combat MoraleForCombat; aliases Dem(0x29)
    Dem = 0x29,   // "dem" Morale (base computation, aliased by Mor)  [S] Mor returns GetDerivedStat(0x29); 0..1 combat-effectiveness blend
    Mcf = 0x2A,   // "mcf" [?] UNKNOWN -- switch = signed quadratic of cat-7 skill
    Obe = 0x2B,   // "obe" Obedience (dog)                            [V] Flash E_DER_OBEDIENCE_NAME; DogStats.as gates morality
    Psr = 0x2C,   // "psr" [?] UNKNOWN -- no switch case; 0 buff usages
    Xpm = 0x2D,   // "xpm" XP gain multiplier                         [S] HC Numbskull xpm*0.6 "lowers acquisition of experience"; soul+0x298
    Osl = 0x2E,   // "osl" [?] UNKNOWN -- no switch case; 0 buff usages
    Mos = 0x2F,   // "mos" [?] UNKNOWN -- switch = flat 1.0; 0 buff usages
    Ore = 0x30,   // "ore" [?] UNKNOWN -- no switch case; 0 buff usages
    Caf = 0x31,   // "caf" [?] UNKNOWN -- no switch case; 0 buff usages
    Rdq = 0x32,   // "rdq" Reading quality (book legibility)          [S] reading_quality + perk_SupremelyAttentive "read faster, learn more"
    Erq = 0x33,   // "erq" Reading bonus (reading comfort)            [S] aliases Rdq; perk_reading_Cushion "sitting comfortably, double reading bonus"
    Sle = 0x34,   // "sle" Sleep state flag                           [S] buff 'sleep' sle=1
    Coc = 0x35,   // "coc" Consciousness flag                         [S] 'unconscious*' buffs coc=0; Mut tests coc==0
    Ufo = 0x36,   // "ufo" Unconsciousness recovery/wake rate         [I] infinite_unconsciousness ufo*0 (never wakes)
    Mut = 0x37,   // "mut" Mute flag (silence voice)                  [S] mute_cutscene mut=1; switch also auto-mutes when unconscious/dead
    Prb = 0x38,   // "prb" Perception priority/range                  [S] percept_prio_*_boost prb>1/5/10; sneak potion prb*1.5
    Fpa = 0x39,   // "fpa" [?] UNKNOWN -- switch = flat 0 (buff path); 0 buff usages
    Apa = 0x3A,   // "apa" Alcohol/drunkenness level                  [I] tippler apa=100; alcoholAntidote apa=0..3
    Cag = 0x3B,   // "cag" Combat aggression                          [I] combat_passivity cag=0, limited_combat cag=1; switch=ComputeComboSteps
    Def = 0x3C,   // "def" Concealment/stealth detection factor       [I] switch = erf light-vs-threshold * stealth skill (code 'def' ambiguous)
    Fol = 0x3D,   // "fol" [?] UNKNOWN -- switch = clamp01(normalized skill 2) (follower?)
    Bad = 0x3E,   // "bad" Badassness (max-opponents driver)          [V] sb_combat: maxOpponentsFromBadassness = GetDerivedStat('bad')
    Dru = 0x3F,   // "dru" Drunkenness                                [S] RTTI-confirmed real; base from buff/perk path
    Poi = 0x40,   // "poi" Poison state flag                          [S] poison potions/weapons poi=1; buff_deadly_poison_desc "You've been poisoned"
    Pos = 0x41,   // "pos" Pickpocket items-revealed count            [S] perk_pocket_sight_1/2/3 pos+1/+2/+8 "reveals items in victim's inventory"
    Ran = 0x42,   // "ran" Anger / angriness level                    [I] robbed_angriness ran+1
    Iex = 0x43,   // "iex" Item-expert (appraisal) level              [S] perk_item_expert "reveals stats for items in a victim's purse"
    Hcm = 0x44,   // "hcm" Horse skittishness/calm (weather)          [I] perk_riders_off_the_storm hcm "horse more skittish" in a storm
    Was = 0x45,   // "was" Hand tremor / shake (alcohol)              [I] HC Shakes was*1.6 "not good for archery/pickpocketing/lockpicking"
    Grm = 0x46,   // "grm" Reputation-gain multiplier                 [I] perk_infamous grm*1.5 "Reputation rises quickly"; group w/ Brm/Jrm
    Brm = 0x47,   // "brm" Reputation multiplier                      [I] perk_local_hero brm*1.5; reputation group
    Drt = 0x48,   // "drt" Clothing/armour dirtiness                  [V] switch = area-weighted per-item dirt byte/255, clamp 0..1; reduces Charisma; [cached]
    Hko = 0x49,   // "hko" Head-hit knockout chance                   [S] perk_headcracker "10% greater chance of knocking out with a blow to the head"
    Enc = 0x4A,   // "enc" [?] UNKNOWN -- switch = skill-0x27-gated 0..1 blend (encumbrance?)
    Fdm = 0x4B,   // "fdm" Fall-damage multiplier                     [S] like_a_feather fdm*0.7 / HC Brittle bones fdm*1.2 "worse injuries when you fall"
    Sma = 0x4C,   // "sma" Book/document trade-price modifier         [I] perk_colleague "trade in books, get a better price" (Cpp:DocumentItemBuff)
    Bma = 0x4D,   // "bma" Herb trade-price/value modifier            [S] perk_botanicus "deal in herbs, get a better price" (Cpp:HerbItemBuff)
    Hgs = 0x4E,   // "hgs" Herb-picking / leg-day stat                [I] perk_leg_day "Herb-picking adds XP to Strength" (domain unclear)
    Pds = 0x4F,   // "pds" Lockpick durability wear rate              [S] perk_lasting_lockpicks pds*0.5 "lockpicks more durable, last twice as long"
    Sha = 0x50,   // "sha" Self-harm / recoil damage                  [I] bow_self_harm_attack sha=5 (single dev buff)
    Pbm = 0x51,   // "pbm" Self-brewed potion sell-price modifier     [S] perk_snake_oil_salesman "sell potions you've brewed for a higher price"
    Rml = 0x52,   // "rml" Looting/hidden-items bonus                 [I] AMBIGUOUS: shakedown "extra money looting a corpse" vs Secret Pockets
    Hml = 0x53,   // "hml" Unhorse (throw-from-horse) susceptibility  [S] perk_jockey hml=0 "horse is fearless" / horse_throwdown_protection
    Bso = 0x54,   // "bso" Stolen-goods sell willingness/value        [I] perk_trustworthy_middleman "merchants more willing to buy stolen items"
    Bld = 0x55,   // "bld" Clothing/armour blood (visible)            [V] switch = area-weighted per-item 'bloodied'/totalArea; reduces Charisma; distinct from Ble; [cached]
    Bba = 0x56,   // "bba" [?] UNKNOWN -- switch reads body/appearance descriptor *(soul+0xBC8+0x1C)
    Arr = 0x57,   // "arr" Intimidation (dialogue) stat               [S] RTTI-confirmed; perk_intimidating_posture "30% more frightening in dialogues"
    Jrm = 0x58,   // "jrm" Reputation multiplier (jail-related)       [I] jail jrm*0, infamous jrm*1.2, local_hero jrm*0.8
    Sur = 0x59,   // "sur" Surrender state flag                       [S] buff 'surrendering' sur=1
    Imm = 0x5A,   // "imm" Immortality flag                           [S] switch = soul byte[0x284] & 0x4; immortality/god_mode imm=1
    Apr = 0x5B,   // "apr" Attack-protection flag                     [S] switch = soul byte[0x284] & 0x2; vip_attackprot apr+1
    Ppr = 0x5C,   // "ppr" Steal/pickpocket-protection flag           [S] switch = soul byte[0x284] & 0x1; vip_stealprot ppr+1
    Upr = 0x5D,   // "upr" Unconsciousness-protection flag            [S] switch = soul byte[0x284] & 0x8; unconsciousness_protection upr=1
    Cds = 0x5E,   // "cds" [?] UNKNOWN -- switch = 1000/lerp(rpg[0x255],rpg[0x254],..) per-1000 rate
    Edm = 0x5F,   // "edm" Equipment/armour durability wear rate      [S] perk_glissade edm*0.8 "weapons and armour suffer 20% less wear"
    Prc = 0x60,   // "prc" Repair effectiveness (code; desc CONFLICTS) [I] perk_repairman desc describes lockpick-return, not repair
    Cdw = 0x61,   // "cdw" Opponent-weapon durability damage          [S] perk_weapon_cruncher "beat opponent in a clinch, damage his weapon 15% more"
    Eqw = 0x62,   // "eqw" Equipped weight                            [S] switch = int *(*(soul+0xC10)+0x80) equipment object; [cached]
    Pla = 0x63,   // "pla" Equipment coverage ratio (plate?)          [I] switch = coverage accum/totalArea; 'pla' label unconfirmed; [cached]
    Wbc = 0x64,   // "wbc" Weapon poison/coating charges              [S] perk_venomous_blade "poison applied to a weapon remains longer"
    Cbi = 0x65,   // "cbi" Self-tailored-clothing charisma bonus      [S] perk_letailleur "clothes you repaired: +0.5 Charisma each, max +2"
    Nbi = 0x66,   // "nbi" Self-padded-armour noise modifier          [S] perk_padding "armour with padding you fixed, not so noisy"
    Alc = 0x67,   // "alc" Alcoholism level                           [S] buff 'alcoholism' alc+1 "Str/Agi/Vit/Speech/Charisma reduced by -3"
    Map = 0x68,   // "map" [?] UNKNOWN -- only 'targeted by ranged' map*0.75; switch = stealth-ish equip value
    Adm = 0x69,   // "adm" Alcohol digestion/metabolism rate          [S] q_*_alchoholDigestionBoost adm=30/60/500
    Btw = 0x6A,   // "btw" Animal wariness / flee distance            [I] perk_animal_in_heart "wild animals notice you less"
    Owl = 0x6B,   // "owl" Night-vision factor                        [S] potion_owl owl+1 "see better in the dark and gloom"
    Rms = 0x6C,   // "rms" Movement/run speed multiplier              [S] perk_dread_steed rms*1.15 "canter and gallop 15% faster"; the speed-BUFF code (cf. Nrs)
    Deb = 0x6D,   // "deb" Confidence/standing stat                   [I] RTTI-confirmed real; alpha_male deb+1 "feeling self-confident"; exact name unconfirmed

    None = 0x6E,  // "---" sentinel: returned by the code->id converter (sub_1802ADE84)
                  // when a code is not found. Also == the count of real ids (0x00..0x6D = 110).
};

}  // namespace wh::rpgmodule
