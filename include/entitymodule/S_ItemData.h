#pragma once

#include "../CryEngine/CryCommon/CryExtension/CryGUID.h"
#include "../CryEngine/CryCommon/CryString.h"   // CryStringT<char> (the string columns)
// <cstdint> + CryGUID base types come from PCH.h.

// ===========================================================================
// wh::entitymodule item-class data hierarchy (S_ItemData + 27 derived types).
//
// The runtime item-CLASS objects pointed to by C_Item::m_pClassData (GetClassDef
// sub_1802D02D0): one per item class, built from the item.xml tables. RE'd 2026-06:
//   * hierarchy  <- RTTI class-hierarchy descriptors (COL->CHD->BaseClassArray);
//   * field offsets/types/order <- every type's ctor;
//   * concrete sizes + the E_ItemDataType id enum <- the factory sub_18108568C
//     (operator new(sizeof(T)) per id);
//   * FIELD NAMES <- master loader sub_1810869C4 + its ~24 per-sub-table loaders
//     (field-offset<-row-offset), cross-referenced with each sub-table's column schema
//     (Libs/Tables/item/<table>.xml). Each sub-loader is dispatched by a cumulative
//     type-flag bitmask in vtable slot[1] ((flags & MASK) == MASK). Within a table the
//     non-PK columns pack by size-class (4B real/int, 8B string, 16B uuid, 1B bool),
//     alphabetical within a class, assigned to that class's row offsets in ascending
//     order — a rule repeatedly confirmed by max(x,1) clamps landing on str_req/max_status
//     and the FK resolve landing on armor_subtype_id. The PK column item_id (uuid) is the
//     16-byte row header; columns shown "<- table" are the verified source.
//
//   S_ItemData (0x20) -> S_PickableItemData (0x60) -> S_PlayerItemData (0x78) -> ...
//   See each struct for its parent. Sizes are the factory-verified totals.
//   String columns are CryStringT<char> (ref-counted; empty = sub_18028D060()+3 sentinel).
//   S_TypedItemData = empty type-tag mixin (RTTI secondary base, no layout impact, omitted).
//   Fields written only by the ctor (never by a loader) are marked "[ctor-only]".
// ===========================================================================

