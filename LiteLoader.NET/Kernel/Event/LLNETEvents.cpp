#include "../../Header/Event/EffectiveEvent/EventManager.hpp"
#include "../../Header/Event/EffectiveEvent/LLNETEvents.hpp"

void InitEvents()
{
    using namespace LLNET::Event::Effective;

#define REGISTER_NATIVE_EVENT(_event) EventManager::_registerNativeEvent<_event>(_event::EventId)

    REGISTER_NATIVE_EVENT(NativeEvents::PlayerPreJoinEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerJoinEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerLeftEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerRespawnEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerChatEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerUseItemEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerUseItemOnEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerChangeDimEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerJumpEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerSneakEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerAttackEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerAttackBlockEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerDieEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerPickupItemEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerDropItemEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerEatEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerConsumeTotemEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerCmdEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerDestroyBlockEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerPlaceBlockEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerEffectChangedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerStartDestroyBlockEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerOpenContainerEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerCloseContainerEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerInventoryChangeEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerMoveEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerSprintEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerSetArmorEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerUseRespawnAnchorEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerOpenContainerScreenEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerUseFrameBlockEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerExperienceAddEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::MobHurtEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::MobDieEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::EntityExplodeEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ProjectileHitEntityEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::WitherBossDestroyEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::EntityRideEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::EntityStepOnPressurePlateEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::NpcCmdEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ProjectileSpawnEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ProjectileCreatedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ItemUseOnActorEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::BlockInteractedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ArmorStandChangeEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::BlockExplodeEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::EntityTransformEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ContainerChangeEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PistonPushEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PistonTryPushEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::RedStoneUpdateEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::BlockExplodedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::LiquidSpreadEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ProjectileHitBlockEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::HopperSearchItemEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::HopperPushOutEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::BlockChangedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::FarmLandDecayEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::FireSpreadEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::CmdBlockExecuteEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ConsoleCmdEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerScoreChangedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ConsoleOutputEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PostInitEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ServerStartedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ServerStoppedEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::RegCmdEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::PlayerBedEnterEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::ScriptPluginManagerEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::MobSpawnEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::BlockPlacedByPlayerEvent);
    REGISTER_NATIVE_EVENT(NativeEvents::FormResponsePacketEvent);
}

#define CallEventAPI_Imp(_event,...) void _event::CallEvent(__VA_ARGS__)

namespace LLNET::Event::Effective::NativeEvents
{
}
