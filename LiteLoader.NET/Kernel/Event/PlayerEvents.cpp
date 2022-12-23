#include <LiteLoader.NET/Header/Event/PlayerEvents.hpp>

void InitPlayerEvents()
{
    using namespace LiteLoader::Event;
#define REGISTER_NATIVE_EVENT(_event) EventManager::_registerNativeEvent<_event^>(_event::EventId)

    REGISTER_NATIVE_EVENT(PlayerPreJoinEvent);
    REGISTER_NATIVE_EVENT(PlayerJoinEvent);
    REGISTER_NATIVE_EVENT(PlayerLeftEvent);
    REGISTER_NATIVE_EVENT(PlayerRespawnEvent);
    REGISTER_NATIVE_EVENT(PlayerChatEvent);
    REGISTER_NATIVE_EVENT(PlayerUseItemEvent);
    REGISTER_NATIVE_EVENT(PlayerUseItemOnEvent);
    REGISTER_NATIVE_EVENT(PlayerChangeDimEvent);
    REGISTER_NATIVE_EVENT(PlayerJumpEvent);
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
    REGISTER_NATIVE_EVENT(PlayerSprintEvent);
    REGISTER_NATIVE_EVENT(PlayerSetArmorEvent);
    REGISTER_NATIVE_EVENT(PlayerUseRespawnAnchorEvent);
    REGISTER_NATIVE_EVENT(PlayerOpenContainerScreenEvent);
    REGISTER_NATIVE_EVENT(PlayerUseFrameBlockEvent);
    REGISTER_NATIVE_EVENT(PlayerExperienceAddEvent);
    REGISTER_NATIVE_EVENT(PlayerInteractEntityEvent);
}