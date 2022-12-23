#include <LiteLoader.NET/Header/Event/OtherEvents.hpp>

void InitOtherEvents()
{
    using namespace LiteLoader::Event;
#define REGISTER_NATIVE_EVENT(_event) EventManager::_registerNativeEvent<_event^>(_event::EventId)

    REGISTER_NATIVE_EVENT(PostInitEvent);
    REGISTER_NATIVE_EVENT(ServerStartedEvent);
    REGISTER_NATIVE_EVENT(ServerStoppedEvent);
    REGISTER_NATIVE_EVENT(ConsoleCmdEvent);
    REGISTER_NATIVE_EVENT(RegCmdEvent);
    REGISTER_NATIVE_EVENT(ConsoleOutputEvent);
    REGISTER_NATIVE_EVENT(PlayerBedEnterEvent);
    REGISTER_NATIVE_EVENT(ScriptPluginManagerEvent);
    REGISTER_NATIVE_EVENT(MobSpawnEvent);
    REGISTER_NATIVE_EVENT(FormResponsePacketEvent);
}