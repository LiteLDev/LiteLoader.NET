#pragma once
#include <mc/CommandSelector.hpp>
#include <mc/CommandMessage.hpp>
#include <src/Header/MC/Types.hpp>

namespace MC {
    ref class CommandOrigin;
}

namespace MC 
{
    public ref class CommandMessage
        :ClassTemplate<CommandMessage, ::CommandMessage> 
    {
    public:
        __ctor(CommandMessage, ::CommandMessage);
    public:
        CommandMessage();

        CommandMessage^ Create();

        String^ GetMessage(CommandOrigin^ origin);
    };
}
