// Precompiled header for KCD RE project.
// AUTO-REGENERATED: includes ALL RE'd module headers. Excludes: CryEngine SDK bulk,
// databasemodule (I_DatabaseListener/I_DatabaseModule redefinition conflicts + 300+
// table-row headers — include individually), and the BehaviorTree/bt/ node catalog
// (aggregated via BTNodes.h).
#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <functional>
#include <string>

#include "CryEngine/CryCommon/BaseTypes.h"
#include "CryEngine/CryCommon/CryExtension/CryGUID.h"

#include "framework/WUID.h"
namespace std {
template<> struct hash<wh::framework::WUID> {
    size_t operator()(const wh::framework::WUID& w) const noexcept { return (size_t)w.value; }
};
}  // namespace std

namespace wh::guimodule {
struct CStrLess {
    bool operator()(const char* a, const char* b) const { return std::strcmp(a, b) < 0; }
};
}  // namespace wh::guimodule
// ---- framework (23) ----
#include "framework/C_Action.h"
#include "framework/C_BaseModule.h"
#include "framework/C_CryLoadGameHelper.h"
#include "framework/C_CrySaveGameHelper.h"
#include "framework/C_HashMap.h"
#include "framework/C_ModuleMessage.h"
#include "framework/C_ParamAction.h"
#include "framework/C_PlayerProfileWHManager.h"
#include "framework/C_ReadinessObserver.h"
#include "framework/C_SaveGameManager.h"
#include "framework/C_ScriptBindFramework.h"
#include "framework/C_ScriptBindTrace.h"
#include "framework/C_ScriptBindVariables.h"
#include "framework/C_Signal.h"
#include "framework/CryDeferrable.h"
#include "framework/I_Action.h"
#include "framework/I_ActionImpl.h"
#include "framework/I_ReadinessDebuggable.h"
#include "framework/I_ReadinessTask.h"
#include "framework/I_WUIDMappingProvider.h"
#include "framework/InplaceVector.h"
#include "framework/S_TypeFactoryEntry.h"
#include "framework/WUID.h"

// ---- Offsets (23) ----
#include "Offsets/Offsets.h"
#include "Offsets/Offsets_VTABLE.h"
#include "Offsets/vtables/I_LocationListener.h"
#include "Offsets/vtables/IActionListener.h"
#include "Offsets/vtables/IActor.h"
#include "Offsets/vtables/IActorSystem.h"
#include "Offsets/vtables/IConsole.h"
#include "Offsets/vtables/IEntity.h"
#include "Offsets/vtables/IEntityEventListener.h"
#include "Offsets/vtables/IEntitySystem.h"
#include "Offsets/vtables/IEntitySystemSink.h"
#include "Offsets/vtables/IGameFramework.h"
#include "Offsets/vtables/IGameFrameworkListener.h"
#include "Offsets/vtables/IGameObject.h"
#include "Offsets/vtables/IGameObjectProfileManager.h"
#include "Offsets/vtables/IGameObjectView.h"
#include "Offsets/vtables/ILog.h"
#include "Offsets/vtables/IScriptSystem.h"
#include "Offsets/vtables/IScriptTable.h"
#include "Offsets/vtables/ISystemEventListener.h"
#include "Offsets/vtables/IUIElementEventListener.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/VCall.h"

// ---- crysystem (5) ----
#include "crysystem/CLog.h"
#include "crysystem/CScriptableBase.h"
#include "crysystem/CScriptSystem.h"
#include "crysystem/CXConsole.h"
#include "crysystem/SSystemGlobalEnvironment.h"

// ---- guimodule (8) ----
#include "guimodule/C_CompassMark.h"
#include "guimodule/C_ScriptBindMap.h"
#include "guimodule/C_UIMap.h"
#include "guimodule/C_UIMapCloudAtlas.h"
#include "guimodule/CUIManager.h"
#include "guimodule/SSpatialBucketContainer.h"
#include "guimodule/SUIEventReceiverDispatcher.h"
#include "guimodule/SUIEventSenderBlock.h"

// ---- game (2) ----
#include "game/CScriptBindGame.h"
#include "game/S_GameContext.h"

// ---- animationmodule (2) ----
#include "animationmodule/C_AnimationDatabase.h"
#include "animationmodule/I_SceneListener.h"

