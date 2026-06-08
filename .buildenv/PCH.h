// Precompiled header for KCD RE project.
// Body mirrors the proven .buildenv/check_sizes.cpp include set, IN THE SAME ORDER (so the
// CryEngine platform macros / assert / smartptr.h resolve correctly), plus the extra RE'd
// headers from the old PCH (Offsets vtables, guimodule, perk + soul-list, BT node catalog).
//
// EXCLUDED on purpose (would break the PCH):
//   * *ScriptBind* headers      -> need IFunctionHandler from the CryEngine script SDK
//   * databasemodule/*          -> I_DatabaseListener/I_DatabaseModule redefinition conflicts
//   * the 300+ table-row headers -> include individually as needed
// std::hash<wh::framework::WUID> is provided by entitymodule/C_Inventory.h (do NOT redefine here).
#pragma once

// ---- Standard library (pulled once) ----
#include <cstdint>
#include <cstring>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <functional>
#include <string>

// ---- CryEngine SDK types (NOT the interfuscated interfaces) ----
#include "CryEngine/CryCommon/BaseTypes.h"
#include "CryEngine/CryCommon/CryExtension/CryGUID.h"

// ---- Common RE utility predicate ----
namespace wh::guimodule {
struct CStrLess {
    bool operator()(const char* a, const char* b) const { return std::strcmp(a, b) < 0; }
};
}  // namespace wh::guimodule

// ============================================================================
// RE'd headers — proven set/order (mirrors check_sizes.cpp)
// ============================================================================
#include "rpgmodule/C_Soul.h"
#include "rpgmodule/C_RPGModule.h"
#include "rpgmodule/C_Effect.h"
#include "rpgmodule/S_RpgParams.h"
#include "rpgmodule/S_PerkPointCounters.h"
#include "crysystem/CXConsole.h"
#include "crysystem/CLog.h"
#include "crysystem/CScriptSystem.h"
#include "framework/I_Action.h"
#include "framework/I_ActionImpl.h"
#include "framework/C_BaseModule.h"
#include "framework/C_ReadinessObserver.h"
#include "framework/I_ReadinessTask.h"
#include "framework/C_CrySaveGameHelper.h"
#include "framework/C_CryLoadGameHelper.h"
#include "framework/C_PlayerProfileWHManager.h"
#include "framework/C_SaveGameManager.h"
#include "game/S_GameContext.h"
#include "animationmodule/C_AnimationDatabase.h"
#include "animationmodule/I_SceneListener.h"
#include "entitymodule/I_ItemAttachmentListener.h"
#include "entitymodule/C_Item.h"
#include "entitymodule/S_ItemData.h"
#include "entitymodule/C_ItemRuntimeData.h"
#include "entitymodule/C_Inventory.h"
#include "entitymodule/C_EquipmentManager.h"
#include "combatmodule/I_CombatActor.h"
#include "combatmodule/I_CombatActorAction.h"
#include "combatmodule/C_CombatComboData.h"
#include "combatmodule/C_CombatDatabase.h"
#include "combatmodule/C_CombatModule.h"
#include "combatmodule/C_CombatScene.h"
#include "combatmodule/C_CombatActor.h"
#include "combatmodule/I_CombatTarget.h"
#include "combatmodule/S_CombatActorState.h"
#include "combatmodule/C_CombatActorObject.h"
#include "combatmodule/C_CombatActorUpdatedObject.h"
#include "combatmodule/C_CombatTrigger.h"
#include "combatmodule/C_CombatSlotTrigger.h"
#include "combatmodule/C_CombatTriggerCombo.h"
#include "combatmodule/C_CombatTriggerPerfectBlock.h"
#include "combatmodule/C_CombatTriggerRiposte.h"
#include "combatmodule/C_CombatTriggerSyncPerfectBlock.h"
#include "combatmodule/C_CombatTriggerSyncRiposte.h"
#include "combatmodule/C_CombatTriggerSyncDodge.h"
#include "combatmodule/C_CombatComboManager.h"
#include "combatmodule/C_CombatActionFactory.h"
#include "combatmodule/C_CombatActorActionManager.h"
#include "combatmodule/C_CombatActorHuntAttack.h"
#include "combatmodule/C_CombatActorHorsePullDown.h"
#include "combatmodule/C_CombatActorMercyKill.h"
#include "combatmodule/C_CombatActorActionT.h"
#include "combatmodule/S_CombatActorActionAttackParams.h"
#include "combatmodule/S_CombatActorActionStaticAttackParams.h"
#include "combatmodule/S_CombatActorActionSyncAttackParams.h"
#include "combatmodule/S_CombatActorActionBlockParams.h"
#include "combatmodule/S_CombatActorActionPerfectBlockParams.h"
#include "combatmodule/S_CombatActorActionComposedRipostePerfectBlockParams.h"
#include "combatmodule/S_CombatActorActionHitParams.h"
#include "combatmodule/S_CombatActorActionFreeBlockParams.h"
#include "combatmodule/S_CombatActorActionBlockTriggerParams.h"
#include "combatmodule/S_CombatActorActionGuardParams.h"
#include "combatmodule/S_CombatActorActionGuardMovementParams.h"
#include "combatmodule/S_CombatActorActionGuardSyncMovementParams.h"
#include "combatmodule/S_CombatActorActionSyncHitParams.h"
#include "combatmodule/S_CombatActorActionSyncPerfectBlockHitParams.h"
#include "combatmodule/S_CombatActorActionSyncTransitionParams.h"
#include "combatmodule/S_CombatActorActionPoseModifierParams.h"
#include "combatmodule/C_CombatActionHelper.h"
#include "combatmodule/I_CombatActorActionBlock.h"
#include "combatmodule/I_CombatActionHelperOwner.h"
#include "combatmodule/C_CombatActorActionAttack.h"
#include "combatmodule/C_CombatActorActionStaticAttack.h"
#include "combatmodule/C_CombatActorActionSyncAttack.h"
#include "combatmodule/C_CombatActorActionBlock.h"
#include "combatmodule/C_CombatActorActionBlockTrigger.h"
#include "combatmodule/C_CombatActorActionFreeBlock.h"
#include "combatmodule/C_CombatActorActionPerfectBlock.h"
#include "combatmodule/C_CombatActorActionComposedRipostePerfectBlock.h"
#include "combatmodule/C_CombatActorActionSyncPerfectBlock.h"
#include "combatmodule/C_CombatActorActionSyncPerfectBlockHit.h"
#include "combatmodule/C_CombatActorActionHit.h"
#include "combatmodule/C_CombatActorActionSyncHit.h"
#include "combatmodule/C_CombatActorActionSyncTransition.h"
#include "combatmodule/C_CombatActorActionGuard.h"
#include "combatmodule/C_CombatActorActionGuardMovement.h"
#include "combatmodule/C_CombatActorActionGuardSyncMovement.h"
#include "combatmodule/C_CombatActorActionRiderMovement.h"
#include "combatmodule/C_CombatActorActionPoseModifier.h"
#include "combatmodule/S_CombatSettings.h"
#include "entitymodule/C_Player.h"
#include "Offsets/vtables/IGameObject.h"
#include "Offsets/vtables/IActorSystem.h"
#include "Offsets/vtables/IEntitySystemSink.h"
#include "Offsets/vtables/IEntityEventListener.h"
#include "xgenaimodule/BehaviorTree/I_Node.h"
#include "xgenaimodule/BehaviorTree/I_DebugNode.h"
#include "xgenaimodule/BehaviorTree/C_Node.h"
#include "xgenaimodule/BehaviorTree/C_Decorator.h"
#include "xgenaimodule/BehaviorTree/C_Composite.h"
#include "xgenaimodule/BehaviorTree/C_Composites.h"
#include "xgenaimodule/BehaviorTree/C_Gate.h"
#include "xgenaimodule/BehaviorTree/C_NodeWrapper.h"
#include "xgenaimodule/BehaviorTree/C_NodeContext.h"
#include "xgenaimodule/BehaviorTree/C_Barrier.h"
#include "rpgmodule/buff/C_BuffInstanceBase.h"
#include "rpgmodule/buff/C_SoulBuffInstance.h"
#include "rpgmodule/buff/C_ConstantSoulBuffInstance.h"
#include "rpgmodule/buff/C_TimedSoulBuffInstance.h"
#include "rpgmodule/buff/C_BuffManager.h"
#include "framework/C_HashMap.h"
#include "framework/S_TypeFactoryEntry.h"
#include "rpgmodule/buff/C_BuffFactory.h"
#include "rpgmodule/buff/C_BuffInitParamsDefault.h"
#include "rpgmodule/buff/C_InjuredBuffInitParams.h"
#include "rpgmodule/buff/C_SleepBuffInitParams.h"
#include "rpgmodule/buff/C_MoraleContextBuffInitParams.h"
#include "rpgmodule/buff/C_ItemHealthCheckingBuffInitParams.h"

