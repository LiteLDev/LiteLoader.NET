#include <src/Header/Event/BlockEvents.hpp>

void InitBlockEvents()
{
    using namespace LiteLoader::Event;
#define REGISTER_NATIVE_EVENT(_event) EventManager::_registerNativeEvent<_event^>(_event::EventId)

    REGISTER_NATIVE_EVENT(BlockInteractedEvent);
    REGISTER_NATIVE_EVENT(BlockChangedEvent);
    REGISTER_NATIVE_EVENT(BlockExplodedEvent);
    REGISTER_NATIVE_EVENT(FireSpreadEvent);
    REGISTER_NATIVE_EVENT(ContainerChangeEvent);
    REGISTER_NATIVE_EVENT(ProjectileHitBlockEvent);
    REGISTER_NATIVE_EVENT(RedStoneUpdateEvent);
    REGISTER_NATIVE_EVENT(HopperSearchItemEvent);
    REGISTER_NATIVE_EVENT(HopperPushOutEvent);
    REGISTER_NATIVE_EVENT(PistonTryPushEvent);
    REGISTER_NATIVE_EVENT(PistonPushEvent);
    REGISTER_NATIVE_EVENT(FarmLandDecayEvent);
    REGISTER_NATIVE_EVENT(LiquidSpreadEvent);
    REGISTER_NATIVE_EVENT(CmdBlockExecuteEvent);
    REGISTER_NATIVE_EVENT(BlockExplodeEvent);
}