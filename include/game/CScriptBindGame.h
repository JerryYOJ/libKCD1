#pragma once
#include "../crysystem/CScriptableBase.h"

// CScriptBindGame — Lua "Game" table
// RTTI: .?AVCScriptBindGame@game@wh@@  vtable: 0x1823f64d8
// Constructor: sub_18217F470
// Registration: sub_182183CA4 (methods), sub_182183AB0 (constants)
// Size: 0x70

namespace wh::game {
class CScriptBindGame : public CScriptableBase {
public:
    Offsets::IScriptSystem* m_pScriptSystem;    // +0x60
    void*                   m_pGame;            // +0x68

    enum EGameCacheResourceType {
        eGameCacheResourceType_Texture                = 0,
        eGameCacheResourceType_TextureDeferredCubemap = 1,
        eGameCacheResourceType_StaticObject           = 2,
        eGameCacheResourceType_Material               = 3,
    };
    enum ESequenceType {
        eSequenceType_Default = 0, eSequenceType_Strength = 1, eSequenceType_Speach = 2,
        eSequenceType_Charisma = 3, eSequenceType_Bribe = 4, eSequenceType_Trigger = 5,
        eSequenceType_Stealth = 6, eSequenceType_FirstAid = 8, eSequenceType_HorseRiding = 11,
        eSequenceType_Repairing = 18, eSequenceType_Drinking_Easy = 26,
        eSequenceType_Drinking_Medium = 27, eSequenceType_Drinking_Hard = 28,
    };

    // int IsDemo(IFunctionHandler* pH);                               // 0x1810BF514 (noop)
    // int IsPlayer(IFunctionHandler* pH);                             // 0x1806F4BEC
    // int SaveGameViaResting(IFunctionHandler* pH);                   // 0x182184AF0
    // int CacheResource(IFunctionHandler* pH);                        // 0x18217FB60
    // int ResetEntity(IFunctionHandler* pH);                          // 0x1821845B8
    // int GetActionControl(IFunctionHandler* pH);                     // 0x1821811D8
    // int LogGameEvent(IFunctionHandler* pH);                         // 0x182182718
    // int ShowTutorial(IFunctionHandler* pH);                         // 0x182185058
    // int ShowTutorialWithCodex(IFunctionHandler* pH);                // 0x182185168
    // int HideTutorial(IFunctionHandler* pH);                         // 0x182182360
    // int BlockTutorials(IFunctionHandler* pH);                       // 0x18217FB20
    // int AllowTutorials(IFunctionHandler* pH);                       // 0x18217FA6C
    // int ShowOverlayTutorial(IFunctionHandler* pH);                  // 0x182184FA8
    // int ShowStatCheckResult(IFunctionHandler* pH);                  // 0x182185000
    // int SetWantedLevel(IFunctionHandler* pH);                       // 0x182184D04
    // int KeybindsRebindInput(IFunctionHandler* pH);                  // 0x182182610
    // int SendInfoText(IFunctionHandler* pH);                         // 0x182184B1C
    // int HideInfoText(IFunctionHandler* pH);                         // 0x1821822C8
    // int ShowItemsTransfer(IFunctionHandler* pH);                    // 0x182184E88
    // int BlockInfoText(IFunctionHandler* pH);                        // 0x18217FAAC
    // int UnblockInfoText(IFunctionHandler* pH);                      // 0x182185434
    // int InventoryModeOnlyCodex(IFunctionHandler* pH);               // 0x182182568
    // int ShowCaptionObjectMessage(IFunctionHandler* pH);             // 0x182184E10
    // int ShowNotification(IFunctionHandler* pH);                     // 0x182184F60
    // int LoadPrefabLibrary(IFunctionHandler* pH);                    // 0x1821826C0
    // int SpawnPrefab(IFunctionHandler* pH);                          // 0x182185350
    // int CreatePrefab(IFunctionHandler* pH);                         // 0x182180E94
    // int MovePrefab(IFunctionHandler* pH);                           // 0x1821827AC
    // int DeletePrefab(IFunctionHandler* pH);                         // 0x182180F48
    // int HidePrefab(IFunctionHandler* pH);                           // 0x182182300
    // int SetPrefabPhase(IFunctionHandler* pH);                       // 0x182184C44
    // int SetPrefabPhaseById(IFunctionHandler* pH);                   // 0x1806DCB50
    // int AddSaveLock(IFunctionHandler* pH);                          // 0x18217FA1C
    // int RemoveSaveLock(IFunctionHandler* pH);                       // 0x182184504
    // int IsLoadingEngineSaveGame(IFunctionHandler* pH);              // 0x1821825A8
    // int ShadowplayStartStop(IFunctionHandler* pH);                  // 0x182184D64
};
static_assert(sizeof(CScriptBindGame) == 0x70);
} // namespace wh::game
