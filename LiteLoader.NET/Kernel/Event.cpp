#include "../Header/Event/Event.hpp"
#include "../Header/Event/EffectiveEvent/EventManager.hpp"
#include "../Header/Event/EffectiveEvent/LLNETEvents.hpp"

void InitEvents()
{
	LLNET::Event::Effective::EventManager::_initEvents();
}

inline void LLNET::Event::Effective::EventManager::_initEvents()
{
#define REGISTER_NATIVE_EVENT(_event) _registerEventInternal<LLNET::Event::Effective::NativeEvents::_event>(LLNET::Event::Effective::NativeEvents::_event::EventId)

	REGISTER_NATIVE_EVENT(PlayerPreJoinEvent);
	REGISTER_NATIVE_EVENT(PlayerJoinEvent);
	REGISTER_NATIVE_EVENT(PlayerLeftEvent);
	REGISTER_NATIVE_EVENT(PlayerRespawnEvent);
	REGISTER_NATIVE_EVENT(PlayerChatEvent);
	REGISTER_NATIVE_EVENT(PlayerUseItemEvent);
	REGISTER_NATIVE_EVENT(PlayerUseItemOnEvent);
	REGISTER_NATIVE_EVENT(PlayerChangeDimEvent);
	REGISTER_NATIVE_EVENT(PlayerJumpEvent);
	REGISTER_NATIVE_EVENT(EntityTransformEvent);
	REGISTER_NATIVE_EVENT(PlayerSneakEvent);
	REGISTER_NATIVE_EVENT(PlayerAttackEvent);
	REGISTER_NATIVE_EVENT(PlayerAttackBlockEvent);
	REGISTER_NATIVE_EVENT(PlayerDieEvent);
	REGISTER_NATIVE_EVENT(PlayerPickupItemEvent);
	REGISTER_NATIVE_EVENT(PlayerDropItemEvent);
	REGISTER_NATIVE_EVENT(PlayerEatEvent);
	REGISTER_NATIVE_EVENT(PlayerConsumeTotemEvent);
	REGISTER_NATIVE_EVENT(PlayerCmdEvent);
	REGISTER_NATIVE_EVENT(PlayerDestroyBlockEvent);
	REGISTER_NATIVE_EVENT(PlayerPlaceBlockEvent);
	REGISTER_NATIVE_EVENT(PlayerEffectChangedEvent);
	REGISTER_NATIVE_EVENT(PlayerStartDestroyBlockEvent);
	REGISTER_NATIVE_EVENT(PlayerOpenContainerEvent);
	REGISTER_NATIVE_EVENT(PlayerCloseContainerEvent);
	REGISTER_NATIVE_EVENT(PlayerInventoryChangeEvent);
	REGISTER_NATIVE_EVENT(PlayerMoveEvent);
	REGISTER_NATIVE_EVENT(PlayerSprintEvent);
	REGISTER_NATIVE_EVENT(PlayerSetArmorEvent);
	REGISTER_NATIVE_EVENT(PlayerUseRespawnAnchorEvent);
	REGISTER_NATIVE_EVENT(PlayerOpenContainerScreenEvent);
	REGISTER_NATIVE_EVENT(PlayerUseFrameBlockEvent);
	REGISTER_NATIVE_EVENT(PlayerExperienceAddEvent);
	REGISTER_NATIVE_EVENT(MobHurtEvent);
	REGISTER_NATIVE_EVENT(MobDieEvent);
	REGISTER_NATIVE_EVENT(EntityExplodeEvent);
	REGISTER_NATIVE_EVENT(ProjectileHitEntityEvent);
	REGISTER_NATIVE_EVENT(WitherBossDestroyEvent);
	REGISTER_NATIVE_EVENT(EntityRideEvent);
	REGISTER_NATIVE_EVENT(EntityStepOnPressurePlateEvent);
	REGISTER_NATIVE_EVENT(NpcCmdEvent);
	REGISTER_NATIVE_EVENT(ProjectileSpawnEvent);
	REGISTER_NATIVE_EVENT(ProjectileCreatedEvent);
	REGISTER_NATIVE_EVENT(ItemUseOnActorEvent);
	REGISTER_NATIVE_EVENT(BlockInteractedEvent);
	REGISTER_NATIVE_EVENT(ArmorStandChangeEvent);
	REGISTER_NATIVE_EVENT(BlockExplodeEvent);
	REGISTER_NATIVE_EVENT(ContainerChangeEvent);
	REGISTER_NATIVE_EVENT(PistonPushEvent);
	REGISTER_NATIVE_EVENT(PistonTryPushEvent);
	REGISTER_NATIVE_EVENT(RedStoneUpdateEvent);
	REGISTER_NATIVE_EVENT(BlockExplodedEvent);
	REGISTER_NATIVE_EVENT(LiquidSpreadEvent);
	REGISTER_NATIVE_EVENT(ProjectileHitBlockEvent);
	REGISTER_NATIVE_EVENT(HopperSearchItemEvent);
	REGISTER_NATIVE_EVENT(HopperPushOutEvent);
	REGISTER_NATIVE_EVENT(BlockChangedEvent);
	REGISTER_NATIVE_EVENT(FarmLandDecayEvent);
	REGISTER_NATIVE_EVENT(FireSpreadEvent);
	REGISTER_NATIVE_EVENT(CmdBlockExecuteEvent);
	REGISTER_NATIVE_EVENT(ConsoleCmdEvent);
	REGISTER_NATIVE_EVENT(PlayerScoreChangedEvent);
	REGISTER_NATIVE_EVENT(ConsoleOutputEvent);
	REGISTER_NATIVE_EVENT(PostInitEvent);
	REGISTER_NATIVE_EVENT(ServerStartedEvent);
	REGISTER_NATIVE_EVENT(ServerStoppedEvent);
	REGISTER_NATIVE_EVENT(RegCmdEvent);
	REGISTER_NATIVE_EVENT(PlayerBedEnterEvent);
	REGISTER_NATIVE_EVENT(ScriptPluginManagerEvent);
	REGISTER_NATIVE_EVENT(MobSpawnEvent);
}

#define CallEventAPI_Imp(_event,...) void _event::CallEvent(__VA_ARGS__)

namespace LLNET::Event::Effective::NativeEvents
{
}