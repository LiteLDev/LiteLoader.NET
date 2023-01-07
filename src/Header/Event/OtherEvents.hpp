#pragma once
#include "Event.hpp"

namespace LiteLoader::Event
{
    ///////////////////////////// Other Events /////////////////////////////

    Class PostInitEvent
        : public EventTemplate<PostInitEvent, ::Event::PostInitEvent>
    {
        EventAPIs(PostInitEvent, 63)
    };

    Class ServerStartedEvent
        : public EventTemplate<ServerStartedEvent, ::Event::ServerStartedEvent>
    {
        EventAPIs(ServerStartedEvent, 64)
    };

    Class ServerStoppedEvent
        : public EventTemplate<ServerStoppedEvent, ::Event::ServerStoppedEvent>
    {
        EventAPIs(ServerStoppedEvent, 65)
    };

    Class ConsoleCmdEvent
        : public EventTemplate<ConsoleCmdEvent, ::Event::ConsoleCmdEvent>
    {
        EventAPIs(ConsoleCmdEvent, 66);

    public:
        Property_String(mCommand, Command);
    };

    Class RegCmdEvent
        : public EventTemplate<RegCmdEvent, ::Event::RegCmdEvent>
    {
        EventAPIs(RegCmdEvent, 67);

    public:
        Property_Ptr(MC, CommandRegistry, mCommandRegistry, CommandRegistry);
    };

    Class ConsoleOutputEvent
        : public EventTemplate<ConsoleOutputEvent, ::Event::ConsoleOutputEvent>
    {
        EventAPIs(ConsoleOutputEvent, 68);

    public:
        Property_String(mOutput, Output);
    };

    Class PlayerBedEnterEvent
        : public EventTemplate<PlayerBedEnterEvent, ::Event::PlayerBedEnterEvent>
    {
        EventAPIs(PlayerBedEnterEvent, 69);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class ScriptPluginManagerEvent
        : public EventTemplate<ScriptPluginManagerEvent, ::Event::ScriptPluginManagerEvent>
    {
        EventAPIs(ScriptPluginManagerEvent, 70);

    public:
        enum class OperationEnum
        {
            Load,
            Unload,
            Reload
        };

        Property_Enum(OperationEnum, ::Event::ScriptPluginManagerEvent::Operation, operation, Operation);
        Property_String(target, Target);
        Property_String(otherInfo, OtherInfo);
        // Property_String(pluginExtention, PluginExtention);
        Property(bool, success, Success);
    };

    Class MobSpawnEvent
        : public EventTemplate<MobSpawnEvent, ::Event::MobSpawnEvent>
    {
        EventAPIs(MobSpawnEvent, 71);

    public:
        Property_String(mTypeName, TypeName);
        Property_ValueType(MC, Vec3, mPos, Pos);
        Property(int, mDimensionId, DimensionId);
    };

    Class FormResponsePacketEvent
        : public EventTemplate<FormResponsePacketEvent, ::Event::FormResponsePacketEvent>
    {
        EventAPIs(FormResponsePacketEvent, 72);

    public:
        Property_Ptr(MC, ServerPlayer, mServerPlayer, Player);
        Property(unsigned, mFormId, FormId);
        Property_String(mJsonData, JsonData);
    };
}