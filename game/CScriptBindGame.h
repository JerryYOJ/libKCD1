#pragma once

#include "../crysystem/CScriptableBase.h"

// -----------------------------------------------
// CScriptBindGame — Lua "Game" table
// -----------------------------------------------
// RTTI: .?AVCScriptBindGame@game@wh@@
// vtable: 0x1823f64d8
// Constructor: sub_18217F470
// Registration: sub_182183CA4 (methods), sub_182183AB0 (constants)
// Size: 0x70

namespace wh::game {

class CScriptBindGame : public CScriptableBase {
public:
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x60
    void*                   m_pGame;            // +0x68  CGame* or IGameFramework*

    enum EGameCacheResourceType {
        eGameCacheResourceType_Texture                = 0,
        eGameCacheResourceType_TextureDeferredCubemap = 1,
        eGameCacheResourceType_StaticObject           = 2,
        eGameCacheResourceType_Material               = 3,
    };

    enum ESequenceType {
        eSequenceType_Default         = 0,
        eSequenceType_Strength        = 1,
        eSequenceType_Speach          = 2,
        eSequenceType_Charisma        = 3,
        eSequenceType_Bribe           = 4,
        eSequenceType_Trigger         = 5,
        eSequenceType_Stealth         = 6,
        eSequenceType_FirstAid        = 8,
        eSequenceType_HorseRiding     = 11,
        eSequenceType_Repairing       = 18,
        eSequenceType_Drinking_Easy   = 26,
        eSequenceType_Drinking_Medium = 27,
        eSequenceType_Drinking_Hard   = 28,
    };

    // Lua methods (35)
    int IsDemo(IFunctionHandler* pH);                                               // 0x1810BF514
    int IsPlayer(IFunctionHandler* pH);                                             // 0x1806F4BEC
    int SaveGameViaResting(IFunctionHandler* pH);                                   // 0x182184AF0
    int CacheResource(IFunctionHandler* pH, const char* whoIsRequesting, const char* resourceName, int resourceType, int resourceFlags); // 0x18217FB60
    int ResetEntity(IFunctionHandler* pH);                                          // 0x1821845B8
    int GetActionControl(IFunctionHandler* pH, const char* actionMap, const char* actionId); // 0x1821811D8
    int LogGameEvent(IFunctionHandler* pH, const char* message);                    // 0x182182718
    int ShowTutorial(IFunctionHandler* pH, const char* text);                       // 0x182185058
    int ShowTutorialWithCodex(IFunctionHandler* pH, const char* text, const char* perkId); // 0x182185168
    int HideTutorial(IFunctionHandler* pH);                                         // 0x182182360
    int BlockTutorials(IFunctionHandler* pH);                                       // 0x18217FB20
    int AllowTutorials(IFunctionHandler* pH);                                       // 0x18217FA6C
    int ShowOverlayTutorial(IFunctionHandler* pH, const char* text);                // 0x182184FA8
    int ShowStatCheckResult(IFunctionHandler* pH, const char* stat, int checkResult); // 0x182185000
    int SetWantedLevel(IFunctionHandler* pH, int level);                            // 0x182184D04
    int KeybindsRebindInput(IFunctionHandler* pH, const char* controller, const char* superaction, int slot, const char* input); // 0x182182610
    int SendInfoText(IFunctionHandler* pH, const char* text);                       // 0x182184B1C
    int HideInfoText(IFunctionHandler* pH);                                         // 0x1821822C8
    int ShowItemsTransfer(IFunctionHandler* pH, const char* itemClassId, int amount); // 0x182184E88
    int BlockInfoText(IFunctionHandler* pH, const char* infoTextCategory);          // 0x18217FAAC
    int UnblockInfoText(IFunctionHandler* pH, const char* infoTextCategory);        // 0x182185434
    int InventoryModeOnlyCodex(IFunctionHandler* pH, bool enable);                  // 0x182182568
    int ShowCaptionObjectMessage(IFunctionHandler* pH, const char* captionObjectName); // 0x182184E10
    int ShowNotification(IFunctionHandler* pH, const char* message);                // 0x182184F60
    int LoadPrefabLibrary(IFunctionHandler* pH, const char* libraryName);           // 0x1821826C0
    int SpawnPrefab(IFunctionHandler* pH, EntityId entityId, const char* libname, const char* prefabname, int seed, int maxSpawn); // 0x182185350
    int CreatePrefab(IFunctionHandler* pH, EntityId entityId, const char* libname, const char* prefabname, int maxSpawn); // 0x182180E94
    int MovePrefab(IFunctionHandler* pH);                                           // 0x1821827AC
    int DeletePrefab(IFunctionHandler* pH);                                         // 0x182180F48
    int HidePrefab(IFunctionHandler* pH, EntityId entityId, bool value);            // 0x182182300
    int SetPrefabPhase(IFunctionHandler* pH, EntityId entityId, const char* categoryName, const char* phase); // 0x182184C44
    int SetPrefabPhaseById(IFunctionHandler* pH, EntityId entityId, const char* categoryName, int idx); // 0x1806DCB50
    int AddSaveLock(IFunctionHandler* pH, const char* name_of_lock, const char* ui_description); // 0x18217FA1C
    int RemoveSaveLock(IFunctionHandler* pH, const char* name_of_lock);             // 0x182184504
    int IsLoadingEngineSaveGame(IFunctionHandler* pH);                              // 0x1821825A8
    int ShadowplayStartStop(IFunctionHandler* pH);                                  // 0x182184D64
};
static_assert(sizeof(CScriptBindGame) == 0x70);

} // namespace wh::game