// ---- entitymodule (29) ----
#include "entitymodule/C_Actor.h"
#include "entitymodule/C_ArmorRuntimeData.h"
#include "entitymodule/C_ConsumableRuntimeData.h"
#include "entitymodule/C_EquipmentManager.h"
#include "entitymodule/C_EquippableItemRuntimeData.h"
#include "entitymodule/C_Human.h"
#include "entitymodule/C_Inventory.h"
#include "entitymodule/C_Item.h"
#include "entitymodule/C_ItemRuntimeData.h"
#include "entitymodule/C_Player.h"
#include "entitymodule/C_ScriptBindActor.h"
#include "entitymodule/C_ScriptBindEntityModule.h"
#include "entitymodule/C_ScriptBindGameRules.h"
#include "entitymodule/C_ScriptBindHorse.h"
#include "entitymodule/C_ScriptBindHuman.h"
#include "entitymodule/C_ScriptBindInteractiveObject.h"
#include "entitymodule/C_ScriptBindInventory.h"
#include "entitymodule/C_ScriptBindItemManager.h"
#include "entitymodule/C_ScriptBindPickableItem.h"
#include "entitymodule/C_ScriptBindPlayer.h"
#include "entitymodule/C_WeaponRuntimeData.h"
#include "entitymodule/CScriptBindBoids.h"
#include "entitymodule/I_EquipmentManagerListener.h"
#include "entitymodule/I_ExactPosHelperListener.h"
#include "entitymodule/I_InventoryListener.h"
#include "entitymodule/I_ItemAttachmentListener.h"
#include "entitymodule/I_ItemRuntimeData.h"
#include "entitymodule/S_ItemData.h"
#include "entitymodule/S_ItemRuntimeDataTable.h"

// ---- rpgmodule (41) ----
#include "rpgmodule/buff/C_BuffFactory.h"
#include "rpgmodule/buff/C_BuffInitParamsDefault.h"
#include "rpgmodule/buff/C_BuffInstanceBase.h"
#include "rpgmodule/buff/C_BuffManager.h"
#include "rpgmodule/buff/C_ConstantSoulBuffInstance.h"
#include "rpgmodule/buff/C_InjuredBuffInitParams.h"
#include "rpgmodule/buff/C_ItemHealthCheckingBuffInitParams.h"
#include "rpgmodule/buff/C_MoraleContextBuffInitParams.h"
#include "rpgmodule/buff/C_SleepBuffInitParams.h"
#include "rpgmodule/buff/C_SoulBuffInstance.h"
#include "rpgmodule/buff/C_TimedSoulBuffInstance.h"
#include "rpgmodule/buff/E_BuffStat.h"
#include "rpgmodule/buff/E_ModifierOp.h"
#include "rpgmodule/buff/I_BuffInitParams.h"
#include "rpgmodule/buff/S_ModifierNode.h"
#include "rpgmodule/C_Effect.h"
#include "rpgmodule/C_FactionManager.h"
#include "rpgmodule/C_FactionScriptBind.h"
#include "rpgmodule/C_LocationScriptBind.h"
#include "rpgmodule/C_PerkList.h"
#include "rpgmodule/C_POI.h"
#include "rpgmodule/C_RPGModule.h"
#include "rpgmodule/C_ScriptbindBarber.h"
#include "rpgmodule/C_ScriptBindCalendar.h"
#include "rpgmodule/C_ScriptBindRPGModule.h"
#include "rpgmodule/C_ScriptBindSoul.h"
#include "rpgmodule/C_ScriptBindStatistics.h"
#include "rpgmodule/C_Soul.h"
#include "rpgmodule/C_SoulList.h"
#include "rpgmodule/C_SoulPropertyNotifier.h"
#include "rpgmodule/E_DerivedStat.h"
#include "rpgmodule/I_CombatSoul.h"
#include "rpgmodule/I_POI.h"
#include "rpgmodule/I_Soul.h"
#include "rpgmodule/I_SoulResolver.h"
#include "rpgmodule/S_PerkDefinition.h"
#include "rpgmodule/S_PerkManagement.h"
#include "rpgmodule/S_PerkPointCounters.h"
#include "rpgmodule/S_PerkSubsystem.h"
#include "rpgmodule/S_RpgParams.h"
#include "rpgmodule/S_SoulArchetype.h"