// ============================================================================
// Additional RE'd headers (platform already set up above, so safe to append)
// ============================================================================
#include "crysystem/SSystemGlobalEnvironment.h"
#include "Offsets/Offsets.h"
#include "Offsets/vtables/VCall.h"
#include "Offsets/vtables/IEntity.h"
#include "Offsets/vtables/IScriptTable.h"
#include "rpgmodule/I_Soul.h"
#include "rpgmodule/I_CombatSoul.h"
#include "rpgmodule/E_DerivedStat.h"
#include "rpgmodule/E_RPGStat.h"
#include "rpgmodule/E_RPGSkill.h"
#include "rpgmodule/S_SoulArchetype.h"
#include "rpgmodule/C_SoulPropertyNotifier.h"
#include "rpgmodule/C_SoulList.h"
#include "rpgmodule/C_PerkList.h"
#include "rpgmodule/S_PerkSubsystem.h"
#include "rpgmodule/S_PerkManagement.h"
#include "rpgmodule/S_PerkDefinition.h"
#include "rpgmodule/C_FactionManager.h"
#include "rpgmodule/buff/S_ModifierNode.h"
#include "rpgmodule/buff/E_ModifierOp.h"
#include "rpgmodule/buff/E_BuffStat.h"
#include "framework/WUID.h"
#include "framework/CryDeferrable.h"
#include "framework/C_Signal.h"
#include "entitymodule/I_InventoryListener.h"
#include "guimodule/CUIManager.h"
#include "guimodule/C_UIMap.h"

// The full BehaviorTree node catalog (481 nodes) aggregated via one header:
#include "xgenaimodule/BehaviorTree/BTNodes.h"

// ---- databasemodule: intentionally EXCLUDED (redefinition conflicts + 300+ table rows) ----