namespace wh { namespace entitymodule {

// Type discriminant (item.item_category_id) of the factory sub_18108568C. id 7 reserved.
enum class E_ItemDataType : int {
    Misc = 0, MeleeWeapon = 1, MissileWeapon = 2, Ammo = 3, Armor = 4, Food = 5,
    Money = 6, Document = 8, AlchemyMaterial = 9, Herb = 0xA, AlchemyBase = 0xB,
    NPCTool = 0xC, Ointment = 0xD, Potion = 0xE, Die = 0xF, Helmet = 0x10,
    Key = 0x11, KeyRing = 0x12, Cooking = 0x13,
};

// --- root ------------------------------------------------------------------
struct S_ItemData {                             // ctor sub_181080034, vtable 0x1822E15D0
    virtual ~S_ItemData();                      // +0x00
    CryGUID           m_itemId;                 // +0x08  <- item.item_id  (the class GUID)
    CryStringT<char>  m_itemName;               // +0x18  <- item.item_name
};
static_assert(sizeof(S_ItemData) == 0x20);

struct S_AlchemyBaseData : S_ItemData {         // ctor sub_18107FA28, vtable 0x1826C2848
    CryStringT<char>  m_uiName;                 // +0x20  <- alchemy_base.ui_name
};
static_assert(sizeof(S_AlchemyBaseData) == 0x28);   // factory id 0xB

// --- pickable --------------------------------------------------------------
struct S_PickableItemData : S_ItemData {        // ctor sub_181080348, vtable 0x1822E1938
    CryStringT<char>  m_entityScript;           // +0x20  <- pickable_item.entity_script
    CryStringT<char>  m_material;               // +0x28  <- pickable_item.material
    CryStringT<char>  m_model;                  // +0x30  <- pickable_item.model
    float             m_ownerFadingCoef;        // +0x38  <- pickable_item.owner_fading_coef
    int32_t           m_price;                  // +0x3C  <- pickable_item.price
    float             m_visibilityCoef;         // +0x40  <- pickable_item.visibility_coef
    float             m_weight;                 // +0x44  <- pickable_item.weight
    uint64_t          m_runtime48[3];           // +0x48  [ctor-only] runtime, zero-init
};
static_assert(sizeof(S_PickableItemData) == 0x60);

struct S_NPCToolData : S_PickableItemData {     // ctor sub_181080244, vtable 0x1826C3158
    int32_t           m_npcToolSubtypeId;       // +0x60  <- npc_tool.npc_tool_subtype_id
    int32_t           m_npcToolTypeId;          // +0x64  <- npc_tool.npc_tool_type_id
    int32_t           m_manipulationType;       // +0x68  <- npc_tool.manipulation_type
    uint32_t          _pad6C;                   // +0x6C
};
static_assert(sizeof(S_NPCToolData) == 0x70);       // factory id 0xC

struct S_PlayerItemData : S_PickableItemData {  // ctor sub_1810803B4, vtable 0x1822E1818
    int32_t           m_iconId;                 // +0x60  <- player_item.icon_id
    uint32_t          _pad64;                   // +0x64
    CryStringT<char>  m_uiName;                 // +0x68  <- player_item.ui_name
    CryStringT<char>  m_uiInfo;                 // +0x70  <- player_item.ui_info
};
static_assert(sizeof(S_PlayerItemData) == 0x78);

// --- equippables -----------------------------------------------------------
struct S_EquippableItemData : S_PlayerItemData {  // ctor sub_18107FE68, vtable 0x1822E16E0
    float             m_charisma;               // +0x78  <- equippable_item.charisma
    float             m_conspicuousness;        // +0x7C  <- equippable_item.conspicuousness
    float             m_rpgBuffWeight;          // +0x80  <- equippable_item.rpg_buff_weight
    int32_t           m_socialClassId;          // +0x84  <- equippable_item.social_class_id
    float             m_visibility;             // +0x88  <- equippable_item.visibility
    int32_t           m_wealthLevel;            // +0x8C  <- equippable_item.wealth_level
};
static_assert(sizeof(S_EquippableItemData) == 0x90);

struct S_WeaponEquipData : S_EquippableItemData {  // accessor sub_18044DA9C, vtable 0x1822E1460
    // no own fields — intermediate base for weapons & ammo (just swaps the vtable)
};
static_assert(sizeof(S_WeaponEquipData) == 0x90);

struct S_WeaponData : S_WeaponEquipData {        // ctor sub_181080754, vtable 0x1822E12E8
    void*             m_p90;                    // +0x90  [ctor-only] default &unk_1835A2820
    uint64_t          m_q98;                    // +0x98  [ctor-only] runtime
    int32_t           m_maxStatus;              // +0xA0  <- weapon.max_status
    int32_t           m_strReq;                 // +0xA4  <- max(weapon.str_req, 1)
    int32_t           m_weaponClassId;          // +0xA8  <- weapon.weapon_class_id
    int32_t           m_weaponSubClassId;       // +0xAC  <- weapon.weapon_sub_class_id
    uint8_t           m_isBreakable;            // +0xB0  <- weapon.is_breakable
    uint8_t           _padB1[7];                // +0xB1
    CryStringT<char>  m_holsterMaterial;        // +0xB8  <- weapon.holster_material
    CryStringT<char>  m_holsterModel;           // +0xC0  <- weapon.holster_model
    // (weapon.agi_req / weapon.defense are not copied into this object)
};
static_assert(sizeof(S_WeaponData) == 0xC8);

struct S_MeleeWeaponData : S_WeaponData {        // ctor sub_1810801A4, vtable 0x1826C17C8
    float             m_attack;                 // +0xC8  <- melee_weapon.attack
    float             m_smashAttMod;            // +0xCC  <- melee_weapon.smash_att_mod
    float             m_slashAttMod;            // +0xD0  <- melee_weapon.slash_att_mod
    float             m_stabAttMod;             // +0xD4  <- melee_weapon.stab_att_mod
};
static_assert(sizeof(S_MeleeWeaponData) == 0xD8);   // factory id 1

struct S_MissileWeaponData : S_WeaponData {      // ctor sub_1810801EC, vtable 0x1826C1F20
    float             m_power;                  // +0xC8  <- missile_weapon.power
    uint32_t          _padCC;                   // +0xCC
    void*             m_pD0;                    // +0xD0  [ctor-only] = sub_18073DAD0() handle
    uint64_t          m_qD8;                    // +0xD8  [ctor-only] runtime
    CryStringT<char>  m_weaponSoundSwitch;      // +0xE0  <- missile_weapon.weapon_sound_switch
};
static_assert(sizeof(S_MissileWeaponData) == 0xE8); // factory id 2

struct S_AmmoData : S_WeaponEquipData {           // ctor sub_18107FB24, vtable 0x1826C26D0
    int32_t           m_ammoClassId;            // +0x90  <- ammo.ammo_class_id
    int32_t           m_id94;                   // +0x94  [ctor-only] -1
    float             m_slashAtt;               // +0x98  <- ammo.slash_att
    float             m_powerMod;               // +0x9C  <- ammo.power_mod
    float             m_smashAtt;               // +0xA0  <- ammo.smash_att
    float             m_stabAtt;                // +0xA4  <- ammo.stab_att
    CryStringT<char>  m_inquiverMaterial;       // +0xA8  <- ammo.inquiver_material
    CryStringT<char>  m_inquiverModel;          // +0xB0  <- ammo.inquiver_model
    CryGUID           m_brokenItemId;           // +0xB8  <- ammo.broken_item_id
};
static_assert(sizeof(S_AmmoData) == 0xC8);          // factory id 3

struct S_ArmorData : S_EquippableItemData {       // ctor sub_18107FBB0, vtable 0x1826C3018
    int32_t           m_armorSubtypeId;         // +0x90  <- armor.armor_subtype_id (FK for m_pArchetype)
    int32_t           m_armorTypeId;            // +0x94  <- armor.armor_type_id
    CryGUID           m_clothing2Id;            // +0x98  <- armor.clothing2_id
    CryGUID           m_clothingId;             // +0xA8  <- armor.clothing_id
    void*             m_pArchetype;             // +0xB8  FK-resolved from m_armorSubtypeId (sub_180303B1C)
    int32_t           m_maxStatus;              // +0xC0  <- armor.max_status
    int32_t           m_color;                  // +0xC4  <- armor.color
    float             m_noise;                  // +0xC8  <- armor.noise
    float             m_slashDef;               // +0xCC  <- armor.slash_def
    float             m_smashDef;               // +0xD0  <- armor.smash_def
    float             m_dyeZones[12];           // +0xD4  <- armor dye block: {brightness, color_hue,
                                                //         color_saturation, zone1_b/h/s, zone2_b/h/s,
                                                //         zone3_b/h/s} (copied as 3 OWORDs; per-element
                                                //         order inferred alphabetical)
    float             m_stabDef;                // +0x104 <- armor.stab_def
    float             m_strReq;                 // +0x108 <- max(armor.str_req, 1)
    int32_t           m_superfactionId;         // +0x10C <- armor.superfaction_id
    uint8_t           m_isUnderwear;            // +0x110 <- armor.is_underwear
    uint8_t           _pad111[7];               // +0x111
};
static_assert(sizeof(S_ArmorData) == 0x118);        // factory id 4

struct S_HelmetData : S_ArmorData {               // accessor sub_181083000, vtable 0x1822E0B50
    int32_t           m_visorTypeId;            // +0x118 <- helmet.visor_type_id
    uint32_t          _pad11C;                  // +0x11C
};
static_assert(sizeof(S_HelmetData) == 0x120);       // factory id 0x10

// --- divisibles (stackables) -----------------------------------------------
struct S_DivisibleItemData : S_PlayerItemData {   // ctor sub_18107FD7C, vtable 0x1826C2B98
    uint8_t           m_isDivisible;            // +0x78  <- divisible_item.is_divisible
    uint8_t           _pad79[7];                // +0x79
    CryStringT<char>  m_containerMaterial;      // +0x80  <- divisible_item.container_material
    CryStringT<char>  m_containerModel;         // +0x88  <- divisible_item.container_model
};
static_assert(sizeof(S_DivisibleItemData) == 0x90);

struct S_MoneyData : S_DivisibleItemData {        // factory-inlined, vtable 0x1822E0908
    // no own fields (factory id 6)
};
static_assert(sizeof(S_MoneyData) == 0x90);

struct S_CookingData : S_DivisibleItemData {      // factory-inlined, vtable 0x1822E0A28
    // no own fields (factory id 0x13)
};
static_assert(sizeof(S_CookingData) == 0x90);

struct S_KeyRingData : S_DivisibleItemData {      // ctor sub_181080174, vtable 0x1826C2CB8
    int32_t           m_keyringTypeId;          // +0x90  <- keyring.keyring_type_id
    int32_t           m_id94;                   // +0x94  [ctor-only] -1
};
static_assert(sizeof(S_KeyRingData) == 0x98);       // factory id 0x12

struct S_DieData : S_DivisibleItemData {          // ctor sub_18107FD30, vtable 0x1826C2EF8
    int32_t           m_sideValue[6];           // +0x90  <- die.side_value_1..6
    float             m_sideWeight[6];          // +0xA8  <- die.side_weight_1..6
};
static_assert(sizeof(S_DieData) == 0xC0);           // factory id 0xF

struct S_ConsumableData : S_DivisibleItemData {   // ctor sub_18107FD00, vtable 0x1826C2A78
    CryGUID           m_buffId;                 // +0x90  <- consumable_item.buff_id
};
static_assert(sizeof(S_ConsumableData) == 0xA0);

struct S_OintmentData : S_ConsumableData {        // ctor sub_181080278, vtable 0x1826C22F8
    int32_t           m_ointmentSubtypeId;      // +0xA0  <- ointment_item.ointment_item_subtype_id
    int32_t           m_ointmentTypeId;         // +0xA4  <- ointment_item.ointment_item_type_id
    float             m_efficiency;             // +0xA8  <- ointment_item.efficiency
    uint32_t          _padAC;                   // +0xAC
};
static_assert(sizeof(S_OintmentData) == 0xB0);      // factory id 0xD

struct S_FoodData : S_ConsumableData {            // ctor sub_18107FEA8, vtable 0x1826C2570
    float             m_nutritionBenefit;       // +0xA0  <- food.nutrition_benefit
    float             m_refreshBenefit;         // +0xA4  <- food.refresh_benefit
    float             m_alcoholContent;         // +0xA8  <- food.alcohol_content
    float             m_decayTimeHours;         // +0xAC  <- food.decay_time_hours
    int32_t           m_foodSubtypeId;          // +0xB0  <- food.food_subtype_id
    int32_t           m_foodTypeId;             // +0xB4  <- food.food_type_id
    float             m_healthBenefit;          // +0xB8  <- food.health_benefit
    int32_t           m_maxStatus;              // +0xBC  <- max(food.max_status, 1)
    CryGUID           m_cookedItemId;           // +0xC0  <- food.cooked_item_id
    CryGUID           m_driedItemId;            // +0xD0  <- food.dried_item_id
    CryGUID           m_smokedItemId;           // +0xE0  <- food.smoked_item_id
    float             m_shortTermNutritionRatio;// +0xF0  <- food.short_term_nutrition_benefit_ratio
    uint32_t          _padF4;                   // +0xF4
};
static_assert(sizeof(S_FoodData) == 0xF8);          // factory id 5

struct S_PotionData : S_FoodData {                // ctor sub_1810803F8, vtable 0x1826C2428
    CryGUID           m_weaponBuffId;           // +0xF8  <- potion.weapon_buff_id
};
static_assert(sizeof(S_PotionData) == 0x108);       // factory id 0xE

struct S_AlchemyMaterialData : S_DivisibleItemData {  // ctor sub_18107FAF4, vtable 0x1826C21D0
    int32_t           m_subtypeId;              // +0x90  <- alchemy_material.alchemy_material_subtype_id
    int32_t           m_typeId;                 // +0x94  <- alchemy_material.alchemy_material_type_id
};
static_assert(sizeof(S_AlchemyMaterialData) == 0x98);   // factory id 9

struct S_HerbData : S_AlchemyMaterialData {       // ctor sub_18107FFCC, vtable 0x1826C20A8
    int32_t           m_id98;                   // +0x98  [ctor-only] -1
    uint32_t          _pad9C;                   // +0x9C
    CryStringT<char>  m_latinName;              // +0xA0  <- herb.latin_name
    CryStringT<char>  m_uiDesc;                 // +0xA8  <- herb.ui_desc
    CryStringT<char>  m_uiEffect;               // +0xB0  <- herb.ui_effect
    CryStringT<char>  m_uiOccur;                // +0xB8  <- herb.ui_occur
    uint8_t           m_poisonous;              // +0xC0  <- herb.poisonous
    uint8_t           _padC1[3];                // +0xC1
    int32_t           m_element1Id;             // +0xC4  <- herb.element1_id
    int32_t           m_element2Id;             // +0xC8  <- herb.element2_id
    uint32_t          _padCC;                   // +0xCC
};
static_assert(sizeof(S_HerbData) == 0xD0);          // factory id 0xA

// --- questibles (quest / story items) --------------------------------------
struct S_QuestibleItemData : S_PlayerItemData {   // ctor sub_181080454, vtable 0x1826C2958
    uint8_t           m_isQuest;                // +0x78  <- questible_item.is_quest
    uint8_t           _pad79[7];                // +0x79
};
static_assert(sizeof(S_QuestibleItemData) == 0x80);

struct S_MiscData : S_QuestibleItemData {         // factory-inlined, vtable 0x1826C1680
    int32_t           m_miscSubtypeId;          // +0x80  <- misc.misc_subtype_id
    int32_t           m_miscTypeId;             // +0x84  <- misc.misc_type_id
};
static_assert(sizeof(S_MiscData) == 0x88);          // factory id 0

struct S_KeyData : S_QuestibleItemData {          // ctor sub_181080144, vtable 0x1826C2DD8
    int32_t           m_keySubtypeId;           // +0x80  <- key.key_subtype_id
    int32_t           m_keyTypeId;              // +0x84  <- key.key_type_id
};
static_assert(sizeof(S_KeyData) == 0x88);           // factory id 0x11

struct S_DocumentData : S_QuestibleItemData {     // ctor sub_18107FDC4, vtable 0x1826C1DE8
    int32_t           m_documentUiLayout;       // +0x80  <- document.document_ui_layout
    int32_t           m_id84;                   // +0x84  [ctor-only] -1
    int32_t           m_classId;                // +0x88  <- document.class_id
    float             m_lengthInGameHours;      // +0x8C  <- document.length_in_game_hours
    int32_t           m_recipeId;               // +0x90  <- document.recipe_id
    int32_t           m_textId;                 // +0x94  <- document.text_id
};
static_assert(sizeof(S_DocumentData) == 0x98);      // factory id 8

}} // namespace wh::entitymodule
