#pragma once
#include <mc/CommandOutputMessage.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>
namespace MC
{
public
ref class CommandOutputMessage : ClassTemplate<CommandOutputMessage, ::CommandOutputMessage>
{
public:
    __ctor_all(CommandOutputMessage, ::CommandOutputMessage);

    inline static CommandOutputMessage ^ Create(CommandOutputMessage ^ cm);
    inline static CommandOutputMessage ^ Create(int _EnumCommandOutputMessageType, String^ a0, List<String^> ^ a1);
    inline String^ GetMessageId();
    inline List<String^> ^ GetParams();
    inline int GetType();
};
} // namespace MC