// ---- combatmodule (64) ----
#include "combatmodule/C_CombatActionFactory.h"
#include "combatmodule/C_CombatActionHelper.h"
#include "combatmodule/C_CombatActor.h"
#include "combatmodule/C_CombatActorActionAttack.h"
#include "combatmodule/C_CombatActorActionBlock.h"
#include "combatmodule/C_CombatActorActionBlockTrigger.h"
#include "combatmodule/C_CombatActorActionComposedRipostePerfectBlock.h"
#include "combatmodule/C_CombatActorActionFreeBlock.h"
#include "combatmodule/C_CombatActorActionGuard.h"
#include "combatmodule/C_CombatActorActionGuardMovement.h"
#include "combatmodule/C_CombatActorActionGuardSyncMovement.h"
#include "combatmodule/C_CombatActorActionHit.h"
#include "combatmodule/C_CombatActorActionManager.h"
#include "combatmodule/C_CombatActorActionPerfectBlock.h"
#include "combatmodule/C_CombatActorActionPoseModifier.h"
#include "combatmodule/C_CombatActorActionRiderMovement.h"
#include "combatmodule/C_CombatActorActionStaticAttack.h"
#include "combatmodule/C_CombatActorActionSyncAttack.h"
#include "combatmodule/C_CombatActorActionSyncHit.h"
#include "combatmodule/C_CombatActorActionSyncPerfectBlock.h"
#include "combatmodule/C_CombatActorActionSyncPerfectBlockHit.h"
#include "combatmodule/C_CombatActorActionSyncTransition.h"
#include "combatmodule/C_CombatActorActionT.h"
#include "combatmodule/C_CombatActorHorsePullDown.h"
#include "combatmodule/C_CombatActorHuntAttack.h"
#include "combatmodule/C_CombatActorObject.h"
#include "combatmodule/C_CombatActorUpdatedObject.h"
#include "combatmodule/C_CombatComboData.h"
#include "combatmodule/C_CombatComboManager.h"
#include "combatmodule/C_CombatDatabase.h"
#include "combatmodule/C_CombatModule.h"
#include "combatmodule/C_CombatScene.h"
#include "combatmodule/C_CombatSlotTrigger.h"
#include "combatmodule/C_CombatTrigger.h"
#include "combatmodule/C_CombatTriggerCombo.h"
#include "combatmodule/C_CombatTriggerPerfectBlock.h"
#include "combatmodule/C_CombatTriggerRiposte.h"
#include "combatmodule/C_CombatTriggerSyncDodge.h"
#include "combatmodule/C_CombatTriggerSyncPerfectBlock.h"
#include "combatmodule/C_CombatTriggerSyncRiposte.h"
#include "combatmodule/I_CombatActionHelperOwner.h"
#include "combatmodule/I_CombatActor.h"
#include "combatmodule/I_CombatActorAction.h"
#include "combatmodule/I_CombatActorActionBlock.h"
#include "combatmodule/I_CombatActorActionParamsReflect.h"
#include "combatmodule/I_CombatTarget.h"
#include "combatmodule/S_CombatActorActionAttackParams.h"
#include "combatmodule/S_CombatActorActionBlockParams.h"
#include "combatmodule/S_CombatActorActionBlockTriggerParams.h"
#include "combatmodule/S_CombatActorActionComposedRipostePerfectBlockParams.h"
#include "combatmodule/S_CombatActorActionFreeBlockParams.h"
#include "combatmodule/S_CombatActorActionGuardMovementParams.h"
#include "combatmodule/S_CombatActorActionGuardParams.h"
#include "combatmodule/S_CombatActorActionGuardSyncMovementParams.h"
#include "combatmodule/S_CombatActorActionHitParams.h"
#include "combatmodule/S_CombatActorActionPerfectBlockParams.h"
#include "combatmodule/S_CombatActorActionPoseModifierParams.h"
#include "combatmodule/S_CombatActorActionStaticAttackParams.h"
#include "combatmodule/S_CombatActorActionSyncAttackParams.h"
#include "combatmodule/S_CombatActorActionSyncHitParams.h"
#include "combatmodule/S_CombatActorActionSyncPerfectBlockHitParams.h"
#include "combatmodule/S_CombatActorActionSyncTransitionParams.h"
#include "combatmodule/S_CombatActorState.h"
#include "combatmodule/S_CombatSettings.h"

// ---- playermodule (10) ----
#include "playermodule/C_FastTravel.h"
#include "playermodule/C_FastTravelScriptBind.h"
#include "playermodule/C_PlayerModule.h"
#include "playermodule/C_ScriptBind_Alchemy.h"
#include "playermodule/C_ScriptBind_Dice.h"
#include "playermodule/C_ScriptBind_Sharpening.h"
#include "playermodule/C_ScriptBindBackgammon.h"
#include "playermodule/C_ScriptBindMinigame.h"
#include "playermodule/C_ScriptBindTutorial.h"
#include "playermodule/I_RandomEventListener.h"

// ---- dialogmodule (1) ----
#include "dialogmodule/C_ScriptBindDialog.h"

// ---- environmentmodule (1) ----
#include "environmentmodule/C_ScriptBindEnvironment.h"

// ---- questmodule (1) ----
#include "questmodule/C_ScriptBindQuest.h"

// ---- shopmodule (1) ----
#include "shopmodule/C_ScriptBindShop.h"

// ---- xgenaimodule (16) ----
#include "xgenaimodule/BehaviorTree/BTNodes.h"
#include "xgenaimodule/BehaviorTree/C_Barrier.h"
#include "xgenaimodule/BehaviorTree/C_Composite.h"
#include "xgenaimodule/BehaviorTree/C_Composites.h"
#include "xgenaimodule/BehaviorTree/C_Decorator.h"
#include "xgenaimodule/BehaviorTree/C_Gate.h"
#include "xgenaimodule/BehaviorTree/C_Node.h"
#include "xgenaimodule/BehaviorTree/C_NodeContext.h"
#include "xgenaimodule/BehaviorTree/C_NodeFactory.h"
#include "xgenaimodule/BehaviorTree/C_NodeWrapper.h"
#include "xgenaimodule/BehaviorTree/I_DebugNode.h"
#include "xgenaimodule/BehaviorTree/I_Node.h"
#include "xgenaimodule/BehaviorTree/NodeAttribute.h"
#include "xgenaimodule/C_ScriptBindSmartObject.h"
#include "xgenaimodule/C_ScriptBindXGenAIModule.h"
#include "xgenaimodule/I_NoRTTITypeInfo.h"

// ---- databasemodule: intentionally EXCLUDED (redefinition conflicts + 300+ table rows) ----
